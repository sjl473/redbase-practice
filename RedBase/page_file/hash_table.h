#include "hash_table_node.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class HashTable {
public:
    const static int kInitCapacity = 20;

private:
    inline static int CalHash(int fd, int page_idx);

private:
    unique_ptr<vector<unique_ptr<list<unique_ptr<HashTableNode> > > > > table_;

public:
    int SearchSlot(int fd, int page_idx);

    int InsertNode(const HashTableNode *node);

    int RemoveNode(int fd, int page_idx);

public:
    HashTable() {
        auto *temp =
                new vector<unique_ptr<list<unique_ptr<HashTableNode>>>>(kInitCapacity);
        table_ =
                unique_ptr<vector<unique_ptr<list<unique_ptr<HashTableNode>>>>>(temp);
    }
};