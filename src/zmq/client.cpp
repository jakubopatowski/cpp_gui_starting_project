#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <zmq.hpp>

using namespace std::chrono_literals;
using namespace boost::program_options;

// initialize the zmq context with a single IO thread
zmq::context_t context{ 1 };

using run_in_threads = std::function<void(std::string)>;

///
/// @brief Simple Request function to illustrate Request/Reply pattern.
///
///
auto req = [](std::string thread_id) {
    // construct a REQ(request) socket and connect to interface
    zmq::socket_t socket{ context, zmq::socket_type::req };
    socket.connect("tcp://localhost:5555");

    // set up some static data to send
    const std::string data{ "Hello request from " + thread_id };

    for (auto request_num = 0; request_num < 10; ++request_num) {
        std::cout << "Sending Hello " << request_num << "..." << '\n';
        socket.send(zmq::buffer(data), zmq::send_flags::none);

        // wait for reply from server
        zmq::message_t reply{};
        auto tmp = socket.recv(reply, zmq::recv_flags::none);

        std::cout << "Received " << reply.to_string();
        std::cout << " (" << request_num << ")";
        std::cout << '\n';
    }
};

///
/// @brief
///
///
auto pair = [](std::string thread_id) {
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.connect("tcp://localhost:5555");

    const std::string data{ "Hello pair from client " + thread_id };

    for (auto request_num = 0; request_num < 10; ++request_num) {
        std::cout << "Client Sending Hello " << request_num << "..." << '\n';
        socket.send(zmq::buffer(data), zmq::send_flags::none);
    }
};

///
/// @brief
///
///
auto pull = [](std::string thread_id) {
    zmq::socket_t socket(context, zmq::socket_type::pull);
    socket.connect("tcp://localhost:5555");

    while (1) {
        zmq::message_t in_msg;
        auto tmp = socket.recv(in_msg);

        std::cout << thread_id << ": " << in_msg.to_string_view() << '\n';
    }
};

///
/// @brief
///
///
auto subscribe = [](std::string thread_id) {
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.connect("tcp://localhost:5555");

    std::vector<std::string> topics{ "topic1", "topic2" };

    auto mark = 0;
    while (1) {
        if (mark == 0) {
            socket.setsockopt(ZMQ_UNSUBSCRIBE, topics[0].data(), topics[0].size());
            socket.setsockopt(ZMQ_SUBSCRIBE, topics[1].data(), topics[1].size());
            ++mark;
        } else {
            socket.setsockopt(ZMQ_UNSUBSCRIBE, topics[1].data(), topics[1].size());
            socket.setsockopt(ZMQ_SUBSCRIBE, topics[0].data(), topics[0].size());
            --mark;
        }

        zmq::message_t topic;
        zmq::message_t msg;

        auto tmp = socket.recv(topic);
        tmp = socket.recv(msg);

        std::cout << thread_id << ": " << topic.to_string_view() << " - " << msg.to_string_view() << '\n';
        std::this_thread::sleep_for(200ms);
    }
};

///
/// @brief
///
///
auto subscribe_conflate = [](std::string thread_id) {
    zmq::socket_t socket(context, zmq::socket_type::sub);
    int set_conflate = 1;
    socket.setsockopt(ZMQ_CONFLATE, &set_conflate, sizeof(set_conflate));
    socket.connect("tcp://localhost:5555");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    while (1) {
        zmq::message_t msg;
        socket.recv(msg);
        std::cout << thread_id << ": " << msg.to_string_view() << '\n';
        std::this_thread::sleep_for(500ms);
    }
};

///
/// @brief
///
///
auto dealer_send = [](std::string thread_id) {
    zmq::socket_t socket(context, zmq::socket_type::dealer);

    socket.setsockopt(ZMQ_IDENTITY, thread_id.data(), thread_id.size());
    socket.connect("tcp://localhost:5555");

    std::string data = "takie tam od klienta " + thread_id;
    while (1) {
        socket.send(zmq::buffer(data), zmq::send_flags::none);
        std::this_thread::sleep_for(1000ms);
    }
};

auto dealer_receive = [](std::string thread_id) {

};

///
/// @brief
///
/// @param thread_no
/// @param function
///
void run(int thread_no, run_in_threads &function)
{
    if (thread_no == 1) {
        function("main_thread");
        return;
    }

    std::vector<std::unique_ptr<std::thread>> threads;
    for (int i = 0; i < thread_no; ++i) {
        threads.push_back(std::make_unique<std::thread>(function, "thread_" + std::to_string(i)));
    }
    for (auto &it : threads) { it->join(); }
}

int main(int argc, char const *argv[])
{
    try {
        options_description desc{ "Client Options" };
        desc.add_options()("help,h", "Help screen.")("request,r", value<int>(), "Send Request in <x> threads.")(
          "threadsno,t", value<int>()->default_value(1), "Number of threads")("pair,p",
          value<int>(),
          "Pair with server in <x> threads.")("pull,u", value<int>(), "Pull from server with <x> threads.")(
          "subscribe,s", value<int>(), "Subscribe for a topic1 with <x> threads.")(
          "subconf,c", value<int>(), "Subscribe with conflate for all topics with <x> threads.")(
          "dealersend,d", value<int>(), "Send Dealer for Router with <x> threads.")(
          "dealerrec,e", value<int>(), "Receive Dealer for Router with <x> threads.");


        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << '\n';
        } else if (vm.count("request")) {
            run_in_threads fun = req;
            run(vm["request"].as<int>(), fun);
        } else if (vm.count("pair")) {
            run_in_threads fun = pair;
            run(vm["pair"].as<int>(), fun);
        } else if (vm.count("pull")) {
            run_in_threads fun = pull;
            run(vm["pull"].as<int>(), fun);
        } else if (vm.count("subscribe")) {
            run_in_threads fun = subscribe;
            run(vm["subscribe"].as<int>(), fun);
        } else if (vm.count("subconf")) {
            run_in_threads fun = subscribe_conflate;
            run(vm["subconf"].as<int>(), fun);
        } else if (vm.count("dealer")) {
            run_in_threads fun = dealer_send;
            run(vm["dealer"].as<int>(), fun);
        } else if (vm.count("dealerrec")) {
            run_in_threads fun = dealer_receive;

        } else {
            std::cout << desc << '\n';
        }
    } catch (const error &err) {
        std::cout << err.what() << '\n';
    }

    return 0;
}
