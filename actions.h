#include <iostream>
using namespace std;

//Àáñòðàêòíàÿ ôàáðèêà äëÿ ñîçäàíèÿ äåéñòâèé ïîñëå ïîñåùåíèÿ ðàáî÷åãî ìåñòà
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //ïîñëåäñòâèÿ ïîñëå çàõîäà â ðàáî÷óþ òî÷êó
	void ChangeStatus() {
        status = (status + 1) % 2;
	}
private:
    int status;
};

class BadStep: public Actions {
public:
    BadStep() {
        status = 0;
    }
	void info();
	int consequence();
	void ChangeStatus();
private:
    int status;
};

class ChanceStep: public Actions {
public:
    ChanceStep() {
        B = new BadStep();
        fl = 0;
    }
    void info();
    int consequence();
private:
    int fl;
    Actions* B;
};

class GoodStep: public Actions {
public:
	void info();
	int consequence();
};

class VeryGoodStep: public Actions {
public:
	void info();
	int consequence();
};

class WinStep: public Actions {
public:
	void info();
	int consequence();
};

class BlefGoodStep: public Actions {
public:
	void info();
	int consequence();
};
