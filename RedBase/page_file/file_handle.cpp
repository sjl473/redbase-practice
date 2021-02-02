#include "file_handle.h"

int FileHandle::GetPage(int page_idx, PageHandle *page_handle) {
    if (this->is_opened_) {
        if (page_idx < 0 || page_idx >= this->file_header_->size()) {
            return -1; // todo:
        } else {
            char *dst;
            if (this->buffer_->GetPage(this->fd_, page_idx, &dst) < 0) {
                return -1; // todo:
            }
            PageHeader *page_header = reinterpret_cast<PageHeader *>(dst);
            if (page_header->free() != 0) { // todo: page header所在的page是空闲的
                this->buffer_->UnpinPage(this->fd_, page_idx); // todo: unpin 嘎哈？
            }
            page_handle->set_page_idx(page_idx);
            page_handle->set_data_(dst + sizeof(page_header));
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

        } else {
            page_idx = this->file_header_->size();
            rc = this->buffer_->AllocPage(this->fd_, page_idx, &addr);
            if(rc == 0) {
                return rc;
            }
            this->file_header_->size_plus_plus();
        }
    } else {
        return false; // todo:
    }
}

////RC PFFileHandle::allocPage(PFPageHandle &page)
////{
////    RC rc;		// 返回码
////    Page num;
////    Ptr addr;
////
////    if (!opened_) return PF_CLOSEDFILE;
////
////    if (hdr_.free != PF_PAGE_LIST_END) { // 仍然存在空闲页面,取出一块
////        num = hdr_.free;
////        if (rc = buff_->getPage(fd_, num, addr)) return rc;
////        // tofix - 这里我是存在疑问的,那就是新得到的页面的free初始化过了吗? 初始化过
////        hdr_.free = ((PFPageHdr *)addr)->free; // 空洞数目减1
////    }
////    else { // 空闲链表为空
////        num = hdr_.size;
////        // 分配一个新的页面
////        if (rc = buff_->allocPage(fd_, num, addr)) return rc;
////        hdr_.size++;
////    }
////    changed_ = true; // 文件发生了变动
////    // 将这个页面标记为USED
////    ((PFPageHdr *)addr)->free = PF_PAGE_USED;
////    memset(addr + sizeof(PFPageHdr), 0, PF_PAGE_SIZE);
////    // 将页面标记为脏
////    markDirty(num);
////    // 将页面的信息填入pph中
////    page.num_ = num;
////    page.addr_ = addr + sizeof(PFPageHdr); // 指向实际的数据
////    return 0;
////}
