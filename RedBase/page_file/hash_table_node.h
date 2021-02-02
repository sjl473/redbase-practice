#include <memory>

class HashTableNode {
private:
    int fd_;
    int page_idx_;
    int slot_;

public:
    int fd() const { return fd_; }

    int page_idx() const { return page_idx_; }

    int slot() const { return slot_; }

public:
    HashTableNode(int fd, int page_idx, int slot) : fd_(fd), page_idx_(page_idx), slot_(slot) {};

    ~HashTableNode() = default;
};
