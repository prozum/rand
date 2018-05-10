board = get_option('board')
samples_enabled = get_option('samples')
test_enabled = get_option('test')
simulator_enabled = get_option('simulator')
doc_enabled = get_option('doc')

cross = meson.is_cross_build()
if not cross
    message('Building mock libraries only.')
endif

add_project_arguments(
    '-D@0@_BOARD'.format(board.to_upper()),
    language: 'c',
)

filecopier = find_program('filecopier.py')

objcopy = find_program('avr-objcopy')
avrdude = find_program('avrdude')

eep_gen = generator(objcopy,
  output : '@BASENAME@.eep',
  arguments : ['-O', 'ihex', '-j', '.eeprom',
    '--set-section-flags=.eeprom=alloc,load',
    '--no-change-warnings', '--change-section-lma',
    '.eeprom=0', '@INPUT@', '@OUTPUT@',
  ]
)

hex_gen = generator(objcopy,
  output : '@BASENAME@.hex',
  arguments : ['-O', 'ihex', '-R', '.eeprom',
    '@INPUT@', '@OUTPUT@',
  ],
)
