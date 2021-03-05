//
// Created by jinlai song on 2021/2/12.
//

#include "buffer_node.h"


int BufferNode::page_idx() const {
    return this->page_idx_;
}

int BufferNode::fd() const {
    return this->fd_;
}

int BufferNode::counter() const {
    return this->counter_;
}

bool BufferNode::is_dirty() const {
    return this->is_dirty_;
}

void BufferNode::decrease_counter() {
    if (this->counter_ >= -1) {
        this->counter_--;
    }
}

void BufferNode::modify_dirty() {
    this->is_dirty_ = -(this->is_dirty_);
}

void BufferNode::increase_counter() {
    ++this->counter_;
}

char *BufferNode::storage() {
    return &((this->storage_)[0]);
}

BufferNode::BufferNode() = default;

BufferNodeRC BufferNode::set_counter(int counter) {
    if (counter < 0) {
        return BufferNodeRC::INVALID_COUNTER_SETTINGS;
    }
    this->counter_ = counter_;
    return BufferNodeRC::BUFFER_NODE_RC_OK;
}

void BufferNode::set_fd(int fd) {
    this->fd_ = fd;
}


void BufferNode::set_dirty(bool is_dirty) {
    this->is_dirty_ = is_dirty;
}










