cmake_minimum_required(VERSION 3.5)
project(flicker-sdl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=reorder -Werror=return-type -Werror=switch -O0 -g -std=c++17 -stdlib=libc++")

set(PROJECT_DIR ${PROJECT_SOURCE_DIR})

add_definitions("-Wall -g")

configure_file(
  ${PROJECT_SOURCE_DIR}/main/src/config.h.in
  ${PROJECT_BINARY_DIR}/config.h
)

add_compile_definitions(IS_SIMULATOR=1)

# SDL2 simulator
find_package(SDL2 CONFIG REQUIRED)

if(SDL2_FOUND)
  message("Find SDL2: ${SDL2_INCLUDE_DIRS}; ${SDL2_LIBRARIES};")
endif()

# cpprest
find_package(cpprestsdk REQUIRED)

# openssl (cpprest需要)
find_package(openssl REQUIRED)

set(PROJECT_PARENT_DIR "${PROJECT_SOURCE_DIR}/../")
set(PROJECT_PARENT_MAIN_DIR "${PROJECT_SOURCE_DIR}/../main")

include_directories(
  ${PROJECT_BINARY_DIR} # for config.h.in
  ${PROJECT_SOURCE_DIR} # for lv_xxx.h in root

  # mock
  ${PROJECT_SOURCE_DIR}/main/mock/lvgl_epaper_drivers
  ${PROJECT_SOURCE_DIR}/main/mock/lvgl_epaper_drivers/lvgl_tft
  ${PROJECT_SOURCE_DIR}/main/mock/freertos/include
  ${PROJECT_SOURCE_DIR}/main/mock/ota/include
  ${PROJECT_SOURCE_DIR}/main/mock/include

  # common
  ${PROJECT_PARENT_MAIN_DIR}/common/models

  # sub modules
  ${PROJECT_PARENT_DIR}/components
  ${PROJECT_PARENT_DIR}/components/lvgl/src

  # main
  ${PROJECT_SOURCE_DIR}/main
  ${PROJECT_PARENT_MAIN_DIR}
  ${PROJECT_PARENT_MAIN_DIR}/include
  ${PROJECT_PARENT_MAIN_DIR}/modules/include

  # sdl2
  ${SDL2_PREFIX}/include

  # openssl
  ${OPENSSL_INCLUDE_DIR}
)

# 子模块
add_subdirectory(lv_drivers)
add_subdirectory(../components/lvgl lvgl)

# src files
file(GLOB SRC_FILES
  ${PROJECT_SOURCE_DIR}/main/src/main.cpp
  ${PROJECT_SOURCE_DIR}/main/src/mouse_cursor_icon.cpp
  ${PROJECT_SOURCE_DIR}/main/src/project.cpp

  # mock
  ${PROJECT_SOURCE_DIR}/main/mock/esp/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/esp/driver/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/buzzer/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/gxht30/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/powermon/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/PCF8563/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/lvgl_epaper_drivers/lvgl_tft/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/freertos/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/ota/*.cpp

  # mock
  ${PROJECT_SOURCE_DIR}/main/mock/modules/app/services/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/modules/app/models/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/modules/common/services/*.cpp
  ${PROJECT_SOURCE_DIR}/main/mock/modules/common/utils/*.cpp

  # common
  ${PROJECT_PARENT_MAIN_DIR}/modules/common/components/*.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/common/utils/fl_async.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/common/utils/fl_async_hardware.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/common/utils/event_bus.cpp

  # app
  ${PROJECT_PARENT_MAIN_DIR}/modules/app/*.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/app/services/index.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/app/services/basic.cpp

  # tester
  ${PROJECT_PARENT_MAIN_DIR}/modules/tester/pack/*.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/tester/simple_page/*.cpp
  ${PROJECT_PARENT_MAIN_DIR}/modules/tester/touch/*.cpp
)

# target
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  cpprestsdk::cpprest
  lvgl_drivers
  lvgl
)
