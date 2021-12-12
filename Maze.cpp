#include <iostream>
#include "Maze.h"

void main() {
	Maze m;

	m.load("test.txt");
	m.print();
	Sleep(1500);
	//system("cls");
	m.searchExit();
}