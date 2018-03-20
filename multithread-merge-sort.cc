/**
 * @author: xiaozongyang
 * @data  : 2018-03-20
 **/
// standard lib
#include <thread>
#include <future>
#include <queue>
#include <mutex>
// third-party lib
// user-defined lib
#include "merge.h"
#include "bilist.h"

std::vector<int> merge_sort_with_multithread(std::vector<std::vector<int>> nums_list){
    std::queue<std::vector<int>> q;
    BiLinkedList<std::shared_future<std::vector<int>>> running_futures;
    int counts = 0;
    for(auto nums: nums_list){
        std::shared_future<std::vector<int>> f = std::async(std::launch::async, merge_sort, std::ref(nums));
        running_futures.add(f);
        counts += nums.size();
    }

    std::mutex m;

    while(true){
        for(auto f = running_futures.begin(); f != running_futures.end(); f = f->next){
            if(f->val.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready){
                q.push(f->val.get());
                printf("push one in q\n");
                running_futures.remove(f);
            }
        }
        while(q.size() > 1){
            auto n1 = q.front();
            q.pop();
            auto n2 = q.front();
            q.pop();

            std::shared_future<std::vector<int>> f = std::async(std::launch::async, merge_sorted, std::ref(n1), std::ref(n2));
            running_futures.add(f);
            printf("add one in r\n");
        }
        std::sleep_for(std::chrono::seconds(2));
        if(running_futures.empty()){
            printf("r.empty = %d q.size = %d q.front.size = %d counts = %d\n", running_futures.empty(), q.size(), q.front().size(), counts);
            // std::lock_guard<std::mutex> lk(m);
            if(q.front().size() == counts) break;
        }
    }

    for_each(q.front().begin(), q.front().end(), [](int n){printf("%d ", n);});

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
    auto ret = merge_sort_with_multithread(nums_list);
    printf("size = %d\n", ret.size());
    for_each(ret.begin(), ret.end(), [](int n){printf("%d ", n);});
    return 0;
}
