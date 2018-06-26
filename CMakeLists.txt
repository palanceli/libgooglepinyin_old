project(googlepinyin)
cmake_minimum_required(VERSION 2.6)

option(ENABLE_STATIC "Build static library" False)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

if(NOT DEFINED LIB_INSTALL_DIR)
    set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()

set(prefix      ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX})
set(bindir ${prefix}/bin)
set(libdir ${LIB_INSTALL_DIR})
set(datadir ${CMAKE_INSTALL_PREFIX}/share)
set(localedir ${CMAKE_INSTALL_PREFIX}/share/locale)
set(includedir  ${CMAKE_INSTALL_PREFIX}/include/googlepinyin)
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAG}")

add_subdirectory(src)
add_subdirectory(exe)
add_subdirectory(tools)
add_subdirectory(include)
add_subdirectory(data)


# 构建unittest的可执行项目
add_subdirectory(googletest)
include_directories(${PROJECT_SOURCE_DIR}/googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

# 收集各子项的*.cpp、*.h文件
foreach ( folder exe src tools)
  file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/${folder}/*.cpp" "${PROJECT_SOURCE_DIR}/${folder}/*.h")
  list(APPEND ALL_SRC ${SRC})
endforeach(folder)

# 屏蔽main函数，因为gtest_main已经有了
LIST(REMOVE_ITEM ALL_SRC "${PROJECT_SOURCE_DIR}/exe/main.cpp")
LIST(REMOVE_ITEM ALL_SRC "${PROJECT_SOURCE_DIR}/tools/pinyinime_dictbuilder.cpp")
add_executable(myexe_test ${ALL_SRC})
target_link_libraries(myexe_test gtest_main)
