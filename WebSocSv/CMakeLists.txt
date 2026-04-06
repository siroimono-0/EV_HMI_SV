cmake_minimum_required(VERSION 3.16)

project(WebSocSv VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Network)
# find_package(Qt6 REQUIRED COMPONENTS QuickEffects)
# find_package(Qt6 REQUIRED COMPONENTS QuickControls2)


find_package(Qt6 COMPONENTS Sql REQUIRED)


qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appWebSocSv
    main.cpp
)

target_sources(appWebSocSv PRIVATE
    ./Cpp_Module/Cpp_Module.h
    ./Cpp_Module/Cpp_Module.cpp
    ./Cpp_Module/StatModel.h
    ./Cpp_Module/StatModel.cpp
    ./Cpp_Module/Hub.h
    ./Cpp_Module/Hub.cpp
    ./Cpp_Module/WK_Soc.h
    ./Cpp_Module/WK_Soc.cpp
    ./Cpp_Module/DB_PostgreSQL.h
    ./Cpp_Module/DB_PostgreSQL.cpp
    ../Common/StatData.h

)
# qt_add_qml_module(appWebSocSv
    # URI WebSocSv
    # VERSION 1.0

    # QML_FILES
        # Main.qml
        # Start_page.qml
        # SV_info_page.qml
        # BackBtn.qml
        # StoreManagement.qml
        # ./Qml_Module/BackGround.qml
        # ./Qml_Module/Popup_Text.qml
        # ./Qml_Module/RecBtn.qml
        # ./Qml_Module/PopUp_CreateStore_DB.qml

    # SOURCES
        # ./Cpp_Module/Cpp_Module.h ./Cpp_Module/Cpp_Module.cpp
        # ./Cpp_Module/StatModel.h ./Cpp_Module/StatModel.cpp
        # ./Cpp_Module/Hub.h ./Cpp_Module/Hub.cpp
        # ./Cpp_Module/WK_Soc.h ./Cpp_Module/WK_Soc.cpp
        # ./Cpp_Module/DB_PostgreSQL.h ./Cpp_Module/DB_PostgreSQL.cpp
        # ../Common/StatData.h
# )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWebSocSv PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWebSocSv
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# target_link_libraries(appWebSocSv PRIVATE Qt6::Quick)
target_link_libraries(appWebSocSv PRIVATE Qt6::Core)
target_link_libraries(appWebSocSv PRIVATE Qt6::WebSockets)
target_link_libraries(appWebSocSv PRIVATE Qt6::Sql)
target_link_libraries(appWebSocSv PRIVATE Qt6::Network)
# target_link_libraries(appWebSocSv PRIVATE Qt6::QuickEffects)
# target_link_libraries(appWebSocSv PRIVATE Qt6::QuickControls2)

include(GNUInstallDirs)
install(TARGETS appWebSocSv
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



# add_custom_command(TARGET appWebSocSv POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different
    # "${PG_BIN_DIR}/libpq.dll"
    # $<TARGET_FILE_DIR:appWebSocSv>
# )

if(WIN32)
    # set(PG_BIN_DIR "C:/Program Files/PostgreSQL/18/bin")
    set(PG_DLL_PATH "C:/Program Files/PostgreSQL/18/bin/libpq.dll")

    if(EXISTS "${PG_DLL_PATH}")
        add_custom_command(TARGET appWebSocSv POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PG_DLL_PATH}"
            $<TARGET_FILE_DIR:appWebSocSv>
        )
    endif()

elseif(UNIX)
    find_library(PQ_LIB pq REQUIRED)
    message(STATUS "PQ_LIB = ${PQ_LIB}")
    target_link_libraries(appWebSocSv  PRIVATE ${PQ_LIB})
endif()




