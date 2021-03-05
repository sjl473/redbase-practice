//
// Created by jinlai song on 2021/2/10.
//

#ifndef REDBASE_PAGE_HEADER_H
#define REDBASE_PAGE_HEADER_H

#include "page_header_rc.h"

class PageHeader {
private:
    int free_{};

public:
    explicit PageHeader(int free) : free_(free) {}

    PageHeader() = default;

public:
    int free() const { return free_; }

    PageHeaderRC set_free(int free) {
        if (free <= 0) {
            return PageHeaderRC::INVALID_SET_FREE;
        }
        this->free_ = free;
        return PageHeaderRC::PAGE_HEADER_RC_OK;
    }
};


#endif //REDBASE_PAGE_HEADER_H
