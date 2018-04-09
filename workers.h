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

