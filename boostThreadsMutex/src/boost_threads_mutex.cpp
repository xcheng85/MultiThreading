#include <boost/thread.hpp>
#include <iostream>

int globalVariable;

class Reader
{
  public:
    Reader(int waitTime) { _waitTime = waitTime;}
    void operator() () {
      for (int i=0; i < 10; i++) {
        std::cout << "Reader Api: " << globalVariable << std::endl;
        usleep(_waitTime);
      }
      return;
    }
  private:
    int _waitTime;
};

class Writer
{
  public:
    Writer(int variable, int waitTime)
    {
      _writerVariable = variable;
      _waitTime = waitTime;
    }
    void operator () () {
      for (int i=0; i < 10; i++) {
        usleep(_waitTime);
        // Take lock and modify the global variable
        boost::mutex::scoped_lock lock(_writerMutex);
        globalVariable = _writerVariable;
        _writerVariable++;
        // since we have used scoped lock, 
        // it automatically unlocks on going out of scope
      }
    }
  private:
    int _writerVariable;
    int _waitTime;
    static boost::mutex _writerMutex;
};

boost::mutex
Writer::_writerMutex;

int main()
{
  Reader reads(100);
  Writer writes1(100, 200);
  Writer writes2(200, 200);

  boost::thread readerThread(reads);
  boost::thread writerThread1(writes1);
  usleep(100);
  boost::thread writerThread2(writes2);

  readerThread.join();
  writerThread1.join();
  writerThread2.join();
}