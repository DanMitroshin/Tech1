#include <iostream>
#include "constActions.cpp"
#include "actions.h"
#include <ctime>
#include <random>
using namespace std;

void BadStep::info() {
    cout << BadS;
}

void BadStep::ChangeStatus() {
    //status = (status + 1) % 2;
    status = 1;
}

int BadStep::consequence() {
    if (status == 1) {
        cout << yourElixir;
    }
    return status;
}

void ChanceStep::info() {
    srand(time(0));
    int index = rand() % 100;
    if (index < 95) {
        fl = 0;
        B.info();
    } else {
        cout<< question1;
        int index1 = rand() % 100;
        int try1;
        cin >> try1;
        if (try1 == index1) {
            fl = 1;
            D.info();
        } else {
            fl = 0;
            B.info();
        }
    }
}

int ChanceStep::consequence() {
    return fl;
}

void GoodStep::info() {
	cout << GoodS;
}

int GoodStep::consequence() {
    return 1;
}

void VeryGoodStep::info() {
    cout << VGoodS;
}

int VeryGoodStep::consequence() {
	return 3;
}


void WinStep::info() {
    cout << WinS;
}

int WinStep::consequence() {
	return 2;
}

void BlefGoodStep::info() {
		cout << BlefS;
	}

int BlefGoodStep::consequence() {
    string s;
    cout << BlefS_Hello;
    cin >> s;
    while (s != BlefS_No or s != BlefS_Yes) {
        if (s == BlefS_Yes) {
            cout << BlefS_Bad;
            return 0;
        } else if (s == BlefS_No) {
            cout << BlefS_Good;
            return 1;
        } else {
            cout << BlefS_Misunderstand;
            cin >> s;
        }
    }
}
