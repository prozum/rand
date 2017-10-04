project('randie', 'c', 'cpp')

board = get_option('board')
samples_enabled = get_option('samples')
test_enabled = get_option('test')
simulator_enabled = get_option('simulator')
doc_enabled = get_option('doc')

incdir = include_directories(['src'])

cross = meson.is_cross_build()
if not cross
    message('Building mock libraries only.')
endif

add_project_arguments(
    '-D@0@_BOARD'.format(board.to_upper()),
    language: 'c',
)

subdir('src')
if samples_enabled
  subdir('samples')
endif
if test_enabled
  subdir('test')
endif
if simulator_enabled
  subdir('test/randsim')
endif
if doc_enabled
endif
