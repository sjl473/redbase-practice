

class PageHeader {
private:
    int free_{};

public:
    explicit PageHeader(int free) : free_(free) {}

    PageHeader() = default;

public:
    int free() const { return free_; }

    bool set_free(int free) {
        if (free <= 0) {
            return false;
        }
        this->free_ = free;
        return true;
    }
};

