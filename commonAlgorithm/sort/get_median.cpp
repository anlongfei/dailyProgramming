
/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : anlongfei
#   Email         : 在 vimrc 文件中添加 let g:file_copyright_email = 'your email'
#   File Name     : get_median.cpp
#   Last Modified : 2019-07-24 15:27
#   Describe      :
#
# ====================================================*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class toGetMedian {
public:
    void Insert(int num) {
       int size = maxheap.size() + minheap.size();
       if (size&1) {                                   //第偶数个的情况
            int tmp = num;
            if ((!maxheap.empty())&&(num < maxheap[0])) {
                tmp = maxheap[0];
                maxheap[0] = num;
                make_heap(maxheap.begin(),maxheap.end());
            }

            minheap.push_back(tmp); // 第偶数次插入minheap，插入的值：num，或者maxheap的最大值
            push_heap(minheap.begin(),minheap.end(),greater<int>());
       } else {
            int tmp = num;
            if ((!minheap.empty())&&(num > minheap[0])) {
                tmp = minheap[0];
                minheap[0] = num;
                make_heap(minheap.begin(),minheap.end(),greater<int>());
            }
            maxheap.push_back(tmp);
            push_heap(maxheap.begin(),maxheap.end());
       }
    }

    double GetMedian() {
        std::cout << maxheap.size() << " " << minheap.size() << std::endl;
        int size = maxheap.size() + minheap.size();
        double resu;
        if (size & 1) {
            resu = maxheap[0];
        } else {
            resu =  (maxheap[0] + minheap[0])/2.;
        }
        return resu;
    }
private:
    vector<int> maxheap;
    vector<int> minheap;
}; // end - toGetMedian

int main() {
    toGetMedian test;
    test.Insert(1);
    test.Insert(9);
    test.Insert(3);
    test.Insert(6);
    test.Insert(20);
    test.Insert(82);

    cout << test.GetMedian() << endl;
    test.Insert(4);
    test.Insert(2);
    cout << test.GetMedian() << endl;

    return 0;
} // end - main
