find_package(OpenCV REQUIRED)

aux_source_directory(src PALM_DIRS)
add_library(Palm STATIC ${PALM_DIRS})

target_include_directories(Palm PUBLIC include ${OpenCV_INCLUDE_DIRS} ) #类头文件
target_link_libraries(Palm ${OpenCV_LIBS} LibFrangi )  #OpenCV链接

