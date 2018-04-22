#include <iostream>
using namespace std;

//Абстрактная фабрика(класс!!???) для создания действий после посещения рабочего места
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //последствия после захода в рабочую точку
	void ChangeStatus() {
        status = (status + 1) % 2;
	}
private:
    int status;
};

class BadStep: public Actions {
public:
    BadStep() {
        status = 0;
    }
	void info();
	int consequence();
	void ChangeStatus();
private:
    int status;
};

class ChanceStep: public Actions {
public:
    ChanceStep() {
        B = new BadStep();
        fl = 0;
    }
    void info();
    int consequence();
private:
    int fl;
    Actions* B;
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
