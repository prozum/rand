# generate_avr_library(['ir', 'MOCK', 'BOARD', 'uno', 'SRCS', 'ir.c', 'LIBS', 'kalman', 'core'])
#

if cross
    ir_lib = static_library('ir', 
                            'ir.c',
                            include_directories: incdir,
                            link_with: [kalman_lib, core_lib],
                            pic: false)
endif

ir_mock_lib = library('ir-mock', 
                      'ir.c',
                      include_directories: incdir,
                      link_with: [kalman_mock_lib, core_mock_lib],
                      native: true)
