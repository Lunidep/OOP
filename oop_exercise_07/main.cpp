//Попов Илья Павлович
//М80-206Б-20

//Лабораторная работа №7
//Вариант № 22. 
//Фигуры: 5 - угольник 6 - угольник 8 - угольник


//Взаимодействуем с документом(document.h) происходит посредством editor.h, в котором лежат ссылки на документ(вектор фигур) и стек команд
//Перенаправление записи и вывода из файла происходят в factory.h
//Команды отслеживаются в command.h, что необходимо для реализации undo

/*
Требование к функционалу редактора:
    создание нового документа
    импорт документа из файла
    экспорт документа в файл
    создание графического примитива (согласно варианту задания)
    удаление графического примитива
    отображение документа на экране (печать перечня графических объектов и их характеристик в std::cout)
    реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для операций добавления/удаления фигур.

Требования к реализации:
    Создание графических примитивов необходимо вынести в отдельный класс – Factory.
    Сделать упор на использовании полиморфизма при работе с фигурами;
    Взаимодействие с пользователем (ввод команд) реализовать в функции main;
*/

#include <iostream>
#include "factory.h"
#include "editor.h" 

void usage() {
    cout << "______________________________________" << endl;
    cout << "Available commands:\n";
    cout << "create <path> - create a new file\n";
    cout << "save - save data to a file\n";
    cout << "add <hexagon, pentagon trapezoid>\n";
    cout << "remove <index> - remove a figure by index\n";
    cout << "print\n";
    cout << "undo - undo the last action\n";
    cout << "load <path> - load data from a file\n";
    cout << "______________________________________" << endl << endl;
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

void create(editor& edit) {
    string tmp;
    cin >> tmp;
    edit.CreateDocument(tmp);
    cout << "Create success\n\n";
}

void load(editor& edit) {
    string tmp;
    cin >> tmp;
    try {
        edit.LoadDocument(tmp);
        cout << "Load success\n\n";
    } catch (runtime_error& e) {
        cout << e.what() << "\n\n";
    }
}

void save(editor& edit) {
    string tmp;
    try {
        edit.SaveDocument();
    } catch (runtime_error& err) {
        cout << err.what() << "\n\n";
    }
}

void add(editor& edit) {
    factory fac;
    try {
        shared_ptr<figure> newElem = fac.FigureCreate(cin);
        edit.InsertInDocument(newElem);
    } catch (logic_error& err) {
        cout << err.what() << "\n\n";
    }
}

void remove(editor& edit) {
    try {
        string str;
        cin >> str;
        if (!is_number(str)) {
            cout << "Index error!\n\n";
        }
        else {
            uint32_t index = stoi(str);
            edit.DeleteInDocument(index);
        }
    
    } catch (logic_error& err) {
        cout << err.what() << "\n\n";
    }
}

int main() {
    usage();
    editor edit;
    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "help") {
            usage();
        } else if (cmd == "create") {
            create(edit);
        } else if (cmd == "load") {
            load(edit);
        } else if (cmd == "save") {
            save(edit);
        } else if (cmd == "exit") {
            break;
        } else if (cmd == "add") {
            add(edit);
        } else if (cmd == "remove") {
            remove(edit);
        } else if (cmd == "print") {
            edit.PrintDocument();
        } else if (cmd == "undo") {
            try {
                edit.Undo();
                cout << "Undo success\n\n";
            } catch (logic_error& err) {
                cout << err.what() << "\n\n";
            }
        } else {
            cout << "Error input!\n\n";
        }
        cout << "______________________________________" << endl;
    }
    return 0;
}
