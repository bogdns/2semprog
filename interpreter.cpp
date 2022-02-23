//
// Created by Salimov Bogdan on 18.02.2022.
//

#include "interpreter.h"

void Interpreter::run() {
    InterpreterShouldStop = false;
    while (!InterpreterShouldStop) {
        try {
            /*TODO костыль, так как почему-то после ввода данных, например, в -add
             * откуда-то не пойми откуда считывается дополнительный перевод строки
             * и получается вывод: "> > " вместо "> " так как
             */
            if (!(hist[hist.size() - 1].empty() && !hist[hist.size() - 2].empty())) std::cout << "> ";
//            std::cout << "> ";
            remainder = get_string();
            hist.push_back(remainder);
            command = get_first_word(remainder); // now we can ignore extra params
            if (command.empty()) {}
            else if ("-help" == command) help(); // вывести на экран список команд
            else if ("-clear" == command) clear(); // очистить список
            else if ("-load" == command) load();// <filename> добавить список из файла
            else if ("-save" == command) save(); // <filename> сохранить список в файле
            else if ("-add" == command) add(); // (переходит в режим ввода, начинающийся с ">") - добавить элемент
            else if ("-sort" == command) sort();// отсортировать
            else if ("-find" == command) find(); // <условия> вывести на экран элементы, удовлетворяющие условиям
            else if ("-delete" == command) remove(); // <условия> удалить элементы, удовлетворяющие условиям
            else if ("-history" == command) print_hist();
            else if ("-exit" == command) quit(); // завершить работу и выйти.
            else std::cout << "Command not found" << std::endl;
        }
        catch (const std::ios_base::failure &ex) {
            if (std::cin.eof()) {
                std::cin.clear();
                quit();
            } else {
                //NOTE cerr медленнее cout и к тому же это разные несинхронизированные потоки, что в итоге
                // приводит к тому, что несмотря на более ранний вызов cerr последующий cout отрабатывает раньше,
                // поэтому я использовую cout с цветным текстом вместо cerr
                std::cin.clear();
                std::cout << RED << ex.what() << RESET << '\n';
            }
        }
        catch (const std::exception &ex) {
            std::cout << RED << ex.what() << RESET << std::endl;
            std::cin.clear();
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
                 "нижняя граница баллов, верхняя граница баллов(если количество 0, то пропуск условия)\n";
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
                get_vector("Lower score limit: "),
                get_vector("Upper score limit: "));
}

void Interpreter::remove() {
    base->remove(get_string("Name: "), get_integer("Min test number: "),
                 get_integer("Max test number: "),
                 get_vector("Lower score limit: "),
                 get_vector("Upper score limit: "));
}

void Interpreter::quit() {
    InterpreterShouldStop = true;
}

std::string Interpreter::get_string(const std::string &message) {
    std::string temp;
    std::cout << message;
    std::getline(std::cin, temp);
    return temp;
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
    std::cout << message << std::endl;
    std::cout << "How many numbers: ";
    std::cin >> n;
    if (n < 0) throw std::runtime_error("Size cannot be less than zero!");
    if (n != 0)std::cout << "Numbers: ";
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
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit | std::ios_base::eofbit);
}

Interpreter::~Interpreter() {
    delete base;
}

void Interpreter::print_hist() {
    std::cout << "History:" << std::endl;
    for (int i = 1; i < hist.size(); ++i) {
        std::cout << '\"' << hist[i] << '\"' << std::endl;
    }
}



