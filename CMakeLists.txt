cmake_minimum_required(VERSION 3.17)

project(dedlock)

add_definitions(--std=c++17)

set(CMAKE_BUILD_TYPE Realease)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(KEEP_RPATHS)

file (GLOB_RECURSE Dedlock_src src/main.cpp)

#file (GLOB_RECURSE Zia  src/Client/*.cpp 
#                        src/Core/*.cpp
#                        src/Core/ConfigHandler/*.cpp
#			src/Service/Service.cpp
#                        src/Server/*.cpp
#                        src/Shell/*.cpp
#                        src/TcpConnection/*.cpp
#			src/*.cpp
#			src/HttpRequest/*.cpp
#                        Modules/Logger/Logger.cpp
#)
#
#file (GLOB_RECURSE MOD  src/HttpRequest/HttpRequest.cpp
#			src/Core/DllHandler/DllHandler.cpp
#			src/TcpConnection/TcpConnection.cpp
#    			src/Client/Client.cpp
#                        Modules/Logger/Logger.cpp
#			src/Service/Service.cpp
#)

if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

if (UNIX)
    SET(GXX_COVERAGE_COMPILE_FLAGS "-g3")
endif(UNIX)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

add_executable(dedlock ${Dedlock_src})
#add_executable(zia ${Zia})

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Modules/lib)

#those lines are to build shared librairies

#add_library(PhpCgi SHARED
#    Modules/PhpCgi/PhpCgi.cpp
#   ${MOD}
#)
#
#add_library(Html SHARED
#    src/Service/Service.cpp
#    Modules/Html/Html.cpp
#    ${MOD}
#)
#
#add_library(FileServe SHARED
#    Modules/FileServe/FileServe.cpp
#    ${MOD}
#)
#
#add_library(Logger SHARED	
#    ${MOD}
#)
#
#add_library(SSL SHARED
#    Modules/SSL/SSL.cpp
#    Modules/SSL/SslConnexion/SslConnexion.cpp    
#    ${MOD}
#)
#
#add_library(Http SHARED
#    Modules/Http/Http.cpp    
#    ${MOD}
#)
#
#add_library(Ftp SHARED
#    Modules/Ftp/Ftp.cpp    
#    ${MOD}
#)

# Now we link the binaries with conan libs

target_link_libraries(dedlock ${CONAN_LIBS})

#target_link_libraries(PhpCgi ${CONAN_LIBS})
#target_link_libraries(SSL ${CONAN_LIBS})
#target_link_libraries(Html ${CONAN_LIBS})
#target_link_libraries(FileServe ${CONAN_LIBS})
#target_link_libraries(Ftp ${CONAN_LIBS})
#target_link_libraries(Http ${CONAN_LIBS})
#target_link_libraries(Logger ${CONAN_LIBS})
#target_link_libraries(zia ${CONAN_LIBS})