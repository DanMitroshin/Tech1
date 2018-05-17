#include <iostream>
using namespace std;

//Àáñòðàêòíàÿ ôàáðèêà äëÿ ñîçäàíèÿ äåéñòâèé ïîñëå ïîñåùåíèÿ ðàáî÷åãî ìåñòà
class Actions {
public:
	virtual void info() = 0;
	virtual int consequence() = 0; //ïîñëåäñòâèÿ ïîñëå çàõîäà â ðàáî÷óþ òî÷êó
};

class BadStep: public Actions {
public:
	void info();
	int consequence();
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
