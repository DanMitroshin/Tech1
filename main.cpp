#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <string>
#include "classgame.cpp"
using namespace std;



int main(){
    setlocale(LC_ALL, "Russian");
	//srand(time(0));
	Hero* h1 = new Hero;
	Game game(h1, 12, 30);
	GoodWorkplace gf;
	Office * of = game.createOffice();
	game.play(* of);
	//cout << "Office:" << endl;
	//of->info();
	return 0;
	// ...
}
