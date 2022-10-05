set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "d:\\Qt5\\5.14.2\\msvc2017_64")
find_package(Qt5 5.12.5 REQUIRED COMPONENTS Widgets)

add_executable(qt-example 
    main.cpp
    DataModel.hpp
    DataSample.hpp
    DataSample.cpp
    ui/MainWindow.hpp
    ui/mainWindow.cpp
    ui/MainWindow.ui)

set_property(TARGET qt-example PROPERTY AUTOMOC ON)

target_include_directories(qt-example PUBLIC ./ui)

target_link_libraries(
  qt-example
  PRIVATE Qt5::Widgets  
          project_warnings
          #project_options
          )