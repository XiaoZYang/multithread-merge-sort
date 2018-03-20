/**
 * @author: xiaozongyang
 * @data  : 2018-03-20
 **/
// standard lib
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
// third-party lib
// user-defined lib
#include "merge.h"


class ConcurrentQueue{
private:
    std::condition_variable cv;
    std::mutex mut_in;
    std::mutex mut_out;
    std::mutex mut_size;
    std::atomic<int> sorted_cnt;
    std::queue<std::vector<int>> q;

public:
    void push(std::vector<int> v){
        {
            std::lock_guard<std::mutex> lk(mut_in);
            q.push(v);
        }
        sorted_cnt++;
        cv.notify_one();
    }

    std::vector<std::vector<int>> pop2(){
        std::unique_lock<std::mutex> lk(mut_out);
        cv.wait(lk, [this](){return this->sorted_cnt > 1;});
        sorted_cnt--;
        sorted_cnt--;

        std::vector<std::vector<int>> ret;
        ret.push_back(q.front());
        q.pop();
        ret.push_back(q.front());
        q.pop();

        lk.unlock();
        return ret;
    }

    int size(){
        std::lock_guard<std::mutex> lk(mut_size);
        return q.size();
    }

    std::vector<int> front(){
        return q.front();
    }
};

std::vector<int> merge_sort_with_multithread(std::vector<std::vector<int>> nums_list){
    ConcurrentQueue q;
    std::queue<std::shared_future<std::vector<int>>> running_futures;
    for(auto nums: nums_list){
        std::shared_future<std::vector<int>> f = std::async(std::launch::async, merge_sort, std::ref(nums));
        running_futures.push(f);
    }

    while(!running_futures.empty()){
        auto f = running_futures.front();
        f.wait();
        auto v = f.get();
        running_futures.pop();
        q.push(v);
        if(q.size() > 1){
            auto nums_list = q.pop2();
            std::shared_future<std::vector<int>> f = std::async(std::launch::async, merge_sorted, std::ref(nums_list[0]), std::ref(nums_list[1]));
            running_futures.push(f);
            q.push(f.get());
        }
    }

    return q.front();
}

int main(){
    std::vector<int> nums1 = {1, 5, 5, 2, 7, 6, 0, 9, 8, 1, 7};
    std::vector<int> nums2 = {1, 3, 0, 2, 1, 9, 3, 1, 9, 5, 9};
    std::vector<int> nums3 = {1, 5, 6, 5, 9, 8, 3, 2, 3, 6, 3};
    std::vector<std::vector<int>> nums_list;
    nums_list.push_back(nums1);
    nums_list.push_back(nums2);
    nums_list.push_back(nums3);
    //auto n = merge_sort_with_multithread(nums_list);
    // auto f = std::async(std::launch::async, merge_sort_with_multithread, nums_list);
    auto f = std::async(std::launch::async, merge_sort, std::ref(nums1));
    f.wait();
    for(auto i: f.get()){
        printf("%d ", i);
    }
    printf("\n");
    for(auto i: merge_sort(nums1)){
        printf("%d ", i);
    }
    return 0;
}
