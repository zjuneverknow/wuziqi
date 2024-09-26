#include "board.h"

#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<algorithm>

#include<iostream>

const COLORREF VIEWBACKCOLOR = RGB(255, 213, 109);

const type_size WINDOWWIDTH = 1080;
const type_size WINDOWHEIGHT = 960;
type_size STATX;
type_size STATY;

Board::Board(type_size row, type_size col, type_size blocksize) :
	rows(row + 1),
	cols(col + 1),
	blocksize(blocksize),
	boardwidth(col* blocksize),
	boardheight(row* blocksize),
	mouse(new ExMessage),
	cursorX(new short),
	cursorY(new short),
	round(new int)
{
	//round = new int; // why here not round(0)??
	*round = 0;     // why need assign here??
	STATX = (WINDOWWIDTH - col * blocksize) / 2;
	STATY = (WINDOWHEIGHT - row * blocksize) / 2;
	boardinfo = new int* [row + 1];
	for (int i = 0; i < rows; i++) {
		boardinfo[i] = new int[cols];
		for (int j = 0; j < cols; j++)
			boardinfo[i][j] = 0;
	}
}

void Board::Game(){
	Init();
	ProcessInput();
}

Board::~Board() {
	// 别的为什么不用delete？？
	delete mouse;
	delete cursorX;
	delete cursorY;
	delete round;
	for (int i = 0; i < rows; i++)
		delete[] boardinfo[i];
	delete[] boardinfo;
}

void Board::ProcessInput() {
	while (true) {
		*mouse = getmessage(EX_MOUSE | EX_KEY);
		switch (mouse->message){
		case WM_MOUSEMOVE:
			GetCursor(mouse->x,mouse->y);
			break;
		case WM_LBUTTONDOWN:
			if (IsMouseOnBoard(mouse->x, mouse->y))
				AddPiece(mouse->x, mouse->y, boardinfo);
			break;
		case WM_KEYDOWN:
			break;
		default: break;
		}
		DrawBoard();
		DrawPiece();
		DrawCursor();
	}
}

void Board::Init() {
	HWND hwnd = initgraph(WINDOWWIDTH, WINDOWHEIGHT);
	SetWindowText(hwnd, L"wuziqi");
	//CreateBoard();

	//_getch();
}

void Board::CreateBoard() {
	setbkcolor(YELLOW);				    // 设置当前窗口背景颜色
	cleardevice();							    // 使用当前背景颜色清除绘图设备
	setlinecolor(BLACK);						// 设置设备画线颜色

	for (int row = 0; row < rows; row++)
		line(STATX , STATY + row * blocksize, STATX + boardwidth, STATY + row * blocksize);

	for (int col = 0; col < cols; col++)
		line(STATX + col * blocksize, STATY, STATX + col * blocksize, STATY + boardheight);	
}

void Board :: DrawCursor() {
	setlinecolor(RED);
	circle(*cursorX, *cursorY, 10);
}
void Board::DrawPiece() {
	
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			//std::cout << *(*(boardinfo + i) + j) << std::endl;
			if (*(*(boardinfo + i) + j) == 2) {
				setfillcolor(BLACK);
				fillcircle(STATX + (i) * blocksize, STATY + (j) * blocksize, 20);
			}
			if (*(*(boardinfo + i) + j) == 1) {
				setfillcolor(WHITE);
				fillcircle(STATX + (i) * blocksize, STATY + (j) * blocksize, 20);
			}
		}	
}
void Board::DrawBoard() {
	setfillcolor(YELLOW);
	fillrectangle(0, WINDOWHEIGHT, WINDOWWIDTH, 0);

	setlinecolor(BLACK);						// 设置设备画线颜色

	for (int row = 0; row < rows; row++)
		line(STATX, STATY + row * blocksize, STATX + boardwidth, STATY + row * blocksize);

	for (int col = 0; col < cols; col++)
		line(STATX + col * blocksize, STATY, STATX + col * blocksize, STATY + boardheight);


}
void Board::GetCursor(short x, short y) {
	*cursorX = x;
	*cursorY = y;
}

void Board::AddPiece(short x, short y, int** boardinfo) {
	int Numx = (x - STATX + blocksize / 2) / blocksize;
	int Numy = (y - STATY + blocksize / 2) / blocksize;

	if (*(*(boardinfo + Numx) + Numy) == 0) {
		*(*(boardinfo + Numx) + Numy) = *round % 2 + 1;
		*round = *round + 1;
	}

}

bool Board::IsMouseOnBoard(short x, short y){
	if (x > STATX - blocksize / 2 && x < STATX + blocksize * (cols - 1.5) && y > STATY - blocksize / 2 && y < STATY + blocksize * (rows - 1.5))
		return 1;
	else return 0;
}


// 指针和数组  为何成员变量定义用指针  a（x）意味着什么？？

