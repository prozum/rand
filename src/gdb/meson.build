srcs = ['gdb.c']

if cross
    gdb_lib = static_library('gdb', 
                              srcs,
                              include_directories: incdir,
                              pic: false)
endif
