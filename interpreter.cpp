//
// Created by Salimov Bogdan on 18.02.2022.
//

#include "interpreter.h"

void Interpreter::run() {

    InterpreterShouldStop = false;
    while (!InterpreterShouldStop) {
        try {
            remainder = get_string();
            command = get_first_word(remainder); // now we can ignore extra params
            if ("-help" == command) help(); // вывести на экран список команд
            else if ("-clear" == command) clear(); // очистить список
            else if ("-load" == command) load();// <filename> добавить список из файла
            else if ("-save" == command) save(); // <filename> сохранить список в файле
            else if ("-add" == command) add(); // (переходит в режим ввода, начинающийся с ">") - добавить элемент
            else if ("-sort" == command) sort();// отсортировать
            else if ("-find" == command) find(); // <условия> вывести на экран элементы, удовлетворяющие условиям
            else if ("-delete" == command) remove(); // <условия> удалить элементы, удовлетворяющие условиям
            else if ("-exit" == command) quit(); // завершить работу и выйти.
        }
        catch (const std::exception &ex) {
            std::cerr << ex.what() << std::endl;
        }
    }
}

void Interpreter::help() {
    std::cout << "-help - вывести на экран список команд\n"
                 "-clear - очистить список\n"
                 "-load <имя файла> - добавить список из файла\n"
                 "-save <имя файла> - сохранить список в файле\n"
                 "-add (переходит в режим ввода, начинающийся с \">\") - добавить элемент\n"
                 "-sort - отсортировать\n"
                 "-find <условия> - вывести на экран элементы, удовлетворяющие условиям\n"
                 "-delete <условия> - удалить элементы, удовлетворяющие условиям\n"
                 "-exit - завершить работу и выйти.\n\n"
                 "<условия>: \n"
                 "имя(\"*\" - пропуск условия)\n"
                 "минимальный номер теста, максимальный номер теста(если номера тестов равны -1, то пропуск условия)\n"
                 "количество элементов массивов(0 - пропуск условия)\n"
                 "нижняя граница баллов, верхняя граница баллов\n";
}

void Interpreter::clear() {
    base->destroy();
}

void Interpreter::load() {
    base->read(get_first_word(remainder));
}

void Interpreter::save() {
    base->write(get_first_word(remainder));
}

void Interpreter::add() {
    auto *temp = new PersonTest();
    temp->read();
    base->add(temp);
}

void Interpreter::sort() {
    base->sort();
}

void Interpreter::find() {
    base->print(get_string("Name: "), get_integer("Min test number: "),
                get_integer("Max test number: "),
                get_integer("Number of numbers: "),
                get_vector("Lower score limit: "),
                get_vector("Upper score limit: "));
}

void Interpreter::remove() {
    base->remove(get_string("Name: "), get_integer("Min test number: "),
                 get_integer("Max test number: "),
                 get_integer("Number of numbers"),
                 get_vector("Lower score limit: "),
                 get_vector("Upper score limit: "));
}

void Interpreter::quit() {
    InterpreterShouldStop = true;
}

std::string Interpreter::get_string(const std::string &message) {
    char param[255];
    std::cout << message;
    std::cin.getline(param, 255);
    return param;
}

float Interpreter::get_float(const std::string &message) {
    float param;
    std::cout << message;
    std::cin >> param;
    return param;
}

int Interpreter::get_integer(const std::string &message) {
    int param;
    std::cout << message;
    std::cin >> param;
    return param;
}

std::vector<float> Interpreter::get_vector(const std::string &message) {
    int n;
    std::vector<float> vec;
    std::cout << "How many numbers: ";
    std::cin >> n;
    std::cout << "Numbers: ";
    for (int i = 0; i < n; ++i) {
        float temp;
        std::cin >> temp;
        vec.push_back(temp);
    }
    return vec;
}

std::string Interpreter::get_first_word(std::string &word) {
    std::string result;
    int start = 0;
    int end = 0;

    if (word.empty()) return result;

    while (start < word.size() && word[start] == ' ') ++start; // delete first spaces
    end = start;

    while (end < word.size() && word[end] != ' ') ++end;
    result = word.substr(start, end - start);
    word = word.substr(end, word.size() - end);
    return result;
}

Interpreter::Interpreter() {
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    base = new TestBase();
}

Interpreter::Interpreter(TestBase &testBase) : base(&testBase) {
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
}

Interpreter::~Interpreter() {
    delete base;
}



