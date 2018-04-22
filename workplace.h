#include "workers.h"
#include "actions.h"
#include <iostream>
#include <vector>
using namespace std;

// ����������� ������� ��� ������������ ������� ����
class WorkplaceFactory {
public:
	virtual Worker* createWorker() = 0;
	virtual Actions* createActions() = 0;
	virtual ~WorkplaceFactory() {}
	virtual void info() = 0;
};


// ������� ��� �������� ������ ������� ����
class BadWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker();
	Actions* createActions();
	void info();
};


class GetChance: public WorkplaceFactory {
public:
    Worker* createWorker();
    Actions* createActions();
    void info();
};


// ������� ��� �������� ������� ������� ����
class GoodWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker();
	Actions* createActions();
	void info();
};

// ������� ��� �������� ����� ������� ������� ����
class VeryGoodWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker();
	Actions* createActions();
	void info();
};

class WinWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker();
	Actions* createActions();
	void info();
};

class TeaWorkplace: public WorkplaceFactory {
public:
    Worker* createWorker();
    Actions* createActions();
    void info();
};


class FractionMarketing: public WorkplaceFactory {
public:
    Worker* createWorker();
    Actions* createActions();
    void info();
    void add(WorkplaceFactory* worker);
    void help();
private:
    vector<WorkplaceFactory*> friends;
};

class HelpWorkplace: public WorkplaceFactory {
public:
    Worker* createWorker();
    Actions* createActions();
    void info();
};
