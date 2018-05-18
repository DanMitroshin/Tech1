#include <iostream>
using namespace std;

// Абстрактный базовый класс видов людей
class Worker {
public:
	virtual void info() = 0;
	virtual ~Worker() {}
};

// Классы всех видов людей
class GoodWorker: public Worker {
public:
	void info();
};

class BadWorker: public Worker {
public:
	void info();
};

class ManagerWorker: public Worker {
public:
	void info();
};

class DecoratorW: public Worker {
public:
    DecoratorW(Worker* w1){
        w = w1;
    }
    void info();
private:
    Worker* w;
};

class DecoratorHelp: public DecoratorW {
public:
    DecoratorHelp(Worker* w): DecoratorW(w){}
    void info();
};

class DecoratorInfo: public DecoratorW {
public:
    DecoratorInfo(Worker* w): DecoratorW(w){}
    void info();
};
