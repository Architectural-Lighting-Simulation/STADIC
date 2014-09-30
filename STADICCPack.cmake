set(CPACK_PACKAGE_VENDOR "The Pennsylvania State University")
set(CPACK_PACKAGE_CONTACT "${CPACK_PACKAGE_VENDOR} <something@psu.edu>")

set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_VERSION_PATCH}")
set(FULL_VERSION_STRING ${STADIC_VERSION}.${CMAKE_VERSION_BUILD})

if(CMAKE_CL_64)
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${FULL_VERSION_STRING}-Win64")
  #set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
elseif(UNIX AND NOT APPLE AND NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${FULL_VERSION_STRING}-${CMAKE_SYSTEM_NAME}-x86")
else()
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${FULL_VERSION_STRING}-${CMAKE_SYSTEM_NAME}")
endif()

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simulation Tool for Architectural Daylighting and Integrated Controls")

set(CPACK_WIX_UPGRADE_GUID 65D84AD9-6793-4656-99F6-592D892A8D58)
set(CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/installer/banner.bmp")
set(CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/installer/background.bmp")

#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/CPack.Description.txt")
#set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/CPack.Description.txt")
#set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/CPack.Welcome.txt")

set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "STADIC\n ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
#set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://psu.edu")
set(CPACK_DEBIAN_PACKAGE_SECTION "science")
#set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/CMake/debian/postinst")

if(WIN32)
  set(CPACK_GENERATOR "WIX")
endif()

# Maybe this should go elsewhere

if(MINGW)
  get_filename_component(MinGW_Path ${CMAKE_CXX_COMPILER} PATH)
  set(MINGW_RUNTIME_LIBS ${MinGW_Path}/libgcc_s_dw2-1.dll
                         ${MinGW_Path}/libstdc++-6.dll
                         ${MinGW_Path}/libwinpthread-1.dll)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${MINGW_RUNTIME_LIBS})
endif()

include(InstallRequiredSystemLibraries)

include(CPack)

