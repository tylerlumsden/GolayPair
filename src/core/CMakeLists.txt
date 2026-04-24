add_subdirectory(uncompression)
add_subdirectory(filter)
add_subdirectory(generate)
add_subdirectory(match)
add_subdirectory(sort)

add_library(core INTERFACE)

target_link_libraries(core INTERFACE utils uncompress filter generate sort match)