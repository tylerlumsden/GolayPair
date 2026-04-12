add_library(sort STATIC
    sort.cpp
)

target_include_directories(sort
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(sort PRIVATE utils)