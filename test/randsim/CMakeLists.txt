if (APPLE)
    link_directories(/usr/local/lib)
endif()

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

if (APPLE)
  set(CMAKE_MACOSX_BUNDLE true) 
  set_source_files_properties(fonts/Ubuntu-C.ttf PROPERTIES MACOSX_PACKAGE_LOCATION Resources/fonts/)
endif()

file(COPY "fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(randsim main.cpp fonts/Ubuntu-C.ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(randsim ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

