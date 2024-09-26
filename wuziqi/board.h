#ifndef __BOARD_H__
#define __BOARD_H__
 // 保护头文件以防被多次编译
#include "player.h"
#include "queue"

using type_size = int;
using type_game = char;

class Board {
public:
	Board(type_size row, type_size col, type_size blocksize);
	~Board();
	void Game();
private:
	void Init();
	void CreateBoard();
	//bool IsGameOver();
	void ProcessInput();
	//void ShowCursor(short x, short y);
	void DrawBoard();
	void DrawPiece();
	void DrawCursor();
	void GetCursor(short x, short y);

	bool IsMouseOnBoard(short x, short y);
	void AddPiece(short x, short y, int** boardinfo);
	
	type_size rows;
	type_size cols;
	type_size blocksize;
	type_size boardwidth;
	type_size boardheight;

	short* cursorX;
	short* cursorY;

	ExMessage* mouse;
	int** boardinfo;
	int* round;
};



#endif
