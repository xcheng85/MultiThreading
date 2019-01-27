#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

struct Counter {
    int value;

    Counter() : value(0) {}

    void increment(){
        ++value;
    }

    void decrement(){
        if(value == 0){
            throw "Value cannot be less than 0";
        }

        --value;
    }
};

struct ConcurrentCounter {
    std::mutex mutex;
    Counter counter;

    void increment(){
        mutex.lock();
        counter.increment();
        mutex.unlock();
    }

    void decrement(){
        mutex.lock();
        counter.decrement();        
        mutex.unlock();
    }
};

struct ConcurrentSafeCounter {
    std::mutex mutex;
    Counter counter;

    void increment(){
        std::lock_guard<std::mutex> guard(mutex);
        counter.increment();
    }

    void decrement(){
        std::lock_guard<std::mutex> guard(mutex);
        counter.decrement();
    }
};

// automatic lock management

void hello(){
    std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main(){
    std::vector<std::thread> threads;

    /*
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread(hello));
    }*/

    /*
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([](){
            std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
        }));
    }

    for(auto& thread : threads){
        thread.join();
    }*/

    ConcurrentSafeCounter counter;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([&counter](){
            for(int i = 0; i < 100; ++i){
                counter.decrement();
            }
        }));
    }

    for(auto& thread : threads){
        thread.join();
    }

    std::cout << counter.counter.value << std::endl;

    return 0;
}