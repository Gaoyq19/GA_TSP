//
//  GA.hpp
//  GA_TSP
//
//  Created by 高裕淇 on 2021/11/18.
//  Copyright © 2021 高裕淇. All rights reserved.
//

#ifndef GA_hpp
#define GA_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "decode.hpp"
class GA{
private:
    int individuals;
    std::vector<std::vector<int>> genotype;
    std::vector<double> fitness;
    std::vector<int> elite;
    int eliteFit;
    int minDistance = INT32_MAX; //最大适应度,即最小距离
    int aveFitness = 0;
    double pm = 3; //变异概率
    double pc = 70; //交叉概率
    
public:
    std::vector<int> getGenotype(int i);
    int getmaxFItness();
    int geteIndividuals();
    void calFitness();
    void draw(int i); //调用Node类的画图函数,对路径进行画图, 输入为一个序列(基因型)
    void selection(); //二元锦标赛
    void crossover(); //顺序交叉
    void mutation(); //随机交换两个节点
    void initializePopulation(int size); //对初始种群编码,随机生成路径
    void saveElite();
    GA(int individuals, int generations);
};
std::vector<int> GA::getGenotype(int i){
    return genotype[i];
}
int GA::getmaxFItness(){
    return eliteFit;
}
void GA::calFitness(){
    eliteFit = INT32_MAX;
    for (int i = 0; i < genotype.size(); ++i) {
        //计算适应度,并记录最优个体及其适应度.
        int dis = Node::getDistance(genotype[i]);
        if (dis < minDistance) {
            minDistance = dis;
        }
        if (dis < eliteFit) {
            eliteFit = dis;
            elite = genotype[i];
        }
        fitness[i] = dis;
        aveFitness += (dis - aveFitness) / (i + 1);
    }
}
void GA::draw(int i){
    Node::draw(genotype[i]);
}
void GA::selection(){
    srand((unsigned int)time(0));
    int size = 2;
    std::vector<std::vector<int>> selectedGenotype;
    for (int i = 0; i < individuals; ++i) {
        int min = -1;
        std::map<int,bool> occ;
        //随机选两个个体,取最优放入下一代,直到选够N
        for (int j = 0; j < size; ++j) {
            int r = rand() % individuals;
            while (occ[r]) {
                r = rand() % individuals;
            }
            occ[r] = true;
            if (min == -1 || fitness[r] < fitness[min]) {
                min = r;
            }
        }
        selectedGenotype.push_back(genotype[min]);
    }
    genotype = selectedGenotype;
}
void GA::crossover(){
    pc = 70;
    srand((unsigned int)time(0));
    int size = genotype[0].size();
    std::vector<std::vector<int>> childGenotype;
    std::map<int,bool> occ;
    for (int i = 0; i < genotype.size() / 2; ++i) {
        int r = rand() % 100;
        int k1 = rand() % individuals;
        int k2 = rand() % individuals;
        while (occ[k1]) {
            k1 = rand() % individuals;
        }
        occ[k1] = true;
        while (occ[k2]) {
            k2 = rand() % individuals;
        }
        occ[k2] = true;
        
        int larger = std::max(Node::getDistance(genotype[k1]), Node::getDistance(genotype[k2]));
        if (larger <= aveFitness) {
            int a = (larger - eliteFit);
            int b = (aveFitness - eliteFit);
            if(b <= 50){
                pc = 90;
            }else{
                double c = (double)a / b;
                pc = 60 * c;
                if(pc == 0){
                    pc = 40;
                }
            }
            
        }else{
            pc = 90;
        }

        if (r > pc) {
            childGenotype.push_back(genotype[k1]);
            childGenotype.push_back(genotype[k2]);
            continue;
        }
        //固定start - end 段基因
        int start = rand() % size;
        int end = rand() % size;
        if (start > end) {
            std::swap(start, end);
        }
        
        std::vector<int> parent1 = genotype[k1];
        std::vector<int> parent2 = genotype[k2];
        std::map<int, bool> part1;
        std::map<int, bool> part2;
        std::vector<int> child1(size);
        std::vector<int> child2(size);
        for (int j = start; j <= end; ++j) {
            child1[j] = parent1[j];
            child2[j] = parent2[j];
            part1[parent1[j]] = true;
            part2[parent2[j]] = true;
        }
        //
        int p1 = 0;
        int p2 = 0;
        for (int j = 0; j < size; ++j) {
            if (!part1.count(parent2[j])) {
                if (p1 == start) {
                    p1 = end + 1;
                }
                child1[p1] = parent2[j];
                ++p1;
            }
            if (!part2.count(parent1[j])) {
                if (p2 == start) {
                    p2 = end + 1;
                }
                child2[p2] = parent1[j];
                ++p2;
            }
        }
        childGenotype.push_back(child1);
        childGenotype.push_back(child2);
    }
    genotype = childGenotype;
}
void GA::mutation(){
    pm = 6;
    srand((unsigned int)time(0));
    
    for (int i = 0; i < individuals; ++i) {
        int fit = Node::getDistance(genotype[i]);
        if (fit <= aveFitness) {
            int a = fit - eliteFit;
            int b = aveFitness - eliteFit;
            if(b <= 40){
                pm = 600;
            }else{
                double c = (double)a / b;
                pm = 6 * c;
                if(pm == 0){
                    pm = 4;
                }
            }
            
        }else{
            pm = 10;
        }
        int r = rand() % 1000;
        if (r < pm) {
            int k2 = rand() % 52;
            int k1 = rand() % 52;
            int l = std::min(k1,k2);
            int r = std::max(k1,k2);
            for (int p = l; p < (l + r) / 2; ++p) {
                std::swap(genotype[i][p],genotype[i][r - p]);
            }
        }
    }
}
void GA::initializePopulation(int size){
    srand((unsigned int)time(0));
    for (int i = 0; i < size; ++i) {
        std::vector<int> sequence(52);
        std::vector<bool> used(52,false);
        for (int j = 0; j < 52; ++j) {
            int tmp = rand() % 52;
            //生成非重复节点
            while (used[tmp]) {
                tmp = rand() % 52;
            }
            used[tmp] = true;
            sequence[j] = tmp;
        }
        genotype.push_back(sequence);
    }
}
void GA::saveElite(){
    int minD = INT_MAX;
    int maxD = 0;
    int maxOrder = 0;
    for (int i = 0; i < genotype.size(); ++i) {
        int dis = Node::getDistance(genotype[i]);
        if (dis > maxD) {
            maxD = dis;
            maxOrder = i;
        }
        if (dis < minD){
            minD = dis;
        }
    }
    if (minD > eliteFit) {
        genotype[maxOrder] = elite;
    }
    
}
GA::GA(int individuals, int generations){
    this->individuals = individuals;
    initializePopulation(individuals);
    fitness = std::vector<double>(individuals);
    for (int i = 0; i < generations; ++i) {
        calFitness();
        selection();
        crossover();
        mutation();
        saveElite();
        std::cout << "minDistance:" << minDistance << " ave:" << aveFitness << std::endl;
        if (minDistance <= 7550) {
            break;
        }
    }
}
#endif /* GA_hpp */
