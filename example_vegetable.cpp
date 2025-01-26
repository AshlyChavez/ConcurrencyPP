#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

bool chopping = true;
unsigned int vegetable_count = 0;
std::mutex mtx;

void vegetable_chopper(const char* name) {
  while (chopping) {
    std::lock_guard<std::mutex> lock(mtx);
    vegetable_count++;
  }
  printf("%s chopped %u vegetables. \n", name, vegetable_count);
}

int main() {
  std::thread olivia(vegetable_chopper, "Olivia");
  std::thread barron(vegetable_chopper, "Barron");

  printf("Barron and Olivia are chopping vegetables...\n");
  std::this_thread::sleep_for(std::chrono::microseconds(1));

  chopping = false;

  barron.join();
  olivia.join();

  return 0;
}




