# generate_avr_library(['laser', 'MOCK', 'BOARD', 'uno', 'SRCS', 'laser.c', 'LIBS', 'core', 'libfixmath'])

srcs = ['laser.c']

if cross
    laser_lib = static_library('laser', 
                              srcs,
                              include_directories: incdir,
                              link_with: [
                                core_lib, 
                                libfixmath_lib, 
                                ],
                              pic: false)
endif

laser_mock_lib = library('laser-mock', 
                       srcs,
                       include_directories: incdir,
                       link_with: [
                         core_mock_lib,
                         libfixmath_mock_lib,
                         ],
                       native: true)
