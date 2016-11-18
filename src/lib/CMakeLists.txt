# Core (I/O,Log) library
add_subdirectory(core)

# gdb library
add_subdirectory(gdb)

# Flight Controller library
add_subdirectory(fc)

# Sensor libraries
add_subdirectory(ir)
add_subdirectory(sonar)
add_subdirectory(laser)

# Kalman library
add_subdirectory(kalman)
add_subdirectory(matrix)

add_subdirectory(positioning)
# Positioning and control
# Map library
add_subdirectory(map)