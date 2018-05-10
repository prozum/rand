subdir('Fonts')

map = custom_target('randsim-map',
    input : 'map.txt',
    output : 'map.txt',
    command : [filecopier, '@INPUT@', '@OUTPUT@'])

minimap = custom_target('randsim-minimap',
    input : 'minimap.txt',
    output : 'minimap.txt',
    command : [filecopier, '@INPUT@', '@OUTPUT@'])

sdl2 = dependency('sdl2')
sdl2image = dependency('SDL2_image')
sdl2ttf = dependency('SDL2_ttf')

randsim_exe = executable('randsim', 'Main.cpp', 'SimObject/Drone.cpp', 'UI/Minimap.cpp', 'Simulator.cpp', 'Simulator.h', 'UI/Renderer.cpp', 'UI/Renderer.h', 'UI/SdlRenderer.cpp', 'UI/SdlRenderer.h', 'SimObject/SimObject.cpp', 'SimObject/SimObject.h', 'SimObject/Block.cpp', 'SimObject/Block.h', 'Common/Vector2D.cpp', 'Common/Vector2D.h', 'SimObject/Sonar.cpp', 'SimObject/Sonar.h', 'Common/Ray.cpp', 'Common/Ray.h', 'SimObject/Laser.cpp', 'SimObject/Laser.h', 'UI/BlockBuilder.cpp', 'UI/BlockBuilder.h',
                         include_directories: incdir,
                         dependencies: [sdl2, sdl2image, sdl2ttf],
                         link_depends: [font, map, minimap],
                         cpp_args: ['-DMOCK', '-DUNO_BOARD'],
                         link_with: [nav_mock_lib, fc_mock_lib, kalman_mock_lib, matrix_mock_lib, map_mock_lib, sonar_mock_lib, ir_mock_lib, laser_mock_lib])
