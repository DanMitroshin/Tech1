#include <iostream>
#include <vector>
#include <list>
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

// Îôèñ (êëàññ), ñîäåðæàùèé âñå âèäû ðàáî÷èõ ìåñò
class Office{
public:
    vector<vector<WorkplaceFactory*>> place; //êàðòà îôèñà
	Office(Hero* h, int n, int m): h(*h), n(n), m(m), place(n + 4) {
        line = n / 2 + 2;
        column = m / 2 + 2;
        potentialLine = line;
        potentialColumn = column;
	}
	~Office(){
        for (int i = 0; i < n + 4; i++) {
            for (int j = 0; j < m + 4; j++) {
                delete place[i][j];
            }
        }
	}
	WorkplaceFactory* TRight () {
        WorkplaceFactory* it;
        column++;
        potentialColumn = column + 1;
        return place[line][column];
	}
	WorkplaceFactory* TLeft () {
        WorkplaceFactory* it;
        column--;
        potentialColumn = column - 1;
        return place[line][column];
	}
	WorkplaceFactory* TUp () {
        WorkplaceFactory* it;
        line--;
        potentialLine = line - 1;
        return place[line][column];
	}
	WorkplaceFactory* TDown () {
        WorkplaceFactory* it;
        line++;
        potentialLine = line + 1;
        return place[line][column];
	}
	void ToStart() {
        line = n / 2 + 2;
        column = m / 2 + 2;
        potentialLine = line;
        potentialColumn = column;
	}
	void NormalPotentialTurn() {
        potentialLine = line;
        potentialColumn = column;
	}
	WorkplaceFactory* PotentialTurn() {
        return place[potentialLine][potentialColumn];
	}
	pair<int, int> GetCoordinates() {
        return make_pair(line, column);
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
private:
	int n;
	int m;
	int line, column;
	int potentialLine, potentialColumn;
	Hero& h;
};

class Visitor {
public:
    virtual void visit(Office& of, int b, int a) = 0;
};

class ShowArea: public Visitor {
public:
    void visit(Office& of, int b, int a) {
        WorkplaceFactory* it;
        cout << HelpingPoint << endl;
        for (int i = b - 1; i <= b + 1; i++) {
            for (int j = a - 1; j <= a + 1; j++) {
                it = of.place[i][j];
                it->createWorker()->info();
                cout << '|';
            }
            cout << endl;
        }
    }
};

class Command {
protected:
   Office* office;
public:
    virtual ~Command() {}
    virtual WorkplaceFactory* Right() = 0;
    virtual WorkplaceFactory* Left() = 0;
    virtual WorkplaceFactory* Up() = 0;
    virtual WorkplaceFactory* Down() = 0;
    virtual WorkplaceFactory* PTurn() = 0;
    virtual pair<int, int> Coordinates() = 0;
    virtual void BackToStart() = 0;
    virtual void NormalTurn() = 0;
    virtual bool IsMagicPotion(int n, int m) = 0;
    void setOffice(Office* _office ) {
        office = _office;
   }
};

class UsualCommand: public Command{
    int line;
    string str;
public:
    //UsualCommand( int _line, const string & _str ): line( _line ), str( _str ) {}
    WorkplaceFactory* Right(){
        return office->TRight();
    }
    WorkplaceFactory* Left(){
        return office->TLeft();
    }
    WorkplaceFactory* Up(){
        return office->TUp();
    }
    WorkplaceFactory* Down(){
        return office->TDown();
    }
    WorkplaceFactory* PTurn() {
        return office->PotentialTurn();
    }
    pair<int, int> Coordinates() {
        return office->GetCoordinates();
    }
    bool IsMagicPotion(int b, int c) {
        pair<int, int> a;
        a = office->GetCoordinates();
        if (a.second == c && a.first == b) {
            return 1;
        } else {
            return 0;
        }
    }
    void BackToStart(){
        office->ToStart();
    }
    void NormalTurn() {
        office->NormalPotentialTurn();
    }
};

class Receiver{
   vector<Command*> DoneCommands;
   Office& of;
   Command* command;
public:
    Receiver(Office& of): of(of) {}
    WorkplaceFactory* Right() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Right();
    }
    WorkplaceFactory* Left() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Left();
    }
    WorkplaceFactory* Up() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Up();
    }
    WorkplaceFactory* Down() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Down();
    }
    WorkplaceFactory* Potential() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->PTurn();
    }
    void NormalTurn() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        command->NormalTurn();
    }
    void ToStart() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        command->BackToStart();
    }
    bool IsHelping(int n, int m) {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->IsMagicPotion(n, m);
    }
    void Undo() {
        if (DoneCommands.size() != 0) {
            command = DoneCommands.back();
            DoneCommands.pop_back();
            delete command;
        }
    }
    void info() {
        of.info();
    }
};

// Çäåñü ñîçäàåòñÿ íàø îôèñ è ïðîèñõîäèò èãðà
class Game {
public:
	Game(Hero* h1, int n, int m): h1(h1), n(n), m(m) {}
	Office* createOffice() { //Ïðèìåð ñîçäàíèÿ îôèñà
		srand(time(0));
		Office* o1 = new Office(h1, n, m);
		for (int i = 0; i < m + 4; i++) {
            WorkplaceFactory* b1 = new BadWorkplace();
            o1->place[0].push_back(b1);
            o1->place[1].push_back(b1);
            o1->place[2].push_back(b1);
            WorkplaceFactory* b3 = new BadWorkplace();
            o1->place[n + 1].push_back(b3);
            o1->place[n + 3].push_back(b3);
            o1->place[n + 2].push_back(b3);
		}
		for (int i = 3; i < n + 1; i++) {
		    WorkplaceFactory* b88 = new BadWorkplace();
            o1->place[i].push_back(b88);
            o1->place[i].push_back(b88);
            o1->place[i].push_back(b88);
			if (i == 3) {
			    WorkplaceFactory* w = new WinWorkplace();
				o1->place[i].push_back(w);
				for (int j = 2; j < m - 1; j++) {
				    WorkplaceFactory* g = new GoodWorkplace();
					o1->place[i].push_back(g);
				}
			} else {
				for (int j = 1; j < m - 1; j++) {
					int index = rand() % 100;
					if (index > 10 && index < 65) {
					    WorkplaceFactory* g = new GoodWorkplace();
						o1->place[i].push_back(g);
					} else if (index > 64 && index < 75) {
					    WorkplaceFactory* t = new TeaWorkplace();
					    o1->place[i].push_back(t);
					} else if (index > 74) {
					    WorkplaceFactory* b4 = new BadWorkplace();
						o1->place[i].push_back(b4);
						f.add(b4);
					} else {
					    WorkplaceFactory* vg = new VeryGoodWorkplace();
						o1->place[i].push_back(vg);
					}
				}
			}
            WorkplaceFactory* b2 = new BadWorkplace();
			o1->place[i].push_back(b2);
			o1->place[i].push_back(b2);
			o1->place[i].push_back(b2);
		}
		return o1;
	}
	void play(Office& of) {
		cout << HelloConst;
		cout << CommandsConst;
		WorkplaceFactory* it;
		WorkplaceFactory* potentialIt;
		ShowArea SA;
		Receiver RR(of);
		int line;
		int column;
		int potentialLine;
		int potentialColumn;
		int a, b;
		line = n / 2 + 2;
        column = m / 2 + 2;
        potentialLine = line;
        potentialColumn = column;
        a = line - 1;
        b = column;
		//it = of.place[line][column];
		string willContinue;
		while (willContinue != "n") {
		    RR.ToStart();
		    //h1->doll = 0;
            while (true) {
                bool flag = 1;
                char step;
                cout << ChooseWay;
                cin >> step;
                cout << endl;
                RR.NormalTurn();
                switch (step) {
                case 'w':
                    it = RR.Up();
                    break;
                case 's':
                    it = RR.Down();
                    break;
                case 'a':
                    it = RR.Left();
                    break;
                case 'd':
                    it = RR.Right();
                    break;
                default:
                    flag = 0;
                    cout << BreakConst1;
                    break;
                }
                bool flag2 = 1;
                if (flag == 1) {
                    if (RR.IsHelping(n / 2 + 2, m / 2 + 3)) {
                        cout << BigHelp;
                        f.help();
                    }
                    if (RR.IsHelping(n / 2 + 1, m / 2 + 2)) {
                        SA.visit(of, a, b);
                    }
                    potentialIt = RR.Potential();
                    Worker* w1 = new DecoratorHelp(potentialIt->createWorker());
                    w1->info();
                    cout << endl;
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








/*#include <iostream>
#include <vector>
#include <list>
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

// Îôèñ (êëàññ), ñîäåðæàùèé âñå âèäû ðàáî÷èõ ìåñò
class Office{
public:
    vector<vector<WorkplaceFactory*>> place; //êàðòà îôèñà
	Office(Hero* h, int n, int m): h(*h), n(n), m(m), place(n + 4) {
        line = n / 2 + 2;
        column = m / 2 + 2;
        potentialLine = line;
        potentialColumn = column;
	}
	~Office(){
        for (int i = 0; i < n + 4; i++) {
            for (int j = 0; j < m + 4; j++) {
                delete place[i][j];
            }
        }
	}
	WorkplaceFactory* TRight () {
        WorkplaceFactory* it;
        column++;
        potentialColumn = column + 1;
        return place[line][column];
	}
	WorkplaceFactory* TLeft () {
        WorkplaceFactory* it;
        column--;
        potentialColumn = column - 1;
        return place[line][column];
	}
	WorkplaceFactory* TUp () {
        WorkplaceFactory* it;
        line--;
        potentialLine = line - 1;
        return place[line][column];
	}
	WorkplaceFactory* TDown () {
        WorkplaceFactory* it;
        line++;
        potentialLine = line + 1;
        return place[line][column];
	}
	void ToStart() {
        line = n / 2 + 2;
        column = m / 2 + 2;
        potentialLine = line;
        potentialColumn = column;
	}
	void NormalPotentialTurn() {
        potentialLine = line;
        potentialColumn = column;
	}
	WorkplaceFactory* PotentialTurn() {
        return place[potentialLine][potentialColumn];
	}
	pair<int, int> GetCoordinates() {
        return make_pair(line, column);
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
	int line, column;
	int potentialLine, potentialColumn;
	Hero& h;
};

class Visitor {
public:
    virtual void visit(Office& of, int b, int a) = 0;
};

class ShowArea: public Visitor {
public:
    void visit(Office& of, int b, int a) {
        WorkplaceFactory* it;
        cout << HelpingPoint << endl;
        for (int i = b - 1; i <= b + 1; i++) {
            for (int j = a - 1; j <= a + 1; j++) {
                it = of.place[i][j];
                it->createWorker()->info();
                cout << '|';
            }
            cout << endl;
        }
    }
};

class Command {
protected:
   Office* office;
public:
    virtual ~Command() {}
    virtual WorkplaceFactory* Right() = 0;
    virtual WorkplaceFactory* Left() = 0;
    virtual WorkplaceFactory* Up() = 0;
    virtual WorkplaceFactory* Down() = 0;
    virtual WorkplaceFactory* PTurn() = 0;
    virtual pair<int, int> Coordinates() = 0;
    virtual void BackToStart() = 0;
    virtual void NormalTurn() = 0;
    virtual bool IsMagicPotion(int n, int m) = 0;
    void setOffice(Office* _office ) {
        office = _office;
   }
};

class UsualCommand: public Command{
    int line;
    string str;
public:
    //UsualCommand( int _line, const string & _str ): line( _line ), str( _str ) {}
    WorkplaceFactory* Right(){
        return office->TRight();
    }
    WorkplaceFactory* Left(){
        return office->TLeft();
    }
    WorkplaceFactory* Up(){
        return office->TUp();
    }
    WorkplaceFactory* Down(){
        return office->TDown();
    }
    WorkplaceFactory* PTurn() {
        return office->PotentialTurn();
    }
    pair<int, int> Coordinates() {
        return office->GetCoordinates();
    }
    bool IsMagicPotion(int b, int c) {
        pair<int, int> a;
        a = office->GetCoordinates();
        if (a.second == c && a.first == b) {
            return 1;
        } else {
            return 0;
        }
    }
    void BackToStart(){
        office->ToStart();
    }
    void NormalTurn() {
        office->NormalPotentialTurn();
    }
};

class Receiver{
   vector<Command*> DoneCommands;
   Office& of;
   Command* command;
public:
    Receiver(Office& of): of(of) {}
    WorkplaceFactory* Right() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Right();
    }
    WorkplaceFactory* Left() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Left();
    }
    WorkplaceFactory* Up() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Up();
    }
    WorkplaceFactory* Down() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->Down();
    }
    WorkplaceFactory* Potential() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->PTurn();
    }
    void NormalTurn() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        command->NormalTurn();
    }
    void ToStart() {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        command->BackToStart();
    }
    bool IsHelping(int n, int m) {
        command = new UsualCommand();
        command->setOffice(&of);
        DoneCommands.push_back(command);
        return command->IsMagicPotion(n, m);
    }
    void Undo() {
      if (DoneCommands.size() != 0) {
         command = DoneCommands.back();
         DoneCommands.pop_back();
         delete command;
      }
   }
   void info()
   {
      of.info();
   }
};

// Çäåñü ñîçäàåòñÿ íàø îôèñ è ïðîèñõîäèò èãðà
class Game {
public:
	Game(Hero* h1, int n, int m): h1(h1), n(n), m(m) {}
	Office* createOffice() { //Ïðèìåð ñîçäàíèÿ îôèñà
		srand(time(0));
		Office* o1 = new Office(h1, n, m);
		for (int i = 0; i < m + 4; i++) {
            WorkplaceFactory* b1 = new BadWorkplace();
            o1->place[0].push_back(b1);
            o1->place[1].push_back(b1);
            o1->place[2].push_back(b1);
            WorkplaceFactory* b3 = new BadWorkplace();
            o1->place[n + 1].push_back(b3);
            o1->place[n + 3].push_back(b3);
            o1->place[n + 2].push_back(b3);
		}
		for (int i = 3; i < n + 1; i++) {
		    WorkplaceFactory* b88 = new BadWorkplace();
            o1->place[i].push_back(b88);
            o1->place[i].push_back(b88);
            o1->place[i].push_back(b88);
			if (i == 3) {
			    WorkplaceFactory* w = new WinWorkplace();
				o1->place[i].push_back(w);
				for (int j = 2; j < m - 1; j++) {
				    WorkplaceFactory* g = new GoodWorkplace();
					o1->place[i].push_back(g);
				}
			} else {
				for (int j = 1; j < m - 1; j++) {
					int index = rand() % 100;
					if (index > 10 && index < 65) {
					    WorkplaceFactory* g = new GoodWorkplace();
						o1->place[i].push_back(g);
					} else if (index > 64 && index < 75) {
					    WorkplaceFactory* t = new TeaWorkplace();
					    o1->place[i].push_back(t);
					} else if (index > 74) {
					    WorkplaceFactory* b4 = new BadWorkplace();
						o1->place[i].push_back(b4);
						f.add(b4);
					} else {
					    WorkplaceFactory* vg = new VeryGoodWorkplace();
						o1->place[i].push_back(vg);
					}
				}
			}
            WorkplaceFactory* b2 = new BadWorkplace();
			o1->place[i].push_back(b2);
			o1->place[i].push_back(b2);
			o1->place[i].push_back(b2);
		}
		return o1;
	}
	void play(Office& of) {
		cout << HelloConst;
		cout << CommandsConst;
		WorkplaceFactory* it;
		WorkplaceFactory* potentialIt;
		ShowArea SA;
		Receiver RR(of);
		int line;
		int column;
		int potentialLine;
		int potentialColumn;
		int a, b;
		//it = of.place[line][column];
		string willContinue;
		while (willContinue != "n") {

		    line = n / 2 + 2;
            column = m / 2 + 2;
            potentialLine = line;
            potentialColumn = column;
            a = line - 1;
            b = column;
		    //it = of.place[line][column];
		    RR.ToStart();
		    //h1->doll = 0;
            while (true) {
                bool flag = 1;
                char step;
                cout << ChooseWay;
                cin >> step;
                cout << endl;
                potentialLine = line;
                potentialColumn = column;
                RR.NormalTurn();
                switch (step) {
                case 'w':
                    line--;
                    potentialLine -= 2;
                    it = RR.Up();
                    break;
                case 's':
                    line++;
                    potentialLine += 2;
                    it = RR.Down();
                    break;
                case 'a':
                    column--;
                    potentialColumn -= 2;
                    it = RR.Left();
                    break;
                case 'd':
                    column++;
                    potentialColumn += 2;
                    it = RR.Right();
                    //potentialIt = RR.PotentialTurn();
                    break;
                default:
                    flag = 0;
                    cout << BreakConst1;
                    break;
                }
                bool flag2 = 1;
                if (flag == 1) {
                    if (RR.IsHelping(n / 2 + 2, m / 2 + 3)) {
                        cout << BigHelp;
                        f.help();
                    }
                    if (RR.IsHelping(n / 2 + 1, m / 2 + 2)) {
                        SA.visit(of, a, b);
                    }
                    //potentialIt = of.place[potentialLine][potentialColumn];
                    potentialIt = RR.Potential();
                    Worker* w1 = new DecoratorHelp(potentialIt->createWorker());
                    w1->info();
                    cout << endl;
                    //it = of.place[line][column];
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
*/





/*#include <iostream>
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
                //delete place[i][j];
            }
        }
	}
	void info() {
		for(int i = 0; i < place.size(); i++)  {
			for (int j = 0; j < place[i].size(); j++) {
				//place[i][j]->info();
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


// Здесь делается наш офис и происходит игра
class Game {
public:
	Game(Hero* h1, int n, int m): h1(h1), n(n), m(m), setPlaces(n * m + 2 * (m + n) + 4) {
	}
	BadWorkplace b9;
	vector<WorkplaceFactory*> setPlaces;
	Office* createOffice() { //Пример создания офиса
		srand(time(0));
		Office* o1 = new Office(h1, m + 2, n + 2);
		for (int i = 0; i < n * 4 + (m - 4) * 4; i++) {
            BadWorkplace b1;
            setPlaces[i] = &b1;
        }
		for (int i = 0; i < n + 2; i++) {
            WorkplaceFactory* b1 = new BadWorkplace();
            o1->place[0].push_back(setPlaces[i]);
            WorkplaceFactory* b3 = new BadWorkplace();
            o1->place[m].push_back(setPlaces[n + 2 + i]);
            o1->place[m + 1].push_back(setPlaces[(n + 2) * 2 + i]);
            o1->place[1].push_back(setPlaces[(n + 2) * 3 + i]);
		}
		for (int i = 2; i < m; i++) {
		    WorkplaceFactory* b = new BadWorkplace();
            o1->place[i].push_back(setPlaces[(n + 2) * 4 + (i - 2) * 4]);
            o1->place[i].push_back(setPlaces[(n + 2) * 4 + (i - 2) * 4 + 1]);
			if (i == 2) {
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
					    //WorkplaceFactory* b7 = new BadWorkplace();
						o1->place[i].push_back(&b9);
						f.add(&b9);
					} else {
					    WorkplaceFactory* vg = new VeryGoodWorkplace();
						o1->place[i].push_back(vg);
					}
				}
			}
            WorkplaceFactory* b2 = new BadWorkplace();
			o1->place[i].push_back(setPlaces[(n + 2) * 4 + (i - 2) * 4] + 2);
			o1->place[i].push_back(setPlaces[(n + 2) * 4 + (i - 2) * 4] + 3);
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
                if (column == n / 2 + 1 && line == m / 2) {
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
*/





