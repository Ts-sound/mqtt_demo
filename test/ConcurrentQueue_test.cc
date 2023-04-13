
#include "include/ConcurrentQueue.h"

#include <gtest/gtest.h>

#include <thread>

const int MaxCount = 100;
const int TimeInterval = 200 * 100;  // us

TEST(ConcurrentQueue, main) {
  ConcurrentQueue<int> c_qu(INT32_MAX);

  auto f1 = [](ConcurrentQueue<int>* qu) {
    int count = MaxCount;
    while (count--) {
      int ret;
      qu->wait_and_pop(ret);
      printf("f1 pop data : %d \n", ret);
    }
  };

  auto f2 = [](ConcurrentQueue<int>* qu) {
    int count = MaxCount;
    while (count--) {
      qu->push(count);
      printf("f2 push data : %d \n", count);
      usleep(TimeInterval);
    }
  };

  std::thread t1(f1, &c_qu);
  std::thread t2(f2, &c_qu);

  t1.join();
  t2.join();

  return;
}