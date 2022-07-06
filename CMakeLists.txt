cmake_minimum_required(VERSION 3.0)

project(logc
	VERSION 0.1
	DESCRIPTION "logc - small and simple c logger library"
	LANGUAGES C)

if(NOT UNIX)
	message(FATAL_ERROR "Your system is not unix. Fail to build.")
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE DEBUG)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -Wextra -Werror -Wpedantic -g -O0 -DDEBUG=1")
	set(CMAKE_C_FLAGS_RELEASE "-std=c11 -O1")
endif()

set(LIB logc)
set(SOURCE logc.c)
set(HEADER logc.h)

set(TEST1 testc_logc)
set(TEST1_SOURCE tests/test.c)

#set(TEST2 testcpp_logc)
#set(TEST2_SOURCE tests/test.cpp)

add_library(${LIB} STATIC ${SOURCE} ${HEADER})
add_library(lib::logc ALIAS ${LIB})

target_include_directories(${LIB} PRIVATE "${CMAKE_SOURCE_DIR}")

add_executable(${TEST1} ${TEST1_SOURCE})
target_link_libraries(${TEST1} PRIVATE ${LIB})

#add_executable(${TEST2} ${TEST2_SOURCE})
#target_link_libraries(${TEST2} PRIVATE ${LIB})

install(TARGETS ${LIB} DESTINATION lib)
install(FILES ${HEADER} DESTINATION include)

