#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <string>
#include "game_office.h"
using namespace std;



int main(){
    setlocale(LC_ALL, "Russian");
	//srand(time(0));
	Hero h1;
	Game game(&h1, 30, 12);
	GoodWorkplace gf;
	Office * of = game.createOffice();
	game.play(* of);
	//cout << "Office:" << endl;
	of->info();

	return 0;
	// ...
}
