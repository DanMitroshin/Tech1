#include <iostream>
#include "constActions.cpp"
#include "actions.h"
using namespace std;

void BadStep::info() {
		cout << BadS;
}

int BadStep::consequence() {
    return 0;
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
