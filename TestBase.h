//
// Created by Salimov Bogdan on 17.02.2022.
//

#ifndef INC_2SEM_TESTBASE_H
#define INC_2SEM_TESTBASE_H

#include "PersonTest.h"

class TestBase {
private:
    struct Node{
        PersonTest &test;
        Node *next = nullptr;
        Node *prev = nullptr;


        explicit Node(PersonTest &test);
        Node &operator=(const Node &other);
        bool operator==(const Node &other) const;
        bool operator!=(const Node &other);
    };

    struct BaseIterator{
        Node *node;
        explicit BaseIterator(Node &element);
        // prefix increment
        BaseIterator& operator++();

        // prefix decrement
        BaseIterator& operator--();
    };

    Node *first = nullptr;
    Node *last = nullptr;
    int _size = 0;

    Node **sortarray = nullptr; // sort optimisation (O(1) element access)

    void sort_q(int l, int r);

public:
    TestBase();

    TestBase(const TestBase &testbase);

    ~TestBase();

    void read(const std::string &path);

    void write(const std::string &path);

    BaseIterator begin();
    BaseIterator end();

    void add(PersonTest &element);

    bool is_empty() const;

    void sort();

    void addToSorted(const PersonTest &element);

    std::ifstream &operator>>(std::ifstream &file);

    std::ofstream &operator<<(std::ofstream &file);

    void remove(const std::string &name, int test_number_min, int test_number_max,
                int number_of_numbers,
                const std::vector<float> &lower_score_limit,
                const std::vector<float> &upper_score_limit);

    void destroy();

    void copy(const TestBase &testBase);

    void print(const std::string &name, int test_number_min, int test_number_max,
               int number_of_numbers,
               const std::vector<float> &lower_score_limit,
               const std::vector<float> &upper_score_limit);

    PersonTest &getBallList(int test_number);
};

#endif //INC_2SEM_TESTBASE_H
