# generate_avr_library(['sonar', 'MOCK', 'BOARD', 'uno', 'SRCS', 'sonar.c', 'LIBS', 'core', 'kalman', 'sonar'])
srcs = ['sonar.c']

if cross
    sonar_lib = static_library('sonar', 
                              srcs,
                              include_directories: incdir,
                              link_with: [
                                core_lib, 
                                libfixmath_lib, 
                                kalman_lib, 
                                ],
                              pic: false)
endif

sonar_mock_lib = library('sonar-mock', 
                       srcs,
                       include_directories: incdir,
                       link_with: [
                         core_mock_lib,
                         libfixmath_mock_lib,
                         kalman_mock_lib,
                         ],
                       native: true)
