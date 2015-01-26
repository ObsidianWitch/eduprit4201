cmake_minimum_required(VERSION 2.6)
project(Projet)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

add_executable(test_Image2D.out
    src/test_Image2D.cc
    src/Image2D.hh
)

add_executable(test_compute_dmap.out
    src/test_compute_dmap.cc
    src/compute_dmap.hh
    src/Image2D.hh
)

add_executable(test_external_modification.out
    src/test_external_modification.cc
    src/Image2D.hh
)

add_executable(test_fill.out
    src/test_fill.cc
    src/Image2D.hh
    src/FunImage.hh
)

add_executable(test_FunImage.out
    src/test_FunImage.cc
    src/FunImage.hh
    src/compute_dmap.hh
    src/Image2D.hh
)

# add_executable(test_image_if.out
#     src/test_image_if.cc
#     src/image_if.hh
#     src/Image2D.hh
# )

# add_executable(test_compute_dmap__v2.out
#     src/test_compute_dmap__v2.cc
#     src/Image2D.hh
#     src/image_if.hh
#     src/helper.hh
#     src/compute_dmap__v2.hh
# )

# add_executable(music_score_analysis.out
#     src/music_score_analysis.cc
#     src/analyze.hh
#     src/Image2D.hh
#     src/image_if.hh
#     src/helper.hh
#     src/compute_dmap__v2.hh
# )
