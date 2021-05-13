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
	src/inc/sample_renders.h
	) 

set ( SOURCE_RAYTRACER 
	src/main.cpp
	src/sphere.cpp
	src/hittable_object_list.cpp
	src/vec3.cpp
	)

find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(raytracer ${SOURCE_RAYTRACER} ${RAYTRACER_INC})

include_directories(src/inc)
