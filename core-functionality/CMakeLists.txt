cmake_minimum_required(VERSION 3.10)

project(MorseCodeProject C)

set(CMAKE_C_STANDARD 11)

file(GLOB MORSE_SOURCES "morse_code/*.c")

file(GLOB NETWORKING_SOURCES "networking/*.c")

add_executable(test_code ${MORSE_SOURCES} ${NETWORKING_SOURCES})
# add_executable(test_code
#     morse_code/main.c
#     morse_code/morse_core.c
#     morse_code/text_to_wav.c
#     morse_code/wavfile.c
#     morse_code/wav_to_morse.c
# )

target_include_directories(test_code PRIVATE morse_code)

target_compile_options(test_code PRIVATE -Wall -Wextra)
target_link_libraries(test_code PRIVATE m)

set_target_properties(test_code PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

add_custom_target(makefile_generation ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeLists.txt ${CMAKE_BINARY_DIR}/generated_Makefile
    COMMENT "Generating Makefile"
    VERBATIM
)
