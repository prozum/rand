if cross
    core_lib = static_library('core', 
                              'io.c', 'log.c',
                              include_directories: incdir,
                              pic: false)
endif

core_mock_lib = library('core-mock', 
                       'io-mock.c', 'log.c',
                       include_directories: incdir,
                       native: true)
