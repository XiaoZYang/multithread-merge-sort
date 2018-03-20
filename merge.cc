#include "merge.h"
#include <stdio.h>

std::vector<int> merge(std::vector<int> &v, int beg, int end){
    if(beg + 1 == end) return std::vector<int>();
    int mid = (beg + end) >> 1;
    merge(v, beg, mid);
    merge(v, mid, end);
    std::vector<int> buf(end - beg);
    int i = beg;
    int j = mid;
    int k = 0;
    while(i != mid && j != end){
        buf[k++] = v[i] < v[j] ? v[i++] : v[j++];
    }
    while(i != mid) buf[k++] = v[i++];
    while(j != end) buf[k++] = v[j++];

    return buf;
}

std::vector<int> merge_sort(std::vector<int> &v){
    return merge(v, 0, v.size());
}

std::vector<int> merge_sorted(std::vector<int> &v1, std::vector<int>&v2){
    std::vector<int> v;
    v.reserve(v1.size() + v2.size());
    auto i = v1.begin();
    auto j = v2.begin();
    while(i < v1.end() && j < v2.end()){
        v.push_back(*i < *j? *i++: *j++);
    }
    while(i < v1.end()) v.push_back(*i++);
    while(j < v2.end()) v.push_back(*j++);
    return v;
}
