#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void calculator() {
    int num1, num2;

    mtx.lock();
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;
    std::cout << "The sum is: " << num1 + num2 << std::endl;
    mtx.unlock();
}

int main() {
    std::thread thread1(calculator);
    std::thread thread2(calculator);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}


