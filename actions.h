#include <iostream>
using namespace std;

//����������� �������(�����!!???) ��� �������� �������� ����� ��������� �������� �����
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //����������� ����� ������ � ������� �����
};

class BadStep: public Actions {
public:
	void info();
	int consequence();
};

class GoodStep: public Actions {
public:
	void info();
	int consequence();
};

class VeryGoodStep: public Actions {
public:
	void info();
	int consequence();
};

class WinStep: public Actions {
public:
	void info();
	int consequence();
};

class BlefGoodStep: public Actions {
public:
	void info();
	int consequence();
};
