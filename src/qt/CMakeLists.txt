set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "d:\\Qt5\\5.12.5\\msvc2017_64")
find_package(Qt5 5.12.5 REQUIRED COMPONENTS Gui Core)

add_executable(qt-example 
    main.cpp
    ui/dialog.ui)

target_link_libraries(
  qt-example
  PRIVATE Qt5::Gui
          Qt5::Core  
          project_warnings
          project_options)