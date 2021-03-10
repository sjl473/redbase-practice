//
// Created by jinlai song on 2021/3/9.
//

#ifndef REDBASE_PAGE_HANDLE_H
#define REDBASE_PAGE_HANDLE_H

#include <memory>

using namespace std;

class PageHandle {
private:
    bool is_dirty_;
    int page_idx_;
    unique_ptr<char> content_;
public:
    PageHandle() : page_idx_(-1), is_dirty_(false) {
        this->content_ = unique_ptr<char>(nullptr);
    }

    explicit PageHandle(const PageHandle *pageHandle);

    void set_dirty(bool val);

    inline int page_idx();

    inline void set_page_idx(int page_idx);

    inline void set_content(char *content);

    inline bool is_dirty();

    inline const char *content();


};


#endif //REDBASE_PAGE_HANDLE_H

