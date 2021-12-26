//Попов Илья Павлович
//М80-206Б-20

//Лабораторная работа №8
//Вариант № 24
//Фигуры - квадрат, треугольник, 8-угольник

/*
Программа считывает из стандартного ввода данные фигур, согласно варианту задания, выводит их характеристики на экран и записывать в файл.
*/

/*
Программа должна:
1. Осуществлять ввод из стандартного ввода данных фигур, согласно варианту задания;
2. Программа должна создавать классы, соответствующие введенным данных фигур;
3. Программа должна содержать внутренний буфер, в который помещаются фигуры. Для создания буфера допускается использовать стандартные контейнеры STL. Размер буфера задается параметром командной строки. Например, для буфера размером 10 фигур: oop_exercise_08 10
4. При накоплении буфера они должны запускаться на асинхронную обработку, после чего буфер должен очищаться;
5. Обработка должна производиться в отдельном потоке;
6. Реализовать два обработчика, которые должны обрабатывать данные буфера:
a. Вывод информации о фигурах в буфере на экран;
b. Вывод информации о фигурах в буфере в файл. Для каждого буфера должен создаваться файл с уникальным именем.
7. Оба обработчика должны обрабатывать каждый введенный буфер. Т.е. после каждого заполнения буфера его содержимое должно выводиться как на экран, так и в файл.
8. Обработчики должны быть реализованы в виде лямбда-функций и должны хранится в специальном массиве обработчиков. 
   Откуда и должны последовательно вызываться в потоке – обработчике.
9. В программе должно быть ровно два потока (thread). Один основной (main) и второй для обработчиков;
10. В программе должен явно прослеживаться шаблон Publish-Subscribe. Каждый обработчик должен быть реализован как отдельный подписчик.
11. Реализовать в основном потоке (main) ожидание обработки буфера в потоке-обработчике. Т.е. после отправки буфера на обработку основной поток должен ждать, 
    пока поток обработчик выведет данные на экран и запишет в файл.
*/

#include <vector>
#include "subscriber.h"


void usage() {
    cout << "______________________________________" << endl;
    cout << "Available commands:\n";
    cout << "add <square, triangle, octagon>\n";
    cout << "menu - print this menu\n";
    cout << "exit\n";
    cout << "______________________________________" << endl;
}

bool is_number(const string& s) {
    bool point = false;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '-' && i == 0) {
            continue;
        }
        else if (s[i] == '.') {
            if ((i == 0 || i == s.length() - 1) || point) {
                return false;
            }
            else {
                point = true;
            }
        }
        else if (s[i] < '0' || s[i] > '9') { return false; }
    }
    return true;
}

int main(int argc,char* argv[]) {
    try {
        if (argc != 2) {
            throw logic_error("2 arguments needed!\n\n");
            return -1;
        }
        usage();

        if (!is_number(argv[1])) {
            throw logic_error("Wrong argument!\n\n");
            return -2;
        }

        int cur = stoi(argv[1]);

        if (cur <= 0) {
            throw logic_error("Wrong argument!\n\n");
            return -3;
        }
    }
    catch (invalid_argument& err) {
        cout << err.what() << '\n\n';
    }

    int  buffer_size = stoi(argv[1]);

    shared_ptr<vector<shared_ptr<figure>>> buffer = make_shared<vector<shared_ptr<figure>>>();
    buffer->reserve(buffer_size);

    factory factory;
    
    subscriber sub;
    sub.processors.push_back(make_shared<stream_processor>());
    sub.processors.push_back(make_shared<file_processor>());
    thread sub_thread(ref(sub));

    bool quit = false;
    string cmd;
    try {
        while (!quit) {
            unique_lock<mutex> locker(sub.mtx);

            cin >> cmd;
            if (cmd == "add") {
                buffer->push_back(factory.new_figure(cin));
                cout << "Figure has been successfuly added!";
                cout << endl << "______________________________________" << endl;


                if (buffer->size() == buffer_size) {
                    cout << "Buffer is full\n";
                    sub.buffer = buffer;
                    sub.cond_var.notify_all();
                    sub.cond_var.wait(locker, [&](){ return sub.buffer == nullptr;});
                    buffer->clear();
                }
            } 
            else if (cmd == "menu") {
                usage();
            }
            else if (cmd == "exit")  {
                quit = true;
            } 
            else {
                cout << "Wrong command\n";
            }
        }
    } 
    catch (logic_error &err) {
        cout << err.what() << "\n\n";
    }


    sub.stop = true;
    sub.cond_var.notify_all();
    sub_thread.join();

    return 0;
}
