cmake_minimum_required(VERSION 2.6)
project(Projet)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

add_executable(test_image2d.out
    src/test_image2d.cc
    src/image2d.hh
)

add_executable(test_compute_dmap.out
    src/test_compute_dmap.cc
    src/compute_dmap.hh
    src/image2d.hh
)

add_executable(test_external_modification.out
    src/test_external_modification.cc
    src/image2d.hh
)

add_executable(test_fill.out
    src/test_fill.cc
    src/image2d.hh
    src/fun_image.hh
)

add_executable(test_fun_image.out
    src/test_fun_image.cc
    src/fun_image.hh
    src/compute_dmap.hh
    src/image2d.hh
)

# add_executable(test_image_if.out
#     src/test_image_if.cc
#     src/image_if.hh
#     src/image2d.hh
# )

# add_executable(test_compute_dmap__v2.out
#     src/test_compute_dmap__v2.cc
#     src/image2d.hh
#     src/image_if.hh
#     src/helper.hh
#     src/compute_dmap__v2.hh
# )

# add_executable(music_score_analysis.out
#     src/music_score_analysis.cc
#     src/analyze.hh
#     src/image2d.hh
#     src/image_if.hh
#     src/helper.hh
#     src/compute_dmap__v2.hh
# )
