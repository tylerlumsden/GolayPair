add_library(generate STATIC
    generate_hybrid.cpp
)

target_include_directories(generate
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(generate PRIVATE utils)