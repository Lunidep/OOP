//����� ���� ��������
//�80-206�-20

//������������ ������ �8
//������� � 24
//������ - �������, �����������, 8-��������

/*
��������� ��������� �� ������������ ����� ������ �����, �������� �������� �������, ������� �� �������������� �� ����� � ���������� � ����.
*/

/*
��������� ������:
1. ������������ ���� �� ������������ ����� ������ �����, �������� �������� �������;
2. ��������� ������ ��������� ������, ��������������� ��������� ������ �����;
3. ��������� ������ ��������� ���������� �����, � ������� ���������� ������. ��� �������� ������ ����������� ������������ ����������� ���������� STL. ������ ������ �������� ���������� ��������� ������. ��������, ��� ������ �������� 10 �����: oop_exercise_08 10
4. ��� ���������� ������ ��� ������ ����������� �� ����������� ���������, ����� ���� ����� ������ ���������;
5. ��������� ������ ������������� � ��������� ������;
6. ����������� ��� �����������, ������� ������ ������������ ������ ������:
a. ����� ���������� � ������� � ������ �� �����;
b. ����� ���������� � ������� � ������ � ����. ��� ������� ������ ������ ����������� ���� � ���������� ������.
7. ��� ����������� ������ ������������ ������ ��������� �����. �.�. ����� ������� ���������� ������ ��� ���������� ������ ���������� ��� �� �����, ��� � � ����.
8. ����������� ������ ���� ����������� � ���� ������-������� � ������ �������� � ����������� ������� ������������. 
   ������ � ������ ��������������� ���������� � ������ � �����������.
9. � ��������� ������ ���� ����� ��� ������ (thread). ���� �������� (main) � ������ ��� ������������;
10. � ��������� ������ ���� �������������� ������ Publish-Subscribe. ������ ���������� ������ ���� ���������� ��� ��������� ���������.
11. ����������� � �������� ������ (main) �������� ��������� ������ � ������-�����������. �.�. ����� �������� ������ �� ��������� �������� ����� ������ �����, 
    ���� ����� ���������� ������� ������ �� ����� � ������� � ����.
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
