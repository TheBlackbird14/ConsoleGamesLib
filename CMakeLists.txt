cmake_minimum_required(VERSION 3.16.3)
project(cgl)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the executable for the main program
add_executable(cgl main.c)

add_executable(tictactoe games/tictactoe.c)
add_executable(battleships games/battleships.c)

# Add the libraries
add_library(strcap STATIC libs/strcap.c)
add_library(cs50 STATIC libs/cs50.c)

# Link the libraries to the executables
target_link_libraries(cgl strcap cs50)
target_link_libraries(tictactoe strcap cs50)
target_link_libraries(battleships strcap cs50)

# Set the output directory for the executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

# Install the cgl executable to /usr/local/bin
install(TARGETS cgl DESTINATION /usr/local/bin)

#mute warnings for tictactoe

target_compile_options(tictactoe PRIVATE "-w")

set(CMAKE_BUILD_TYPE Release)