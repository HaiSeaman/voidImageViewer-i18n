# Install script for directory: D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/libheif")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/plugins/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/Release/heif.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libheif" TYPE FILE FILES
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_export.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_library.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_image.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_color.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_error.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_plugin.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_properties.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_regions.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_items.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_sequences.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_tai_timestamps.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_brands.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_metadata.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_aux_images.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_entity_groups.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_security.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_encoding.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_decoding.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_image_handle.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_context.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_tiling.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_components.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_uncompressed.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_text.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_omaf.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/libheif-1.23.1/libheif/api/libheif/heif_cxx.h"
    "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/heif_version.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif/libheif-config.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif/libheif-config.cmake"
         "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/CMakeFiles/Export/5cd8613eea38798f9c35b1a25e1b106b/libheif-config.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif/libheif-config-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif/libheif-config.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif" TYPE FILE FILES "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/CMakeFiles/Export/5cd8613eea38798f9c35b1a25e1b106b/libheif-config.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif" TYPE FILE FILES "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/CMakeFiles/Export/5cd8613eea38798f9c35b1a25e1b106b/libheif-config-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libheif" TYPE FILE FILES "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/libheif-config-version.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/AI/Github/voidImageViewer-master/voidImageViewer-master/third_party/build-heif/libheif/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
