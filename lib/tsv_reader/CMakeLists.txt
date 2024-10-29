add_library(tsv_reader tsv_reader.cpp tsv_reader.hpp)

target_link_libraries(tsv_reader PUBLIC sandpile)
target_include_directories(tsv_reader PUBLIC ${PROJECT_SOURCE_DIR})

