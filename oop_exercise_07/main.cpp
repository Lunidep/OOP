//����� ���� ��������
//�80-206�-20

//������������ ������ �7
//������� � 22. 
//������: 5 - �������� 6 - �������� 8 - ��������


//��������������� � ����������(document.h) ���������� ����������� editor.h, � ������� ����� ������ �� ��������(������ �����) � ���� ������
//��������������� ������ � ������ �� ����� ���������� � factory.h
//������� ������������� � command.h, ��� ���������� ��� ���������� undo

/*
���������� � ����������� ���������:
    �������� ������ ���������
    ������ ��������� �� �����
    ������� ��������� � ����
    �������� ������������ ��������� (�������� �������� �������)
    �������� ������������ ���������
    ����������� ��������� �� ������ (������ ������� ����������� �������� � �� ������������� � std::cout)
    ����������� �������� undo, ���������� ��������� ��������� ��������. ������ ����������� ��� �������� ����������/�������� �����.

���������� � ����������:
    �������� ����������� ���������� ���������� ������� � ��������� ����� � Factory.
    ������� ���� �� ������������� ������������ ��� ������ � ��������;
    �������������� � ������������� (���� ������) ����������� � ������� main;
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
