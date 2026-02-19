cmake_minimum_required(VERSION 3.19)
project(Admin LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

qt_standard_project_setup()

qt_add_executable(Admin
    WIN32 MACOSX_BUNDLE
    main.cpp
    Admin.cpp
    Admin.h
    Admin.ui
    Dia_Register.h Dia_Register.cpp Dia_Register.ui
    ./CppModule/WK_soc.h CppModule/WK_soc.cpp

)

target_link_libraries(Admin
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(Admin PRIVATE Qt6::Core)
target_link_libraries(Admin PRIVATE Qt6::WebSockets)

include(GNUInstallDirs)

install(TARGETS Admin
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Admin
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
