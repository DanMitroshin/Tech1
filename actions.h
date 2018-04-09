#include <iostream>
using namespace std;

//Абстрактная фабрика(класс!!???) для создания действий после посещения рабочего места
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //последствия после захода в рабочую точку
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
