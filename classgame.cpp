#include <iostream>
#include <vector>
#include "constGame.cpp"
#include <ctime>
#include <random>
#include <string>
#include "workplace.h"
using namespace std;

class Hero {
public:
    Hero() {
        doll = 0;
    }
	bool doll;
	string status;
};

// Офис (класс), содержащий все виды рабочих мест
class Office{
public:
    vector<vector<WorkplaceFactory*>> place; //карта офиса
	Office(Hero* h, int n, int m): h(*h), n(n), m(m), place(n) {}
	~Office(){
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                delete place[i][j];
            }
        }
	}
	void info() {
		for(int i = 0; i < place.size(); i++)  {
			for (int j = 0; j < place[i].size(); j++) {
				place[i][j]->info();
				cout << '|';
			}
			cout << endl;
		}
	}
protected:
	int n;
	int m;
	Hero& h;
};


// Здесь создается наш офис и происходит игра
class Game {
public:
	Game(Hero* h1, int n, int m): h1(h1), n(n), m(m) {}
	Office* createOffice() { //Пример создания офиса
		srand(time(0));
		Office* o1 = new Office(h1, m, n);
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
		cout << HelloConst;
		cout << CommandsConst;
		WorkplaceFactory* it;
		int line;
		int column;
		//it = of.place[line][column];
		string willContinue;
		while (willContinue != "n") {
		    line = m / 2;
            column = n / 2;
		    it = of.place[line][column];
		    h1->doll = 0;
            while (true) {
                bool flag = 1;
                char step;
                cout << ChooseWay;
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
                    cout << BreakConst1;
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
                            cout << SavingConst1;
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
                            cout << BreakConst2;
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
            cout << ContinueQuestion;
            cin >> willContinue;
            cout << endl;
		}
	}
	Hero* h1;
protected:
    int n;
    int m; // size of office
};
