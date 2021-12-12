#include <iostream>
#include "Maze.h"

void main() {
	Maze m;

	m.load("maze.txt");
	m.print();
	Sleep(1500);
	//system("cls");
	m.searchExit();
}