//
// Created by Salimov Bogdan on 18.02.2022.
//

#ifndef INC_2SEM_INTERPRETER_H
#define INC_2SEM_INTERPRETER_H

#include "TestBase.h"

class Interpreter {
private:
    TestBase *base{};
    bool InterpreterShouldStop = false;
    std::string command;
    std::string remainder;

    std::vector<float> get_vector(const std::string &message); // get array from interpreter
    std::string get_first_word(std::string &word);
    std::string get_command(); // get command from interpreter
    std::string get_string(const std::string &message = ""); // get string parameters from interpreter
    int get_integer(const std::string &message = ""); // get integer parameters from interpreter
    float get_float(const std::string &message = ""); // get float parameters from interpreter
public:
    explicit Interpreter(TestBase &testBase);

    Interpreter();

    void run(); // run interpreter

    // supported commands

    void help();

    void clear();

    void load();

    void save();

    void add();

    void sort();

    void find();

    void remove();

    void quit();
};

#endif //INC_2SEM_INTERPRETER_H
