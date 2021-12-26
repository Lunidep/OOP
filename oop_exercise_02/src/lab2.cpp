/*
Создать класс BitString для работы с 128-битовыми строками.
Битовая строка должна быть представлена двумя полями типа unsigned long long.
Должны быть реализованы все традиционные операции для работы с битами: and &, or |, xor ^, not ~.
Реализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное количество битов.
Реализовать операцию вычисления количества единичных битов, операции сравнения по количеству единичных битов.
Реализовать операцию проверки включения.
*/

#include <iostream>
#include <cmath>
#include <string> 
using namespace std;
using ull = unsigned long long;

string dec_to_two(const ull a);

class BitString {
private:
    ull lo;//младшие байты числа
    ull hi;//старшие байты числа
	int ko_vo_ed;//кол-во единичных битов в числе
public:
    BitString() : lo(0), hi(0), ko_vo_ed(0) {}
    BitString(ull h, ull l) : lo(l), hi(h) {}

    ull hight() const { return hi; }
    ull low() const { return lo; }

	void cmp(const  BitString& b1) {//сравнение по кол-ву единичных битов
		cout << ko_vo_ed;
		if (ko_vo_ed > b1.ko_vo_ed) {
			cout << " > ";
		}
		else if (ko_vo_ed = b1.ko_vo_ed) {
			cout << " = ";
		}
		else {
			cout << " < ";
		}
		cout << b1.ko_vo_ed;
	}
	

	/////////////////////////////////////////////////////////////////////////////////
	void shiftRight(int a) {//Сдавиг вправо на заданное количество битов
		if (a < 0) {
			cout << "Ошибка! Сдвиг не может производиться на отрицательное число!" << endl;
			exit(3);
		}
		if (a < 64) {
			lo = lo >> a;
			/**/
			ull f1 = (hi << (64 - a));
			lo = lo | f1;
			hi = hi >> a;
		}
		else if (a >= 64 && a < 128) {
			lo = 0;
			ull f1 = hi >> (a - 64);
			lo = lo | f1;
			hi = hi >> (128 - a);
		}
		else {//случай, когда сдвиг > 128, тогда все число сдвигается и остается 0
			lo = 0;
			hi = 0;
		}
	}

	void shiftLeft(int a) {//Сдавиг влево на заданное количество битов
		if (a < 0) {
			cout << "Ошибка! Сдвиг не может производиться на отрицательное число!" << endl;
			exit(3);
		}
		if (a < 64) {
			hi = hi << a;
			ull f2 = lo >> (64 - a);
			lo = lo << a;
			hi = hi | f2;
		}
		else if (a >= 64 && a < 128) {
			hi = hi << a;
			ull f2 = lo;
			f2 = f2 << (a - 64);
			lo = 0;
			hi = hi | f2;
		}
		else if (a >= 128) {//случай, когда сдвиг > 128, тогда все число сдвигается и остается 0
			hi = 0;
			lo = 0;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
	void scan(const string& str) {//считываем из строки два unsigned long long числа
		ull cur_hi = 0;
		ull cur_lo = 0;
		int count_step = 0;
		if(str.size() > 64) {//случай, когда надо задействовать старшие байты числа
			for (int i = 0; i < str.size(); i++) {
				if ((str[i] - '0') == 1) {//операция вычисления количества единичных битов
					ko_vo_ed++;
				}
				
				if (i < str.size() - 64) {//условие, позволяющее отличить старшие биты от младших
					cur_hi = (cur_hi << 1) + (str[i] - '0');
					if (cur_hi == 0) {//условие, позволяющее не потерять нулевые биты(для чисел, старшие байты которых начинаются с 0)
						count_step++;
					}
				}
				else {
					cur_lo = (cur_lo << 1) + (str[i] - '0');
				}
			}
		}
		else {//случай, когда не надо задействовать старшие байты числа
			for (int i = 0; i < str.size(); i++) {
				if ((str[i] - '0') == 1) {
					ko_vo_ed++;
				}
				cur_lo = (cur_lo << 1) + (str[i] - '0');
			}
		}
		
		hi = cur_hi;
		lo = cur_lo;
		if (count_step) {
			hi *= pow(2, count_step);
		}
	}

	bool is_include(const BitString& b1) {//операция проверки включения
		string s, p;
		if (hi){
			s = dec_to_two(hi);
			if (dec_to_two(lo).length() < 64) {
				string str;
				for (int i = dec_to_two(lo).length(); i < 64; i++) {
					str.push_back('0');
				}
				s = s + str;
			}
			s = s + dec_to_two(lo);
		}
		else { s = dec_to_two(lo); }

		if (b1.hight()) { 
			p = dec_to_two(b1.hight());
			if (dec_to_two(b1.low()).length() < 64) {
				string str;
				for (int i = dec_to_two(b1.low()).length(); i < 64; i++) {
					str.push_back('0');
				}
				p = p + str;
			}
			p = p + dec_to_two(b1.low());
		}
		else { p = dec_to_two(b1.low());  }


		cout << s << endl << p << endl;

		int i, j;
		for (i = 0; i < s.length(); i++) {
			for (j = 1; j < p.length(); j++) {
				if (s[i + j] != p[j]) {
					break;
				}
			}
			if (j == p.length()) {
				cout << "INCLUDE!\n";
				return true;
			}
		}
		cout << "NOT INCLUDE!\n";
	}

    friend istream& operator>> (istream& in, BitString& b);
};

/////////////////////////////////////////////////////////////////////////////////
bool is_bin_number(const string& s) {//проверка входных данных
	bool otr = false;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] < '0' || s[i] > '1') {
			return false;
		}
	}
	return true;
}

istream& operator>> (istream& in, BitString& b) {//перегруженный оператор для ввода
	cout << "\nВведите свою Bitstring:\n";
	string str;
	cin >> str;

	if (str.length() > 128) {
		cout << "Ошибка! Число слишком большое!" << endl;
		exit(1);
	}
	if (!is_bin_number(str)) {
		cout << "Ошибка! Некорректный ввод." << endl;
		exit(2);
	}

	b.scan(str);

	return in;
}

string dec_to_two(const ull a) {//числа в полях ull представлены в 10-ичном виде, чтобы сделать их читаемыми юзаем эту функцию
	string str;
	ull cur_a = a;
	while (cur_a > 0) {
		str.push_back((cur_a % 2) + '0');
		cur_a /= 2;
	}
	string res;
	for (int i = str.length(); i >= 0; i--) {
		res.push_back(str[i]);
	}
	return res;
}

ostream& operator<< (ostream& out, const BitString& b) {//перегруженный оператор для выввода
	//cout << b.hight() << "    " << b.low() << endl;
	if (b.hight()){//если у числа есть старшие байты, а младшие байты не заполнены до конца(их не 64), то дозаполняем вывод нулями
		cout << dec_to_two(b.hight());// << "    ";
		int length = dec_to_two(b.low()).length();
		while (length <= 64) {
			cout << "0";
			length++;
		}
		//cout << " " << dec_to_two(b.low()) << endl << endl;
		cout << dec_to_two(b.low()) << endl << endl;
	}
	else {
		cout << dec_to_two(b.low()) << endl << endl;
	}
	return out;
}

/////////////////////////////////////////////////////////////////////////////////
//традиционные операции для работы с битами: and &, or |, xor ^, not ~

BitString operator & (const  BitString& b1, const  BitString& b2) {
	ull res_hi = b1.hight() & b2.hight();
	ull res_lo = b1.low() & b2.low();
	BitString res(res_hi, res_lo);
	return res;
}

BitString operator | (const  BitString& b1, const  BitString& b2) {
	ull res_hi = b1.hight() | b2.hight();
	ull res_lo = b1.low() | b2.low();
	BitString res(res_hi, res_lo);
	return res;
}

BitString operator ^ (const  BitString& b1, const  BitString& b2) {
	ull res_hi = b1.hight() ^ b2.hight();
	ull res_lo = b1.low() ^ b2.low();
	BitString res(res_hi, res_lo);
	return res;
}

BitString operator ~ (const  BitString& b1) {
	BitString res(~b1.hight(), ~b1.low());
	return res;
}
/////////////////////////////////////////////////////////////////////////////////


int main() {
	setlocale(LC_ALL, "rus");
	BitString a, b;

	cin >> a >> b;
	cout << "----------------------------------------------------------------------------\n";

	cout << "Ваши BitStrings:\n";
	cout << a << b;
	/**/
	cout << "----------------------------------------------------------------------------\n";

	cout << "Традиционные операции для работы с битами: and &, or |, xor ^, not ~:\n";
	cout << "a & b = " << (a & b);
	cout << "a | b = " << (a | b);
	cout << "a ^ b = " << (a ^ b);
	cout << "~a = " << ~a;
	cout << "~b = " << ~b;
	
	cout << "----------------------------------------------------------------------------\n";

	cout << "Введите числа для демонстрации сдвигов чисел(первое - для сдвига влево, второе - для сдвига вправо):\n";
	int num1, num2;
	cin >> num1 >> num2;
	cout << "\nСдвиги числа №1:\n";
	BitString cur_la = a;
	BitString cur_ra = a;
	cur_la.shiftLeft(num1);
	cur_ra.shiftRight(num2);
	cout << "Влево: " << cur_la;
	cout << "Вправо: " << cur_ra;

	cout << "Сдвиги числа №2:\n";
	BitString cur_lb = b;
	BitString cur_rb = b;
	cur_lb.shiftLeft(num1);
	cur_rb.shiftRight(num2);
	cout << "Влево: " << cur_lb;
	cout << "Вправо: " << cur_rb;

	cout << "----------------------------------------------------------------------------\n";
	
	cout << "Сравним количество единичных битов в числах:\n\n";
	a.cmp(b);
	
	cout << "\n\n----------------------------------------------------------------------------\n";

	cout << "\nПроверим включение числа №2 в число №1:\n";
	a.is_include(b);
	cout << "\nПроверим включение числа №1 в число №2:\n";
	b.is_include(a);

}
//Набор пробных чисел:

//100101001010100101001010101111111111111111111111111111111111111111111111111 --- длина 75
//1001010010101001010010101011111111111111111111111111111111111111 --- длина 64

//1111111111111111111111111111111111111111111111111111111111111111 --- старшие байты числа не используются
//10000000000000000000000000000000000000000000000000000000000000001 --- старшие байты числа используются

//11111100000100000000111111111111111111111100000000000000011111111111111111