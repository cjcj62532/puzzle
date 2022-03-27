#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

SceneID scene;
ObjectID start, restart, piece[15], board[15];

TimerID timer_mix, timer1, timer2;
int rand_count;

int pieceX[15] = { 138, 338, 538, 738, 938, 138, 338, 538, 738, 938, 138, 338, 538, 738, 938 };
int pieceY[15] = { 430, 430, 430, 430, 430, 230, 230, 230, 230, 230, 30, 30, 30, 30, 30 };
int blank;
int recorded_time;

const char* image_name[15] = {
	"images/0.png",
	"images/1.png",
	"images/2.png",
	"images/3.png",
	"images/4.png",
	"images/5.png",
	"images/6.png",
	"images/7.png",
	"images/8.png",
	"images/9.png",
	"images/10.png",
	"images/11.png",
	"images/12.png",
	"images/13.png",
	"images/14.png",
};

int piece_index(ObjectID object)
{
	for (int i = 0; i < 15; i++) {
		if (piece[i] == object) return i;
	}
	return -1;
}

void piece_move(int index)
{
	ObjectID temp = piece[blank];
	piece[blank] = piece[index];
	piece[index] = temp;

	locateObject(piece[blank], scene, pieceX[blank], pieceY[blank]);
	locateObject(piece[index], scene, pieceX[index], pieceY[index]);

	blank = index;
}

bool movable(int index)
{
	if (blank < 0 || blank > 14) return false;
	if (blank - 1 == index && blank % 5 != 0) return true;
	if (blank + 1 == index && blank % 5 != 4) return true;
	if (blank - 5 == index && blank / 5 != 0) return true;
	if (blank + 5 == index && blank / 5 != 2) return true;

	return false;
}

void piece_rand()
{
	int index;

	do {
		switch (rand() % 4) {
		case 0: index = blank - 1; break;
		case 1: index = blank + 1; break;
		case 2: index = blank - 5; break;
		case 3: index = blank + 5; break;
		}
	} while (!movable(index));
		piece_move(index);
}

bool cleared() {
	for (int i = 0; i < 16; i++) {
		if (board[i] != piece[i]) return false;
	}

	return true;
}

void mouseCallback(ObjectID object, int X, int Y, MouseAction action)
{
	if (object == start || object == restart) {
		rand_count = 200;
		startTimer(timer_mix);
		hideObject(start);
		startTimer(timer2);
	}
	else {
		int index = piece_index(object);
		if (movable(index) == true) {
			piece_move(index);

			if (cleared()) {
				showObject(piece[blank]);
				showObject(restart);		
				stopTimer(timer2);
			}
		}
	}
	
	
}

void timerCallback(TimerID timer) 
{
	rand_count--;
	if (timer == timer_mix && rand_count > 0) {
		piece_rand();

		setTimer(timer_mix, 0.05f);
		startTimer(timer_mix);
	}

	if (timer == timer2) {
		increaseTimer(timer1, 1.0);
		setTimer(timer2, 1.f);
		startTimer(timer2);
	}
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	srand(time(NULL));

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene = createScene("배경", "images/background.png");


	for (int i = 0; i < 15; i++) {
		piece[i] = createObject(image_name[i]);
		board[i] = piece[i];
		locateObject(piece[i], scene, pieceX[i], pieceY[i]);
		showObject(piece[i]);
	}

	blank = 14;
	hideObject(piece[blank]);

	start = createObject("images/start.png");
	locateObject(start, scene, 610, 100);
	showObject(start);

	restart = createObject("images/restart.png");
	locateObject(restart, scene, 610, 100);

	timer_mix = createTimer(1.0f);
	
	timer1 = createTimer(0.f);
	showTimer(timer1);

	timer2 = createTimer(1.0f);
	
	startGame(scene);

	return 0;
}



