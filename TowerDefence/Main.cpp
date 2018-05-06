#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace sf;

#define GRASS 'G'
#define DIRT 'D'
#define TOWERU '1'
#define TOWERD '2'
#define BUSH 'B'

char map[40][30];
Sprite level[40][30];

int numOfTowers = 8;
int numOfBushes = 40;

void makeMap() {

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 30; j++) {
			if (j == 15) map[i][j] = DIRT;
			else map[i][j] = GRASS;
		}
	}

	srand(50);

	while (numOfTowers > 0) {
		int rnd = rand() % 2;
		int row;
		if (rnd == 0) row = 13;
		else row = 16;
		int column = rand() % 40;
		
		if (row == 13) {
			map[column][row] = TOWERU;
			map[column][row + 1] = TOWERD;
			numOfTowers--;
		}

		if (row == 16) {
			map[column][row] = TOWERU;
			map[column][row + 1] = TOWERD;
			numOfTowers--;
		}
		
		
	}

	while (numOfBushes > 0) {
		int row = rand() % 30;
		int column = rand() % 40;

		if (map[column][row] == GRASS) {
			map[column][row] = BUSH;
			numOfBushes--;
		}
	}

}

int main()
{
	RenderWindow window(VideoMode(640, 480), "Tower Defence");

	makeMap();

	Texture texture;

	if (!texture.loadFromFile("sum.png"))
		return EXIT_FAILURE;

	Sprite spriteGrass(texture, IntRect(16, 0, 16, 16));
	Sprite spriteDirt(texture, IntRect(0, 0, 16, 16));
	Sprite spriteTowerU(texture, IntRect(32, 0, 16, 16));
	Sprite spriteTowerD(texture, IntRect(32, 16, 16, 16));
	Sprite spriteBush(texture, IntRect(64, 0, 16, 16));


	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 30; j++) {
			if (map[i][j] == GRASS) {
				level[i][j] = spriteGrass;
				level[i][j].setPosition(Vector2f(i * 16, j * 16));
			}

			if (map[i][j] == DIRT) {
				level[i][j] = spriteDirt;
				level[i][j].setPosition(Vector2f(i * 16, j * 16));
			}

			if (map[i][j] == TOWERU) {
				level[i][j] = spriteTowerU;
				level[i][j].setPosition(Vector2f(i * 16, j * 16));
			}
			if (map[i][j] == TOWERD) {
				level[i][j] = spriteTowerD;
				level[i][j].setPosition(Vector2f(i * 16, j * 16));
			}

			if (map[i][j] == BUSH) {
				level[i][j] = spriteBush;
				level[i][j].setPosition(Vector2f(i * 16, j * 16));
			}

		}

	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 30; j++) {
				window.draw(level[i][j]);
			}
		}
		window.display();
	}

	return 0;
}