//
// Created by jinlai song on 2021/2/10.
//

#ifndef REDBASE_HASH_TABLE_H
#define REDBASE_HASH_TABLE_H

#include "hash_table_rc.h"
#include "hash_table_node.h"
#include <memory>
#include <vector>
#include <list>

using namespace std;

class HashTable {
public:
    const static int kHashTableInitCapacity = 20;
private:
    inline static int CalHash(int fd, int page_idx);

private:
    vector<unique_ptr<list<unique_ptr<HashTableNode>>>> hash_map_;
public:
    HashTable() {
        hash_map_ = vector<unique_ptr<list<unique_ptr<HashTableNode>>>>(kHashTableInitCapacity);
    }

public:
    HashTableRC SearchSlot(int fd, int page_idx, int *slot);

    HashTableRC InsertNode(const HashTableNode *node);

    HashTableRC DeleteNode(int fd, int page_idx);

    HashTableRC SearchSlots(int fd, int page_idx, vector<int>* slots);
};

#endif //REDBASE_HASH_TABLE_H
