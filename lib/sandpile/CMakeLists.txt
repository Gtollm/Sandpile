add_library(sandpile sandpile.cpp sandpile.hpp)

target_link_libraries(sandpile INTERFACE  linked_list)
target_link_libraries(sandpile INTERFACE matrix)
target_link_libraries(sandpile PUBLIC bmp_writer)

target_include_directories(sandpile PUBLIC ${PROJECT_SOURCE_DIR})

