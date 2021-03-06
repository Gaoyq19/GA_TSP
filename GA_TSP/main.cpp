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
    
    //GA *p = nullptr;
    vector<int> sequence;
    int minDistance = -1;
    double total = 0;
    for (int i = 0; i < 5; ++i) {
        GA ga(2000,5000);
        if (minDistance == -1 || ga.getmaxFItness() < minDistance) {
            sequence = ga.getGenotype(i);
            minDistance = ga.getmaxFItness();
        }
        total += ga.getmaxFItness();
        if (minDistance <= 7542) {
            cout<< "minDistance:" << minDistance << endl;
            for (int i = 0; i < sequence.size(); ++i) {
                cout << i + 1 << ": " << sequence[i] << " ";
            }
            cout << endl;
            Node::draw(sequence);
            Py_Finalize();
            return 0;
        }
    }
    cout<< "minDistance:" << minDistance << endl;
    cout<< "average:" << total / 5 <<endl;
    Node::draw(sequence);
    Py_Finalize();
    return 0;
}
