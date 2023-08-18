cmake_minimum_required(VERSION 3.10)

project(MorseCodeProject C)

set(CMAKE_C_STANDARD 11)

file(GLOB MAIN_SOURCE "src/ip-over-morse.c")

file(GLOB MORSE_SOURCES "src/morse_code/*.c")

file(GLOB NETWORKING_SOURCES "src/networking/*.c")

add_executable(ip-over-morse ${MAIN_SOURCE} ${MORSE_SOURCES} ${NETWORKING_SOURCES})

target_include_directories(ip-over-morse PRIVATE morse_code networking)

# target_compile_options(ip-over-morse PRIVATE -Wall -Wextra)
target_compile_options(ip-over-morse PRIVATE)
target_link_libraries(ip-over-morse PRIVATE m)

set_target_properties(ip-over-morse PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
