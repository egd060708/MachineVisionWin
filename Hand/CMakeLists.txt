find_package(OpenCV REQUIRED)

aux_source_directory(src HAND_DIRS)
add_library(Hand STATIC ${HAND_DIRS})

target_include_directories(Hand PUBLIC include ${OpenCV_INCLUDE_DIRS} ) #类头文件
target_link_libraries(Hand ${OpenCV_LIBS} LibFrangi )  #OpenCV链接

