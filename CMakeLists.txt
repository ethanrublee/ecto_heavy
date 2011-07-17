cmake_minimum_required(VERSION 2.8)
project(ecto_heavy)

find_package(ecto REQUIRED)
find_package(OpenCV REQUIRED)

add_definitions("-fno-strict-aliasing -Wall -Wl,--no-undefined")

ectomodule(ecto_heavy
    heavy_magick.cpp
    heavy_cell.cpp
)

ecto_python_env_gen(${CMAKE_BINARY_DIR})

#optionally link against other libs
link_ecto(ecto_heavy
  ${OpenCV_LIBS}
)
