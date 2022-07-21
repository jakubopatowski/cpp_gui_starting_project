add_executable(zmq-client client.cpp)
add_executable(zmq-server server.cpp)

find_package(cppzmq CONFIG)
find_package(boost CONFIG)

target_link_libraries( zmq-client
PRIVATE 
    cppzmq
    Boost::program_options
    #project_warnings
    #project_options
)

target_link_libraries( zmq-server
PRIVATE 
    cppzmq
    Boost::program_options
    #project_warnings
    #project_options
)