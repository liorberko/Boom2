cmake_minimum_required(VERSION 3.0.0)
project(Boom2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Boom2 TimeCheck.cpp lecture.cpp lectureKey.cpp course.cpp boom.cpp library2.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
