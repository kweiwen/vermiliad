# Install script for directory: /Users/kweiwen/Documents/vermiliad/VST_SDK/VST3_SDK

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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
  # Include the install script for each subdirectory.
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/vstgui4/vstgui/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/pluginterfaces/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/base/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/public.sdk/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/public.sdk/source/vst/interappaudio/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/my_plugins/build/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/public.sdk/samples/vst/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/public.sdk/source/vst/auwrapper/again/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/public.sdk/source/vst/auv3wrapper/cmake_install.cmake")
  include("/Users/kweiwen/Documents/vermiliad/VST_SDK/build/public.sdk/samples/vst-hosting/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/kweiwen/Documents/vermiliad/VST_SDK/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
