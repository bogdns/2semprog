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
    int number_of_questions;

public:
    PersonTest(const std::string &name, const int &test_number, const std::vector<float> &results);

    PersonTest(const PersonTest &test);

    PersonTest();

    void init();

    void init(const std::string &name, const int &test_number, const std::vector<float> &results);

    void copy(const PersonTest &other);

    void destroy();

    void read();

    void read(std::ifstream &file);

    void write(std::ofstream &file);

    void print();

    std::string getName();

    int getTestNumber() const;

    std::vector<float> getResults();

    int getNumberOfQuestions() const;

    //TODO нужно ли использовать атрибут [[nodiscard]] и насколько необходимо использовать атрибуты?
    // захламление кода или необходимость?
    int compare(const PersonTest *other) const;

    static int comparator(const PersonTest *first, const PersonTest *second);

    bool check(const std::string &name,
               int test_number_min, int test_number_max,
               int number_of_numbers,
               const std::vector<float> &lower_score_limit,
               const std::vector<float> &upper_score_limit);

    float GetProperty(const std::vector<float> &weights);

    bool operator==(const PersonTest &other);
};

#endif //INC_2SEM_PERSONTEST_H
