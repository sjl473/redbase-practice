class FileHeader {
private:
    int size_;
    int free_;
public:
    FileHeader(int size, int free) : free_(free), size_(size) {}

    inline int size() const { return size_; }

    inline int free() const { return free_; }

    inline void set_free(int free) {
        this->free_ = free;
    }

    inline void size_plus_plus() { this->size_++; }
};