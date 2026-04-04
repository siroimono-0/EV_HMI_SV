cmake_minimum_required(VERSION 3.19)
project(Admin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Qml)
find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS QuickWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(Admin
    WIN32 MACOSX_BUNDLE
    main.cpp
    Admin.cpp
    Admin.h
    Admin.ui
    Dia_Register.h Dia_Register.cpp Dia_Register.ui
    Dia_Register_HMI.h Dia_Register_HMI.cpp
    Dia_Register_HMI.ui
    Dia_membership_card.h Dia_membership_card.cpp
    Dia_membership_card.ui
    Dia_HMI.h Dia_HMI.cpp Dia_HMI.ui
    Dia_ad.h Dia_ad.cpp Dia_ad.ui

    ./CppModule/WK_soc.h CppModule/WK_soc.cpp
    ../Common/StatData.h
    CppModule/MD_charging_log.h CppModule/MD_charging_log.cpp
    CppModule/MD_hmi_current_stat.h
    CppModule/MD_hmi_current_stat.cpp
    CppModule/MD_hmi_device.h
    CppModule/MD_hmi_device.cpp
    CppModule/MD_membership_card.h
    CppModule/MD_membership_card.cpp
    CppModule/MD_membership_log.h
    CppModule/MD_membership_log.cpp
    CppModule/MD_store_user.h
    CppModule/MD_store_user.cpp

)

qt_add_qml_module(Admin
    URI Admin
    VERSION 1.0
    QML_FILES
        Qml_Module/View_ChargingLog.qml
        Qml_Module/BackGround.qml
        Qml_Module/Rec_header.qml
        Qml_Module/Rec_header_2.qml
        Qml_Module/Rec_data.qml
        Qml_Module/View_hmi_current_stat.qml
        Qml_Module/View_hmi_device.qml
        Qml_Module/View_membership_card.qml
        Qml_Module/View_membership_log.qml
        Qml_Module/View_store_user.qml
)

target_link_libraries(Admin
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(Admin PRIVATE Qt6::Core)
target_link_libraries(Admin PRIVATE Qt6::WebSockets)
target_link_libraries(Admin PRIVATE Qt6::Gui)
target_link_libraries(Admin PRIVATE Qt6::Qml)
target_link_libraries(Admin PRIVATE Qt6::Quick)
target_link_libraries(Admin PRIVATE Qt6::QuickWidgets)
target_link_libraries(Admin PRIVATE Qt6::Core)
target_link_libraries(Admin PRIVATE Qt6::Core)
target_link_libraries(Admin PRIVATE Qt6::Widgets)
target_link_libraries(Admin PRIVATE Qt6::Core)
target_link_libraries(Admin PRIVATE Qt6::Core)

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
