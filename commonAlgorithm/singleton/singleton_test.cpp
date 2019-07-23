
/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : anlongfei
#   Email         : 在 vimrc 文件中添加 let g:file_copyright_email = 'your email'
#   File Name     : singleton_test.cpp
#   Last Modified : 2019-07-23 17:20
#   Describe      :
#
# ====================================================*/

#include <iostream>
#include "singleton.h"
using namespace std;
class Test {
    public:
        void sayHi() {
            std::cout << "hi !" << std::endl;
        }
};
int main() {
    singleton<Test>::getInstance()->sayHi();
    return 0;
}

// g++ singleton_test.cpp -O3 -I. -std=c++11


