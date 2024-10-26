add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE parser)
# target_link_libraries(${PROJECT_NAME} PRIVATE sandpile)
target_link_libraries(${PROJECT_NAME} PRIVATE bmp_writer)
target_link_libraries(${PROJECT_NAME} PRIVATE tsv_reader)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
