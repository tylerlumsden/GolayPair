add_library(filter STATIC
    filter.cpp
)

target_include_directories(filter
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(filter PRIVATE utils)