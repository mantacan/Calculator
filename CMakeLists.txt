cmake_minimum_required(VERSION 3.27)
project(CPP3_SmartCalc_v2_0_1)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(src/develop)
include_directories(src/develop/controller)
include_directories(src/develop/model)
include_directories(src/develop/view)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(CPP3_SmartCalc_v2_0_1
        src/develop/controller/controller.cpp
        src/develop/controller/controller.h
        src/develop/model/calculator.cpp
        src/develop/model/calculator.h
        src/develop/tests/tests.cpp
        src/develop/view/main.cpp
        src/develop/view/design.h
        src/develop/smartcalc.h
        src/develop/model/credit_calculator.cpp
        src/develop/model/deposit_calculator.cpp
        src/develop/view/viewCredCalc.cpp
        src/develop/view/viewDepCalc.cpp
        src/develop/view/viewGraph.cpp
        src/develop/view/eventProcessing.cpp
        src/develop/view/layout.cpp
        src/develop/view/controllerOperation.cpp
        src/develop/view/widgets.cpp
)

target_link_libraries(CPP3_SmartCalc_v2_0_1 ${GTK3_LIBRARIES})
