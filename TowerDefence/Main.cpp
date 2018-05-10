#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "maps.h"

using namespace sf;

// set resolution
int res_x = 800;
int res_y = 600;
float scalex = (float)res_x / 320;
float scaley = (float)res_y / 240;

#define GRASS 'G'
#define DIRTPREVIOUS 'P'
#define DIRT 'D'
#define BUSH 'B'
#define LAKE1 '1'
#define LAKE2 '2'
#define LAKE3 '3'
#define LAKE4 '4'
#define LAKE5 '5'
#define LAKE6 '6'
#define HP1 '7'
#define HP2 '8'
#define HP3 '9'
#define HP4 '0'
#define CREEP 0
#define CREEP1 1
#define CREEP2 2
#define CREEP3 3
#define CREEP4 4
#define MOVEDCREEP 'c'
#define SPOT 'S'
#define SELECTEDSPOT 'X'
#define TOWER 'T'
#define TOWER2 't'
#define SELECTEDTOWER 'O'
#define SELECTEDTOWER2 'o'

Sprite level[SIZEROW * SIZECOLUMN];

bool endGame = false;
int rowFields[7] = { 5,5,3,10,10,7,5 };
int columnFields[7] = { 3,5,7,9,12,14,17 };
int currentI = 0;
int btnCnt = 0;
int currentHP = 3;
int coins = 21;

Texture texture;


void drawSprite(int in_x, int in_y, int out_x, int out_y, int width, int height) {

	int tout_x = out_x / 16;
	int tout_y = out_y / 16;
	Sprite sprite(texture, IntRect(in_x, in_y, width, height));

	level[tout_y * SIZECOLUMN + tout_x] = sprite;
	level[tout_y * SIZECOLUMN + tout_x].setPosition(Vector2f(out_x*scalex, out_y*scaley));
	level[tout_y * SIZECOLUMN + tout_x].scale(scalex, scaley);
}

void drawMap() {
	int row, column;
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if (mapChanges[row][column]) {
				mapChanges[row][column] = false;
				if (map1[row][column] == GRASS) {
					drawSprite(16, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == DIRT || map1[row][column] == DIRTPREVIOUS) {
					drawSprite(0, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == BUSH) {
					drawSprite(32, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP) {
					drawSprite(48, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP1) {
					drawSprite(48, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP2) {
					drawSprite(48, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP3) {
					drawSprite(48, 48, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP4) {
					drawSprite(48, 64, column * 16, row * 16, 16, 16);

				}
				else if (map1[row][column] == LAKE1) {
					drawSprite(0, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE2) {
					drawSprite(16, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE3) {
					drawSprite(32, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE4) {
					drawSprite(0, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE5) {
					drawSprite(16, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE6) {
					drawSprite(32, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == SPOT) {
					drawSprite(64, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == SELECTEDSPOT) {
					drawSprite(64, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == TOWER) {
					drawSprite(80, 48, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == TOWER2) {
					drawSprite(96, 48, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == SELECTEDTOWER) {
					drawSprite(80, 64, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == SELECTEDTOWER2) {
					drawSprite(96, 64, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == HP1) {
					drawSprite(112, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == HP2) {
					drawSprite(112, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == HP3) {
					drawSprite(112, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == HP4) {
					drawSprite(112, 48, column * 16, row * 16, 16, 16);
				}


			}
		}
	}
}

void printNum(int row, int column, int num) {

	if (num == 0) {
		drawSprite(16, 48, column * 8, row * 8, 8, 8);
	}
	else if (num == 1) {
		drawSprite(24, 48, column * 8, row * 8, 8, 8);
	}

	else if (num == 2) {
		drawSprite(32, 48, column * 8, row * 8, 8, 8);
	}
	else if (num == 3) {
		drawSprite(40, 48, column * 8, row * 8, 8, 8);
	}
	else if (num == 4) {
		drawSprite(16, 56, column * 8, row * 8, 8, 8);
	}
	else if (num == 5) {
		drawSprite(24, 56, column * 8, row * 8, 8, 8);
	}
	else if (num == 6) {
		drawSprite(32, 56, column * 8, row * 8, 8, 8);
	}
	else if (num == 7) {
		drawSprite(40, 56, column * 8, row * 8, 8, 8);
	}
	else if (num == 8) {
		drawSprite(16, 64, column * 8, row * 8, 8, 8);
	}
	if (num == 9) {
		drawSprite(24, 64, column * 8, row * 8, 8, 8);
	}


}
void printCoins() {
	int l, r;
	l = coins / 10;
	r = coins % 10;
	printNum(0, 1, r);
	if (l != 0) {
		printNum(0, 0, l);
	}
	else {
		drawSprite(16, 0, 0, 0, 8, 8);
	}


}

void moveCreep() {

	int row, column;
	int i = 0;
	int pom[10];
	int x[10], y[10];
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if (map1[row][column] == CREEP4) {
				map1[row][column] = DIRT;
				if (coins < 99) {
					coins++;
					printCoins();
				}
				mapChanges[row][column] = true;

				if (map1[row + 1][column] == DIRTPREVIOUS) {
					map1[row + 1][column] = DIRT;
				}

				if (map1[row - 1][column] == DIRTPREVIOUS) {
					map1[row - 1][column] = DIRT;
				}

				if (map1[row][column + 1] == DIRTPREVIOUS) {
					map1[row][column + 1] = DIRT;
				}

				if (map1[row][column - 1] == DIRTPREVIOUS) {
					map1[row][column - 1] = DIRT;
				}
			}

			else if (map1[row][column] == CREEP || map1[row][column] == CREEP1 || map1[row][column] == CREEP2 || map1[row][column] == CREEP3) {
				if (column == 19) {
					map1[row][column] = DIRT;
					currentHP--;
					if (currentHP == 2) {
						map1[5][19] = HP2;
						map1[7][19] = HP2;
						mapChanges[5][19] = true;
						mapChanges[7][19] = true;
					}
					else if (currentHP == 1) {
						map1[5][19] = HP3;
						map1[7][19] = HP3;
						mapChanges[5][19] = true;
						mapChanges[7][19] = true;
					}
					else if (currentHP == 0) {
						map1[5][19] = HP4;
						map1[7][19] = HP4;
						mapChanges[5][19] = true;
						mapChanges[7][19] = true;
						endGame = true;
					}
				}
				else {
					pom[i] = map1[row][column];
					map1[row][column] = DIRTPREVIOUS;
					if (map1[row + 1][column] == DIRT) {
						map1[row + 1][column] = MOVEDCREEP;
						mapChanges[row + 1][column] = true;
						x[i] = row + 1;
						y[i++] = column;
					}
					if (map1[row - 1][column] == DIRT) {
						map1[row - 1][column] = MOVEDCREEP;
						mapChanges[row - 1][column] = true;
						x[i] = row - 1;
						y[i++] = column;
					}
					if (map1[row][column + 1] == DIRT) {
						map1[row][column + 1] = MOVEDCREEP;
						mapChanges[row][column + 1] = true;
						x[i] = row;
						y[i++] = column + 1;
					}
					if (map1[row][column - 1] == DIRT) {
						map1[row][column - 1] = MOVEDCREEP;
						mapChanges[row][column - 1] = true;
						x[i] = row;
						y[i++] = column - 1;
					}
					if (map1[row + 1][column] == DIRTPREVIOUS) {
						map1[row + 1][column] = DIRT;

					}
					if (map1[row - 1][column] == DIRTPREVIOUS) {
						map1[row - 1][column] = DIRT;
					}
					if (map1[row][column + 1] == DIRTPREVIOUS) {
						map1[row][column + 1] = DIRT;
					}
					if (map1[row][column - 1] == DIRTPREVIOUS) {
						map1[row][column - 1] = DIRT;
					}
				}
				if (map1[row + 1][column] == DIRTPREVIOUS) {
					map1[row + 1][column] = DIRT;

				}
				if (map1[row - 1][column] == DIRTPREVIOUS) {
					map1[row - 1][column] = DIRT;
				}
				if (map1[row][column + 1] == DIRTPREVIOUS) {
					map1[row][column + 1] = DIRT;
				}
				if (map1[row][column - 1] == DIRTPREVIOUS) {
					map1[row][column - 1] = DIRT;
				}
				mapChanges[row][column] = true;


			}
		}
	}
	int j;
	for (j = 0; j<i; j++) {
		map1[x[j]][y[j]] = pom[j];
	}
}


void placeTower() {
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (currentI<6) {
			if (map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != TOWER2 &&
				map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER2) {
				map1[rowFields[currentI]][columnFields[currentI]] = SPOT;
			}
			else {
				if (map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER) {
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER;
				}
				else {
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER2;
				}
			}

			mapChanges[rowFields[currentI]][columnFields[currentI]] = true;
			currentI++;
			if (map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != TOWER2) {
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDSPOT;
			}
			else {
				if (map1[rowFields[currentI]][columnFields[currentI]] == TOWER) {
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
				}
				else {
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (currentI>0) {
			if (map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != TOWER2 &&
				map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER2) {
				map1[rowFields[currentI]][columnFields[currentI]] = SPOT;
			}
			else {
				if (map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER) {
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER;
				}
				else {
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER2;
				}
			}
			mapChanges[rowFields[currentI]][columnFields[currentI]] = true;
			currentI--;
			if (map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != TOWER2) {
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDSPOT;
			}
			else {
				if (map1[rowFields[currentI]][columnFields[currentI]] == TOWER) {
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
				}
				else {
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		btnCnt = (btnCnt + 1) % 2;
		if (btnCnt == 0) {
			map1[0][19] = SELECTEDTOWER;
			map1[1][19] = TOWER2;
		}
		else {
			map1[0][19] = TOWER;
			map1[1][19] = SELECTEDTOWER2;
		}
		mapChanges[0][19] = true;
		mapChanges[1][19] = true;
	}


	if (Keyboard::isKeyPressed(Keyboard::Return)) {
		if (map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDSPOT) {
			if (btnCnt == 0) {
				if (coins >= 5) {
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
					coins -= 5;
					printCoins();
				}
			}
			else {
				if (coins >= 7) {
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
					coins -= 7;
					printCoins();
				}
			}
		}
		else if (map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER) {
			if (coins >= 2) {
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
				coins -= 2;
				printCoins();
			}
		}

	}

	mapChanges[rowFields[currentI]][columnFields[currentI]] = true;
}


void insertCreep() {
	map1[0][2] = CREEP;
	mapChanges[0][2] = true;
}

void turretOneFire() {
	int row, column;
	for (row = 0; row < SIZEROW - 1; row++) {
		for (column = 0; column < SIZECOLUMN - 1; column++) {
			if ((map1[row][column] == TOWER) || map1[row][column] == SELECTEDTOWER
				) {


				int i, j;
				for (i = -1; i<2; i++) {
					for (j = -1; j<2; j++) {
						if (map1[row + i][column + j] == CREEP || map1[row + i][column + j] == CREEP1 || map1[row + i][column + j] == CREEP2 || map1[row + i][column + j] == CREEP3) {
							drawSprite(80, 80, column * 16, row * 16, 16, 16);
							mapChanges[row][column] = true;
							map1[row + i][column + j]++;
							mapChanges[row + i][column + j] = true;

						}

					}
				}
			}
		}
	}
	for (row = 0; row < 500000; row++);
}

void turretTwoFire() {
	int row, column;
	for (row = 0; row < SIZEROW - 1; row++) {
		for (column = 0; column < SIZECOLUMN - 1; column++) {
			if ((map1[row][column] == TOWER2) || map1[row][column] == SELECTEDTOWER2) {
				int i, j;
				for (i = -1; i<2; i++) {
					for (j = -1; j<2; j++) {
						if (map1[row + i][column + j] == CREEP || map1[row + i][column + j] == CREEP1 || map1[row + i][column + j] == CREEP2 || map1[row + i][column + j] == CREEP3) {
							drawSprite(96, 80, column * 16, row * 16, 16, 16);
							mapChanges[row][column] = true;
							map1[row + i][column + j]++;
							mapChanges[row + i][column + j] = true;
						}

					}
				}
			}
		}
	}
	for (row = 0; row < 500000; row++);
}

void drawEndGame() {
	int row, column;
	while (1) {
		for (row = 0; row < SIZEROW; row++) {
			for (column = 0; column < SIZECOLUMN; column++) {
				if (gameOver[row][column] == DIRT) {
					drawSprite(0, 0, column * 16, row * 16, 16, 16);
				}
				else if (gameOver[row][column] == CREEP) {
					drawSprite(48, 0, column * 16, row * 16, 16, 16);
					gameOver[row][column] = CREEP4;
				}
				else if (gameOver[row][column] == CREEP4) {
					drawSprite(48, 64, column * 16, row * 16, 16, 16);
					gameOver[row][column] = CREEP;
				}
			}
		}
		for (row = 0; row < 2500000; row++);
	}
}

int main()
{
	RenderWindow window(VideoMode(res_x, res_y), "Tower Defence");

	unsigned int creepTimeCnt = 0;
	int rnd, cnt = 0, cnt1 = 0;
	srand(30);
	int creepCnt = 0;

	bool firsttime = true;
	texture.loadFromFile("towerdefence_sprites.png");

	window.setFramerateLimit(10);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		/*
		if (endGame) {
			drawEndGame();
			window.display();

			for (int i = 0; i < SIZECOLUMN*SIZEROW; i++) {
				window.draw(level[i]);
			}
		} else {
			*/
			drawMap();
			if (firsttime) {
				printCoins();
				drawSprite(8, 64, 16, 0, 8, 8);
				firsttime = false;
			}
			if (endGame) {
				drawEndGame();
				break;
			}
			placeTower();
			moveCreep();

			if (creepCnt == 5) {
				insertCreep();
				creepCnt = 0;
				/*creepCnt++;
				creepTimeCnt = 0;
				rnd = (rand() % 20) + 5;*/
			}

			if (cnt == 6) {
				turretOneFire();
				cnt = 0;
			}
			if (cnt1 == 4) {
				turretTwoFire();
				cnt1 = 0;
			}
			cnt++;
			cnt1++;
			creepCnt++;

			for (int i = 0; i < SIZECOLUMN*SIZEROW; i++) {
				window.draw(level[i]);
			}

			for (int i = 0; i < SIZEROW; i++) {
				for (int j = 0; j < SIZECOLUMN; j++) {
					printf("%c ", map1[i][j]);
				}
				printf("\n");
			}
			window.display();
			system("cls");
		}

	

	return 0;
}