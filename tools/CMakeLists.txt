
find_package(glog 0.3.5 REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS}) 

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(DICTBUILDER_SRCS
	pinyinime_dictbuilder.cpp
)

add_executable(dictbuilder ${DICTBUILDER_SRCS})

set(LINKER_LIBS "")
list(APPEND LINKER_LIBS glog::glog)
list(APPEND LINKER_LIBS googlepinyin-static)
list(APPEND LINKER_LIBS  ${GTEST_BOTH_LIBRARIES})
target_link_libraries(dictbuilder ${LINKER_LIBS})

