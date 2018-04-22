#include "workplace.h"
#include "constWorkplace.cpp"
#include <iostream>
using namespace std;


Worker* BadWorkplace::createWorker() {
    return new BadWorker;
}

Actions* BadWorkplace::createActions() {
	return new ChanceStep;
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

void FractionMarketing::add(WorkplaceFactory* worker) {
    friends.push_back(worker);
}

void FractionMarketing::help() {
    for (int i = 0; i < friends.size(); i++) {
        friends[i]->createActions()->ChangeStatus();
    }
}

Worker* FractionMarketing::createWorker() {
    return new GoodWorker;
}

Actions* FractionMarketing::createActions() {
    return new GoodStep;
}

void FractionMarketing::info() {
    cout << GWP;
}
