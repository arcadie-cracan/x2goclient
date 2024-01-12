cmake_minimum_required(VERSION 3.6)

project(x2goclient VERSION "4.1.2.5" LANGUAGES CXX)
set(PROJECT_LABEL "X2Go Client")

set(CONTRIB_PATH ${CMAKE_SOURCE_DIR}/../x2goclient-contrib)
set(CONTRIB_VCXSRV_VERSION 1.20.6.0_bin)
set(CONTRIB_PULSE_VERSION 13.0-lp151.19.1_bin)
set(CONTRIB_CYGWIN_VERSION 20180615-1_bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/ui)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
if(WIN32)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools Network Multimedia Svg WinExtras REQUIRED)
else()
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools Network Multimedia Svg REQUIRED)
endif()

# look for libssh
find_package(libssh CONFIG REQUIRED)

set(X2GOCLIENT_SRC
    src/sharewidget.cpp
    src/settingswidget.cpp
    src/mediawidget.cpp
    src/configwidget.cpp
    src/sessionwidget.cpp
    src/connectionwidget.cpp
    src/configdialog.cpp
    src/editconnectiondialog.cpp
    src/exportdialog.cpp
    src/imgframe.cpp
    src/LDAPSession.cpp
    src/onmainwindow.cpp
    src/sessionbutton.cpp
    src/sessionmanagedialog.cpp
    src/sshmasterconnection.cpp
    src/sshprocess.cpp
    src/SVGFrame.cpp
    src/InteractionDialog.cpp
    src/userbutton.cpp
    src/x2gologdebug.cpp
    src/printprocess.cpp
    src/cupsprint.cpp
    src/cupsprintwidget.cpp
    src/cupsprintersettingsdialog.cpp
    src/printwidget.cpp
    src/printercmddialog.cpp
    src/printdialog.cpp
    src/wapi.cpp
    src/clicklineedit.cpp
    src/httpbrokerclient.cpp
    src/ongetpass.cpp
    src/x2gosettings.cpp
    src/brokerpassdlg.cpp
    src/contest.cpp
    src/xsettingswidget.cpp
    src/appdialog.cpp
    src/x2goutils.cpp
    src/helpdialog.cpp
    src/sessionexplorer.cpp
    src/folderbutton.cpp
    src/folderexplorer.cpp
    src/non_modal_messagebox.cpp
    src/help.cpp
    src/unixhelper.cpp
    src/compat.cpp
    src/pulsemanager.cpp
    src/x2goclient.cpp
    src/ui/cupsprintsettingsdialog.ui
    src/ui/cupsprintwidget.ui
    src/ui/printdialog.ui
    src/ui/printercmddialog.ui
    src/ui/printwidget.ui
    src/ui/xsettingsui.ui
    src/ui/brokerpassdialog.ui
    src/ui/contest.ui
    src/ui/appdialog.ui
    src/ui/helpdialog.ui
    src/ui/folderexplorer.ui
    src/configdialog.h
    src/editconnectiondialog.h
    src/exportdialog.h
    src/imgframe.h
    src/LDAPSession.h
    src/onmainwindow.h
    src/sessionbutton.h
    src/sessionmanagedialog.h
    src/sshmasterconnection.h
    src/sshprocess.h
    src/SVGFrame.h
    src/InteractionDialog.h
    src/userbutton.h
    src/x2goclientconfig.h
    src/x2gologdebug.h
    src/printprocess.h
    src/cupsprint.h
    src/cupsprintwidget.h
    src/cupsprintersettingsdialog.h
    src/printwidget.h
    src/printercmddialog.h
    src/printdialog.h
    src/wapi.h
    src/sessionwidget.h
    src/configwidget.h
    src/connectionwidget.h
    src/settingswidget.h
    src/mediawidget.h
    src/sharewidget.h
    src/clicklineedit.h
    src/httpbrokerclient.h
    src/ongetpass.h
    src/onmainwindow_privat.h
    src/x2gosettings.h
    src/brokerpassdlg.h
    src/contest.h
    src/xsettingswidget.h
    src/appdialog.h
    src/x2goutils.h
    src/helpdialog.h
    src/sessionexplorer.h
    src/folderbutton.h
    src/folderexplorer.h
    src/non_modal_messagebox.h
    src/help.h
    src/unixhelper.h
    src/compat.h
    src/pulsemanager.h
    res/resources.qrc
)

if (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/res/${PROJECT_NAME}.rc")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_executable(${PROJECT_NAME} ${X2GOCLIENT_SRC} ${APP_ICON_RESOURCE_WINDOWS})
    else()
        add_executable(${PROJECT_NAME} WIN32 ${X2GOCLIENT_SRC} ${APP_ICON_RESOURCE_WINDOWS})
        # add_executable(${PROJECT_NAME}-console ${X2GOCLIENT_SRC} ${APP_ICON_RESOURCE_WINDOWS})
    endif()
    add_executable(x2gohelper x2gohelper/x2gohelper.cpp)
else()
    add_executable(${PROJECT_NAME} ${X2GOCLIENT_SRC})
endif()

# localization
set(X2GOCLIENT_TS
    translations/${PROJECT_NAME}_ro.ts
    translations/${PROJECT_NAME}_pl.ts
    translations/${PROJECT_NAME}_mk.ts
)

set_source_files_properties(${X2GOCLIENT_TS} PROPERTIES OUTPUT_LOCATION "translations")
qt5_add_translation(X2GOCLIENT_QM ${X2GOCLIENT_TS})

add_custom_target(TRS ALL DEPENDS ${X2GOCLIENT_TS})
add_custom_target(QMS ALL DEPENDS ${X2GOCLIENT_QM})

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

#print_all_variables()

#target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Svg
    ssh
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    CFGCLIENT
    APP_NAME=\"${PROJECT_LABEL}\"
    APP_ID=\"${PROJECT_NAME}\"
    APP_VERSION=\"${PROJECT_VERSION}\"
    APP_ORG_NAME=\"${CPACK_PACKAGE_VENDOR}\"
    APP_ORG_DOMAIN=\"vlsi.etti.tuiasi.ro\"
)

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::WinExtras AdvAPI32.lib shell32.lib User32.lib Ws2_32.lib Shlwapi.lib)
else()
endif()

set(CPACK_PACKAGE_VENDOR "vlsi.etti.tuiasi.ro")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_LABEL}: X2Go client")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)

if (WIN32)
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        set(CMAKE_INSTALL_DEBUG_LIBRARIES ON)
    endif()
    include(Windeployqt)
    windeployqt(${PROJECT_NAME} /)
    set(CPACK_GENERATOR NSIS)
else()
    set(CPACK_GENERATOR ZIP)
endif()

# Install the executable
install(TARGETS ${PROJECT_NAME} x2gohelper
    ARCHIVE  DESTINATION /
    LIBRARY  DESTINATION /
    RUNTIME  DESTINATION /
)
list(TRANSFORM X2GOCLIENT_QM PREPEND ${CMAKE_BINARY_DIR}/)
install(FILES ${X2GOCLIENT_QM} DESTINATION /)

if(WIN32)
    install(DIRECTORY ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/ DESTINATION /
        FILES_MATCHING PATTERN "*.dll")
    install(DIRECTORY ${CONTRIB_PATH}/VcXsrv/${CONTRIB_VCXSRV_VERSION}/ DESTINATION VcXsrv)
    install(DIRECTORY ${CONTRIB_PATH}/pulse/${CONTRIB_PULSE_VERSION}/pulse DESTINATION /)
    install(DIRECTORY ${CONTRIB_PATH}/cygwin/${CONTRIB_CYGWIN_VERSION}/ DESTINATION /)
endif()
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_DISPLAY_NAME "X2Go Client")
set(CPACK_PACKAGE_VENDOR "vlsi.etti.tuiasi.ro")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${CMAKE_PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "X2Go Client: open X2Go remote sessions")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "x2goclient")
set(CPACK_PACKAGE_EXECUTABLES "x2goclient;X2Go Client")
#set(CPACK_CREATE_DESKTOP_LINKS x2goclient)
set(CPACK_NSIS_MUI_ICON ${CMAKE_SOURCE_DIR}/res/img/icons/x2go-win-48.ico)
set(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_SOURCE_DIR}/res/img/icons/x2go-win-48.ico)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl-2.0.txt")
set(CPACK_NSIS_MODIFY_PATH OFF)
set(CPACK_NSIS_HELP_LINK "https://vlsi.etti.tuiasi.ro/")
set(CPACK_NSIS_URL_INFO_ABOUT "https://vlsi.etti.tuiasi.ro/")
set(CPACK_NSIS_CONTACT "webmaster@vlsi.etti.tuiasi.ro")

set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
    CreateShortcut '$desktop\\\\${PROJECT_LABEL}.lnk' '$instdir\\\\${PROJECT_NAME}.exe'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'speed' 0x2
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'pack' '16m-jpeg'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'quality' 0x9
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'fstunnel' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'export' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'iconvto' 'UTF-8'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'iconvfrom' 'WINDOWS-1252'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'useiconv' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'fullscreen' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'multidisp' 'false'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'display' 0x1
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'width' 0x320
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'height' 0x258
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'dpi' 0x78
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'setdpi' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'xinerama' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'clipboard' 'both'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'usekbd' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'type' 'auto'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sound' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'soundsystem' 'pulse'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'startsoundsystem' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'soundtunnel' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'defsndport' 'true'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sndport' 0x1269
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'print' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'name' 'sirius'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'icon' ':/img/icons/128x128/x2gosession.png'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'host' 'sirius.etti.tuiasi.ro'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'user' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'key' ''
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshport' 0x16
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'autologin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'krblogin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'krbdelegation' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'kdrive' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'rootless' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'published' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'command' 'XFCE'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'rdpoptions' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'rdpserver' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'xdmcpserver' 'localhost'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'usesshproxy' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxytype' 'SSH'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxyuser' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxykeyfile' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxyhost' ''
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxyport' 0x16
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxysamepass' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxysameuser' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxyautologin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000001' 'sshproxykrblogin' 'false'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'speed' 0x2
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'pack' '16m-jpeg'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'quality' 0x9
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'fstunnel' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'export' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'iconvto' 'UTF-8'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'iconvfrom' 'WINDOWS-1252'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'useiconv' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'fullscreen' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'multidisp' 'false'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'display' 0x1
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'width' 0x320
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'height' 0x258
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'dpi' 0x78
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'setdpi' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'xinerama' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'clipboard' 'both'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'usekbd' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'type' 'auto'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sound' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'soundsystem' 'pulse'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'startsoundsystem' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'soundtunnel' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'defsndport' 'true'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sndport' 0x1269
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'print' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'name' 'canopus'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'icon' ':/img/icons/128x128/x2gosession.png'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'host' 'canopus.etti.tuiasi.ro'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'user' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'key' ''
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshport' 0x16
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'autologin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'krblogin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'krbdelegation' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'kdrive' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'rootless' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'published' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'command' 'XFCE'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'rdpoptions' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'rdpserver' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'xdmcpserver' 'localhost'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'usesshproxy' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxytype' 'SSH'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxyuser' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxykeyfile' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxyhost' ''
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxyport' 0x16
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxysamepass' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxysameuser' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxyautologin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000002' 'sshproxykrblogin' 'false'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'speed' 0x2
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'pack' '16m-jpeg'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'quality' 0x9
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'fstunnel' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'export' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'iconvto' 'UTF-8'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'iconvfrom' 'WINDOWS-1252'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'useiconv' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'fullscreen' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'multidisp' 'false'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'display' 0x1
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'width' 0x320
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'height' 0x258
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'dpi' 0x78
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'setdpi' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'xinerama' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'clipboard' 'both'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'usekbd' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'type' 'auto'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sound' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'soundsystem' 'pulse'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'startsoundsystem' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'soundtunnel' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'defsndport' 'true'
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sndport' 0x1269
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'print' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'name' 'arcturus'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'icon' ':/img/icons/128x128/x2gosession.png'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'host' 'arcturus.etti.tuiasi.ro'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'user' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'key' ''
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshport' 0x16
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'autologin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'krblogin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'krbdelegation' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'kdrive' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'rootless' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'published' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'command' 'XFCE'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'rdpoptions' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'rdpserver' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'xdmcpserver' 'localhost'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'usesshproxy' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxytype' 'SSH'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxyuser' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxykeyfile' ''
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxyhost' ''
    WriteRegDWORD HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxyport' 0x16
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxysamepass' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxysameuser' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxyautologin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\sessions\\\\2024010500000003' 'sshproxykrblogin' 'false'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'options' '-multiwindow -notrayicon -clipboard'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'onstart' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'noprimaryclip' 'true'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'optionswin' '-screen 0 %wx%h -notrayicon -clipboard'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'optionsfs' '-fullscreen -notrayicon -clipboard'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'optionssingle' '-multiwindow -notrayicon -clipboard'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'optionswholedisplay' '-nodecoration -notrayicon -clipboard -screen 0 @'
    WriteRegStr HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient\\\\settings' 'showStatus' 'true'
")
#    Delete '$desktop\\\\${PROJECT_LABEL}.lnk'
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
    DeleteRegKey HKEY_CURRENT_USER 'Software\\\\Obviously Nice\\\\x2goclient'
")
include(CPack)
