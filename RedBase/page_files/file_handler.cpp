//
// Created by jinlai song on 2021/3/9.
//

#include "file_handler.h"


FileHandleRC FileHandler::GetPage(int page_idx, PageHandle *page_handle) {
    if(this->is_opened_) {
        if(page_idx <= 0 || page_idx >= this->head_->size()) {
            // return invalid page
        }
        char* dst;
        this->buffer_->GetPage(this->fd_, page_idx, &dst);

    }
    // return file not open
    FileHandleRC result;
    return result;
}

//
// getPage - 获取文件中指定的页, 并将内容填充入一个PFPageHandle的一个实体
//
//RC PFFileHandle::getPage(Page num, PFPageHandle &page) const
//{
//
//    if (!opened_) return PF_CLOSEDFILE;
//    if (num < 0 || num >= hdr_.size) return PF_INVALIDPAGE;
//    Ptr addr;
//    buff_->getPage(fd_, num, addr);
//    PFPageHdr *hdr = (PFPageHdr *)addr;
//    // 如果页面已经被使用了，那么让pph指向这个页面
//    if (hdr->free == PF_PAGE_USED) {
//        page.num_ = num;
//        // 注意到这里的data_,指向的并不是页的首部,而是首部后面4个字节处
//        page.addr_ = addr + sizeof(PFPageHdr);
//        return 0; // 一切正常
//    }
//    // 到了这里的话,页面多半为空
//    unpin(num);
//    return PF_INVALIDPAGE;
//}