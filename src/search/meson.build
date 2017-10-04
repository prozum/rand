srcs = ['search.c']

if cross
    search_lib = static_library('search', 
                              srcs,
                              include_directories: incdir,
                              link_with: [
                                core_lib, 
                                ],
                              pic: false)
endif

search_mock_lib = library('search-mock', 
                       srcs,
                       include_directories: incdir,
                       link_with: [
                         core_mock_lib,
                         ],
                       native: true)
