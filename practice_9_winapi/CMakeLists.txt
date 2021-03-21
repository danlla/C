cmake_minimum_required (VERSION 3.11)

project (practice_9_winapi C)

add_executable(winapi_practice WIN32 "winapi_practice.c")
target_compile_options(winapi_practice PUBLIC /DUNICODE /D_UNICODE /utf-8)
