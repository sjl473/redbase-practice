#include "buffer.h"
#include "file_header.h"
#include "page_handle.h"

class FileHandle {
private:
    shared_ptr<Buffer> buffer_;
    unique_ptr<FileHeader> file_header_;

    bool is_opened_;
    bool is_modified_;
    int fd_;
public:
    explicit FileHandle(Buffer *buffer) {
        is_opened_ = is_modified_ = false;
        buffer_ = shared_ptr<Buffer>(buffer);
        is_modified_ = false;
        fd_ = -1;
        file_header_ = nullptr;
    }

    int GetPage(int page_idx, PageHandle *page_handle);

    bool UnpinPage(int page_idx);

    bool AllocPage(PageHandle *page);

    bool MarkDirty(int page_idx);

};


