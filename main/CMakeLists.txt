
file(GLOB_RECURSE HAL ${CMAKE_SOURCE_DIR} "HAL/*.cpp")
file(GLOB_RECURSE HAL_C ${CMAKE_SOURCE_DIR} "HAL/*.c")
idf_component_register(SRCS "main.c"  ${HAL} ${HAL_C}
                    INCLUDE_DIRS "." "HAL")