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
    int maxFitness = -1;
    int eIndividuals;
    int mutationP = 5;
    int crossoverP = 70;
public:
    void calFitness(){
        for (int i = 0; i < genotype.size(); ++i) {
            int dis = Node::getDistance(genotype[i]);
            if (maxFitness == -1 || dis < maxFitness) {
                maxFitness = dis;
                eIndividuals = i;
            }
            fitness[i] = dis;
        }
    }
    void draw(int i){
        Node::draw(genotype[i]);
    }
    void selection(){
        srand((unsigned int)time(0));
        int size = 2;
        std::vector<std::vector<int>> selectedGenotype;
        for (int i = 0; i < individuals; ++i) {
            int min = -1;
            for (int j = 0; j < size; ++j) {
                int r = rand() % individuals;
                if (min == -1 || fitness[r] < fitness[min]) {
                    min = r;
                }
            }
            selectedGenotype.push_back(genotype[min]);
        }
        genotype = selectedGenotype;
    }
    void crossover(){
        srand((unsigned int)time(0));
        int size = genotype[0].size();
        std::vector<std::vector<int>> childGenotype;
        for (int i = 0; i < genotype.size() - 1; i += 2) {
            int r = rand() % 100;
            if (r > crossoverP) {
                childGenotype.push_back(genotype[i]);
                childGenotype.push_back(genotype[i + 1]);
                continue;
            }
            int start = rand() % size;
            int end = rand() % size;
            if (start > end) {
                std::swap(start, end);
            }
            std::vector<int> parent1 = genotype[i];
            std::vector<int> parent2 = genotype[i + 1];
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
    void mutation(){
        srand((unsigned int)time(0));
        for (int i = 0; i < individuals; ++i) {
            int r = rand() % 500;
            if (r < mutationP) {
                int k = rand() % 52;
                int k1 = rand() % 52;
                std::swap(genotype[i][k1], genotype[i][k]);
            }
        }
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
                used[tmp] = true;
                sequence[j] = tmp;
            }
            genotype.push_back(sequence);
        }
    }
    GA(int individuals, int generations){
        this->individuals = individuals;
        encode(individuals);
        fitness = std::vector<double>(individuals);
        draw(0);
        for (int i = 0; i < generations; ++i) {
            calFitness();
            selection();
            crossover();
            mutation();
            std::cout << "minDistance:" << maxFitness<< std::endl;
        }
        draw(eIndividuals);
    }
};
#endif /* GA_hpp */
