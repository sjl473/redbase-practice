#include "hash_table.h"

int HashTable::SearchSlot(int fd, int page_idx) {
    int key = CalHash(fd, page_idx);
    if (key >= 0) {
        auto lst = *((*table_)[key]);
        decltype(lst)::const_iterator iter;
        for (iter = lst.begin(); iter != lst.end(); iter++) {
            if ((*iter)->fd() == fd && (*iter)->page_idx() == page_idx) {
                return (*iter)->slot();
            }
        }
        return -1;
    } else {
        return -1;
    }
}

int HashTable::CalHash(int fd, int page_idx) {
    return (fd + page_idx) % HashTable::kInitCapacity;
}

int HashTable::RemoveNode(int fd, int page_idx) {
    int key = CalHash(fd, page_idx);
    if (key < 0) {
        return -1;
    }
    auto lst = *((*table_))[key];
    decltype(lst)::const_iterator iter;
    int counter = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++) {
        if (fd == (*iter)->fd() && page_idx == (*iter)->page_idx()) {
            lst.erase(iter);
            return counter;
        }
        ++counter;
    }
    return counter;
}

int HashTable::InsertNode(const HashTableNode *node) {
    int key = CalHash(node->fd(), node->page_idx());
    if (key < 0) {
        return -1;
    }
    auto lst = *((*table_))[key];
    decltype(lst)::const_iterator iter;
    int counter = 0;
    for (iter = lst.begin(); iter != lst.end(); iter++) {
        if (node->fd() == (*iter)->fd() &&
            node->page_idx() == (*iter)->page_idx()) {
            return -1;
        }
        ++counter;
    }
    lst.emplace_back(const_cast<HashTableNode *>(node));
    return counter;
}