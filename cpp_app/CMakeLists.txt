cmake_minimum_required(VERSION 3.10)

add_executable(main main.cpp)
add_dependencies(main build_rust_lib)
target_link_libraries(main PRIVATE ${RUST_LIB_PATH}/librust_lib.so)
