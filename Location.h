#include <cstdlib>
#include <iostream>

class Location  		//��ǥ Ž�� �� ���� ��ǥ�� ��ġ
{
	int row;
	int col;
public:
	int getRow() { return row; }
	void setRow(int n) { row = n; }

	int getCol() { return col; }
	void setCol(int n) { col = n; }

	Location(int r = 0, int c = 0) { r = row, c = col; }
	void display() {
		printf("(%d, %d) ", this->row, this->col);
	}
};