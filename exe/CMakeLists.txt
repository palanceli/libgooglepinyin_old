set(SRCS main.cpp)

add_executable(main ${SRCS})
target_link_libraries(main googlepinyin-static)

