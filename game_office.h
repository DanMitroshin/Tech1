#include <iostream>
#include <vector>
#include <list>
#include "workplace.h"
using namespace std;

class Notifications;

class IObserver {
public:
    IObserver() {
        doll = 0;
    }
	bool doll;
	string status;
    virtual void handleEvent(const Notifications&) = 0;
};

class Hero: public IObserver {
public:
    void handleEvent(const Notifications& gg);
};


class Office{
public:
    vector<vector<WorkplaceFactory*>> place; //êàðòà îôèñà
	Office(IObserver* h, int n, int m): h(*h), n(n), m(m), place(n + 4) {
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
	WorkplaceFactory* TRight();
	WorkplaceFactory* TLeft();
	WorkplaceFactory* TUp();
	WorkplaceFactory* TDown();
	void ToStart();
	void NormalPotentialTurn();
	WorkplaceFactory* PotentialTurn();
	pair<int, int> GetCoordinates();
	void info();
private:
	int n;
	int m;
	int line, column;
	int potentialLine, potentialColumn;
	IObserver& h;
};

class Visitor {
public:
    virtual void visit(Office& of, int b, int a) = 0;
};

class ShowArea: public Visitor {
public:
    void visit(Office& of, int b, int a);
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
    WorkplaceFactory* Right();
    WorkplaceFactory* Left();
    WorkplaceFactory* Up();
    WorkplaceFactory* Down();
    WorkplaceFactory* PTurn();
    pair<int, int> Coordinates();
    bool IsMagicPotion(int b, int c);
    void BackToStart();
    void NormalTurn();
};

class Receiver{
   vector<Command*> DoneCommands;
   Office& of;
   Command* command;
public:
    Receiver(Office& of): of(of) {}
    WorkplaceFactory* Right();
    WorkplaceFactory* Left();
    WorkplaceFactory* Up();
    WorkplaceFactory* Down();
    WorkplaceFactory* Potential();
    void NormalTurn();
    void ToStart();
    bool IsHelping(int n, int m);
    void ClearCommands();
    void info();
};

class Notifications {
public:
    void add(IObserver& player);
    void remove(IObserver& player);
    const string& GetHelpingMarketing() const;
    void reset(string str);
private:
    string _str;
    list<IObserver*> _observers;
    void _Notify();
};

// Çäåñü ñîçäàåòñÿ íàø îôèñ è ïðîèñõîäèò èãðà
class Game {
public:
	Game(IObserver* h1, int n, int m): h1(h1), n(n), m(m) {}
	Office* createOffice();
	void play(Office& of);
	IObserver* h1;
private:
    FractionMarketing f;
    int n;
    int m; // size of office
};
