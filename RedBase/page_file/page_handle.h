class PageHandle {
public:
    PageHandle(bool is_dirty, int page_idx, char *data)
            : is_dirty_(is_dirty), page_idx_(page_idx), data_(data) {}

private:
    bool is_dirty_;
    int page_idx_;
    char *data_;
public:
    inline bool is_dirty() const { return this->is_dirty_; }

    inline int page_idx() const { return this->page_idx_; }

    inline char *data() const { return data_; }

    inline void modifyDirty(bool flag) { this->is_dirty_ = flag; }

    inline void set_data_(char *data) { this->data_ = data; }

    inline bool set_page_idx(int page_idx) {
        if (page_idx_ < 0) { return false }
        this->page_idx_ = page_idx;
        return true;
    }
};