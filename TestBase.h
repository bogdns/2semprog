//
// Created by Salimov Bogdan on 17.02.2022.
//

#ifndef INC_2SEM_TESTBASE_H
#define INC_2SEM_TESTBASE_H

#include "PersonTest.h"

class TestBase {
private:
    struct Node {
        PersonTest *test;
        Node *next;
        Node *prev;

        explicit Node(PersonTest *test);
    };

    Node *first;
    Node *last;
    int _size;

    Node **sortarray = nullptr; // sort optimisation (O(1) element access)

    void sort_q(int l, int r);

public:
    TestBase();

    TestBase(const TestBase &testbase);

    ~TestBase();

    void read(const std::string &path);

    void write(const std::string &path);

    void read(std::ifstream &file);

    void write(std::ofstream &file);

    void add(PersonTest *element);

    [[nodiscard]] int size() const;

    [[nodiscard]] bool is_empty() const;

    void sort();

    void addToSorted(PersonTest *element);

    void remove(const std::string &name, int test_number_min, int test_number_max,
                const std::vector<float> &lower_score_limit,
                const std::vector<float> &upper_score_limit);

    void destroy();

    void copy(const TestBase &other);

    void print(const std::string &name, int test_number_min, int test_number_max,
               const std::vector<float> &lower_score_limit,
               const std::vector<float> &upper_score_limit);

    void getBallList(int test_number);
};

std::ifstream &operator>>(std::ifstream &file, TestBase &testBase);

std::ofstream &operator<<(std::ofstream &file, TestBase &testBase);

#endif //INC_2SEM_TESTBASE_H
