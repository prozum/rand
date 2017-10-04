#simavr_incdir = include_directories('sim','/usr/avr/include')
simavr_incdir = include_directories('sim')

subdir('cores')
subdir('sim')

libelf_dep = dependency('libelf', native: true)
simavr_lib = library('simavr', 
                     srcs,
                     dependencies: libelf_dep,
                     include_directories: simavr_incdir,
                     native: true,
                     override_options : 'c_std=c11',)
                     #link_with:)

  # include_directories([LIBELF_INCLUDE_DIRS, '/usr/local/include/', 'avr'])
  # file(['GLOB', 'SRCS', 'sim/*.c', 'sim/*.h'])
  # set_property(['TARGET', 'simavr', 'PROPERTY', 'C_STANDARD', '11'])
  # target_link_libraries(['simavr', 'simavr-cores', LIBELF_LIBRARIES])
