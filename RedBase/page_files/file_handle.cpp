//
// Created by jinlai song on 2021/3/9.
//

#include "file_handle.h"


FileHandleRC FileHandler::GetPage(int page_idx, PageHandle *page_handle) {
    if (this->is_opened_) {
        if (page_idx <= 0 || page_idx >= this->head_->size()) {
            // return invalid page
        }
        char *dst;
        if (this->buffer_->GetPage(this->fd_, page_idx, &dst) == BufferRC::BUFFER_OK) {
            PageHeader *header = reinterpret_cast<PageHeader *>(dst);
            if (header->free() == kPFBeingUsed) {
                page_handle->set_page_idx(page_idx);
                page_handle->set_content(dst + sizeof(PageHeader));
                // todo : OK?
            }
            this->buffer_->UnpinPage(this->fd_, page_idx); // todo: 我写的对？？？？
        }
    }
    // return file not open
    FileHandleRC result;
    return result;
}

