/*
������� ����� BitString ��� ������ � 128-�������� ��������.
������� ������ ������ ���� ������������ ����� ������ ���� unsigned long long.
������ ���� ����������� ��� ������������ �������� ��� ������ � ������: and &, or |, xor ^, not ~.
����������� ����� ����� shiftLeft � ����� ������ shiftRight �� �������� ���������� �����.
����������� �������� ���������� ���������� ��������� �����, �������� ��������� �� ���������� ��������� �����.
����������� �������� �������� ���������.
*/

#include <iostream>
#include <cmath>
#include <string> 
using namespace std;
using ull = unsigned long long;

string dec_to_two(const ull a);

class BitString {
private:
    ull lo;//������� ����� �����
    ull hi;//������� ����� �����
	int ko_vo_ed;//���-�� ��������� ����� � �����
public:
    BitString() : lo(0), hi(0), ko_vo_ed(0) {}
    BitString(ull h, ull l) : lo(l), hi(h) {}

    ull hight() const { return hi; }
    ull low() const { return lo; }

	void cmp(const  BitString& b1) {//��������� �� ���-�� ��������� �����
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
	void shiftRight(int a) {//������ ������ �� �������� ���������� �����
		if (a < 0) {
			cout << "������! ����� �� ����� ������������� �� ������������� �����!" << endl;
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
		else {//������, ����� ����� > 128, ����� ��� ����� ���������� � �������� 0
			lo = 0;
			hi = 0;
		}
	}

	void shiftLeft(int a) {//������ ����� �� �������� ���������� �����
		if (a < 0) {
			cout << "������! ����� �� ����� ������������� �� ������������� �����!" << endl;
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
		else if (a >= 128) {//������, ����� ����� > 128, ����� ��� ����� ���������� � �������� 0
			hi = 0;
			lo = 0;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
	void scan(const string& str) {//��������� �� ������ ��� unsigned long long �����
		ull cur_hi = 0;
		ull cur_lo = 0;
		int count_step = 0;
		if(str.size() > 64) {//������, ����� ���� ������������� ������� ����� �����
			for (int i = 0; i < str.size(); i++) {
				if ((str[i] - '0') == 1) {//�������� ���������� ���������� ��������� �����
					ko_vo_ed++;
				}
				
				if (i < str.size() - 64) {//�������, ����������� �������� ������� ���� �� �������
					cur_hi = (cur_hi << 1) + (str[i] - '0');
					if (cur_hi == 0) {//�������, ����������� �� �������� ������� ����(��� �����, ������� ����� ������� ���������� � 0)
						count_step++;
					}
				}
				else {
					cur_lo = (cur_lo << 1) + (str[i] - '0');
				}
			}
		}
		else {//������, ����� �� ���� ������������� ������� ����� �����
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

	bool is_include(const BitString& b1) {//�������� �������� ���������
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
bool is_bin_number(const string& s) {//�������� ������� ������
	bool otr = false;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] < '0' || s[i] > '1') {
			return false;
		}
	}
	return true;
}

istream& operator>> (istream& in, BitString& b) {//������������� �������� ��� �����
	cout << "\n������� ���� Bitstring:\n";
	string str;
	cin >> str;

	if (str.length() > 128) {
		cout << "������! ����� ������� �������!" << endl;
		exit(1);
	}
	if (!is_bin_number(str)) {
		cout << "������! ������������ ����." << endl;
		exit(2);
	}

	b.scan(str);

	return in;
}

string dec_to_two(const ull a) {//����� � ����� ull ������������ � 10-����� ����, ����� ������� �� ��������� ����� ��� �������
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

ostream& operator<< (ostream& out, const BitString& b) {//������������� �������� ��� �������
	//cout << b.hight() << "    " << b.low() << endl;
	if (b.hight()){//���� � ����� ���� ������� �����, � ������� ����� �� ��������� �� �����(�� �� 64), �� ����������� ����� ������
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
//������������ �������� ��� ������ � ������: and &, or |, xor ^, not ~

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

	cout << "���� BitStrings:\n";
	cout << a << b;
	/**/
	cout << "----------------------------------------------------------------------------\n";

	cout << "������������ �������� ��� ������ � ������: and &, or |, xor ^, not ~:\n";
	cout << "a & b = " << (a & b);
	cout << "a | b = " << (a | b);
	cout << "a ^ b = " << (a ^ b);
	cout << "~a = " << ~a;
	cout << "~b = " << ~b;
	
	cout << "----------------------------------------------------------------------------\n";

	cout << "������� ����� ��� ������������ ������� �����(������ - ��� ������ �����, ������ - ��� ������ ������):\n";
	int num1, num2;
	cin >> num1 >> num2;
	cout << "\n������ ����� �1:\n";
	BitString cur_la = a;
	BitString cur_ra = a;
	cur_la.shiftLeft(num1);
	cur_ra.shiftRight(num2);
	cout << "�����: " << cur_la;
	cout << "������: " << cur_ra;

	cout << "������ ����� �2:\n";
	BitString cur_lb = b;
	BitString cur_rb = b;
	cur_lb.shiftLeft(num1);
	cur_rb.shiftRight(num2);
	cout << "�����: " << cur_lb;
	cout << "������: " << cur_rb;

	cout << "----------------------------------------------------------------------------\n";
	
	cout << "������� ���������� ��������� ����� � ������:\n\n";
	a.cmp(b);
	
	cout << "\n\n----------------------------------------------------------------------------\n";

	cout << "\n�������� ��������� ����� �2 � ����� �1:\n";
	a.is_include(b);
	cout << "\n�������� ��������� ����� �1 � ����� �2:\n";
	b.is_include(a);

}
//����� ������� �����:

//100101001010100101001010101111111111111111111111111111111111111111111111111 --- ����� 75
//1001010010101001010010101011111111111111111111111111111111111111 --- ����� 64

//1111111111111111111111111111111111111111111111111111111111111111 --- ������� ����� ����� �� ������������
//10000000000000000000000000000000000000000000000000000000000000001 --- ������� ����� ����� ������������

//11111100000100000000111111111111111111111100000000000000011111111111111111