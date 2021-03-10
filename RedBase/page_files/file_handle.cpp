//
// Created by jinlai song on 2021/3/9.
//

#include "file_handle.h"


FileHandleRC FileHandle::GetPage(int page_idx, PageHandle *page_handle) {
    if (!this->is_opened_) {
        return FileHandleRC::FILE_NOT_OPENED;
    }
    if (page_idx < 0 || page_idx >= this->head_->size()) {
        return FileHandleRC::INVALID_PAGE_IDX;
    }
    char *dst = new char();
    this->buffer_->GetPage(this->fd_, page_idx, &dst); // todo: 错误返回码
    auto *p_page_header = (PageHeader *) dst;
    if (p_page_header->free() == kPFBeingUsed) {
        page_handle->set_page_idx(page_idx);
        page_handle->set_content(dst + sizeof(p_page_header));
        // pointer to aggregate
        return FileHandleRC::FILE_HANDLE_OK;
    }
    this->buffer_->UnpinPage(this->fd_, page_idx); // todo: 错误返回码
    return FileHandleRC::FILE_HANDLE_OK;
}

FileHandleRC FileHandle::UnpinPage(int page_idx) {
    if (!this->is_opened_) {
        return FileHandleRC::FILE_NOT_OPENED;
    }
    if (page_idx < 0 || page_idx >= this->head_->size()) {
        return FileHandleRC::INVALID_PAGE_IDX;
    }
    return FILE_HANDLE_OK;
}

FileHandleRC FileHandle::FirstPage(PageHandle *page_handle) {

    return FILE_HANDLE_OK;
}

FileHandleRC FileHandle::NextPage(PageHandle *page_handle) {
    return FILE_HANDLE_OK;
}

FileHandleRC FileHandle::PrevPage(int curr_page_idx, PageHandle *page_handle) {
    if (!this->is_opened_) {
        return FileHandleRC::FILE_NOT_OPENED;
    }
    if (curr_page_idx < 0 || curr_page_idx >= this->head_->size()) {
        return FileHandleRC::INVALID_PAGE_IDX;
    }
    int prev;
    for (prev = curr_page_idx - 1; prev >= 0; prev--) {
        if (FileHandleRC::FILE_HANDLE_OK == this->GetPage(curr_page_idx, page_handle)) {
            // todo: return ok
        }
    }
    return FILE_HANDLE_OK; // todo: not ok
}

FileHandleRC FileHandle::LastPage(PageHandle *page_handle) {
    return FILE_HANDLE_OK;
}

FileHandleRC FileHandle::AllocPage(PageHandle *page_handle) {
    return FILE_HANDLE_OK;
}

FileHandleRC FileHandle::MarkDirty(PageHandle *page_handle) {
    return FILE_HANDLE_OK;
}


