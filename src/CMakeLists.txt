project(src)
add_executable(maguey main.cpp)
target_link_libraries(maguey ${SDL2_LIBRARY})
install(TARGETS maguey RUNTIME DESTINATION ${BIN_DIR})