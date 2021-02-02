#include "file_header.h"
#include "file_handle.h"
#include <cstring>

int FileHandle::GetPage(int page_idx, PageHandle *page_handle) {
    if (this->is_opened_) {
        if (page_idx < 0 || page_idx >= this->file_header_->size()) {
            return -1; // todo:
        } else {
            char *dst;
            if (this->buffer_->GetPage(this->fd_, page_idx, &dst) < 0) {
                return -1; // todo:
            }
            auto *page_header = reinterpret_cast<PageHeader *>(dst);
            if (page_header->free() != 0) { // todo: page header所在的page是空闲的
                this->buffer_->UnpinPage(this->fd_, page_idx); // todo: unpin 嘎哈？
            }
            page_handle->set_page_idx(page_idx);
            page_handle->set_data_(dst + sizeof(PageHeader));
        }
    } else {
        return -1; // todo: pf not opened
    }
}

bool FileHandle::AllocPage(PageHandle *page) {
    if (is_opened_) {
        int rc;
        int page_idx;
        char *addr;
        if (this->file_header_->free() != 0) { // todo: file header的free等于某个值说明buffer里的东西已经没有空闲页面了
            page_idx = this->file_header_->free();
            rc = this->buffer_->GetPage(fd_, page_idx, &addr);
            if (rc == 0) return rc; // todo: 等于0????????
            this->file_header_->set_free(reinterpret_cast<PageHeader *>(addr)->free()); // todo: 空洞数目 - 1 ?????????
        } else {
            page_idx = this->file_header_->size();
            rc = this->buffer_->AllocPage(this->fd_, page_idx, &addr);
            if (rc == 0) { // todo: 等于0????????
                return rc;
            }
            this->file_header_->size_plus_plus();
        }
        this->is_modified_ = true;
        reinterpret_cast<PageHeader *>(addr)->set_free(1); // todo: modified 1 to pf page used enum
        memset(addr + sizeof(PageHeader), 0, buffer_->test_buffer_node.kPageSize - sizeof(PageHeader));
        this->MarkDirty(page_idx);
        (*page).set_page_idx(page_idx);
    } else {
        return false; // todo:
    }
}

bool FileHandle::UnpinPage(int page_idx) {
    if (page_idx >= this->file_header_->size() || page_idx < 0) {
        return false;
    }
    (*buffer_).UnpinPage(this->fd_, page_idx);
    return true;
}

bool FileHandle::MarkDirty(int page_idx) {
    if (page_idx >= this->file_header_->size() || page_idx < 0) {
        return false;
    }
    (*buffer_).MarkDirty(this->fd_, page_idx);
    return true;
}

