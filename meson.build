project('randie', 'c', 'cpp')

subdir('meson')

incdir = include_directories(['src'])

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
