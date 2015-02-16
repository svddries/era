cmake_minimum_required(VERSION 2.8.3)
project(era)

find_package(catkin REQUIRED COMPONENTS
    rgbd
)

# find_package(Boost REQUIRED COMPONENTS system program_options)
# find_package(PCL REQUIRED)
# find_package(OpenCV REQUIRED)

# ------------------------------------------------------------------------------------------------
#                                     ROS MESSAGES AND SERVICES
# ------------------------------------------------------------------------------------------------

# Generate messages
# add_message_files(
#    FILES
#    message1.msg
#    ...
# )

# Generate services
# add_service_files(
#    FILES
#    service1.srv
#    ...
# )

# Generate added messages and services with any dependencies listed here
# generate_messages(
#    DEPENDENCIES
#    geometry_msgs
#    ...
# )

# ------------------------------------------------------------------------------------------------
#                                          CATKIN EXPORT
# ------------------------------------------------------------------------------------------------

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bla
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

# ------------------------------------------------------------------------------------------------
#                                              BUILD
# ------------------------------------------------------------------------------------------------

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

SET(HEADER_FILES
    include/era/types.h
    include/era/buffer.h
    include/era/blackboard.h
    include/era/plugin.h
)

#add_library(era
#    include/era/buffer.h
#)
#target_link_libraries(era ${catkin_LIBRARIES})

# ------------------------------------------------------------------------------------------------
#                                               TEST
# ------------------------------------------------------------------------------------------------

add_executable(era_test
    test/test.cpp
    ${HEADER_FILES}
)
#target_link_libraries(exec_nama ${catkin_LIBRARIES})


