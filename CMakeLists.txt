cmake_minimum_required(VERSION 3.6)

project(x2goclient VERSION "4.1.2.5" LANGUAGES CXX)
set(PROJECT_LABEL "x2goclient")

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

#if (NOT CMAKE_CROSSCOMPILING)
#    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
#endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
if(WIN32)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools Network Multimedia Svg WinExtras REQUIRED)
else()
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools Network Multimedia Svg REQUIRED)
endif()

# look for libssh
find_package(libssh CONFIG REQUIRED)

# look for Leptonica and Tesseract libraries
# if(WIN32)
#     find_package(Leptonica CONFIG REQUIRED)
#     find_package(Tesseract CONFIG REQUIRED)
# else()
#     find_library(leptonica_lib NAMES lept PATHS /usr/lib/x86_64-linux-gnu)
#     find_library(tesseract_lib NAMES tesseract PATHS /usr/lib/x86_64-linux-gnu)
#     set(leptonica_includes /usr/include/leptonica)
#     set(Leptonica_INCLUDE_DIRS ${leptonica_includes})
#     set(Leptonica_LIBRARIES ${leptonica_lib})
#     set(tesseract_includes /usr/include/tesseract)
#     set(Tesseract_INCLUDE_DIRS ${tesseract_includes})
#     set(Tesseract_LIBRARIES ${tesseract_lib})
# endif()

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
    add_executable(${PROJECT_NAME} WIN32 ${X2GOCLIENT_SRC} ${APP_ICON_RESOURCE_WINDOWS})
else()
    add_executable(${PROJECT_NAME} ${X2GOCLIENT_SRC})
endif()

# localization
set(X2GOCLIENT_TS
    translations/${PROJECT_NAME}_ro.ts
    translations/${PROJECT_NAME}_pl.ts
    translations/${PROJECT_NAME}_mk.ts
)

qt_create_translation(TS_FILES ${CMAKE_SOURCE_DIR} ${X2GOCLIENT_TS})
set_source_files_properties(${X2GOCLIENT_TS} PROPERTIES OUTPUT_LOCATION ${CMAKE_BINARY_DIR})
#qt_add_translation(QM_FILES ${X2GOCLIENT_TS}})

add_custom_target(QMS ALL DEPENDS ${QM_FILES})
add_custom_target(TRS ALL DEPENDS ${TS_FILES})

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

print_all_variables()

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

get_property(propVal TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)
if (propVal)
    message("${PROJECT_NAME}-INCLUDE_DIRECTORIES:   ${propVal}")
endif()

get_target_property(propVal ${PROJECT_NAME} SOURCES)
if (propVal)
    message("${PROJECT_NAME}-sources:   ${propVal}")
endif()

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
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::WinExtras AdvAPI32.lib shell32.lib User32.lib Ws2_32.lib)
else()
endif()

set(CPACK_PACKAGE_VENDOR "vlsi.etti.tuiasi.ro")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_LABEL}: X2Go client")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)

if (WIN32)
    include(Windeployqt)
    windeployqt(${PROJECT_NAME} /)
    set(CPACK_GENERATOR NSIS)
else()
    set(CPACK_GENERATOR ZIP)
endif()

# Install the executable
install(TARGETS ${PROJECT_NAME}
    ARCHIVE  DESTINATION /
    LIBRARY  DESTINATION /
    RUNTIME  DESTINATION /
)

# install(FILES

#     DESTINATION /)

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
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "X2Go Client: open X2Go remote sessions")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "x2goclient")
set(CPACK_NSIS_MUI_ICON ${CMAKE_SOURCE_DIR}/res/img/icons/x2go-win-48.ico)
set(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_SOURCE_DIR}/res/img/icons/x2go-win-48.ico)
set(CPACK_NSIS_CREATE_ICONS "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_LABEL}.lnk' '$instdir\\\\${PROJECT_NAME}.exe'")
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "CreateShortcut '$desktop\\\\${PROJECT_LABEL}.lnk' '$instdir\\\\${PROJECT_NAME}.exe'")
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "Delete '$desktop\\\\${PROJECT_LABEL}.lnk'")
set(CPACK_NSIS_HELP_LINK "https://vlsi.etti.tuiasi.ro/")
set(CPACK_NSIS_URL_INFO_ABOUT "https://vlsi.etti.tuiasi.ro/")
set(CPACK_NSIS_CONTACT "webmaster@vlsi.etti.tuiasi.ro")
include(CPack)
