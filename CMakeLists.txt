cmake_minimum_required(VERSION 2.8.7)

project(HABCforNRP)

find_package( Boost REQUIRED COMPONENTS date_time )

set(HABCforNRP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(HABCforNRP_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${HABCforNRP_INCLUDE_DIR})
include_directories(${HABCforNRP_SRC_DIR})

add_executable(nrp
               ${HABCforNRP_SRC_DIR}/main.cpp
	       ${HABCforNRP_SRC_DIR}/scheduling_period.cpp
	       ${HABCforNRP_SRC_DIR}/scheduling_period/shift.cpp
	       ${HABCforNRP_SRC_DIR}/scheduling_period/contract.cpp
	       ${HABCforNRP_SRC_DIR}/scheduling_period/pattern.cpp
               ${HABCforNRP_SRC_DIR}/scheduling_period/employee.cpp
               ${HABCforNRP_SRC_DIR}/roster.cpp
	       ${HABCforNRP_SRC_DIR}/objective_function.cpp
	       ${HABCforNRP_SRC_DIR}/neighbourhood.cpp
	       ${HABCforNRP_SRC_DIR}/HABC.cpp)

target_link_libraries(nrp Boost::date_time)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fopenmp -std=gnu++17 -Wall -Wextra -pedantic")
