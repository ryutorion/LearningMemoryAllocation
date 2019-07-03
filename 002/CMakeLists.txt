cmake_minimum_required(VERSION 3.14.0)

get_filename_component(DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(
	${DIR_NAME}
	main.cpp
)
