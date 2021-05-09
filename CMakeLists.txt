cmake_minimum_required(VERSION 3.10)

project (raytracer)

set ( CMAKE_CXX_STANDARD 17 )

set (RAYTRACER_INC
	src/inc/colour.h
	src/inc/vec3.h
	src/inc/ray.h
	src/inc/hittable_object.h
	src/inc/sphere.h
	src/inc/hittable_object_list.h
	src/inc/utility.h
	src/inc/camera.h
	src/inc/material.h
	) 

set ( SOURCE_RAYTRACER 
	src/main.cpp
	src/sphere.cpp
	src/hittable_list.cpp
	src/vec3.cpp
	)

add_executable(raytracer ${SOURCE_RAYTRACER} ${RAYTRACER_INC})

include_directories(src/inc)
