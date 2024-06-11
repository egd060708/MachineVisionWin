find_package(OpenCV REQUIRED)

aux_source_directory(src FINGER_DIRS)
add_library(FingerVein STATIC ${FINGER_DIRS})

target_include_directories(FingerVein PUBLIC include ${OpenCV_INCLUDE_DIRS} ) #类头文件
target_link_libraries(FingerVein ${OpenCV_LIBS} LibFrangi)  #OpenCV链接


