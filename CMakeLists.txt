cmake_minimum_required(VERSION 2.8.3)
project(era)

include_directories(
    include
)

SET(HEADER_FILES
    include/era/types.h
    include/era/buffer.h
    include/era/blackboard.h
    include/era/plugin.h
)

# ------------------------------------------------------------------------------------------------
#                                               TEST
# ------------------------------------------------------------------------------------------------

add_executable(era_test
    test/test.cpp
    ${HEADER_FILES}
)
