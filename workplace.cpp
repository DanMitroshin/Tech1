#include "workplace.h"
#include "constWorkplace.cpp"
#include <iostream>
using namespace std;


Worker* BadWorkplace::createWorker() {
    return new BadWorker;
}

Actions* BadWorkplace::createActions() {
	return new BadStep;
}

void BadWorkplace::info() {
	cout << BWP;
}


Worker* GoodWorkplace::createWorker() {
	return new GoodWorker;
}

Actions* GoodWorkplace::createActions() {
	return new GoodStep;
}

void GoodWorkplace::info() {
	cout << GWP;
}


Worker* VeryGoodWorkplace::createWorker() {
	return new GoodWorker;
}

Actions* VeryGoodWorkplace::createActions() {
	return new VeryGoodStep;
}

void VeryGoodWorkplace::info() {
	cout << VGWP;
}


Worker* WinWorkplace::createWorker() {
	return new ManagerWorker;
}

Actions* WinWorkplace::createActions() {
	return new WinStep;
}

void WinWorkplace::info() {
	cout << WWP;
}


Worker* TeaWorkplace::createWorker() {
    return new GoodWorker;
}

Actions* TeaWorkplace::createActions() {
    return new BlefGoodStep;
}

void TeaWorkplace::info() {
    cout << TWP;
}
