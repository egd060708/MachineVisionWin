cmake_minimum_required(VERSION 3.5)
project(Vein) #指静脉
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(Finger)
add_subdirectory(Palm)
# add_subdirectory(Math)
add_subdirectory(FrangiFilter)

find_package(OpenCV REQUIRED)
# link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_world460.dll)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_plot460.dll)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_imgproc460.dll)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_highgui460.dll)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_core460.dll)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libopencv_imgcodecs460.dll)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_world460.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_plot460.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_imgproc460.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_highgui460.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_core460.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libopencv_imgcodecs460.dll DESTINATION ${CMAKE_BINARY_DIR})

add_executable(FingerVein fingervein.cpp)
target_include_directories( FingerVein PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(FingerVein ${OpenCV_LIBS} Finger )

add_executable(PalmVein palmvein.cpp)
target_include_directories( PalmVein PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(PalmVein ${OpenCV_LIBS}  Palm)
