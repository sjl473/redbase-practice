//
// Created by jinlai song on 2021/3/9.
//

#ifndef REDBASE_FILE_HANDLE_H
#define REDBASE_FILE_HANDLE_H

#include "buffer.h"
#include "file_handle_rc.h"
#include "page_handle.h"

class FileHandler {
public:
    FileHandler();

public:

private:
    shared_ptr<Buffer> buffer_;
    bool is_opened_;
    bool is_changed_;
    int fd_;
    unique_ptr<PageHeader> head_;
public:
    FileHandleRC GetPage(int page_idx, PageHandle *page_handle);
};


#endif //REDBASE_FILE_HANDLE_H
