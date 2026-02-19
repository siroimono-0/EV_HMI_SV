cmake_minimum_required(VERSION 3.19)
project(HttpSv LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS HttpServer)

qt_standard_project_setup()

qt_add_executable(HttpSv
    main.cpp
    HttpSv.h HttpSv.cpp
)

target_link_libraries(HttpSv
    PRIVATE
        Qt::Core
)
target_link_libraries(HttpSv PRIVATE Qt6::Core)
target_link_libraries(HttpSv PRIVATE Qt6::HttpServer)

include(GNUInstallDirs)

install(TARGETS HttpSv
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
