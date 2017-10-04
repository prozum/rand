srcs = ['kalman.c', 'kalman-datafusion.c']

if cross
    kalman_lib = static_library('kalman', 
                              srcs,
                              include_directories: incdir,
                              link_with: [core_lib, libfixmath_lib, matrix_lib],
                              pic: false)
endif

kalman_mock_lib = library('kalman-mock', 
                          srcs,
                          include_directories: incdir,
                          link_with: [core_mock_lib, libfixmath_mock_lib, matrix_mock_lib],
                          native: true)
