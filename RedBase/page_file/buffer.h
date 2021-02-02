#include "buffer_node.h"
#include "hash_table.h"
#include "page_header.h"

class Buffer {
public:
    const static int kMaxCapacity = 40;

private:
    int first_{};
    int last_{};
    int free_{};
    unique_ptr<HashTable> hash_table_;
    // buffer node class is "page" on implementation views
    unique_ptr<vector<unique_ptr<BufferNode>>> nodes_;
    // that is a designed problem
    static BufferNode test_buffer_node_;

public:
    explicit Buffer() {
        auto* hash_table = new HashTable();
        hash_table_ = unique_ptr<HashTable>(hash_table);
    }

    ~Buffer() = default;

    int GetPage(int fd, int page_idx, char **dst);

    int GetAvailableNode(BufferNode *node);

    int PinPage(int fd, int page_idx);

    int UnpinPage(int fd, int page_idx);

    int EvictPageIfDirty(int fd, int page_id, char *dst);

    int ForceAllDirtyPages(int fd);

    int ClearAllDirtyPages(int fd);

    int AllocPage(int fd, int page_idx, char** evictedData);

private:
    static int ReadFromDisk(int fd, int page_idx, char *dst);

    static int WriteToDisk(int fd, int page_idx, const char *src);
};