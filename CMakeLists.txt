cmake_minimum_required(VERSION 3.5)
project(Vein) #指静脉
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(Finger)
add_subdirectory(Hand)
# add_subdirectory(Math)
add_subdirectory(Hessian)

find_package(OpenCV REQUIRED)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_world460.dll)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_world460.dll DESTINATION ${CMAKE_BINARY_DIR})

add_executable(FingerVein fingervein.cpp)
target_include_directories( FingerVein PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(FingerVein ${OpenCV_LIBS} Finger )

add_executable(HandVein handvein.cpp)
target_include_directories( HandVein PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(HandVein ${OpenCV_LIBS}  Hand)
