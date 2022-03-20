#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

ObjectID createObject(const char* image, SceneID scene, int x, int y);
void changePosition(ObjectID object, int NULLNum, int objectNum);
void movePicture(ObjectID object);
void mouseCallback(ObjectID object, int x, int y, MouseAction action);
void startGame();


SceneID scene1, scene2;
ObjectID picture[15], position[15], startButton, restartButton, endButton;
char pictureName[14][100], pictureNumber[14][100];
int positionX[15], positionY[15], pictureX[15], pictureY[15];
bool existence[15];

int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);

	scene1 = createScene("starting", "images/original.png");
	scene2 = createScene("background", "images/background.png");

	startButton = createObject("images/start.png", scene1, 590, 70);
	restartButton = createObject("images/restart.png", scene2, 10, 20);
	endButton = createObject("images/end.png", scene2, 10, 60);

	for (int i = 0; i < 14; i++) {
		strcpy(pictureName[i], "images/");
		sprintf(pictureNumber[i], "%d", i);
		strcat(pictureName[i], pictureNumber[i]);
		strcat(pictureName[i], ".png");
	}
		
	for (int i = 0; i < 15; i++) {
		if (i < 5) {
			pictureX[i] = positionX[i] = 138 + 200 * i;
			pictureY[i] = positionY[i] = 430;
			position[i] = picture[i];
		}
		else if (i >= 5 && i < 10) {
			pictureX[i] = positionX[i] = 138 + 200 * (i - 5);
			pictureY[i] = positionY[i] = 230;
			position[i] = picture[i];
		}
		else if (i >= 10) {
			pictureX[i] = positionX[i] = 138 + 200 * (i - 10);
			pictureY[i] = positionY[i] = 30;
			position[i] = picture[i];
		}
		picture[i] = createObject(pictureName[i], scene2, positionX[i], positionY[i]);
		picture[14] = NULL;
		position[i] = picture[i];
	}
	
	
	startGame(scene1);
}

//void checkPosition(ObjectID object, int x, int y)
//{
//	for (int i = 0; i < 15; i++) {
//		if (i < 5 && x == 138 + 200 * i && y == 430) {
//			position[i] = object;
//		}
//		else if (i >= 5 && i < 10 && x == 138 + 200 * (i - 5) && y == 230) {
//			position[i] = object;
//		}
//		else if (i >= 10 && x == 138 + 200 * (i - 10) && y == 30) {
//			position[i] = object;
//		}
//	}
//}

ObjectID createObject(const char* image, SceneID scene, int x, int y)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	showObject(object);

	return object;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == startButton || object == restartButton) {
		startGame();
	}
	else if (object == endButton) {
		endGame();
	}

	for (int i = 0; i < 14; i++) {
		if (object == picture[i]) {
			movePicture(object);
		}
	}
	
}

void movePicture(ObjectID object)
{
	changePosition(object, 0, 1);
	changePosition(object, 0, 5);
	changePosition(object, 1, 0);
	changePosition(object, 1, 2);
	changePosition(object, 1, 6);
	changePosition(object, 2, 1);
	changePosition(object, 2, 3);
	changePosition(object, 2, 7);
	changePosition(object, 3, 2);
	changePosition(object, 3, 4);
	changePosition(object, 3, 8);
	changePosition(object, 4, 3);
	changePosition(object, 4, 9);
	changePosition(object, 5, 0);
	changePosition(object, 5, 6);
	changePosition(object, 5, 10);
	changePosition(object, 6, 1);
	changePosition(object, 6, 5);
	changePosition(object, 6, 7);
	changePosition(object, 6, 11);
	changePosition(object, 7, 2);
	changePosition(object, 7, 6);
	changePosition(object, 7, 8);
	changePosition(object, 7, 12);
	changePosition(object, 8, 3);
	changePosition(object, 8, 7);
	changePosition(object, 8, 9);
	changePosition(object, 8, 13);
	changePosition(object, 9, 4);
	changePosition(object, 9, 8);
	changePosition(object, 9, 14);
	changePosition(object, 10, 5);
	changePosition(object, 10, 11);
	changePosition(object, 11, 6);
	changePosition(object, 11, 10);
	changePosition(object, 11, 12);
	changePosition(object, 12, 7);
	changePosition(object, 12, 11);
	changePosition(object, 12, 13);
	changePosition(object, 13, 8);
	changePosition(object, 13, 12);
	changePosition(object, 13, 14);
	changePosition(object, 14, 9);
	changePosition(object, 14, 13);
}

void changePosition(ObjectID object, int num1, int num2)
{
	if (object == picture[num1]) {
		if (position[num2] == NULL) {
			pictureX[num1] = positionX[num2];
			pictureY[num1] = positionY[num2];
			locateObject(object, scene2, pictureX[num1], picture[num2]);
		}
	}
}

void startGame()
{
	enterScene(scene2);
	
}


