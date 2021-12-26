//����� ���� ��������
//�80-206�-20

//������������ ������ �6
//������� � 20
//������ - ��������
//��������� - �������
//��������� - �������

/*
������� ������ ������������ ���������, �������� �������� �������:
1.   	��������� ������ ���� ����������� � ������� ����� ���������� (std::shared_ptr, std::weak_ptr). ����������� ������������� std::unique_ptr.
2.   	� �������� ��������� ������� ��������� ������ ��������� ��� ������.
3.   	��������� ������ ��������� ����� �������:
o	���� � pop, push, top;
o	������� � pop, push, top;
o	������, ������������ ������ � ������ � �������� �� ��������� [].
4.   	����������� ���������, ������� �������� ������������� ������ ������ (���������� ������ ������ � �������� ���������� ������� ����������). ������ ��������� ������ ������� ��������� �� ������������ ���� ������ � ������������ ��������� ���������� �� ��������� �����. ������������ ��������� ������ ��������������� �������� ������� (������������ ������, ������, ����, �������).
5.   	��������� ������ ������������ ��������� ��� ��������� � ������������ ������ ��� ����� ���������.
6.   	��������� ������ ���� ��������� � ������������ std::map � std::list (����������� � vector).
7.   	����������� ���������, �������:
o	��������� ������� � ���������� ������ (� ����� int � �������� ��������� ������� ������) � ��������� � ��������� ������������ ���������;
o	��������� ������� ������� �� ��������� �� ������ ��������;
o	������� �� ����� ��������� ������ c ������� std::for_each.

*/



#include <iostream>
#include <string> 
#include <algorithm>
#include <functional> 
#include "trapezoid.h"
#include "queue.h"
#include "allocator.h"

const int alloc_size = 280;

void usage() {
	std::cout << "______________________________________" << std::endl;
	std::cout << "Add - to add an item to queue(Push/Iter).\n";
	std::cout << "Del - Delete an item from queue(Pop/Iter).\n";
	std::cout << "Print - print queue.\n";
	std::cout << "Front - first element of queue.\n";
	std::cout << "Back - last element of queue.\n";
	std::cout << "Count_if - number of objects with an area less than the specified one..\n";
	std::cout << "Menu.\n";
	std::cout << "Exit.\n";
	std::cout << "______________________________________" << std::endl;
}

bool is_number(const std::string& s) {
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

int main() {
	Queue<Trapezoid<int>, allocator<Trapezoid<int>, alloc_size>> q;

	std::string cmd, cur;

	usage();

	while (std::cin >> cmd) {
		try {
			if (cmd == "Add") {
				std::cout << "Add an item to the back of the queue[Push] or to the iterator position[Iter]" << std::endl;
				std::cin >> cmd;
				if (cmd == "Push") {
					
					std::cout << "Input points: ";
					std::string str_a, str_b, str_h;
					std::cout << "\na = "; std::cin >> str_a;
					std::cout << "\nb = "; std::cin >> str_b;
					std::cout << "\nh = "; std::cin >> str_h;
					if (!is_number(str_a) || !is_number(str_b) || !is_number(str_h)) {
						throw std::invalid_argument("Invalid input!\n\n");
						continue;
					}
					unsigned int a, b, h;
					a = stoi(str_a);
					b = stoi(str_b);
					h = stoi(str_h);
						
					Trapezoid<int> t(a,b,h);
					/*
					try {
						std::cin >> t;
					}
					catch (std::exception& e) {
						std::cout << e.what() << std::endl;
						continue;
					}*/
					try {
						q.Push(t);
					}
					catch (std::bad_alloc& e) {
						std::cout << e.what() << std::endl;
						continue;
					}
					std::cout << "Figure is added." << std::endl;
				}
				else if (cmd == "Iter") {

					std::cout << "Input points: ";
					std::string str_a, str_b, str_h;
					std::cout << "\na = "; std::cin >> str_a;
					std::cout << "\nb = "; std::cin >> str_b;
					std::cout << "\nh = "; std::cin >> str_h;
					if (!is_number(str_a) || !is_number(str_b) || !is_number(str_h)) {
						throw std::invalid_argument("Invalid input!\n\n");
						continue;
					}
					unsigned int a, b, h;
					a = stoi(str_a);
					b = stoi(str_b);
					h = stoi(str_h);

					Trapezoid<int> t(a, b, h);
					/*
					try {
						std::cin >> t;
					}
					catch (std::exception& e) {
						std::cout << e.what() << std::endl;
						continue;
					}*/
					std::cout << "Input index: ";

					unsigned int i;
					std::cin >> cur;
					if (!is_number(cur)) {
						throw std::invalid_argument("Invalid input!\n\n");
						continue;
					}
					i = stoi(cur);

					if (i > q.Size()) {
						std::cout << "The index must be less than the number of elements" << std::endl;
						continue;
					}
					Queue<Trapezoid<int>, allocator<Trapezoid<int>, alloc_size>>::ForwardIterator it = q.Begin();
					for (unsigned int cnt = 0; cnt < i; cnt++) {
						it++;
					}
					try {
						q.Insert(it, t);
					}
					catch (std::bad_alloc& e) {
						std::cout << e.what() << std::endl;
						continue;
					}
					std::cout << "Figure is added." << std::endl;
				}
				else {
					throw std::invalid_argument("Invalid input!\n\n");
					std::cin.clear();
					std::cin.ignore(30000, '\n');
					continue;
				}
			}
			else if (cmd == "Del") {
				if (q.Empty()) {
					throw std::invalid_argument("Queue is empty\n\n");
					continue;
				}
				std::cout << "Delete item from front of queue[Pop] or to the iterator position[Iter]" << std::endl;
				std::cin >> cmd;
				if (cmd == "Pop") {
					q.Pop();
					std::cout << "Figure is removed." << std::endl;
				}
				else if (cmd == "Iter") {
					std::cout << "Input index: ";
					unsigned int i;
					std::cin >> cur;
					if (!is_number(cur)) {
						throw std::invalid_argument("Invalid input!\n\n");
						continue;
					}
					i = stoi(cur);
					if (i > q.Size()) {
						throw std::invalid_argument("The index must be less than the number of elements\n\n");
						continue;
					}
					Queue<Trapezoid<int>, allocator<Trapezoid<int>, alloc_size>>::ForwardIterator it = q.Begin();
					for (unsigned int cnt = 0; cnt < i; cnt++) {
						it++;
					}
					q.Erase(it);
					std::cout << "Figure is removed." << std::endl;
				}
				else {
					throw std::invalid_argument("Invalid input!\n\n");
					std::cin.clear();
					std::cin.ignore(30000, '\n');
					continue;
				}
			}
			else if (cmd == "Print") {
				std::cout << "______________________________________" << std::endl;
				q.Print();
				std::cout << "______________________________________" << std::endl;
			}
			else if (cmd == "Front") {
				Trapezoid<int> value;
				try {
					value = q.Front();
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
					continue;
				}
				std::cout << value << std::endl;
			}
			else if (cmd == "Back") {
				Trapezoid<int> value;
				try {
					value = q.Back();
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
					continue;
				};
				std::cout << value << std::endl;
			}
			else if (cmd == "Count_if") {
				std::cout << "Input area: ";
				double area;
				std::cin >> cur;
				if (!is_number(cur)) {
					throw std::invalid_argument("Invalid input!\n\n");
					continue;
				}
				area = stod(cur);
				std::cout << "The number of figures with an area less than a given = " << std::count_if(q.Begin(), q.End(), [area](Trapezoid<int> t) {
					return Area(t) < area;
					}) << std::endl;
			}
			else if (cmd == "Menu") {
				usage();
			}
			else if (cmd == "Exit") {
				break;
			}
			else {
				throw std::invalid_argument("Invalid input!\n\n");
				std::cin.clear();
				std::cin.ignore(30000, '\n');
			}
		}
		catch (std::invalid_argument& arg) {
			std::cout << arg.what() << std::endl;
		}
	}


	return 0;
}