# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp8266/ESP8266_RTOS_SDK/tools/kconfig"
  "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/kconfig_bin"
  "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix"
  "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix/tmp"
  "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix/src/mconf-idf-stamp"
  "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix/src"
  "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix/src/mconf-idf-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix/src/mconf-idf-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Ed/Desktop/2022.2/Sistemas Digitais Embarcados/Unidade2/Codigo/exemplo_cpp1/build/mconf-idf-prefix/src/mconf-idf-stamp${cfgdir}") # cfgdir has leading slash
endif()
