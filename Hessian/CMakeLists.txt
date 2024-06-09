find_package(OpenCV REQUIRED)
# link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/../libopencv_world460.dll)

aux_source_directory(src FINGER_DIRS)
add_library(LibFrangi STATIC ${FINGER_DIRS} )

target_include_directories(LibFrangi PUBLIC  include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(LibFrangi ${OpenCV_LIBS})  #OpenCV链接

add_executable(Frangi  ${FINGER_DIRS} main.cpp )
target_include_directories(Frangi PUBLIC include ${OpenCV_INCLUDE_DIRS} ) #类头文件
target_link_libraries(Frangi ${OpenCV_LIBS})  #OpenCV链接
