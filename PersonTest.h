//
// Created by Salimov Bogdan on 14.02.2022.
//
#ifndef INC_2SEM_PERSONTEST_H
#define INC_2SEM_PERSONTEST_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class PersonTest {
private:
    std::string name;
    int test_number;
    std::vector<float> results;
    unsigned long number_of_questions;

public:
    PersonTest(const std::string &name, const int &test_number, const std::vector<float> &results);

    PersonTest(const PersonTest& test);

    PersonTest();

    void init(const std::string &name, const int &test_number, const std::vector<float> &results);

    void copy(const PersonTest &other);

    void destroy();

    void read();

    void read(std::ifstream &file);

    void write(std::ofstream &file);

    void print();

    int compare(const PersonTest &other);

    static int comparator(const PersonTest &first, const PersonTest &second);

    bool check(const std::string &name, int test_number_min, int test_number_max,
               const std::vector<float> &lower_score_limit,
               const std::vector<float> &upper_score_limit);

    float GetProperty(const std::vector<float> &weights);

    bool operator==(const PersonTest &other);
};

#endif //INC_2SEM_PERSONTEST_H
