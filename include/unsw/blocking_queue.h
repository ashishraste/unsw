#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <vector>
#include <cassert>

/**
 * @brief      Blocking Queue implementation.
 *
 * @tparam     T  type of the elements stored in the queue.
 */
template<typename T>
class BlockingQueue
{
public:
  explicit BlockingQueue(const std::vector<T>& buf, size_t cap=10): 
    buffer(buf),capacity(cap)
  {}
  explicit BlockingQueue(): buffer(),capacity(10)
  {}
  void push(const T& elem);
  T pop();
  ~BlockingQueue()
  {}

private:
  boost::mutex mutex;                                   // mutex variable
  boost::condition_variable push_event, pop_event;      // condition variable, to check whether the queue is empty
  std::vector<T> buffer;                                // uses a vector to store the elements, doesn't have capacity constraints
  size_t capacity;
};

template<typename T>
void BlockingQueue<T>::push(const T& elem) 
{
  boost::mutex::scoped_lock lock(mutex);
  pop_event.wait(lock,[&](){ return (buffer.size() < capacity); });
  buffer.push_back(elem);
  push_event.notify_one();                      // notifies one of the waiting threads which are blocked on the queue
  // assert(!buffer.empty());
}

template<typename T>
T BlockingQueue<T>::pop()
{
  boost::mutex::scoped_lock lock(mutex);
  push_event.wait(lock,[&](){ return (buffer.size() > 0); });   // waits for the queue to get filled until its 'size' condition is satisfied
  T elem = buffer.front();
  buffer.erase(buffer.begin());
  pop_event.notify_one();
  return elem;
}

#endif