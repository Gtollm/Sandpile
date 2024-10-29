add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC vector)
target_link_libraries(${PROJECT_NAME} PUBLIC matrix)

# target_link_libraries(${PROJECT_NAME} PRIVATE vector)
# target_link_libraries(${PROJECT_NAME} PRIVATE matrix)
target_link_libraries(${PROJECT_NAME} PUBLIC parser)
target_link_libraries(${PROJECT_NAME} PUBLIC sandpile)
target_link_libraries(${PROJECT_NAME} PUBLIC bmp_writer)
target_link_libraries(${PROJECT_NAME} PUBLIC tsv_reader)
target_link_libraries(${PROJECT_NAME} PUBLIC linked_list)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
