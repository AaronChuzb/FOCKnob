
file(GLOB_RECURSE HAL ${CMAKE_SOURCE_DIR} "HAL/*.cpp")
idf_component_register(SRCS "main.c"  ${HAL}
                    INCLUDE_DIRS "." "HAL")