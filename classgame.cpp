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
		/*WorkplaceFactory* b = new BadWorkplace();
		WorkplaceFactory* g = new GoodWorkplace();
		WorkplaceFactory* vg = new VeryGoodWorkplace();
		WorkplaceFactory* w = new WinWorkplace();
		WorkplaceFactory* t = new TeaWorkplace();*/
		for (int i = 0; i < n; i++) {
            WorkplaceFactory* b1 = new BadWorkplace();
            o1->place[0].push_back(b1);
            WorkplaceFactory* b3 = new BadWorkplace();
            o1->place[m - 1].push_back(b3);
		}
		for (int i = 1; i < m - 1; i++) {
		    WorkplaceFactory* b = new BadWorkplace();
            o1->place[i].push_back(b);
			if (i == 1) {
			    WorkplaceFactory* w = new WinWorkplace();
				o1->place[i].push_back(w);
				for (int j = 2; j < n - 1; j++) {
				    WorkplaceFactory* g = new GoodWorkplace();
					o1->place[i].push_back(g);
				}
			} else {
				for (int j = 1; j < n - 1; j++) {
					int index = rand() % 100;
					if (index > 10 && index < 65) {
					    WorkplaceFactory* g = new GoodWorkplace();
						o1->place[i].push_back(g);
					} else if (index > 64 && index < 75) {
					    WorkplaceFactory* t = new TeaWorkplace();
					    o1->place[i].push_back(t);
					} else if (index > 74) {
					    WorkplaceFactory* b = new BadWorkplace();
						o1->place[i].push_back(b);
						f.add(b);
					} else {
					    WorkplaceFactory* vg = new VeryGoodWorkplace();
						o1->place[i].push_back(vg);
					}
				}
			}
            WorkplaceFactory* b2 = new BadWorkplace();
			o1->place[i].push_back(b2);
		}
		return o1;
	}
	void play(Office& of) {
		cout << HelloConst;
		cout << CommandsConst;
		WorkplaceFactory* it;
		WorkplaceFactory* potentialIt;
		int line;
		int column;
		int potentialLine;
		int potentialColumn;
		//it = of.place[line][column];
		string willContinue;
		while (willContinue != "n") {
		    line = m / 2;
            column = n / 2;
            potentialLine = line;
            potentialColumn = column;
		    it = of.place[line][column];
		    //h1->doll = 0;
            while (true) {
                bool flag = 1;
                char step;
                cout << ChooseWay;
                cin >> step;
                cout << endl;
                potentialLine = line;
                potentialColumn = column;
                switch (step) {
                case 'w':
                    line--;
                    potentialLine -= 2;
                    break;
                case 's':
                    line++;
                    potentialLine += 2;
                    break;
                case 'a':
                    column--;
                    potentialColumn -= 2;
                    break;
                case 'd':
                    column++;
                    potentialColumn += 2;
                    break;
                default:
                    flag = 0;
                    cout << BreakConst1;
                    break;
                }
                if (column == 3 * n / 4 && line == 5 * m / 7) {
                    cout << BigHelp;
                    f.help();
                }
                potentialIt = of.place[potentialLine][potentialColumn];
                Worker* w1 = new DecoratorHelp(potentialIt->createWorker());
                w1->info();
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
    FractionMarketing f;
    int n;
    int m; // size of office
};
