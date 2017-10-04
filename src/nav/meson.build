# generate_avr_library(['nav', 'MOCK', 'BOARD', 'uno', 'SRCS', 'nav.c', 'LIBS', 'fc', 'kalman', 'map', 'search', 'core'])
srcs = ['nav.c']

if cross
    nav_lib = static_library('nav', 
                              srcs,
                              include_directories: incdir,
                              link_with: [
                                core_lib, 
                                libfixmath_lib,
                                kalman_lib, 
                                fc_lib,
                                map_lib,
                                search_lib
                                ],
                              pic: false)
endif

nav_mock_lib = library('nav-mock', 
                       srcs,
                       include_directories: incdir,
                       link_with: [
                         core_mock_lib,
                         libfixmath_mock_lib,
                         kalman_mock_lib,
                         fc_mock_lib,
                         map_mock_lib,
                         search_mock_lib
                         ],
                       native: true)
