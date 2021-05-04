cmake_minimum_required(VERSION 3.10)

project (raytracer)

set ( CMAKE_CXX_STANDARD 17 )

set (RAYTRACER_INC
	code/inc/colour.h
	code/inc/vec3.h
	code/inc/ray.h
	code/inc/hittable_object.h
	code/inc/sphere.h
	code/inc/hittable_list.h
	code/inc/utility.h
	) 

set ( SOURCE_RAYTRACER 
	code/src/main.cpp
	code/src/sphere.cpp
	code/src/hittable_list.cpp
	)

add_executable(raytracer ${SOURCE_RAYTRACER} ${RAYTRACER_INC})

include_directories(code/inc)
