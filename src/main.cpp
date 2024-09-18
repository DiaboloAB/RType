#include <iostream>
#include "entity.hpp"

#include <asio.hpp>

template<typename T>
T square(T x)
{
    return x * x;
}

int main(void)
{
    Entity oui(2);
    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(2));
    t.wait();

    std::cout << "Hello, world!" << std::endl;
}
