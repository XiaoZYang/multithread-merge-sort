#include <cstdio>
#include <vector>
#include <algorithm>

void merge(std::vector<int> &v, int beg, int end){
    if(beg + 1 == end) return;
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
    copy(buf.begin(), buf.end(), v.begin() + beg);
}

void merge_sort(std::vector<int> &v){
    merge(v, 0, v.size());
}

std::vector<int> merge(std::vector<int> &v1, std::vector<int>&v2){
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

int main(){
    std::vector<int> v = {1, 5, 6, 2, 3, 2, 3, 5, 9, 8, 3, 1, 6, 3, 4, 4, 1, 6, 0, 0, 9, 8, 1, 7};
    merge_sort(v);
    std::for_each(v.begin(), v.end(), [](int n){printf("%d ", n);});
}
