/*
Группа М80-206Б-20
Студент: Попов Илья Павлович

Задание:
Создать шаблон динамической коллекцию, согласно варианту задания:
1. Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr;
2. В качестве параметра шаблона коллекция должна принимать тип данных - шестиугольник;
3. Реализовать forward_iterator по коллекции;
4. Коллекция должны возвращать итераторы begin() и  end();
5. Коллекция должна содержать метод вставки на позицию итератора insert(iterator);
6. Коллекция должна содержать метод удаления из позиции итератора erase(iterator);
7. При выполнении недопустимых операций (например выход за границы коллекции или удаление несуществующего элемента) необходимо генерировать исключения;
8. Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if)
9. Список должен содержать метод доступа к элементу по оператору [].
10.	 Реализовать программу, которая:
	позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
	позволяет удалять элемент из коллекции по номеру элемента;
	выводит на экран введенные фигуры c помощью std::for_each;
	выводит на экран количество объектов, у которых площадь меньше заданной (с помощью  std::count_if).

Варинат 15
Фигура: шестиугольник
Контейнер: список

*/
#include <iostream>
#include <cstdlib>
#include <string> 
#include <algorithm>
#include <functional> 
#include "TListItem.h"
#include "TList.h"

void usage() {
	cout << "1. Add new item in begin of list." << endl;
	cout << "2. Add new item in end of list." << endl;
	cout << "3. Delete item from list" << endl;
	cout << "4. Print list." << endl;
	cout << "5. Insert in list" << endl;
	cout << "6. Erase list." << endl;
	cout << "7. Print menu." << endl;
	cout << "8. Print list with iterator." << endl;
	cout << "9. Number of objects with an area less than the specified one." << endl;
	cout << "0. Exit out program." << endl << endl;
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


int main() {
	TList<Hexagon> list;
	string cur, ind_cur;
	int menuNum = 7; 
	int ind;
	int i = 1;
	shared_ptr<Hexagon> sptr;

	while (menuNum != 0) {
		try {
			switch (menuNum) {
			case 1:
				sptr = make_shared<Hexagon>(cin);
				list.addFirst(sptr);
				cout << "Figure is added." << endl;
				break;
			case 2:
				sptr = make_shared<Hexagon>(cin);
				list.addLast(sptr);
				cout << "Figure is added." << endl;
				break;
			case 3:
				cout << "Enter an index." << endl;
				cin >> ind_cur;
				if (!is_number(ind_cur)) {
					menuNum = 7;
					throw invalid_argument("Index error!\n\n");
					break;
				}
				ind = stoi(ind_cur);
				if (ind < 0) {
					menuNum = 7;
					throw invalid_argument("Index error!\n\n");
					break;
				}
				list.delElement(ind);
				cout << "Figure is deleted." << endl;
				break;
			case 4:
				cout << list << endl;
				break;
			case 5:
				sptr = make_shared<Hexagon>(cin);
				cout << "Enter an index." << endl;
				cin >> ind_cur;
				if (!is_number(ind_cur)) {
					menuNum = 7;
					throw invalid_argument("Index error!\n\n");
					break;
				}
				ind = stoi(ind_cur);
				if (ind < 0) {
					menuNum = 7;
					throw invalid_argument("Index error!\n\n");
					break;
				}
				list.insert(ind, sptr);
				cout << "Figure is added." << endl;
				break;
			case 6:
				list.eraseList();
				cout << "The list is cleared." << endl;
				break;
			case 7:
				usage();
				break;
			case 8:
				for (auto i : list) {
					i->Print();
				}
				break;
			case 9:
				long double n;
				cout << "Enter the number " << endl;
				cin >> n;
				for (auto figure : list) {
					if (figure->area() < n) {
						cout << "[" << i << "]";
						figure->Print();
					}
					i++;
				}
				break;
			}
			cin >> cur;
			if (!is_number(cur)) {
				menuNum = 7;
				throw invalid_argument("Incorrect input!\n\n"); 
			}
			menuNum = stoi(cur);
		}
		catch (invalid_argument& arg) {
			cout << arg.what() << endl;
		}
	}
	
	system("pause");
	return 0;
}

/*
1. Add new item in begin of list.
2. Add new item in end of list.
3. Delete item from list
4. Print list.
5. Insert in list
6. Erase list.
7. Print menu.
8. Print list with iterator.
9. Number of objects with an area less than the specified one.
0. Exit out program.

1
Side =1
Figure is added.
1
Side =2
Figure is added.
1
Side =3
Figure is added.
2
Side =4
Figure is added.
2
Side =5
Figure is added.
2
Side =6
Figure is added.
4
[1]a=3
   area=31.1769

[2]a=2
   area=13.8564

[3]a=1
   area=3.4641

[4]a=4
   area=55.4256

[5]a=5
   area=86.6025

[6]a=6
   area=124.708


8
a=3
   area=31.1769

a=2
   area=13.8564

a=1
   area=3.4641

a=4
   area=55.4256

a=5
   area=86.6025

a=6
   area=124.708

7
1. Add new item in begin of list.
2. Add new item in end of list.
3. Delete item from list
4. Print list.
5. Insert in list
6. Erase list.
7. Print menu.
8. Print list with iterator.
9. Number of objects with an area less than the specified one.
0. Exit out program.

3
Enter an index of figure you want to delete
1
Figure is deleted.
3
Enter an index of figure you want to delete
5
Figure is deleted.
4
[1]a=2
   area=13.8564

[2]a=1
   area=3.4641

[3]a=4
   area=55.4256

[4]a=5
   area=86.6025


5
Side =7
Please, enter an index.
1
Figure is added.
5
Side =8
Please, enter an index.
5
Figure is added.
4
[1]a=7
   area=169.741

[2]a=2
   area=13.8564

[3]a=1
   area=3.4641

[4]a=4
   area=55.4256

[5]a=8
   area=221.703

[6]a=5
   area=86.6025


9
Enter the number
70.1
[2]a=2
   area=13.8564

[3]a=1
   area=3.4641

[4]a=4
   area=55.4256

0
Для продолжения нажмите любую клавишу . . .
List deleted!
*/