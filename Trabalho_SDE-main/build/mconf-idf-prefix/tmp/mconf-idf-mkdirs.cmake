# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp8266/ESP8266_RTOS_SDK/tools/kconfig"
  "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/kconfig_bin"
  "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix"
  "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix/tmp"
  "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix/src/mconf-idf-stamp"
  "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix/src"
  "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix/src/mconf-idf-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix/src/mconf-idf-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/esp8266/ESP8266_RTOS_SDK/examples/get-started/trabalho_sde/build/mconf-idf-prefix/src/mconf-idf-stamp${cfgdir}") # cfgdir has leading slash
endif()
