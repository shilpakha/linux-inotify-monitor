// thread_test.cpp

#include <iostream>
#include <thread>

void worker()
{
    for(int i = 1; i <= 5; i++)
    {
        std::cout << "Worker Thread: " << i << std::endl;
    }
}

int main()
{
    std::thread t(worker);

    for(int i = 1; i <= 5; i++)
    {
        std::cout << "Main Thread: " << i << std::endl;
    }

    t.join();

    return 0;
}