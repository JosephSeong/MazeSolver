#include <iostream>
#include <fstream>
#include "Location.h"
#include "Node.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include <string>
#include <windows.h>

using namespace std;
class Maze {
private:
	int row;		//미로의 행 (y좌표)
	int col;		//미로의 열 (x좌표)
	char** map;     //미로 맵
	Location now;	//Location 이용(현재위치 확인 겸 탐색)
	int exit[2];	//도착점
	LinkedQueue lqueue;	//LinkedQueue 활용
	LinkedList llist;   //출력할때 연결리스트
	Node* nnode;
	int x, y;
public:
	Maze() {
		init(0, 0);
	}
	void init(int w, int h)   //map 이차원 배열을 동적으로 할당
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}
	void reset()    //미로 맵 maze를 동적으로 해제
	{
		for (int i = 0; i < col; i++)
			delete[]map[i];
		delete[]map;
	}
	void load(const char* fname) //미로 파일을 읽어옴
	{
		char temp;
		row = 1;
		col = 0;

		ifstream fin(fname, ios::in);    //fname파일을 읽어들임

		fin >> col >> row;
		init(col, row);   //row행 col열 2차원 배열을 생성
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				fin >> temp;    // temp에저장
				map[i][j] = temp;     // map에저장

				if (map[i][j] == 'e')   //출발점의 좌표일 경우, (x,y) 좌표가 벽면일 경우 포함
				{
					now.setRow(i);
					now.setCol(j);
					Node start = Node(now.getRow(), now.getCol());
					Node* p = start.getLink();
					lqueue.enqueue(p);//출발점노드를 링크큐에 쌓는
					printf("\n<출발점: (%d, %d)>", now.getRow(), now.getCol());
					map[i][j] = '5';    //지나온 길로 나중에 설정하기 위해 '5'으로 바꾼다.
					printf("\n");
				}
				else if (map[i][j] == 'x')    //도착점의 좌표일 경우, (x,y) 좌표가 벽면일 경우 포함
				{
					exit[0] = j;
					exit[1] = i;
					printf("<도착점: (%d, %d)>\n", exit[1], exit[0]);
					map[i][j] = '9';
				}
			}

		}
		fin.close();
	}

	void print() //현재 Maze를 화면에 출력
	{
		int check = 1;
		cout << "\n--------미로의 크기---------  " << "----" << row << " * " << col << "----" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] == '0' && ((i != 0 && i != row - 1) && (j != 0 && j != col - 1))) //미로의 길
				{
					cout << "  ";
				}
				else if (map[i][j] == '1')
				{
					cout << "■";
				}
				else if (map[i][j] == '7')
				{
					cout << "◇";   //탐색 길
				}
				else if (map[i][j] == '3') {
					cout << "◆";	//지나온 길(현재 나의 위치 생각)
				}
				else if (map[i][j] == '9')
				{
					cout << "Ⅹ";
				}
				else if (map[i][j] == '5') {
					cout << "E";
				}
			}
			cout << endl;
		}
	}
	void searchExit()        //실제 미로를 탐색하는 함수
	{
		while (1) {


			x = now.getCol();
			y = now.getRow();

			// 지나온 위치를 반복하면서 찍어준다.

			search(x, y - 1);
			search(x, y + 1);
			search(x - 1, y);
			search(x + 1, y);

			printf("-> (%d,%d)", now.getRow(), now.getCol());

			Move();
			print();
			Sleep(200);
			map[y][x] = '3';
		}
		system("cls");
		print();
		llist.display();
	}
	void search(int x1, int y1) {
		if (row > y1 && y1 >= 0 && col > x1 && x1 > -1 && (map[y1][x1] == '0' || map[y1][x1] == '9')) {
			nnode = new Node(x1, y1);
			lqueue.enqueue(nnode);
			if (map[y1][x1] == '0') map[y1][x1] = '7';
		}
	}
	void Move() {
		Node* move = lqueue.dequeue();
		now.setRow(move->getY());
		now.setCol(move->getX());
		llist.addList(move);
	}
};
