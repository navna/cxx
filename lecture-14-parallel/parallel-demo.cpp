#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

using namespace std;
using namespace std::chrono;

const size_t max_delay = 100;
mutex my_mutex;

void run(const size_t n) {
    std::random_device rd;
    std::uniform_int_distribution<size_t> dist(0, max_delay);

    // Перебор всех чисел от 1 до n
    for (size_t i = 1; i <= n; ++i) {
        my_mutex.lock();
        cout << "[" << this_thread::get_id() << "] " << i << endl;
        my_mutex.unlock();

        this_thread::sleep_for(milliseconds(dist(rd)));
    }
}

int main() {
    const size_t max = 10;
    thread t1(run, max);
    thread t2(run, max);
    t1.join();
    t2.join();
}
