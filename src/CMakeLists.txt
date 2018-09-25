project(src)

set(pwd ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB src ${pwd}/*.cpp)

add_library(maguey STATIC ${src})

target_link_libraries(maguey ${SDL2_LIBRARY} ${stdgl_libraries} ${glm_LIBRARY_DIRS})

install(TARGETS maguey
        EXPORT magueyTargets
        DESTINATION lib)
install(DIRECTORY ${pwd}/../include/
        DESTINATION include)