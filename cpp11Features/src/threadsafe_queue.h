#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
public:
  void Insert(T value)
  {
    std::lock_guard<std::mutex> lk(_mut);
    _que.push(value);
    _cond.notify_one();
  };
  T Popup()
  {
    std::unique_lock<std::mutex> lk(_mut);
    _cond.wait(lk, [this] { return !_que.empty(); });
    T value = _que.front();
    _que.pop();
    return value;
  };
  bool Empty()
  {
    std::lock_guard<std::mutex> lk(_mut);
    return _que.empty();
  };

private:
  mutable std::mutex _mut;
  std::queue<T> _que;
  std::condition_variable _cond;
};
