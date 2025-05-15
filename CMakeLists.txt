cmake_minimum_required(VERSION 3.16)
project(DouDiZhuGame)

set(CMAKE_CXX_STANDARD 17)

# 查找Qt库
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 源文件列表
set(SOURCES
    main.cpp
    mainwindow.cpp
    card.cpp
    deck.cpp
    player.cpp
    humanplayer.cpp
    aiplayer.cpp
    cardtypejudger.cpp
    cardwidget.cpp
    cardlayout.cpp
)

# 头文件列表
set(HEADERS
    mainwindow.h
    card.h
    deck.h
    player.h
    humanplayer.h
    aiplayer.h
    cardtypejudger.h
    cardwidget.h
    cardlayout.h
)

# UI文件
set(UIS
    mainwindow.ui
)

# 添加资源文件
set(RESOURCES resources.qrc)

# 添加可执行文件
add_executable(DouDiZhuGame
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    ${RESOURCES}
)

# 链接Qt库
target_link_libraries(DouDiZhuGame PRIVATE Qt6::Widgets)

# 安装目标
install(TARGETS DouDiZhuGame RUNTIME DESTINATION bin)
