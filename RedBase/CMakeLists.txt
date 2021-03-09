cmake_minimum_required(VERSION 3.17)
project(RedBase)

set(CMAKE_CXX_STANDARD 20)

add_executable(RedBase main.cpp page_files/hash_table_node.h page_files/hash_table.cpp page_files/hash_table.h page_files/hash_table_rc.h page_files/page_header.h page_files/page_header_rc.h page_files/buffer_node.cpp page_files/buffer_node.h page_files/buffer_node_rc.h page_files/buffer.cpp page_files/buffer.h page_files/buffer_rc.h page_files/page_handle.cpp page_files/page_handle.h page_files/file_handler.cpp page_files/file_handler.h page_files/file_handler_rc.h)