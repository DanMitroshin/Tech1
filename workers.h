#include <iostream>
using namespace std;

// ����������� ������� ����� ����� �����
class Worker {
public:
	virtual void info() = 0;
	virtual ~Worker() {}
};

// ������ ���� ����� �����
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

