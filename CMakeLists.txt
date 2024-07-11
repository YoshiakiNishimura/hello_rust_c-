cmake_minimum_required(VERSION 3.10)
project(RustCppIntegration)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(RUST_BUILD_COMMAND "--release")
    set(RUST_LIB_DIR "release")
else()
    set(RUST_BUILD_COMMAND "")
    set(RUST_LIB_DIR "debug")
endif()
set(RUST_LIB_PATH ${CMAKE_SOURCE_DIR}/rust_lib/target/${RUST_LIB_DIR})
add_custom_command(
    OUTPUT ${RUST_LIB_PATH}/librust_lib.so
    COMMAND cargo build ${RUST_BUILD_COMMAND} 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/rust_lib
    COMMENT "Building Rust library"
)

add_custom_target(build_rust_lib ALL
    DEPENDS ${RUST_LIB_PATH}/librust_lib.so
)
add_library(rust_hello_lib SHARED IMPORTED)
set_target_properties(rust_hello_lib PROPERTIES
    IMPORTED_LOCATION ${RUST_LIB_PATH}/librust_lib.so
)
add_dependencies(rust_hello_lib build_rust_lib)
add_subdirectory(cpp_app)

add_custom_target(clean_rust_lib
    COMMAND cargo clean
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/rust_lib
    COMMENT "Cleaning Rust library"
)
add_custom_target(clean_all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean_rust_lib
    COMMENT "Cleaning all"
)
