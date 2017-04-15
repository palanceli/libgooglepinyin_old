set(SRCS main.cpp)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main ${SRCS})
target_link_libraries(main googlepinyin-static)
target_link_libraries(main ${PROJECT_SOURCE_DIR}/pthread/lib/x86/pthreadVC2.lib)

