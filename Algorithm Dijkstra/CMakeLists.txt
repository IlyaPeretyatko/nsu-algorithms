cmake_minimum_required(VERSION 3.5.1)
project(lab9 C)

set(SRC src/algorithmDijkstra.c src/input.c src/additional.c src/output.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
