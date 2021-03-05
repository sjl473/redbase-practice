//
// Created by jinlai song on 2021/2/10.
//

#include "hash_table.h"

int HashTable::CalHash(int fd, int page_idx) {
    return (fd + page_idx) % HashTable::kHashTableInitCapacity;
}


HashTableRC HashTable::SearchSlot(int fd, int page_idx, int *slot) {
    int key = CalHash(fd, page_idx);
    if (key >= 0) {
        auto lst = *(this->hash_map_[key]);
        decltype(lst)::const_iterator iter;
        for (iter = lst.begin(); iter != lst.end(); iter++) {
            if ((*iter)->fd() == fd && (*iter)->page_idx() == page_idx) {
                *slot = (*iter)->slot();
                return HashTableRC::HASH_TABLE_RC_OK;
            }
        }
        return HashTableRC::SLOT_NOT_FOUND;
    }
    return HashTableRC::NEGATIVE_KEY;
}

HashTableRC HashTable::InsertNode(const HashTableNode *node) {
    int fd = node->fd();
    int page_idx = node->page_idx();
    int key = CalHash(fd, page_idx);
    if (key < 0) {
        return HashTableRC::NEGATIVE_KEY;
    }
    auto lst = *(this->hash_map_[key]);
    decltype(lst)::const_iterator iter;
    for (iter = lst.begin(); iter != lst.end(); iter++) {
        if (node->fd() == (*iter)->fd() &&
            node->page_idx() == (*iter)->page_idx()) {
            return HashTableRC::REDUNDANT_KEY;
        }
    }
    lst.emplace_back(unique_ptr<HashTableNode>(const_cast<HashTableNode *>(node)));
    return HashTableRC::HASH_TABLE_RC_OK;
}

HashTableRC HashTable::DeleteNode(int fd, int page_idx) {
    int key = CalHash(fd, page_idx);
    if (key < 0) {
        return HashTableRC::NEGATIVE_KEY;
    }
    auto lst = *(this->hash_map_[key]);
    decltype(lst)::const_iterator iter;
    for (iter = lst.begin(); iter != lst.end(); iter++) {
        if (fd == (*iter)->fd() && page_idx == (*iter)->page_idx()) {
            lst.erase(iter);
        }
    }
    return HashTableRC::HASH_TABLE_RC_OK;
}




