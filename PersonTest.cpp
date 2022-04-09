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
    // safe read

    std::string name_ = gets("Name: ");
    int test_number_ = geti("Test number: ");

    if (test_number_ < 0) throw std::runtime_error("Test number cannot be less than 1");

    int number_of_questions_ = geti("Number of questions: ");

    if (number_of_questions_ <= 0) throw std::runtime_error("Number of questions cannot be less than 0!");
    std::vector<float> results_;
    std::cout << "Results: ";
    results_.reserve(number_of_questions_);
    for (int i = 0; i < number_of_questions_; ++i) {
        results_.push_back(getf(""));
    }
    name = name_;
    test_number = test_number_;
    number_of_questions = number_of_questions_;
    results = results_;
}

void PersonTest::read(std::ifstream &file) {
    // additional vars, if something goes wrong, the read data will not affect anything
    std::string _name;
    int _test_number;
    int _number_of_questions;

    file >> _name >> _test_number >> _number_of_questions;

    std::vector<float> _results(_number_of_questions);
    for (float &i: _results) file >> i;
    // the data will be written if the read data is correct
    name = _name;
    test_number = _test_number;
    number_of_questions = _number_of_questions;
    results = _results;
}

void PersonTest::write(std::ofstream &file) {
    //TODO как реализовать безопасную запись? Во время записи может что-то пойти не так и данные будут потерты
    file << name << ' ' << test_number << ' ' << number_of_questions << ' ';
    for (auto &i: results) {
        file << i << ' ';
    }
    file << '\n';
}

int PersonTest::compare(const PersonTest *other) const {
    if (this->name < other->name) return -1;
    else if (this->name > other->name) return 1;
    else if (this->test_number > other->test_number) return 1;
    else if (this->test_number < other->test_number) return -1;
    return 0;
}

int PersonTest::comparator(const PersonTest *first, const PersonTest *second) {
    return first->compare(second);
}

bool PersonTest::check(const std::string &name,
                       int test_number_min, int test_number_max,
                       const std::vector<float> &lower_score_limit,
                       const std::vector<float> &upper_score_limit) {

    // the number of questions must match the size of the given arrays(l_s_l, u_s_l)
    if (!(lower_score_limit.empty() && upper_score_limit.empty())) {
        if (lower_score_limit.size() != upper_score_limit.size())
            throw std::runtime_error("Lower score limit and upper must have same sizes");
        if (number_of_questions != lower_score_limit.size() || number_of_questions != upper_score_limit.size()) {
            return false;
        }
    }
    if (name != "*" && // skip condition
        this->name != name)
        return false;

    if (test_number_max < test_number_min) throw std::runtime_error("MAX cannot be less than MIN");

    if (test_number_min != -1 && test_number_max != -1 && // skip condition
        (test_number < test_number_min || test_number > test_number_max))
        return false;


    if (!lower_score_limit.empty()) { // skip condition
        // check lower and upper score limit
        for (auto cur = results.cbegin(), lwr = lower_score_limit.cbegin(),
                     upr = upper_score_limit.cbegin();
             cur != results.end();
             ++cur, ++lwr, ++upr) {

            if (*cur > *upr && *cur < *lwr) return false;
        }
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

PersonTest::PersonTest(
        const PersonTest &test) {
    copy(test);
}

void PersonTest::print() {
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "Name: " << name << "\nTest number: " << test_number << '\n';
    if (!results.empty()) std::cout << "Score: (" << results[0];
    for (int i = 1; i < results.size(); ++i) {
        std::cout << ", " << results[i];
    }
    std::cout << ")\n";
    std::cout << "-----------------------------------------------------------------------------\n";
}

PersonTest::PersonTest() {
    name = "";
    test_number = 0;
    number_of_questions = 0;
}

void PersonTest::init() {
    name = "";
    test_number = 0;
    number_of_questions = 0;
}

std::string PersonTest::getName() const {
    return name;
}

int PersonTest::getTestNumber() const {
    return test_number;
}

std::vector<float> PersonTest::getResults() {
    return results;
}

int PersonTest::getNumberOfQuestions() const {
    return number_of_questions;
}

std::string PersonTest::gets(const std::string &message) {
    std::cout << message;
    std::string temp;
    std::cin >> temp;
    return temp;
}

float PersonTest::getf(const std::string &message) {
    std::cout << message;
    float temp;
    std::cin >> temp;
    return temp;
}

int PersonTest::geti(const std::string &message) {
    std::cout << message;
    int temp;
    std::cin >> temp;
    return temp;
}

bool PersonTest::operator>(const PersonTest &test) const {
    if(compare(&test) == 1) return true;
    return false;
}

bool PersonTest::operator<(const PersonTest &test) const {
    if(compare(&test) == -1) return true;
    return false;
}

PersonTest &PersonTest::operator=(const PersonTest &test) {
    copy(test);
    return *this;
}
