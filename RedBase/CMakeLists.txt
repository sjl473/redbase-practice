cmake_minimum_required(VERSION 3.17)
project(RedBase)

set(CMAKE_CXX_STANDARD 11)

add_executable(RedBase main.cpp page_file/page_header.cpp page_file/page_header.h page_file/hash_table.cpp page_file/hash_table.h page_file/hash_table_node.cpp page_file/hash_table_node.h page_file/buffer.cpp page_file/buffer.h page_file/buffer_node.cpp page_file/buffer_node.h page_file/message.h page_file/file_handle.cpp page_file/file_handle.h page_file/file_header.cpp page_file/file_header.h page_file/page_handle.cpp page_file/page_handle.h)