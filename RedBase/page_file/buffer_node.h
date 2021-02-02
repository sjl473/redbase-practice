#include "page_header.h"
#include <memory>
#include <vector>

using namespace std;

class BufferNode {
public:
    const int kPageSize = 4 * 1024 - sizeof(int) + sizeof(PageHeader);

private:
    bool is_dirty_{};
    int counter_{};
    int fd_{};
    int page_idx_{};
    int slot_{};
    unique_ptr<vector<char>> storage_;

public:
    BufferNode(int is_dirty, int counter, int fd, int page_idx, int slot)
            : is_dirty_(is_dirty), counter_(counter), fd_(fd), page_idx_(page_idx),
              slot_(slot) {
        storage_ = unique_ptr<vector<char>>(new vector<char>(kPageSize, 0));
    }

    BufferNode() = default;

    ~BufferNode() = default;

public:
    inline bool is_dirty() const { return is_dirty_; }

    inline int counter() const { return counter_; }

    inline int fd() const { return fd_; }

    inline int page_idx() const { return page_idx_; }

    inline int slot() const { return slot_; }

    inline void increaseCounter() { ++counter_; }

    inline int set_slot(int slot) {
        if (slot_ < 0)
            return -1;
        this->slot_ = slot;
    }

    inline void modifyDirty() {
        if (this->is_dirty_) {
            this->is_dirty_ = false;
        } else {
            is_dirty_ = true;
        }
    }

    inline void set_dirty(bool flag) { this->is_dirty_ = flag; }

    inline void decreaseCounter() { --counter_; }

    inline void set_fd(int fd) { this->fd_ = fd; }

    inline void set_page_idx(int idx) { this->page_idx_ = idx; }

    inline void set_counter(int counter) { this->counter_ = counter; }

    inline char *storage() { return &((*storage_)[0]); }
};
