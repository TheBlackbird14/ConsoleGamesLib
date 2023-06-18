cmake_minimum_required(VERSION 3.21.1)
project(cgl)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the executable for the main program
add_executable(cgl main.c)

add_executable(tictactoe games/tictactoe.c)
add_executable(battleships games/battleships.c)
add_executable(hangman games/hangman.c)

# Add the libraries
add_library(strcap STATIC libs/strcap.c)
add_library(CGLgeneral STATIC libs/CGLgeneral.c)

# Link the libraries to the executables
target_link_libraries(cgl strcap CGLgeneral)
target_link_libraries(tictactoe strcap CGLgeneral)
target_link_libraries(battleships strcap CGLgeneral)
target_link_libraries(hangman strcap CGLgeneral ncurses)

# Set the output directory for the executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)


# Install the cgl executable to /usr/local/bin
install(TARGETS cgl tictactoe battleships hangman DESTINATION /usr/local/bin)


#target_compile_options(tictactoe PRIVATE "-w")
target_compile_options(tictactoe PRIVATE "-g")

set(CMAKE_BUILD_TYPE Debug)