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

# Math libraries
add_subdirectory(libfixmath)
add_subdirectory(matrix)

# Kalman filter library
add_subdirectory(kalman)

# Navigation library
add_subdirectory(nav)

# Searching
add_subdirectory(search)

# Map library
add_subdirectory(map)