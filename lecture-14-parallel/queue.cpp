#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <queue>

using namespace std;
using namespace std::chrono;

queue<int> task_queue;
mutex task_queue_mutex;
condition_variable task_queue_cv;

// Поставщик
void producer(const size_t thread_index, const uint64_t seed) {
    mt19937_64 e(seed);
    uniform_int_distribution<size_t> delay_dist(1000, 5000);
    uniform_int_distribution<size_t> value_dist(100, 999);

    while (true) {
        const auto delay = delay_dist(e);
        this_thread::sleep_for(milliseconds(delay));

        const auto value = value_dist(e);

        {
            lock_guard<mutex> lk(task_queue_mutex);
            cout << "Producing " << value << " in thread " << thread_index << endl;
            task_queue.push((int)value);
        }

        task_queue_cv.notify_all();
    }
}

// Потребитель
void consumer() {
    while (true) {
        int value = 0;
        bool valid = false;

        {
            unique_lock<mutex> lk(task_queue_mutex);
            while (task_queue.empty()) {
                task_queue_cv.wait(lk);
            }
            const auto value = task_queue.front();
            task_queue.pop();
            cout << "Consuming " << value << " (left in queue: " << task_queue.size() << ")" << endl;
        }

        this_thread::sleep_for(milliseconds(2000));
    }
}

int main() {
    default_random_engine e;

    thread producer1_thread(producer, 1, e());
    thread producer2_thread(producer, 2, e());
    thread consumer_thread(consumer);

    producer1_thread.join();
    producer2_thread.join();
    consumer_thread.join();
}

//class task {
//public:
//    virtual void run() = 0;
//    virtual ~task() = default;
//};

//struct dot_product_task : public task {
//    void run() override { }
//};

//struct add_vector_task : public task {
//    void run() override { }
//};

//queue<task*>;
