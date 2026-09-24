# ##############################################################################
# vendor/gigadevice/boards/gd32h7/gd32h759imt6/src/CMakeLists.txt
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

# NOTE: The GD32H7 base chip layer lives in openvela nuttx:
#   nuttx/arch/arm/src/gd32h7xx
# The vendor chips/gd32h7 extension directory does not exist yet, so all
# board sources below are local to this board directory. When a vendor chip
# extension directory is added later, uncomment VENDOR_CHIP_SRCDIR and append
# the extension sources from there, mirroring the GD32F4 vendor layout.
# set(VENDOR_CHIP_SRCDIR
#     ${NUTTX_BOARD_ABS_DIR}/../../../chips/gd32h7/src)

set(SRCS gd32h7xx_boot.c)

if(CONFIG_BOARDCTL)
  list(APPEND SRCS gd32h7xx_appinit.c gd32h7xx_bringup.c)
elseif(CONFIG_BOARD_LATE_INITIALIZE)
  list(APPEND SRCS gd32h7xx_bringup.c)
endif()

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS gd32h7xx_autoleds.c)
else()
  list(APPEND SRCS gd32h7xx_userleds.c)
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS gd32h7xx_buttons.c)
endif()

if(CONFIG_GD32H7_SPI)
  list(APPEND SRCS gd32h7xx_spi.c)
endif()

if(CONFIG_MTD_GD25)
  list(APPEND SRCS gd32h7xx_gd25.c)
endif()

if(CONFIG_GD32H7_I2C)
  list(APPEND SRCS gd32h7xx_i2c.c)
endif()

if(CONFIG_GD32H759IMT6_AT24_TEST)
  list(APPEND SRCS gd32h7xx_at24.c)
endif()

target_sources(board PRIVATE ${SRCS})

target_include_directories(
  board BEFORE
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
