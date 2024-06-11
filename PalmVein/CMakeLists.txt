find_package(OpenCV REQUIRED)

aux_source_directory(src PALM_DIRS)
add_library(PalmVein STATIC ${PALM_DIRS})

target_include_directories(PalmVein PUBLIC include ${OpenCV_INCLUDE_DIRS} ) #类头文件
target_link_libraries(PalmVein ${OpenCV_LIBS} LibFrangi )  #OpenCV链接

