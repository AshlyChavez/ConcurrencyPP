#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool turn = true; // -true para "hello"     -false para "goodbye"

void processThread(const std::string& text, bool myTurn) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [myTurn]() { return turn == myTurn; });
        std::cout << text << std::endl;
        turn = !turn;
        cv.notify_all(); //Avisa al otro hilo
    }
}

int main() {
    std::thread process1(processThread, "hello", true);
    std::thread process2(processThread, "goodbye", false);

    process1.join();
    process2.join();

    return 0;
}



