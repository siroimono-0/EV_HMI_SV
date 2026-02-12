cmake_minimum_required(VERSION 3.16)

project(HMI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS QuickEffects)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)




qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appHMI
    main.cpp
)

qt_add_qml_module(appHMI
    URI HMI
    VERSION 1.0
    QML_FILES
        Main.qml
        Start_page.qml
        HMI_main.qml
        Select_charge.qml
        Select_card.qml
        Select_amount.qml
        ./Qml_Module/Popup_Text.qml
        ./Qml_Module/Keypad_Number.qml
        ./Qml_Module/BackGround.qml
        ./Qml_Module/RecBtn.qml

    SOURCES
        ./Cpp_Module/Cpp_Module.h ./Cpp_Module/Cpp_Module.cpp
        ./Cpp_Module/WK_WebSocket.h ./Cpp_Module/WK_WebSocket.cpp
        ./Cpp_Module/WK_Serial.h ./Cpp_Module/WK_Serial.cpp
        ./Cpp_Module/StatStore.h ./Cpp_Module/StatStore.cpp
        ../Common/StatData.h
        QML_FILES Qml_Module/Circle_Number.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHMI PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHMI
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHMI
    PRIVATE Qt6::Quick
)
target_link_libraries(appHMI PRIVATE Qt6::Core)
target_link_libraries(appHMI PRIVATE Qt6::Core)
target_link_libraries(appHMI PRIVATE Qt6::Core)
target_link_libraries(appHMI  PRIVATE Qt6::WebSockets)
target_link_libraries(appHMI  PRIVATE Qt6::SerialPort)
target_link_libraries(appHMI PRIVATE Qt6::Core)
target_link_libraries(appHMI PRIVATE Qt6::QuickEffects)
target_link_libraries(appHMI PRIVATE Qt6::QuickControls2)

include(GNUInstallDirs)
install(TARGETS appHMI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
