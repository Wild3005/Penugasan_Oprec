cmake_minimum_required(VERSION 3.0)

project( penugasan )

find_package( OpenCV REQUIRED )

add_executable( penugasan src/main.cpp )

##add_executable( oke1 src/progrobot.cpp )

target_link_libraries( penugasan ${OpenCV_LIBS} )
