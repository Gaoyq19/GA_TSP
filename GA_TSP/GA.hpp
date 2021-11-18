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
public:
    void calFitness(){
        for (int i = 0; i < genotype.size(); ++i) {
            fitness.push_back(Node::getDistance(genotype[i]));
            std::cout<<fitness[i]<<std::endl;
        }
    }
    void draw(){
        for (auto i : genotype) {
            Node::draw(i);
        }
        
    }
    void selection(){
        
    }
    void crossover(){
        
    }
    void encode(int size){
        srand((unsigned int)time(0));
        for (int i = 0; i < size; ++i) {
            std::vector<int> sequence(52);
            std::vector<bool> used(52,false);
            for (int j = 0; j < 52; ++j) {
                int tmp = rand() % 52;
                while (used[tmp]) {
                    tmp = rand() % 52;
                }
                sequence[j] = tmp;
            }
            genotype.push_back(sequence);
        }
    }
    GA(int individuals, int generations){
        this->individuals = individuals;
        encode(individuals);
        calFitness();
        selection();
    }
};
#endif /* GA_hpp */
