#include <iostream>
using namespace std;

//Абстрактная фабрика для создания действий после посещения рабочего места
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //последствия после захода в рабочую точку
	virtual void ChangeStatus() {}
private:
    int status;
};

class BadStep: public Actions {
public:
    BadStep() {
        status = 0;
    }
    void ChangeStatus();
	void info();
	int consequence();
private:
    int status;
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

class ChanceStep: public Actions {
public:
    ChanceStep() {
        fl = 0;
    }
    void info();
    int consequence();
private:
    int fl;
    BadStep B;
    GoodStep D;
};
