//
// Created by jinlai song on 2021/3/9.
//

#include "page_handle.h"

PageHandle::PageHandle(const PageHandle *pageHandle) {

}

void PageHandle::set_dirty(bool val) {

}

int PageHandle::page_idx() {
    return 0;
}

bool PageHandle::is_dirty() {
    return false;
}

const char *PageHandle::content() {
    return nullptr;
}

bool PageHandle::is_file_handle_expired() {
    return 0;
}

void PageHandle::set_page_idx(int page_idx) {
    ;
}

void PageHandle::set_content(char *content) {

}


