#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
public:
  ThreadSafeQueue()=default;
  ThreadSafeQueue(const ThreadSafeQueue&) = delete;            // disable copying
  ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete; // disable assignment
/*
  void Insert(T value)
  {
    std::lock_guard<std::mutex> lk(_mut);
    _que.push(value);
    _cond.notify_one();
  };
*/
  void Push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(_mut);
    _que.push(item);
    mlock.unlock();
    _cond.notify_one();
  }

  T Pop()
  {
    std::unique_lock<std::mutex> mlock(_mut);
    // _cond.wait(lk, [this] { return !_que.empty(); });
    while(this->_que.empty()){
      this->_cond.wait(mlock);
    }
    auto value = _que.front();
    _que.pop();
    return value;
  };

  void Pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(_mut);
    while(this->_que.empty()){
      this->_cond.wait(mlock);
    }
    item = _que.front();
    _que.pop();
  }

private:
  mutable std::mutex _mut;
  std::queue<T> _que;
  std::condition_variable _cond;
};
