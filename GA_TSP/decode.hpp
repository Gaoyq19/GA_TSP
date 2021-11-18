//
//  decode.hpp
//  GA_TSP
//
//  Created by 高裕淇 on 2021/11/17.
//  Copyright © 2021 高裕淇. All rights reserved.
//

#ifndef decode_hpp
#define decode_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <Python.h>
class Node{
private:
    static const std::vector<double> node;
    static std::pair<double,double> getNode(int i){
        if (2 * i + 1 >= node.size()) {
            throw "out of range";
        }
        return std::make_pair(node[2 * i], node[2 * i + 1]);
    }
    static double twoPointsDistance(int a, int b){
        std::pair<double, double> pA = getNode(a);
        std::pair<double, double> pB = getNode(b);
        double i = pow(pA.first - pB.first, 2);
        double j = pow(pA.second - pB.second, 2);
        return sqrt( i + j );
    }
public:
    static void draw(std::vector<int> sequence){
        
        std::string command;
        std::string x = "[";
        std::string y = "[";
        for (int i = 0; i < sequence.size(); ++i) {
            x += std::to_string(getNode(sequence[i]).first);
            x += ",";
            y += std::to_string(getNode(sequence[i]).second);
            y += ",";
        }
        x += "]";
        y += "]";
        command = "plt.plot(" + x + "," + y + ")";
        PyRun_SimpleString(command.c_str());
        PyRun_SimpleString("plt.show()");
    }
    static double getDistance(std::vector<int> sequence){
        double distance = 0;
        for (int i = 0; i < sequence.size() - 1; ++i) {
            distance += twoPointsDistance(sequence[i], sequence[i + 1]);
        }
        distance += twoPointsDistance(sequence[sequence.size() - 1], sequence[0]);
        return distance;
    }
};
const std::vector<double> Node::node = {
    565.0, 575.0,
    25.0, 185.0,
    345.0, 750.0,
    945.0, 685.0,
    845.0, 655.0,
    880.0, 660.0,
    25.0, 230.0,
    525.0, 1000.0,
    580.0, 1175.0,
    650.0, 1130.0,
    1605.0, 620.0,
    1220.0, 580.0,
    1465.0, 200.0,
    1530.0, 5.0,
    845.0, 680.0,
    725.0, 370.0,
    145.0, 665.0,
    415.0, 635.0,
    510.0, 875.0,
    560.0, 365.0,
    300.0, 465.0,
    520.0, 585.0,
    480.0, 415.0,
    835.0, 625.0,
    975.0, 580.0,
    1215.0, 245.0,
    1320.0, 315.0,
    1250.0, 400.0,
    660.0, 180.0,
    410.0, 250.0,
    420.0, 555.0,
    575.0, 665.0,
    1150.0, 1160.0,
    700.0, 580.0,
    685.0, 595.0,
    685.0, 610.0,
    770.0, 610.0,
    795.0, 645.0,
    720.0, 635.0,
    760.0, 650.0,
    475.0, 960.0,
    95.0, 260.0,
    875.0, 920.0,
    700.0, 500.0,
    555.0, 815.0,
    830.0, 485.0,
    1170.0, 65.0,
    830.0, 610.0,
    605.0, 625.0,
    595.0, 360.0,
    1340.0, 725.0,
    1740.0, 245.0,
};
#endif /* decode_hpp */
