//
// Created by jinlai song on 2021/3/9.
//

#ifndef REDBASE_FILE_HANDLE_RC_H
#define REDBASE_FILE_HANDLE_RC_H
enum FileHandleRC {
    FILE_NOT_OPENED,
    INVALID_PAGE_IDX,
    FILE_HANDLE_OK,
    GET_PAGE_ERROR,
    UNPIN_PAGE_ERR,
};
#endif //REDBASE_FILE_HANDLE_RC_H
