#include <iostream>
#include "Application.hpp"

using namespace tlg_bot;

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}