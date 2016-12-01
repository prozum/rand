if (APPLE)
    link_directories(/usr/local/lib)

    set(CMAKE_MACOSX_BUNDLE true)

    set_source_files_properties([map.txt PROPERTIES MACOSX_PACKAGE_LOCATION Resources/)

#    file(COPY "map.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/MacOS/)
#    file(COPY "fonts/Ubuntu-C.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/Resources/fonts/)
endif()

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

file(COPY "fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
#file(COPY "map.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
configure_file(map.txt map.txt COPYONLY)

add_executable(randsim Main.cpp Drone.cpp Map.cpp map.txt fonts/Ubuntu-C.ttf Simulator.cpp Simulator.h Renderer.cpp Renderer.h SdlRenderer.cpp SdlRenderer.h)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(randsim ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

