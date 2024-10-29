add_library(bmp_writer bmp.cpp bmp.hpp)

target_link_libraries(bmp_writer PRIVATE vector)
target_include_directories(bmp_writer PUBLIC ${PROJECT_SOURCE_DIR})

