
find_package(glog 0.3.5 REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS}) 

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(SRCS main.cpp)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main ${SRCS})

set(LINKER_LIBS "")
list(APPEND LINKER_LIBS glog::glog)
list(APPEND LINKER_LIBS googlepinyin-static)

target_link_libraries(main ${LINKER_LIBS})
if (WIN32)
	target_link_libraries(main ${PROJECT_SOURCE_DIR}/pthread/lib/x86/pthreadVC2.lib)
elseif (APPLE)
	target_link_libraries(main pthread)
endif()
