cmake_minimum_required(VERSION 3.24.0)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_LIST_DIR}/Lib) 

include_directories("D:/Esp-idf/Mysource/inmp441_test/Filter")

project(ad8232_ecg_test)  
