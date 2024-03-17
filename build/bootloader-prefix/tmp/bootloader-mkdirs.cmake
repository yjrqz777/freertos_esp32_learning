# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/Espressif/frameworks/esp-idf-v5.0.2/components/bootloader/subproject"
  "E:/Documents/esp32/code/user/hello_world/build/bootloader"
  "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix"
  "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix/tmp"
  "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix/src"
  "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Documents/esp32/code/user/hello_world/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
