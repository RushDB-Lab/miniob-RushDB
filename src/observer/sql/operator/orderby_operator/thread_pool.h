#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include "src/observer/sql/operator/orderby_operator/order_by_physical_operator.h"

// 子区间排序函数
// template <typename RandomIt>
// void sortSubRange(RandomIt first, RandomIt last)
// {
//   std::sort(first, last, [this](const Tuple *first, const Tuple *second) { return campator->compare(first, second); });
// }

// // 多线程排序函数
// template <typename RandomIt>
// void parallelSort(RandomIt first, RandomIt last, int numThreads)
// {
//   int dataSize  = std::distance(first, last);
//   int chunkSize = dataSize / numThreads;

//   std::vector<std::thread>       threads;
//   std::vector<std::future<void>> futures;

//   // 创建线程并分配子区间
//   for (int i = 0; i < numThreads; ++i) {
//     RandomIt start = first + i * chunkSize;
//     RandomIt end   = (i == numThreads - 1) ? last : start + chunkSize;

//     std::packaged_task<void()> task([start, end]() { sortSubRange(start, end); });

//     futures.push_back(task.get_future());
//     threads.push_back(std::thread(std::move(task)));
//   }

//   // 等待所有线程完成
//   for (auto &future : futures) {
//     future.wait();
//   }

//   // 合并排序结果
//   std::vector<typename RandomIt::value_type> sortedData;
//   for (auto &thread : threads) {
//     thread.join();
//   }

//   for (auto &future : futures) {
//     sortedData.insert(sortedData.end(), future.get());
//   }

//   // 对合并后的容器再次进行排序
//   std::sort(sortedData.begin(), sortedData.end());

//   std::cout << std::endl;
// }
