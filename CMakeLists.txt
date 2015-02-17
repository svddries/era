cmake_minimum_required(VERSION 2.8.3)
project(era)

include_directories(
    include
)

SET(HEADER_FILES
    include/era/types.h
    include/era/buffer.h
    include/era/blackboard.h
    include/era/component.h
    include/era/math/matrix.h
)

add_library(era
    src/engine.cpp
	${HEADER_FILES}
)

# ------------------------------------------------------------------------------------------------
#                                               TEST
# ------------------------------------------------------------------------------------------------

add_executable(era_test
    test/test.cpp
)
target_link_libraries(era_test era)
