//
// Created by jinlai song on 2021/3/1.
//

#ifndef REDBASE_BUFFER_H
#define REDBASE_BUFFER_H

#include "hash_table.h"
#include "buffer_node.h"
#include "buffer_rc.h"
#include "unistd.h"

class Buffer {
public:
    const static int kMaxCapacity = 40;
private:
    int first_;
    int last_;
    int free_;
    HashTable hashTable_;
    vector<unique_ptr<BufferNode>> nodes_;
public:
    Buffer() {
        hashTable_ = HashTable();
        first_ = 0;
        last_ = 0;
        free_ = 0;
    }

    BufferRC UnpinPage(int fd, int page_idx);

    BufferRC PinPage(int fd, int page_idx);

    BufferRC GetPage(int fd, int page_idx, char **dst);

    static BufferRC ReadFromDisk(int fd, int page_idx, char **dst);

    static BufferRC WriteToDisk(int fd, int page_idx, const char *src);

    BufferRC Force(int fd, int page_dix);

    BufferRC MarkDirty(int fd, int page_idx);

    BufferRC FetchMemory(int fd, int page_idx, char** dst);

    BufferRC Alloc(int fd, int page_idx);
};


#endif //REDBASE_BUFFER_H
