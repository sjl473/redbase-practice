//
// Created by jinlai song on 2021/3/1.
//

#include "buffer.h"


BufferRC Buffer::ReadFromDisk(int fd, int page_idx, char *dst) {
    int offset = (page_idx + 1) * BufferNode::kPageSize;
    // which means an offset is equal to ( pageNumber + 1 ) * 4k, include a
    // header's size
    if (lseek(fd, offset, SEEK_SET) < 0) {
        return BufferRC::READ_FROM_DISK_ERR;
    }
    long rc = read(fd, dst, static_cast<size_t>(BufferNode::kPageSize));
    if (rc != BufferNode::kPageSize) {
        return BufferRC::READ_FROM_DISK_ERR;
    }
    return BufferRC::BUFFER_OK;
}

BufferRC Buffer::WriteToDisk(int fd, int page_idx, const char *src) {
    int offset = (page_idx + 1) * BufferNode::kPageSize;
    if (lseek(fd, offset, SEEK_SET) < 0) {
        return BufferRC::WRITE_TO_DISK_ERR;
    }
    long rc = write(fd, src, static_cast<size_t>(BufferNode::kPageSize));
    if (rc != BufferNode::kPageSize) {
        return BufferRC::WRITE_TO_DISK_ERR;
    }
    return BUFFER_OK;
}

BufferRC Buffer::GetPage(int fd, int page_idx, char **dst) {
    int founded_slot;
    BufferRC rc = this->PinPage(fd, page_idx, &founded_slot);
    if (rc == BufferRC::NO_AVAILABLE_NODE || rc == BufferRC::BUFFER_OK) {
        *dst = this->nodes_[founded_slot]->storage();
        return BufferRC::BUFFER_OK;
    }
    return BufferRC::FAILED_TO_GET_PAGE;
}

BufferRC Buffer::PinPage(int fd, int page_idx, int *found_slot) {

    HashTableRC rc = this->hashTable_.SearchSlot(fd, page_idx, found_slot);
    if (rc == HashTableRC::HASH_TABLE_RC_OK) {
        this->nodes_[*found_slot]->increase_counter();
        // increase pin count
        return BufferRC::BUFFER_OK;
    }
    if (rc == HashTableRC::SLOT_NOT_FOUND) {
        // evicted a page which count is zero (pin count is zero)
        int free_slot;
        int free_fd;
        int free_page_idx;
        int x = 0;
        for (auto &i : this->nodes_) {
            if (i->counter() == 0) {
                free_fd = i->fd();
                free_page_idx = i->page_idx();
                break;
            }
            ++x;
        }
        if (x == this->nodes_.size() - 1) {
            return BufferRC::NO_AVAILABLE_NODE;
        }
        // after the evicting, replace position at this slot a new page in hard disk
        free_slot = x;
        if (HashTableRC::NEGATIVE_KEY == this->hashTable_.DeleteNode(free_fd, free_page_idx)) {
            return BufferRC::UPDATE_HASH_TABLE_ERR;
        }
        if (HashTableRC::REDUNDANT_KEY ==
            this->hashTable_.InsertNode(const_cast<HashTableNode *>(new HashTableNode(fd, page_idx, free_slot)))) {
            return BufferRC::UPDATE_HASH_TABLE_ERR;
        }
        if (ReadFromDisk(free_fd, free_page_idx, this->nodes_[free_slot]->storage()) < 0) {
            return BufferRC::READ_FROM_DISK_ERR;
        }
        this->nodes_[free_slot]->set_fd(fd);
        this->nodes_[free_slot]->set_page_idx(page_idx);
        this->nodes_[free_slot]->set_counter(1);
        this->nodes_[free_slot]->set_dirty(false);
        return BufferRC::BUFFER_OK;
    }
    // no return, all cases are involved
}

BufferRC Buffer::Force(int fd, int page_idx, char *dst) {

    int founded_slot;
    HashTableRC rc = this->hashTable_.SearchSlot(fd, page_idx, &founded_slot);
    if (rc == HashTableRC::HASH_TABLE_RC_OK) {
        if (WriteToDisk(fd, page_idx, const_cast<const char *>(this->nodes_[founded_slot]->storage())) ==
            BufferRC::WRITE_TO_DISK_ERR) {
            return BufferRC::FAIL_TO_FORCE_PAGE;
        }
        this->nodes_[founded_slot]->modify_dirty();
        return BUFFER_OK;
    }
    return BufferRC::FAIL_TO_FORCE_PAGE;
}

