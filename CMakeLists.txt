cmake_minimum_required(VERSION 2.4.4...3.5.0)
project(fp)

option(FP_INCLUDED_TEST "include test" OFF)

add_library(fp STATIC 
	src/d185.c
	src/data.c
	src/xml.c
)
target_include_directories(fp
	PUBLIC 
	${PROJECT_SOURCE_DIR}/src
	${LIBXML2_INCLUDE_DIRS}
)
target_link_libraries(fp
	PRIVATE
	${LIBXML2_LIBRARIES} # require build
)

if(FP_INCLUDED_TEST)
	add_executable(test
		${PROJECT_SOURCE_DIR}/src/cli.c
	)
	target_link_libraries(test
		PRIVATE
		fp
	)
endif()
