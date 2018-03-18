#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <string>
using namespace std;

class Hero {
public:
	bool doll;
	string status;
};

// ����������� ������� ����� ����� �����
class Worker {
public:
	virtual void info() = 0;
	virtual ~Worker() {}
};


// ������ ���� ����� �����
class GoodWorker: public Worker {
public:
	void info() {
		cout << "GoodWorker" << endl;
	}
};

class BadWorker: public Worker {
public:
	void info() {
		cout << "BadWorker" << endl;
	}
};

class ManagerWorker: public Worker {
public:
	void info() {
		cout << "ManagerWorker" << endl;
	}
};

//����������� ����� ��� �������� �������� ����� ��������� �������� �����
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //����������� ����� ������ � ������� �����
};

class BadStep: public Actions {
public:
	void info() {
		cout << "�� ����� �� ���� � ��� �������� �� �����..." << endl;
	}
	int consequence() {
		return 0;
	}
};

class GoodStep: public Actions {
public:
	void info() {
		cout << "�� �� ����� �� ����. ������ ������ ���������� �� ��������." << endl;
	}
	int consequence() {
		return 1;
	}
private:
	//bool statusLife;
};

class VeryGoodStep: public Actions {
public:
	void info() {
		cout << "�� ������ � ����� �������� ��������!" << endl;
		cout << "�� ��� ��� �����, ����� �� ����� ��������� ���� �� ����� ��������� �� ����� ��������." << endl;
		cout << "����� �� ����� �� ������� ��, � �� ���!" << endl;
	}
	int consequence() {
		return 3;
	}
private:
	//bool statusLife;
};

class WinStep: public Actions {
public:
	void info() {
		cout << "�� ��������� �� ����! ��� ������������." << endl;
	}
	int consequence() {
		return 2;
	}
};

class BlefGoodStep: public Actions {
public:
	void info() {
		cout << "�� �� ������ �� ����! ��� ����� ����������� �������." << endl;
	}
	int consequence() {
		string s;
		cout << "������! ������ ���? (��/���)" << endl;
		cin >> s;
		if (s == "��") {
			cout << "�� ����� ��� � ����� ��������������." << endl;
			cout << "������� ���� ������� � �����. ���� ��������, ��� �������." << endl;
			return 0;
		} else if (s == "���") {
			return 1;
		} else {
			cout << "��������� �� ����� ��� ����� :(" << endl;
			cin >> s;
		}
	}
};

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
	Worker* createWorker() {
		return new BadWorker;
	}
	Actions* createActions() {
		return new BadStep;
	}
	void info() {
		cout << "BadWP";
	}
};


// ������� ��� �������� ������� ������� ����
class GoodWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker() {
		return new GoodWorker;
	}
	Actions* createActions() {
		return new GoodStep;
	}
	void info() {
		cout << "GoodWP";
	}
};

// ������� ��� �������� ����� ������� ������� ����
class VeryGoodWorkplace: public WorkplaceFactory {
public:
    VeryGoodWorkplace() {
        Worker* w = new GoodWorker;
        Actions* a = new VeryGoodStep;
    }
	Worker* createWorker() {
		return new GoodWorker;
	}
	Actions* createActions() {
		return new VeryGoodStep;
	}
	void info() {
		cout << "VeryGoodWP";
	}
};

class WinWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker() {
		return new ManagerWorker;
	}
	Actions* createActions() {
		return new WinStep;
	}
	void info() {
		cout <<"WinWP";
	}
};

// ���� (�����), ���������� ��� ���� ������� ����
class Office{
public:
	Office(Hero* h, int n, int m): h(*h), place(n) {}
	~Office() {}
	void info() {
		for(int i = 0; i < place.size(); i++)  {
			for (int j = 0; j < place[i].size(); j++) {
				place[i][j]->info();
				cout << '|';
			}
			cout << endl;
		}
	}
	vector< vector<WorkplaceFactory*> > place; //����� �����
protected:
	int n;
	int m;
	Hero& h;
};


// ����� ��������� ��� ����
class Game {
public:
	Game(Hero* h1, int n, int m): h1(h1), n(n), m(m) {}
	Office* createOffice() { //������ �������� �����
		srand(time(0));
		Office* o1 = new Office(h1, n, m);
		WorkplaceFactory* b = new BadWorkplace();
		WorkplaceFactory* g = new GoodWorkplace();
		WorkplaceFactory* vg = new VeryGoodWorkplace();
		WorkplaceFactory* w = new WinWorkplace();
		for (int i = 0; i < n; i++) {
            		o1->place[0].push_back(b);
            		o1->place[m - 1].push_back(b);
		}
		for (int i = 1; i < m - 1; i++) {
            		o1->place[i].push_back(b);
			if (i == 1) {
				o1->place[i].push_back(w);
				for (int j = 2; j < n - 1; j++) {
					o1->place[i].push_back(g);
				}
			} else {
				for (int j = 1; j < n - 1; j++) {
					int index = rand() % 100;
					if (index > 10) {
						o1->place[i].push_back(g);
					} else {
						o1->place[i].push_back(vg);
					}
				}
			}
			o1->place[i].push_back(b);
		}
		return o1;
	}
	Hero* h1;
protected:
    int n;
    int m; // size of office
};


int main(){
	srand(time(0));
	Hero* h1 = new Hero;
	Game game(h1, 10, 10);
	GoodWorkplace gf;
	Office * of = game.createOffice();
	cout << "Office:" << endl;
	of->info();
	return 0;
	// ...
}
