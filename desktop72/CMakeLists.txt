cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 REQUIRED COMPONENTS
	Widgets
)

set(SOURCES
	WIN32 main.cpp
	footer.cpp
	footer__update_pixmaps.cpp
	comandlistener.cpp
)
#file(GLOB SOURCES *.cpp)
#qt5_add_resources (RCC_SOURCES rc.qrc)
add_executable(desktop-indicator ${SOURCES} ${RCC_SOURCES})
target_link_libraries(desktop-indicator Qt5::Core
	Qt5::Widgets
	#$<$<PLATFORM_ID:Linux>:pthread>
)

#QT += core widgets

#HEADERS += \
#    footer.h \
#    comandlistener.h

#SOURCES += \
#    footer.cpp \
#    main.cpp \
#    footer__update_pixmaps.cpp \
#    #get_pixmap.cpp
#    comandlistener.cpp

