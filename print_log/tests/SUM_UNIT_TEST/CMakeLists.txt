cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(sum_log_unit_test)

target_sources(app PRIVATE
  src/sum_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../sum_log/sum_log.c
)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../sum_log)
