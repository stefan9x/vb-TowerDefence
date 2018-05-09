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
				else if ((map1[row][column] == DIRT) || (map1[row][column] == DIRTPREVIOUS)) {
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

void moveCreep() {

	int row, column;
	int i = 0;
	int pom[10];
	int x[10], y[10];
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if (map1[row][column] == CREEP4) {
				map1[row][column] = DIRT;
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
				if (row == 14 || column == 19) {
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
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
			}
			else {
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
			}
		}
		else if (map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER) {
			map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
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
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if ((map1[row][column] == TOWER)) { //  || (map1[row][column] == SELECTEDTOWER)
				int i, j;
				for (i = -1; i<2; i++) {
					for (j = -1; j<2; j++) {
						if (map1[row + i][column + j] == CREEP || map1[row + i][column + j] == CREEP1 || map1[row + i][column + j] == CREEP2 || map1[row + i][column + j] == CREEP3) {
							map1[row + i][column + j]++;
							mapChanges[row + i][column + j] = true;
						}

					}
				}
			}
		}
	}
}

void drawEndGame() {
	int row, column;
	
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
}

int main()
{
	RenderWindow window(VideoMode(res_x, res_y), "Tower Defence");

	unsigned int creepTimeCnt = 0;
	int rnd = 0;
	srand(30);
	int creepCnt = 0;

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

		if (endGame) {
			drawEndGame();
			window.display();

			for (int i = 0; i < SIZECOLUMN*SIZEROW; i++) {
				window.draw(level[i]);
			}
		} else {

			drawMap();

			unsigned int i = 0;

			moveCreep();
			turretOneFire();
			if (creepTimeCnt == rnd) {
				insertCreep();
				creepCnt++;
				creepTimeCnt = 0;
				rnd = (rand() % 20) + 5;

			}
			else {
				creepTimeCnt++;
			}

			placeTower();

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

	}

	return 0;
}