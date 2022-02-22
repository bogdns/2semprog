//
// Created by Salimov Bogdan on 17.02.2022.
//

#include "TestBase.h"

TestBase::TestBase() {
    first = nullptr;
    last = nullptr;
    _size = 0;
}

TestBase::TestBase(const TestBase &testbase) {
    copy(testbase);
}

TestBase::~TestBase() {
    destroy();
}

void TestBase::add(PersonTest *element) {
    /*TODO
     * Проблема. Либо делать PersonTest как Node, либо создавать динамически PersonTest и Node,
     * который просто ссылается на PersonTest и имеет указатель на следующий PersonTest
     * так как при создании временного объекта и его инициализации после присваивания
     * ссылке он всё равно удаляется после завершения функции. Проблема!
    */
    Node *p = new Node(element);
    if (is_empty()) {
        first = p;
        last = p;
        ++_size;
        return;
    }
    last->next = p;
    p->prev = last;
    last = p;
    ++_size;
}

void TestBase::sort() {
    // 1) Create array to optimize sorting
    // 2) Sort this array
    // 3) Change node's next and prev, so they are in the correct order
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
    last = sortarray[_size - 1];
    last->next = nullptr;
    if (first != last) {
        last->prev = sortarray[_size - 2];
        first->next = sortarray[1];
    }
    for (int i = 1; i < _size - 1; ++i) {
        sortarray[i]->prev = sortarray[i - 1];
        sortarray[i]->next = sortarray[i + 1];
    }
    delete[] sortarray;
}

void TestBase::addToSorted(PersonTest *element) {
    if (_size == 0) {
        add(element);
        return;
    }
    Node *elem = new Node(element);
    Node *cur_node = first;
    // add before first element
    if (PersonTest::comparator(first->test, elem->test) == 1) {
        elem->next = cur_node;
        cur_node->prev = elem;
        return;
    }
    // add before second ... last element
    while (cur_node != nullptr) {
        if (cur_node->test->compare(elem->test) != -1) {
            elem->next = cur_node;
            elem->prev = cur_node->prev;

            cur_node->prev->next = elem;
            cur_node->prev = elem;
            return;
        }
        cur_node = cur_node->next;
    }
    // add after last element
    last->next = elem;
    elem->prev = last;
    last = elem;
}

std::ifstream &TestBase::operator>>(std::ifstream &file) {
    // TODO
    return file;
}

std::ofstream &TestBase::operator<<(std::ofstream &file) {
    // TODO
    return file;
}

void TestBase::remove(const std::string &name,
                      const int test_number_min, const int test_number_max,
                      const std::vector<float> &lower_score_limit,
                      const std::vector<float> &upper_score_limit) {

    if (is_empty()) return;


    Node *cur_elem = first->next;

    //remove elements between first and last
    if (_size > 2) {
        while (cur_elem->next != nullptr) {
            if (cur_elem->test->check(name, test_number_min, test_number_max, lower_score_limit,
                                      upper_score_limit)) {
                cur_elem->prev->next = cur_elem->next;
                cur_elem->next->prev = cur_elem->prev;
                Node *temp = cur_elem->next;
                delete cur_elem->test;
                delete cur_elem;
                cur_elem = temp;
                --_size;
                continue;
            }
            cur_elem = cur_elem->next;
        }
    }
    if (_size == 1) {
        if (cur_elem->test->check(name, test_number_min, test_number_max, lower_score_limit,
                                  upper_score_limit)) {
            destroy();
        }
        return;
    }
    // remove first element
    if (first->test->check(name, test_number_min, test_number_max, lower_score_limit,
                           upper_score_limit)) {
        Node *temp = first->next;
        first->next->prev = nullptr;
        delete first->test;
        delete first;
        first = temp;
        --_size;
    }
    // remove last element
    if (last->test->check(name, test_number_min, test_number_max, lower_score_limit,
                          upper_score_limit)) {
        if (_size == 1) {
            destroy();
            return;
        }
        Node *temp = last->prev;
        last->prev->next = nullptr;
        delete last->test;
        delete last;
        last = temp;
        --_size;
    }
}

void TestBase::copy(const TestBase &other) {
    destroy();
    Node *cur_elem = other.first;
    for (int i = 0; i < other._size; ++i) {
        auto *temp = new PersonTest(cur_elem->test->getName(), cur_elem->test->getTestNumber(),
                                    cur_elem->test->getResults());
        add(temp);
        cur_elem = cur_elem->next;
    }
}

void TestBase::destroy() {
    Node *p = first;
    Node *temp;
    while (p) {
        temp = p->next;
        delete p->test;
        delete p;
        p = temp;
    }
    first = nullptr;
    last = nullptr;
    _size = 0;
}

void TestBase::read(const std::string &path) {
    std::ifstream fin;
    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fin.open(path);
    // additional vars, if something goes wrong, the read data will not affect anything
    auto first_ = first;
    auto last_ = last;
    auto size_ = _size;
    first = nullptr;
    last = nullptr;
    _size = 0;
    int n;
    try {
        fin >> n;
        for (int i = 0; i < n; ++i) {
            auto *temp = new PersonTest();
            temp->read(fin);
            add(temp);
        }
    }
    catch (const std::exception &ex) {
        destroy();
        first = first_;
        last = last_;
        _size = size_;
        throw ex;
    }

    // delete old TestBase
    TestBase a;
    a._size = size_;
    a.first = first_;
    a.last = last_;
    // will delete automatically after function end
}

void TestBase::write(const std::string &path) {
    // TODO как реализовать безопасную запись? Во время записи может что-то пойти не так и данные будут потерты

    std::ofstream fout;
    fout.open(path);
    fout << _size << '\n';
    for (auto cur_elem = first; cur_elem != nullptr; cur_elem = cur_elem->next)
        cur_elem->test->write(fout);
}

void TestBase::print(const std::string &name,
                     int test_number_min, int test_number_max,
                     const std::vector<float> &lower_score_limit, const std::vector<float> &upper_score_limit) {

    for (auto i = first; i != nullptr; i = i->next) {
        if (i->test->check(name, test_number_min, test_number_max, lower_score_limit,
                           upper_score_limit)) {
            i->test->print();
        }
    }
}

void TestBase::getBallList(int test_number) {
    auto i = first;
    while (i != nullptr) {
        if (i->test->check("*", test_number, test_number, std::vector<float>(), std::vector<float>())) {
            i->test->print();
        }
        i = i->next;
    }
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

int TestBase::size() const {
    return _size;
}


TestBase::Node::Node(PersonTest *persontest) : test(persontest), next(nullptr), prev(nullptr) {}


