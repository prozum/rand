if cross
    matrix_lib = static_library('matrix',
                              'matrix.c',
                              include_directories: incdir,
                              link_with: [core_lib, libfixmath_lib],
                              pic: false)
endif

matrix_mock_lib = library('matrix-mock', 
                          'matrix.c',
                          include_directories: incdir,
                          link_with: [core_mock_lib, libfixmath_mock_lib],
                          native: true)
