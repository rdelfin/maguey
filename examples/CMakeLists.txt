project(examples)
add_executable(triangle_example triangle_example.cpp)
target_link_libraries(triangle_example maguey)
install(TARGETS triangle_example RUNTIME DESTINATION ${BIN_DIR})