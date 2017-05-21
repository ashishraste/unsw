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
  explicit BlockingQueue(const std::vector<T>& buf): 
    buffer(buf)
  {}
  explicit BlockingQueue(): buffer()
  {}
  void push(const T& elem);
  void push(T&& elem);
  T pop();
  int size() const { return buffer.size(); }
  ~BlockingQueue()
  {}

private:
  boost::mutex mutex;                             // mutex variable
  boost::condition_variable_any notEmptyCond;     // condition variable, to check whether the queue is empty
  std::vector<T> buffer;                          // uses a vector to store the elements, doesn't have capacity constraints
};

template<typename T>
void BlockingQueue<T>::push(const T& elem) 
{
  boost::mutex::scoped_lock lock(mutex);
  buffer.push_back(elem);
  lock.unlock();
  notEmptyCond.notify_one();                      // notifies one of the waiting threads which are blocked on the queue
  // assert(!buffer.empty());
}

// Push with move-semantics.
template<typename T>
void BlockingQueue<T>::push(T&& elem)
{
  push(std::move(elem));
}

template<typename T>
T BlockingQueue<T>::pop()
{
  boost::mutex::scoped_lock lock(mutex);
  notEmptyCond.wait(lock,[&](){ return (buffer.size() > 0); });   // waits for the queue to get filled until its 'size' condition is satisfied
  T elem = buffer.front();
  buffer.erase(buffer.begin());
  return elem;
}

#endif