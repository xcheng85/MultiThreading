#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void accumulator_function2(const std::vector<int> &v, unsigned long long &acm, 
                            unsigned int beginIndex, unsigned int endIndex)
{
    acm = 0;
    for (int i = beginIndex; i < endIndex; ++i)
    {
        acm += v[i];
    }
}

int main()
{
    unsigned long long acm1 = 0;
    unsigned long long acm2 = 0;

    vector<int> v(100, 0); 
    for(int i = 0; i < 100; i++){
        v[i] = i; 
    }

    std::thread t1(accumulator_function2, std::ref(v), std::ref(acm1), 0, v.size() / 2);
    std::thread t2(accumulator_function2, std::ref(v), std::ref(acm2), v.size() / 2, v.size());
    t1.join(); // main threads waits for t1
    t2.join(); // main threads waits for t2

    std::cout << "acm1: " << acm1 << endl;
    std::cout << "acm2: " << acm2 << endl;
    std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;
}