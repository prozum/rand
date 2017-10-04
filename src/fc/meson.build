srcs = ['fc.c']

if cross
    fc_lib = static_library('fc', 
                              srcs,
                              include_directories: incdir,
                              link_with: [
                                core_lib, 
                                libfixmath_lib, 
                                ],
                              pic: false)
endif

fc_mock_lib = library('fc-mock', 
                       srcs,
                       include_directories: incdir,
                       link_with: [
                         core_mock_lib,
                         libfixmath_mock_lib,
                         ],
                       native: true)
