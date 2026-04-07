add_subdirectory(utils)
add_subdirectory(core)

add_executable(main main.cpp)
set_target_properties(main PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
target_include_directories(main PRIVATE ${GOLAYPAIR_THIRD_PARTY_DIR})
target_link_libraries(main PRIVATE core)