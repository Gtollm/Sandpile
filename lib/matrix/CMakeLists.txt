add_library(matrix INTERFACE matrix.hpp)

target_link_libraries(matrix INTERFACE vector)
