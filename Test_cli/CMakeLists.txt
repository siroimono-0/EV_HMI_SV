cmake_minimum_required(VERSION 3.16)

project(Test_cli VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appTest_cli
    main.cpp
)

qt_add_qml_module(appTest_cli
    URI Test_cli
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES Cpp_cli.h Cpp_cli.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTest_cli PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTest_cli
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTest_cli
    PRIVATE Qt6::Quick
)
target_link_libraries(appTest_cli PRIVATE Qt6::Core)
target_link_libraries(appTest_cli PRIVATE Qt6::WebSockets)

include(GNUInstallDirs)
install(TARGETS appTest_cli
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
