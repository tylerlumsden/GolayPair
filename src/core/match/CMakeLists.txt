add_library(match INTERFACE)

target_include_directories(match
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(match INTERFACE utils)