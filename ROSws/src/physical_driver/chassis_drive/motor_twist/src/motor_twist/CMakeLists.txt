cmake_minimum_required(VERSION 3.5)
project(motor_twist)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE Release)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(ALIAS_ROS2_TF2)
  add_definitions(-Dtf2=ros2_tf2)
  add_definitions(-Dtf2_ros=ros2_tf2_ros)
  add_definitions(-Dmessage_filters=ros2_message_filters)
endif()
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package( geometry_msgs REQUIRED)
find_package( rclcpp REQUIRED)
find_package( sensor_msgs REQUIRED)
include_directories("include/motor_twist")
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# Node
add_executable(motor_twist 
src/main.cpp
src/motor_twist.cpp
src/motor_twist_data.cpp
src/ros2nodeinterface.cpp
src/slros2_initialize.cpp
src/slros_busmsg_conversion.cpp
src/slros2_generic_param.cpp
)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_compile_options(motor_twist PUBLIC 
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -Wall -Wextra -Wpedantic
  >)
endif()
target_compile_options(motor_twist PRIVATE
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -DMODEL=motor_twist
  -DNUMST=1
  -DNCSTATES=0
  -DHAVESTDIO
  -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0
  -DCLASSIC_INTERFACE=0
  -DALLOCATIONFCN=0
  -DTID01EQ=0
  -DONESTEPFCN=1
  -DTERMFCN=1
  -DMULTI_INSTANCE_CODE=1
  -DINTEGER_CODE=0
  -DMT=0
  -DROS2_PROJECT
  -DSTACK_SIZE=64
  -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__
  -DRT
  -fpermissive  >
  )
ament_target_dependencies(
  motor_twist
  "geometry_msgs"
  "rclcpp"
  "sensor_msgs"
)
target_include_directories(motor_twist PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(motor_twist 
    "/opt/MATLAB/R2023b/sys/os/glnxa64/orig/libstdc++.so.6"
	${CMAKE_DL_LIBS}
    )
install(TARGETS motor_twist
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
ament_export_include_directories(
  include
)
foreach(file_i ${CUDA_BINS})
add_custom_command(
                   TARGET motor_twist
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/motor_twist_ert_rtw/${file_i}
				   )
add_custom_command(
                   TARGET motor_twist
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/codegen/exe/motor_twist/${file_i}
				   )				   
endforeach(file_i)
ament_package()
# Generated on Sat Apr 13 12:33:48 2024
