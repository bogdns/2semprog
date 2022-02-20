//
// Created by Salimov Bogdan on 14.02.2022.
//

#include "PersonTest.h"

PersonTest::PersonTest(const std::string &name, const int &test_number, const std::vector<float> &results) {
    this->name = name;
    this->test_number = test_number;
    this->results = results;
    this->number_of_questions = results.size();
}

void PersonTest::init(const std::string &name, const int &test_number, const std::vector<float> &results) {
    this->name = name;
    this->test_number = test_number;
    this->results = results;
    this->number_of_questions = results.size();
}

void PersonTest::copy(const PersonTest &other) {
    name = other.name;
    test_number = other.test_number;
    results = other.results;
}

void PersonTest::destroy() {
    name.clear();
    test_number = 0;
    results.clear();
}

void PersonTest::read() {

    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Test number: ";
    std::cin >> test_number;
    std::cout << "How many questions?";
    std::cin >> number_of_questions;
    std::cout << "Results: ";
    for (int i = 0; i < number_of_questions; ++i) {
        float temp;
        std::cin >> temp;
        results.push_back(temp);
    }

}

void PersonTest::read(std::ifstream &file) {
    std::string _name;
    int _test_number;
    int _number_of_questions;

    file >> name >> test_number >> number_of_questions;

    std::vector<float> _results(number_of_questions);
    for(float &i : _results) file >> i;

}

void PersonTest::write(std::ofstream &file) {
    file << name << ' ' << test_number << ' ' << number_of_questions << ' ';
    for (auto &i: results) {
        file << i << ' ';
    }
    file << '\n';
}



void PersonTest::write(std::ofstream &file) {

}

int PersonTest::compare(const PersonTest &other) {
    if (this->name < other.name) return -1;
    else if (this->name > other.name) return 1;
    else if (this->test_number > other.test_number) return 1;
    else if (this->test_number < other.test_number) return -1;
    return 0;
}

int PersonTest::comparator(const PersonTest &first, const PersonTest &second) {
    if (first.name < second.name) return -1;
    else if (first.name > second.name) return 1;
    else if (first.test_number > second.test_number) return 1;
    else if (first.test_number < second.test_number) return -1;
    return 0;
}

bool PersonTest::check(const std::string &name, int test_number_min, int test_number_max,
                       const std::vector<float> &lower_score_limit,
                       const std::vector<float> &upper_score_limit) {
    // the number of questions must match the size of the given arrays(l_s_l, u_s_l)
    if (number_of_questions != lower_score_limit.size() || number_of_questions != upper_score_limit.size()) {
        std::cerr << "Error in \"check\" function: invalid array size\n";
        return false;
    }

    if (name == "*" || this->name != name) return false;

    if (test_number < test_number_min || test_number > test_number_max) return false;

    for (auto cur = results.cbegin(), lwr = lower_score_limit.cbegin(),
                 upr = upper_score_limit.cbegin();
         cur != results.end();
         ++cur, ++lwr, ++upr) {

        if (*cur > *upr && *cur < *lwr) return false;
    }
    return true;
}

float PersonTest::GetProperty(const std::vector<float> &weights) {
    float result = 0;
    if (results.size() != weights.size()) {
        std::cerr << "Error in \"GetProperty\" function: invalid array size\n";
        return false;
    }
    for (auto cur = results.cbegin(), weight = weights.cbegin();
         cur < results.end(); ++cur, ++weight) {

        result += (*cur) * (*weight);
    }
    return result;
}

bool PersonTest::operator==(const PersonTest &other) {
    if (this->name == other.name && this->test_number == other.test_number) return true;
    return false;
}

PersonTest::PersonTest(const PersonTest &test) {
    copy(test);
}

void PersonTest::print() {
    std::cout << "Name: " << name << "Test number: " << test_number << ' ';
    if(!results.empty()) std::cout << '(' << results[0];
    for(int i = 1; i < results.size(); ++i){
        std::cout << ", " << results[i];
    }
    std::cout << ')';
}

PersonTest::PersonTest(){
    name = "";
    test_number = 0;
    number_of_questions = 0;
}




