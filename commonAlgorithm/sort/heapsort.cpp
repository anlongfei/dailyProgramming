
/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : anlongfei
#   Email         : 在 vimrc 文件中添加 let g:file_copyright_email = 'your email'
#   File Name     : heapsort.cpp
#   Last Modified : 2019-07-24 11:28
#   Describe      :
#
# ====================================================*/

#include <iostream>
using namespace std;

void heapadjust(int vec[], int p, int n) {
    int temp = vec[p];
    for (auto i = p*2; i <= n; i = i*2) {
        if (i < n && vec[i] < vec[i+1]) {
            i++;
        }
        if (temp > vec[i]) {
            break;
        }
        vec[p] = vec[i];
        p = i;
    }
    vec[p] = temp;
}

void heapsort(int vec[], int size) {
    for (auto i = size/2; i >= 1; i--) {
        heapadjust(vec, i, size);
    }
    for (auto i = size; i >= 1; i--) {
        swap(vec[1], vec[i]);
        heapadjust(vec, 1, i-1);
    }
}

int main() {
    int i;
    int a[11] = {-1, 5, 2, 6, 0, 3, 9, 1, 7, 4, 8 };
    heapsort(a, 9);
    for (i = 1; i <= 10; i++)
        std::cout << a[i] << std::endl;
    heapadjust(a, 5, 10);
    for (i = 1; i <= 10; i++)
        std::cout << a[i] << std::endl;
}

