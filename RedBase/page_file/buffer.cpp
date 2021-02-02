#include "buffer.h"
#include "hash_table_node.h"
#include "page_header.h"
#include <unistd.h>

// todo : modify those unix api into c++ standard lib stuffs
int Buffer::GetPage(int fd, int page_idx, char **dst) {
    int slot = (*hash_table_).SearchSlot(fd, page_idx);
    if (PinPage(fd, page_idx) < 0) {
        return -1;
    }
    *dst = (*nodes_)[slot]->storage();
    return 0;
}

int Buffer::GetAvailableNode(BufferNode *node) {
    // todo: 增加新函数 get available slot
    for (auto &i : *nodes_) {
        if (i->counter() == 0) {
            (*node).set_fd(i->fd());
            (*node).set_page_idx(i->page_idx());
            (*node).set_slot(i->slot());
            (*node).set_dirty(i->is_dirty());
            (*node).set_counter(i->counter());
            return 0;
        }
    }
    return -1;
}

int Buffer::PinPage(int fd, int page_idx) {
    int slot = (*hash_table_).SearchSlot(fd, page_idx);
    if (slot != -1) {
        (*nodes_)[slot]->increaseCounter();
    } else {
        BufferNode availableNode;
        if (GetAvailableNode(&availableNode) < 0) {
            return -1; // todo: modify this into enum
        } else {
            slot = availableNode.slot();
        }
        if (slot == -1) {
            // no available buffer node
            return -1;
        } else {
            // update (delete and insert) the hash table according to the
            // corresponding slot (idx)
            if ((*hash_table_)
                        .RemoveNode(availableNode.fd(), availableNode.page_idx()) == -1) {
                // remove hash table error
                return -1; // todo: change this to enum
            } else {
                // hash table insertion
                if ((*hash_table_)
                            .InsertNode(const_cast<HashTableNode *>(
                                                new HashTableNode(fd, page_idx, slot))) < 0) {
                    // insertion err
                    return -1;
                }
                if (ReadFromDisk(fd, page_idx, (*nodes_)[slot]->storage()) < 0) {
                    // read data from at id && page index's position to the slot's
                    // node in buffer's storage
                    return -1; // todo : add enum
                } else {
                    // read success, update the extra information of this node
                    (*nodes_)[slot]->set_fd(fd);
                    (*nodes_)[slot]->set_page_idx(slot);
                    (*nodes_)[slot]->set_dirty(false);
                    (*nodes_)[slot]->increaseCounter();
                }
            }
        }
    }
}

int Buffer::EvictPageIfDirty(int fd, int page_idx, char *dst) {
    // todo : evict page if dirty, from the buffer to disk, but don't modify the hashtable?
    for (int i = 0; i < Buffer::kMaxCapacity; i++) {
        if (fd == (*nodes_)[i]->fd() && page_idx == (*nodes_)[i]->page_idx()) {
            if ((*nodes_)[i]->is_dirty()) {
                if (WriteToDisk(fd, page_idx,
                                const_cast<char *>((*nodes_)[i]->storage())) < 0) {
                    return -1;
                }
                (*nodes_)[i]->modifyDirty();
                dst = (*nodes_)[i]->storage();
                return 0;
            }
        }
    }
    return 0;
}

int Buffer::WriteToDisk(int fd, int page_idx, const char *src) {
    int offset =
            (page_idx + 1) * test_buffer_node.kPageSize;
    if (lseek(fd, offset, SEEK_SET) < 0) {
        return -1;
    } else {
        long rc = write(fd, src, static_cast<size_t>(test_buffer_node.kPageSize));
        if (rc != test_buffer_node.kPageSize) {
            return -1;
        }
        return 0;
    }
}

int Buffer::ReadFromDisk(int fd, int page_idx, char *dst) {
    int offset =
            (page_idx + 1) * test_buffer_node.kPageSize;
    // which means an offset is equal to ( pageNumber + 1 ) * 4k, include a
    // header's size
    if (lseek(fd, offset, SEEK_SET) < 0) {
        return -1; // todo : create a enum called lseek error
    } else {
        long rc = read(
                fd, dst,
                static_cast<size_t>(test_buffer_node.kPageSize)); // read from disk
        if (rc != test_buffer_node.kPageSize) {
            return -1; // todo : create a enum called pf incomplete write
        }
        return 0;
    }
}

int Buffer::ForceAllDirtyPages(int fd) {
    // todo : evict all dirty pages from the buffer to disk but don't modify the hashtable?
    for (int i = 0; i < Buffer::kMaxCapacity; i++) {
        if (fd == (*nodes_)[i]->fd()) {
            if ((*nodes_)[i]->is_dirty()) {
                if (WriteToDisk(fd, (*nodes_)[i]->page_idx(),
                                const_cast<char *>((*nodes_)[i]->storage()))) {
                    (*nodes_)[i]->modifyDirty();
                } else {
                    return -1;
                }
            }
        }
    }
    return 0;
}

int Buffer::ClearAllDirtyPages(int fd) {
    // evict all dirty pages from the buffer to disk with modifying the hashtable
    for (int i = 0; i < Buffer::kMaxCapacity; i++) {
        if (fd == (*nodes_)[i]->fd()) {
            if ((*nodes_)[i]->is_dirty()) {
                int page_idx = (*nodes_)[i]->page_idx();
                if ((*hash_table_).RemoveNode(fd, page_idx) < 0) {
                    return -1;
                }
                if (WriteToDisk(fd, page_idx,
                                const_cast<char *>((*nodes_)[i]->storage())) < 0) {
                    return -1;
                }
                (*nodes_)[i]->set_counter(0);
                (*nodes_)[i]->set_dirty(false);
                (*nodes_)[i]->set_fd(-1);
                (*nodes_)[i]->set_page_idx(-1);
            }
        }
    }
    return 0;
}

int Buffer::UnpinPage(int fd, int page_idx) {
    int slot = (*hash_table_).SearchSlot(fd, page_idx);
    if (slot == -1) {
        return -1; // todo
    }
    (*this->nodes_)[slot]->decreaseCounter();
    if ((*nodes_)[slot]->counter() == 0) {
        if ((*nodes_)[slot]->is_dirty()) {
            if (WriteToDisk(fd, page_idx, const_cast<char *>((*nodes_)[slot]->storage())) < 0) {
                return -1; // todo :
            }
            (*nodes_)[slot]->modifyDirty();
        }
        return 0;
    }
}

int Buffer::AllocPage(int fd, int page_idx, char **evictedData) {
    int slot = hash_table_->SearchSlot(fd, page_idx);
    if (slot == -1) {
        return -1;
    }
    BufferNode availableNode;
    if (GetAvailableNode(&availableNode) < 0) {
        return -1;
    } else {
        (*nodes_)[slot]->set_page_idx(slot);
        (*nodes_)[slot]->set_fd(fd); // todo: is this necessary
        (*nodes_)[slot]->set_dirty(false);
        (*nodes_)[slot]->set_counter(0);
        // update the hashtable
        this->hash_table_->RemoveNode(fd, page_idx); // todo: 判断没加，。，。
        *evictedData = (*nodes_)[slot]->storage();
    }
    return 0;
}

int Buffer::MarkDirty(int fd, int page_idx) {
    int slot = this->hash_table_->SearchSlot(fd, page_idx);
    if (slot < 0) {
        return -1;
    }
    if ((*nodes_)[slot]->counter() == 0) {
        return -1; // 不能将一个谁也没用的页设置为脏页
    }
    (*nodes_)[slot]->set_dirty(true);
    return 0;
}


