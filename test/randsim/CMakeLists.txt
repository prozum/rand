if (APPLE)
    link_directories(/usr/local/lib)

    set(CMAKE_MACOSX_BUNDLE true)

    set_source_files_properties([map.txt PROPERTIES MACOSX_PACKAGE_LOCATION Resources/)

#    file(COPY "map.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/MacOS/)
#    file(COPY "Fonts/Ubuntu-C.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/Resources/Fonts/)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Renderer ${CMAKE_CURRENT_SOURCE_DIR}/SimObject)


include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

file(COPY "Fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
#file(COPY "map.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
configure_file(map.txt map.txt COPYONLY)

add_executable(randsim Main.cpp SimObject/Drone.cpp SimObject/Map.cpp Fonts/Ubuntu-C.ttf Simulator.cpp Simulator.h Renderer/Renderer.cpp Renderer/Renderer.h Renderer/SdlRenderer.cpp Renderer/SdlRenderer.h SimObject/SimObject.cpp SimObject/SimObject.h SimObject/Block.cpp SimObject/Block.h)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(randsim fc ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

