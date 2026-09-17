cmake_minimum_required(VERSION 3.20.0)

# Reuse the app's board overlay so the bme280/i2c1 devicetree nodes we're
# sanity-checking actually exist for this build.
set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../../boards/nrf7002dk_nrf5340_cpuapp_ns.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(bme280_dt_test)

target_sources(app PRIVATE
  src/bme280_dt_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../bme280_temp/bme280_temp.c
)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../bme280_temp)
