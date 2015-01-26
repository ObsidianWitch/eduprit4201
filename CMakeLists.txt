cmake_minimum_required(VERSION 2.6)
project(Projet)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

include_directories(src)

add_executable(test_Image2D.out
    src/test_Image2D.cc
    src/tools/Point2D.hh
    src/tools/Box2D.hh
    src/tools/Image2D.hh
)

add_executable(test_compute_dmap.out
    src/test_compute_dmap.cc
    src/tools/compute_dmap.hh
    src/tools/Point2D.hh
    src/tools/Image2D.hh
)

add_executable(test_external_modification.out
    src/test_external_modification.cc
    src/tools/Point2D.hh
    src/tools/Image2D.hh
)

add_executable(test_fill.out
    src/test_fill.cc
    src/tools/Box2D.hh
    src/tools/Image2D.hh
    src/tools/FunImage.hh
)

add_executable(test_FunImage.out
    src/test_FunImage.cc
    src/tools/FunImage.hh
    src/tools/compute_dmap.hh
    src/tools/Image2D.hh
)

# add_executable(test_ImageIf.out
#     src/test_ImageIf.cc
#     src/tools/ImageIf.hh
#     src/tools/Box2D.hh
#     src/tools/Image2D.hh
# )

# add_executable(test_compute_dmap__v2.out
#     src/test_compute_dmap__v2.cc
#     src/tools/Box2D.hh
#     src/tools/Image2D.hh
#     src/tools/ImageIf.hh
#     src/tools/Helper.hh
#     src/tools/compute_dmap__v2.hh
# )

# add_executable(music_score_analysis.out
#     src/music_score_analysis.cc
#     src/tools/analyze.hh
#     src/tools/Box2D.hh
#     src/tools/Image2D.hh
#     src/tools/ImageIf.hh
#     src/tools/Helper.hh
#     src/tools/compute_dmap__v2.hh
# )
