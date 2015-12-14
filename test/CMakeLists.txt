# cmake minimal version
cmake_minimum_required(VERSION 2.6)

# add testing
enable_testing()

# project declaration
project(TestZappyServer)

if (APPLE)
include_directories(
    $ENV{HOME}/.brew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    )
link_directories(
    $ENV{HOME}/.brew/lib
    )
else (APPLE)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )
endif (APPLE)


# sources list
file(
    GLOB_RECURSE
    sources_files
    src/*
    )

list(
    APPEND
    CMAKE_C_FLAGS
    "-Wall -Werror -Wextra ${CMAKE_C_FLAGS}"
    )

add_executable(
    test_zappy_server
    ${sources_files}
    )

#Configuration de l'édition de liens
target_link_libraries(
    test_zappy_server
    check
    )

add_test(
    test_zappy_server
    ${CMAKE_CURRENT_BINARY_DIR}/test_zappy_server
    )
