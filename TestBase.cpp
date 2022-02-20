//
// Created by Salimov Bogdan on 17.02.2022.
//

#include "TestBase.h"

TestBase::TestBase() {

}

TestBase::TestBase(const TestBase &testbase) {

}

TestBase::~TestBase() {
    destroy();
}

void TestBase::add(PersonTest &element) {
    ++_size;
    Node *p = new Node(element);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }

    last->next = p;
    p->prev = last;
    last = p;
}

void TestBase::sort() {
    if (is_empty()) return;
    sortarray = new Node *[_size];
    Node *current_elem = first;
    for (int i = 0; i < _size; ++i) {
        sortarray[i] = current_elem;
        current_elem = current_elem->next;
    }
    sort_q(0, _size - 1);
    first = sortarray[0];
    first->prev = nullptr;
    first->next = sortarray[1];
    last = sortarray[_size - 1];
    last->next = nullptr;
    if (first != last) last->prev = sortarray[_size - 2];
    else last->prev = nullptr;
    for (int i = 1; i < _size - 1; ++i) {
        sortarray[i]->prev = sortarray[i - 1];
        sortarray[i]->next = sortarray[i + 1];
    }
    delete sortarray;
}

void TestBase::addToSorted(const PersonTest &element) {

}

//std::ifstream &TestBase::operator>>(std::ifstream &file) {
//    read(file);
//    return file;
//}
//
//std::ofstream &TestBase::operator<<(std::ofstream &file) {
//    write(file);
//    return file;
//}




void TestBase::remove(const std::string &name,
                      const int test_number_min, const int test_number_max,
                      int number_of_numbers,
                      const std::vector<float> &lower_score_limit,
                      const std::vector<float> &upper_score_limit) {

}

void TestBase::copy(const TestBase &testBase) {

}

void TestBase::destroy() {
    Node *p = first;
    Node *temp;
    while (p) {
        temp = p->next;
        delete p;
        p = temp;
    }
    first = nullptr;
    last = nullptr;
    _size = 0;
}

void TestBase::read(const std::string &path) {

}

void TestBase::write(const std::string &path) {

}

void TestBase::print(const std::string &name,
                     int test_number_min, int test_number_max,
                     int number_of_numbers,
                     const std::vector<float> &lower_score_limit, const std::vector<float> &upper_score_limit) {

}

PersonTest &TestBase::getBallList(int test_number) {
}

bool TestBase::is_empty() const {
    return (_size == 0);
}

void TestBase::sort_q(int l, int r) {
    if (r > l) {
        int R = r;
        int L = l;
        int m = (l + r) / 2;
        while (r >= l) {
            while (PersonTest::comparator(sortarray[l]->test, sortarray[m]->test) == -1 && l <= r) l++;
            while (PersonTest::comparator(sortarray[m]->test, sortarray[r]->test) == -1 && r >= l) r--;
            if (l <= r) {
                std::swap(sortarray[l], sortarray[r]);
                l++;
                r--;
            }
        }
        sort_q(L, r);
        sort_q(l, R);
    }
}

TestBase::BaseIterator TestBase::begin() {
    return BaseIterator(*first);
}

TestBase::BaseIterator TestBase::end() {
    return BaseIterator(*last);
}

TestBase::Node &TestBase::Node::operator=(const TestBase::Node &other) {
    this->test = other.test;
    this->next = other.next;
    return *this;
}

bool TestBase::Node::operator==(const TestBase::Node &other) const {
    return (this->test == other.test);
}

bool TestBase::Node::operator!=(const TestBase::Node &other) {
    return false;
}

TestBase::Node::Node(PersonTest &test) : test(test) {}

TestBase::BaseIterator::BaseIterator(Node &element) {
    *node = element;
}

TestBase::BaseIterator &TestBase::BaseIterator::operator++() {
    if (node == nullptr) std::cerr << "Iterator reached upper edge";
    else node = node->next;
    return *this;
}

TestBase::BaseIterator &TestBase::BaseIterator::operator--() {
    if (node == nullptr) std::cerr << "Iterator reached lower edge";
    else node = node->prev;
    return *this;
}

