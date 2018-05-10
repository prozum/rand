srcs = ['map.c']

if cross
    map_lib = static_library('map', 
                              srcs,
                              include_directories: incdir,
                              link_with: [
                                core_lib, 
                                libfixmath_lib, 
                                ],
                              pic: false)
endif

map_mock_lib = library('map-mock', 
                       srcs,
                       include_directories: incdir,
                       link_with: [
                         core_mock_lib,
                         libfixmath_mock_lib,
                         ],
                       native: true)
