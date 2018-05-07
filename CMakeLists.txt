cmake_minimum_required(VERSION 2.8.7)

project(HBACforNRP)

find_package( Boost REQUIRED COMPONENTS date_time )

set(HBACforNRP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(HBACforNRP_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${HBACforNRP_INCLUDE_DIR})
include_directories(${HBACforNRP_SRC_DIR})

add_executable(nrp
               ${HBACforNRP_SRC_DIR}/main.cpp
	       ${HBACforNRP_SRC_DIR}/scheduling_period.cpp
	       ${HBACforNRP_SRC_DIR}/scheduling_period/shift.cpp
	       ${HBACforNRP_SRC_DIR}/scheduling_period/contract.cpp
	       ${HBACforNRP_SRC_DIR}/scheduling_period/pattern.cpp
               ${HBACforNRP_SRC_DIR}/scheduling_period/employee.cpp
               ${HBACforNRP_SRC_DIR}/roster.cpp
	       ${HBACforNRP_SRC_DIR}/objective_function.cpp
	       ${HBACforNRP_SRC_DIR}/neighbourhood.cpp
	       ${HBACforNRP_SRC_DIR}/HABC.cpp)

target_link_libraries(nrp Boost::date_time)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fopenmp -std=gnu++17 -Wall -Wextra -pedantic")
