project(test)
add_executable(display_test display_test.cpp)
target_link_libraries(display_test maguey)
install(TARGETS display_test RUNTIME DESTINATION ${BIN_DIR})