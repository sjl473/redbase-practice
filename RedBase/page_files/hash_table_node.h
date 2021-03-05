//
// Created by jinlai song on 2021/2/10.
//

#ifndef REDBASE_HASH_TABLE_NODE_H
#define REDBASE_HASH_TABLE_NODE_H


class HashTableNode {
private:
    int fd_;
    int page_idx_;
    int slot_;

public:
    inline int fd() const { return fd_; }

    inline int page_idx() const { return page_idx_; }

    inline int slot() const { return slot_; }

public:
    HashTableNode(int fd, int page_idx, int slot) : fd_(fd), page_idx_(page_idx), slot_(slot) {};

    ~HashTableNode() = default;
};


#endif //REDBASE_HASH_TABLE_NODE_H
