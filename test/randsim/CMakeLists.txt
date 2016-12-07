if (APPLE)
    link_directories(/usr/local/lib)

    set(CMAKE_MACOSX_BUNDLE true)

    set_source_files_properties([map.txt PROPERTIES MACOSX_PACKAGE_LOCATION Resources/)

#    file(COPY "map.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/MacOS/)
#    file(COPY "Fonts/Ubuntu-C.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/Resources/Fonts/)
endif()

# SDL2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
pkg_search_module(SDL2GFX REQUIRED SDL2_gfx>=1.0.0)

# Resource files
file(COPY "Fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
#file(COPY "map.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
configure_file(map.txt map.txt COPYONLY)
configure_file(minimap.txt minimap.txt COPYONLY)

# Add mock definitions
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)

# Target
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Renderer ${CMAKE_CURRENT_SOURCE_DIR}/SimObject)
add_executable(randsim Main.cpp SimObject/Drone.cpp SimObject/Minimap.cpp Fonts/Ubuntu-C.ttf Simulator.cpp Simulator.h Renderer/Renderer.cpp Renderer/Renderer.h Renderer/SdlRenderer.cpp Renderer/SdlRenderer.h SimObject/SimObject.cpp SimObject/SimObject.h SimObject/Block.cpp SimObject/Block.h SimObject/Vector2D.cpp SimObject/Vector2D.h SimObject/Sonar.cpp SimObject/Sonar.h SimObject/Ray.cpp SimObject/Ray.h SimObject/Laser.cpp SimObject/Laser.h)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS})
target_link_libraries(randsim nav fc kalman matrix map laser sonar ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2GFX_LIBRARIES})

