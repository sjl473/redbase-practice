//
// Created by jinlai song on 2021/2/10.
//

#ifndef REDBASE_BUFFER_NODE_H
#define REDBASE_BUFFER_NODE_H

#include <vector>
#include "page_header.h"
#include "buffer_node_rc.h"

using namespace std;

class BufferNode {
public:
    static const int kPageSize = sizeof(int) * 1024 - sizeof(PageHeader) + sizeof(int);
private:
    bool is_dirty_{};
    int counter_{};
    int fd_{};
    int page_idx_{};

    vector<char> storage_;
public:
    BufferNode(int is_dirty, int counter, int fd, int page_idx, int slot)
            : is_dirty_(is_dirty), counter_(counter), fd_(fd), page_idx_(page_idx) {
        storage_ = vector<char>(kPageSize, 0);
    }

    BufferNode();

    inline bool is_dirty() const;

    inline int counter() const;

    inline int fd() const;

    inline int page_idx() const;

    inline char *storage();

    inline void set_fd(int fd);

    inline BufferNodeRC set_counter(int count);

    inline void set_dirty(bool is_dirty);

    inline void decrease_counter();

    inline void modify_dirty();

    inline void increase_counter();

    inline void set_page_idx(int page_idx);

};

#endif //REDBASE_BUFFER_NODE_H
