srcs = files(['fix16.c', 'fix16_exp.c', 'fix16_trig.c', 'fix16_sqrt.c'])

if cross
    libfixmath_lib = static_library('libfixmath', 
                              srcs,
                              include_directories: incdir,
                              pic: false)
endif

libfixmath_mock_lib = library('libfixmath-mock', 
                       srcs,
                       include_directories: incdir,
                       native: true)
