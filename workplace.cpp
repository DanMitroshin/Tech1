#include "workplace.h"
#include "constWorkplace.cpp"
#include <iostream>
using namespace std;


Worker* BadWorkplace::createWorker() {
    return &bwr;
}

Actions* BadWorkplace::createActions() {
	return &bsp;
}

void BadWorkplace::info() {
	cout << BWP;
}


Worker* GoodWorkplace::createWorker() {
	return &gwr;
}

Actions* GoodWorkplace::createActions() {
	return &gsp;
}

void GoodWorkplace::info() {
	cout << GWP;
}


Worker* VeryGoodWorkplace::createWorker() {
	return &gwr;
}

Actions* VeryGoodWorkplace::createActions() {
	return &vgsp;
}

void VeryGoodWorkplace::info() {
	cout << VGWP;
}


Worker* WinWorkplace::createWorker() {
	return &mwr;
}

Actions* WinWorkplace::createActions() {
	return &wsp;
}

void WinWorkplace::info() {
	cout << WWP;
}


Worker* TeaWorkplace::createWorker() {
    return &gwr;
}

Actions* TeaWorkplace::createActions() {
    return &bgsp;
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
