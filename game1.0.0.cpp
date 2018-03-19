#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <string>
using namespace std;

class Hero {
public:
    Hero() {
        doll = 0;
    }
	bool doll;
	string status;
};

// Абстрактный базовый класс видов людей
class Worker {
public:
	virtual void info() = 0;
	virtual ~Worker() {}
};


// Классы всех видов людей
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

//Абстрактная фабрика(класс!!???) для создания действий после посещения рабочего места
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //последствия после захода в рабочую точку
};

class BadStep: public Actions {
public:
	void info() {
		cout << "Вы зашли не туда и вас выкинули из офиса..." << endl;
	}
	int consequence() {
		return 0;
	}
};

class GoodStep: public Actions {
public:
	void info() {
		cout << "Весьма успешно. Можете дальше добираться до кабинета." << endl;
	}
	int consequence() {
		return 1;
	}
};

class VeryGoodStep: public Actions {
public:
	void info() {
		cout << "Вы попали к очень хорошему человеку!" << endl;
		cout << "Он дал вам куклу, чтобы во время неверного шага вы могли подкинуть ее злому человеку." << endl;
		cout << "Тогда из офиса он выкенет ее, а не вас!" << endl;
	}
	int consequence() {
		return 3;
	}
};

class WinStep: public Actions {
public:
	void info() {
		cout << "Вы добрались до цели! Мои поздравления." << endl;
	}
	int consequence() {
		return 2;
	}
};

class BlefGoodStep: public Actions {
public:
	void info() {
		cout << "Вы еще в офисе! Тут очень дружелюбный человек." << endl;
	}
	int consequence() {
		string s;
		cout << "Привет! Хочешь чаю? (yes/no)" << endl;
		cin >> s;
		while (s != "no" or s != "yes") {
			if (s == "yes") {
				cout << "Вы пьете чай и долго разговариваете." << endl;
				cout << "Рабочий день подошел к концу. Офис закрылся, вас выгнали." << endl;
				return 0;
			} else if (s == "no") {
			    cout << "Ну что ты такой злой? Нельзя так.";
				return 1;
			} else {
				cout << "Сотрудник не понял ваш ответ :(" << endl;
				cin >> s;
			}
		}
	}
};

// Абстрактная фабрика для производства рабочих мест
class WorkplaceFactory {
public:
	virtual Worker* createWorker() = 0;
	virtual Actions* createActions() = 0;
	virtual ~WorkplaceFactory() {}
	virtual void info() = 0;
};


// Фабрика для создания плохих рабочих мест
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


// Фабрика для создания хороших рабочих мест
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

// Фабрика для создания ОЧЕНЬ хороших рабочих мест
class VeryGoodWorkplace: public WorkplaceFactory {
public:
	Worker* createWorker() {
		return new GoodWorker;
	}
	Actions* createActions() {
		return new VeryGoodStep;
	}
	void info() {
		cout << "VGoodWP";
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

class TeaWorkplace: public WorkplaceFactory {
public:
    Worker* createWorker() {
        return new GoodWorker;
    }
    Actions* createActions() {
        return new BlefGoodStep;
    }
    void info() {
        cout << "TeaWP";
    }
};

// Офис (класс), содержащий все виды рабочих мест
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
	vector< vector<WorkplaceFactory*> > place; //карта офиса
protected:
	int n;
	int m;
	Hero& h;
};


// Здесь создается наш офис
class Game {
public:
	Game(Hero* h1, int n, int m): h1(h1), n(n), m(m) {}
	Office* createOffice() { //Пример создания офиса
		srand(time(0));
		Office* o1 = new Office(h1, n, m);
		WorkplaceFactory* b = new BadWorkplace();
		WorkplaceFactory* g = new GoodWorkplace();
		WorkplaceFactory* vg = new VeryGoodWorkplace();
		WorkplaceFactory* w = new WinWorkplace();
		WorkplaceFactory* t = new TeaWorkplace();
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
					if (index > 10 && index < 65) {
						o1->place[i].push_back(g);
					} else if (index > 64 && index < 75) {
					    o1->place[i].push_back(t);
					} else if (index > 74) {
						o1->place[i].push_back(b);
					} else {
						o1->place[i].push_back(vg);
					}
				}
			}
			o1->place[i].push_back(b);
		}
		return o1;
	}
	void play(Office& of) {
		cout << "Привет. Ты попал в офис, где стремишься найти кабинет для прохождения собеседования." << endl;
		cout << "Избегай того, чтобы тебя выкинули из офиса." << endl;
		cout << "Для ходов по лабиринту используй команды:" << endl;
		cout << "w - вперд(forward)" << endl;
		cout << "s - назад(back)" << endl;
		cout << "a - налево(left)" << endl;
		cout << "d - направо(right)" << endl;
		WorkplaceFactory* it;
		int line;
		int column;
		line = 1;
		column = m - 2;
		it = of.place[line][column];
		while (true) {
			bool flag = 1;
			char step;
			cout << "Куда пойдем? ";
			cin >> step;
			cout << endl;
			switch (step) {
            case 'w':
				line--;
				break;
            case 's':
				line++;
				break;
            case 'a':
				column--;
				break;
            case 'd':
				column++;
				break;
            default:
				flag = 0;
				cout << "Ты видимо врезался в стенку... Давай еще раз" << endl;
				break;
			}
			bool flag2 = 1;
			if (flag == 1) {
				it = of.place[line][column];
				it->createActions()->info();
				switch (it->createActions()->consequence()) {
                case 0:
                    if (h1->doll == 0) {
                        flag2 = 0;
                    } else {
                        h1->doll = 0;
                        cout << "Но нет :) У вас же есть кукла. Вы спасаетесь, отдавая ее." << endl;
                    }
                    break;
                case 1:
                    break;
                case 2:
                    flag2 = 0;
                    break;
                case 3:
                    if (h1->doll == 0){
                        h1->doll = 1;
                    } else {
                        cout << "Вы взяли сразу 2 куклы. Вам очень тяжело их носить с собой." << endl;
                        cout << "Но вы не хотите оставлять ни одну из них и остаетесь сидеть с ними в офисе." << endl;
                        cout << "В конце рабочего дня вас заставляют покинуть офис..." << endl;
                        flag2 = 0;
                    }
                    break;
				}
				//int act;
				//act = *it;
			}
			if (flag2 == 0)
                break;
		}
	}
	Hero* h1;
protected:
    int n;
    int m; // size of office
};


int main(){
    setlocale(LC_ALL, "Russian");
	srand(time(0));
	Hero* h1 = new Hero;
	Game game(h1, 10, 10);
	GoodWorkplace gf;
	Office * of = game.createOffice();
	game.play(* of);
	cout << "Office:" << endl;
	of->info();
	return 0;
}
