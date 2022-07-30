cmake_minimum_required(VERSION 3.0)

project(logc
	VERSION 0.1
	DESCRIPTION "logc - small and simple c logger library"
	LANGUAGES C)

if(NOT UNIX)
	message(FATAL_ERROR "Your system is not unix. Fail to build.")
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_RELEASE "-std=c99 -O2 -DNDEBUG")

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_C_FLAGS_DEBUG "-std=c99 -Wall -Wextra -Werror -g -O0 -Wpedantic -Wshadow -Wvla -Wpointer-arith -Wwrite-strings -Wfloat-equal -Wcast-align -Wcast-qual -Wbad-function-cast -Wstrict-overflow=4 -Wunreachable-code -Wformat=2 -Wundef -Wstrict-prototypes -Wold-style-definition -Wconversion -Wshift-overflow=2 -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -Wlogical-op -Wcast-align=strict -Wduplicated-cond -Wjump-misses-init -Wstringop-overflow")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_C_FLAGS_DEBUG "-std=c99 -Wall -Wextra -Werror -g -O0 -Wpedantic -Wshadow -Wvla -Wpointer-arith -Wwrite-strings -Wfloat-equal -Wcast-align -Wcast-qual -Wbad-function-cast -Wstrict-overflow=4 -Wunreachable-code -Wformat=2 -Wundef -Wstrict-prototypes -Wold-style-definition -Wconversion -Wshift-overflow -Wredundant-decls -Wnested-externs -Wmissing-include-dirs")
else()
	message(FALAT_ERROR "Clang or GCC is not installed on your system. Fail to build.")
endif()


set(LIB logc)
set(SOURCE logc.c)
set(HEADER logc.h)

set(TEST testc_logc)
set(TEST_SOURCE tests/test.c)

add_library(${LIB} STATIC ${SOURCE} ${HEADER})
add_library(lib::logc ALIAS ${LIB})

target_include_directories(${LIB} PRIVATE "${CMAKE_SOURCE_DIR}")

add_executable(${TEST} ${TEST_SOURCE})
target_link_libraries(${TEST} PRIVATE ${LIB})
target_include_directories(${TEST} PRIVATE "${CMAKE_SOURCE_DIR}")

install(TARGETS ${LIB} DESTINATION lib)
install(FILES ${HEADER} DESTINATION include)

