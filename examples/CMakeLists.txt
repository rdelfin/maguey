project(examples)

add_executable(triangle_example triangle_example.cpp)
target_link_libraries(triangle_example maguey)
install(TARGETS triangle_example RUNTIME DESTINATION ${BIN_DIR})

add_executable(mesh_example mesh_example.cpp)
target_link_libraries(mesh_example maguey)
install(TARGETS mesh_example RUNTIME DESTINATION ${BIN_DIR})
