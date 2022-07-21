#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <zmq.hpp>

using namespace boost::program_options;
using namespace std::chrono_literals;

// initialize the zmq context with a single IO thread
static zmq::context_t context;

///
/// @brief  Simple Reply function to illustrate Request/Reply pattern.
///
///
void rep()
{
    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{ context, zmq::socket_type::rep };
    socket.bind("tcp://*:5555");

    // prepare some static data for responses
    const std::string data{ "Message" };

    while (1) {
        zmq::message_t request;
        // receive a request from client
        auto tmp = socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received " << request.to_string() << '\n';

        // simulate work
        std::this_thread::sleep_for(100ms);

        // send the reply to the client
        socket.send(zmq::buffer(data), zmq::send_flags::none);
    }
}

///
/// @brief
///
///
void pair()
{
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.bind("tcp://*:5555");

    while (1) {
        zmq::message_t in_msg;
        auto tmp = socket.recv(in_msg);
        std::cout << in_msg.to_string() << '\n';

        zmq::message_t out_msg("ok", 2);
        socket.send(out_msg, zmq::send_flags::none);
    }
};

///
/// @brief
///
///
void push()
{
    zmq::socket_t socket(context, zmq::socket_type::push);
    socket.bind("tcp://*:5555");

    auto iter = 0;
    while (1) {
        std::string message = "Message no " + std::to_string(iter++);
        socket.send(zmq::buffer(message), zmq::send_flags::none);
        std::cout << "Send message: " << message << '\n';
        std::this_thread::sleep_for(500ms);
    }
}

void publish()
{
    zmq::socket_t socket(context, zmq::socket_type::pub);
    socket.bind("tcp://*:5555");

    while (1) {
        std::string topic1 = "topic1";
        socket.send(zmq::buffer(topic1), zmq::send_flags::sndmore);

        std::string msg1 = "Message for topic1";
        socket.send(zmq::buffer(msg1), zmq::send_flags::none);

        std::cout << "Send: " << topic1 << " - " << msg1 << '\n';

        std::string topic2 = "topic2";
        socket.send(zmq::buffer(topic2), zmq::send_flags::sndmore);

        std::string msg2 = "Message for topic2";
        socket.send(zmq::buffer(msg2), zmq::send_flags::none);

        std::cout << "Send: " << topic2 << " - " << msg2 << '\n';
    }
}

int main(int argc, char const *argv[])
{
    try {
        options_description desc{ "Server Options" };
        desc.add_options()("help,h", "Help screen")("reply,r", "Reply demo")("pair,p", "Pair demo")(
          "push,u", "Push demo")("publish,b", "Publish demo");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << '\n';
        } else if (vm.count("reply")) {
            rep();
        } else if (vm.count("pair")) {
            pair();
        } else if (vm.count("push")) {
            push();
        } else if (vm.count("publish")) {
            publish();
        } else {
            std::cout << desc << '\n';
        }
    } catch (const error &err) {
        std::cerr << err.what() << '\n';
    }

    return 0;
}
