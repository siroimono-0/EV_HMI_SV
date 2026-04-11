cmake_minimum_required(VERSION 3.16)

project(HMI VERSION 0.1 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/External_Library/crc16.c
    PROPERTIES LANGUAGE C
)



find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS QuickEffects)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
find_package(Qt6 COMPONENTS Sql REQUIRED)





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
        Card_Ready.qml
        Card_Socket.qml
        Charging_Ready.qml
        Card_Failed.qml
        Charging_Monitoring.qml
        Input_Time.qml
        Input_Won.qml
        Input_Kwh.qml
        Charging_Complet.qml
        Ems_Nomal.qml
        Ems_Charging.qml
        Maintenance.qml
        Test.qml
        ./Qml_Module/Popup_Text.qml
        ./Qml_Module/Keypad_Number.qml
        ./Qml_Module/BackGround.qml
        ./Qml_Module/RecBtn.qml
        ./Qml_Module/Circle_Number.qml
        ./Qml_Module/BtnGreen.qml
        ./Qml_Module/NeonLabel.qml
        ./Qml_Module/BackGround_Plus.qml
        ./Qml_Module/Keypad_New.qml
        ./Qml_Module/Rec_Number.qml
        ./Qml_Module/BackGround_Card.qml
        ./Qml_Module/BackGround_Amount.qml
        ./Qml_Module/BtnLed.qml
        ./Qml_Module/Popup_Text_card_err.qml

    SOURCES
        ./Cpp_Module/Cpp_Module.h ./Cpp_Module/Cpp_Module.cpp
        ./Cpp_Module/WK_WebSocket.h ./Cpp_Module/WK_WebSocket.cpp
        ./Cpp_Module/WK_Serial.h ./Cpp_Module/WK_Serial.cpp
        ./Cpp_Module/StatStore.h ./Cpp_Module/StatStore.cpp
        ../Common/StatData.h
        ./External_Library/checksum.h ./External_Library/crc16.c

    RESOURCES
        ./images/combo.svg
        ./images/memberCard.svg
        ./images/creditCard.svg
        ./images/time.svg
        ./images/won.svg
        ./images/voltage.svg
        ./images/battery.svg
        ./images/cardReady.svg
        ./images/cardInsert.svg
        ./images/charging_ready.svg
        ./images/voltage_green.svg
        ./images/settlement_delay.svg
        ./images/warning.svg
        ./images/maintenance.svg
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
target_link_libraries(appHMI PRIVATE Qt6::Sql)

include(GNUInstallDirs)
install(TARGETS appHMI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(WIN32)
    set(PG_DLL_PATH "C:/Program Files/PostgreSQL/18/bin/libpq.dll")

    if(EXISTS "${PG_DLL_PATH}")
        add_custom_command(TARGET appHMI POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PG_DLL_PATH}"
            $<TARGET_FILE_DIR:appHMI>
        )
    endif()

elseif(UNIX)
    find_library(PQ_LIB pq REQUIRED)
    message(STATUS "PQ_LIB = ${PQ_LIB}")
    target_link_libraries(appHMI PRIVATE ${PQ_LIB})
endif()
