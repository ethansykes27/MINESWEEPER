cmake_minimum_required(VERSION 3.23)
project(project4)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(project4 minesweeper.cpp Toolbox.cpp Button.cpp Gamestate.cpp Tile.cpp )
target_link_libraries(project4 sfml-graphics sfml-audio)
