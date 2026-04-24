add_library(match STATIC
    match_pairs.cpp
)

target_include_directories(match
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(match PRIVATE utils)