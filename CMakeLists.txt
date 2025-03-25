cmake_minimum_required(VERSION 3.5.0)
project(fp)

option(FP_INCLUDE_CLI "include cli" OFF)

if(FP_INCLUDE_CLI)
	set(CMAKE_C_FLAGS "-g")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)

	add_executable(test
		${PROJECT_SOURCE_DIR}/src/cli.c
	)
	target_link_libraries(test
		PRIVATE
		fp
	)
endif()

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
