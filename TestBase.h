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

        bool operator==(const Node &other);

        bool operator!=(const Node &other);
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

    void add(PersonTest *element);

    bool is_empty() const;

    void sort();

    void addToSorted(PersonTest *element);

    std::ifstream &operator>>(std::ifstream &file);

    std::ofstream &operator<<(std::ofstream &file);

    void remove(const std::string &name, int test_number_min, int test_number_max,
                int number_of_numbers,
                const std::vector<float> &lower_score_limit,
                const std::vector<float> &upper_score_limit);

    void destroy();

    void copy(const TestBase &other);

    void print(const std::string &name, int test_number_min, int test_number_max,
               int number_of_numbers,
               const std::vector<float> &lower_score_limit,
               const std::vector<float> &upper_score_limit);

    void getBallList(int test_number);
};

#endif //INC_2SEM_TESTBASE_H
