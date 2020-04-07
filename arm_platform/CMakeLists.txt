cmake_minimum_required(VERSION 3.10)

set(PRJ_NAME arm_platform)
project(${PRJ_NAME})

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_C_FLAGS "-march=armv7-a -marm -mfpu=neon")
#set(CMAKE_CXX_FLAGS "-march=armv7-a -marm -mfpu=neon")
set(CMAKE_CXX_STANDARD 11)

add_definitions("-g")

set(APP_BASIC
    app/app_basic/app_basic.cpp
)
set(BUSINESS
    app/business/business.cpp
)
set(APP_SUBSETS
    ${APP_BASIC}
    ${BUSINESS}
)


set(TIMER
    plugin/timer/timer_1ms.cpp
)
set(EASYLOGGING
    plugin/easylogging/easylogging++.cc
)
set(PLUGIN_SUBSETS
    plugin/log.cpp
    ${TIMER}
    ${EASYLOGGING} 
)


INCLUDE_DIRECTORIES(inc/)

set(LINK_LIB m rt pthread)
link_libraries(${LINK_LIB})

add_executable(${PRJ_NAME} 
    main.cpp 
    ${APP_SUBSETS}
    ${PLUGIN_SUBSETS}
)

target_link_libraries(${PRJ_NAME} ${LINK_LIB})
