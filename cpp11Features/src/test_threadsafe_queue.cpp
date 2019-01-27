#include <iostream>
#include <thread>
#include <mutex>
#include "threadsafe_queue.h"

void consumer(int id, ThreadSafeQueue<int>& q){
    for(int i = 0; i < 5; ++i){
        int value = q.Popup();
        std::cout << "Consumer " << id << " fetched " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void producer(int id, ThreadSafeQueue<int>& q){
    for(int i = 0; i < 5; ++i){
        q.Insert(id);
        std::cout << "Produced " << id << " produced " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){
    ThreadSafeQueue<int> queue;

    // two parameters
    std::thread c1(consumer, 0, std::ref(queue));
    std::thread p1(producer, 0, std::ref(queue));

    c1.join();
    p1.join();

    return 0;
}