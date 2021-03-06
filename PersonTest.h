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
    std::string gets(const std::string &message);
    float getf(const std::string &message);
    int geti(const std::string &message);
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

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] int getTestNumber() const;

    std::vector<float> getResults();

    [[nodiscard]] int getNumberOfQuestions() const;

    bool operator>(const PersonTest &test) const;

    bool operator<(const PersonTest &test) const;

    PersonTest& operator=(const PersonTest &test);

    //TODO нужно ли использовать атрибут [[nodiscard]] и насколько необходимо использовать атрибуты?
    // захламление кода или необходимость?
    int compare(const PersonTest *other) const;

    static int comparator(const PersonTest *first, const PersonTest *second);

    bool check(const std::string &name,
               int test_number_min, int test_number_max,
               const std::vector<float> &lower_score_limit,
               const std::vector<float> &upper_score_limit);

    float GetProperty(const std::vector<float> &weights);

    bool operator==(const PersonTest &other);
};

#endif //INC_2SEM_PERSONTEST_H
