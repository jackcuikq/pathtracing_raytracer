cmake_minimum_required(VERSION 3.10)

project (raytracer)

set ( CMAKE_CXX_STANDARD 11 )

set ( SOURCE_RAYTRACER 
	src/main.cpp
	src/inc/color.h
	src/inc/vec3.h
	src/inc/ray.h
	)

add_executable(raytracer ${SOURCE_RAYTRACER})

include_directories(src/inc)