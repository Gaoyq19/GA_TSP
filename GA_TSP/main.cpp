//
//  main.cpp
//  GA_TSP
//
//  Created by 高裕淇 on 2021/11/17.
//  Copyright © 2021 高裕淇. All rights reserved.
//

#include <iostream>
#include "GA.hpp"
#include "decode.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    
    Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/usr/local/lib/python3.9/site-packages')");
    PyRun_SimpleString("import matplotlib.pyplot as plt"); /*调用python文件*/
    GA ga(200,5000);
    Py_Finalize();
    return 0;
}
