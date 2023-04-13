#pragma once

#include <condition_variable>  //NOLINT
#include <mutex>               //NOLINT
#include <queue>
#include <utility>

template <typename T>
class ConcurrentQueue {
 private:
  std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;
  uint32_t max_size = 0;

 public:
  explicit ConcurrentQueue(uint32_t max_size) : max_size(max_size) {
    // pass
  }

  bool push(T value) {
    std::lock_guard<std::mutex> lk(mut);

    if (data_queue.size() >= max_size) return false;

    data_queue.push(std::move(value));
    data_cond.notify_one();
    return true;
  }
  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = std::move(data_queue.front());
    data_queue.pop();
  }

  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return false;
    }
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
  }

  bool empty() {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }

  size_t size() {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.size();
  }
};
