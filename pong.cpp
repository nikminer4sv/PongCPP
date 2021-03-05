#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

const int WIDTH = 800;
const int HEIGHT = 500;
const int TEXT_INDENT = 50;
const int BORDER_WIDTH = 7;
const int CENTRAL_LINE_WIDTH = 3;
const int CENTRAL_LINE_ELEMENT_COUNT = 20;
const int CENTRAL_LINE_INDENT = 10;
const int BORDER_INDENT = 10;
const int PLAYER_WIDTH = 10;
const int PLAYER_HEIGHT = HEIGHT / 8;
const int BORDER_PLAYER_INDENT = 15;
const int BALL_SIZE = 8;

const float BALL_SPEED = (float)20/60;
const float SPEED = (float)30/60;

int counter1 = 0;
int counter2 = 0;

bool changeDirection = true;
bool isFinished = false;

vector<RectangleShape> createGameField() {

	vector<RectangleShape> field(4 + CENTRAL_LINE_ELEMENT_COUNT);

	RectangleShape leftBorder(Vector2f(BORDER_WIDTH, HEIGHT - 2*BORDER_INDENT));
	RectangleShape topBorder(Vector2f(WIDTH - 2*BORDER_INDENT, BORDER_WIDTH));
	RectangleShape rightBorder(Vector2f(BORDER_WIDTH, HEIGHT - 2*BORDER_INDENT));
	RectangleShape bottomBorder(Vector2f(WIDTH - 2*BORDER_INDENT, BORDER_WIDTH));

	leftBorder.setPosition(BORDER_INDENT, BORDER_INDENT);
	topBorder.setPosition(BORDER_INDENT, BORDER_INDENT);
	rightBorder.setPosition(WIDTH - BORDER_INDENT - BORDER_WIDTH, BORDER_INDENT);
	bottomBorder.setPosition(BORDER_INDENT, HEIGHT - BORDER_INDENT - BORDER_WIDTH);

	float centralElementHeight = (HEIGHT - 2*BORDER_INDENT - CENTRAL_LINE_ELEMENT_COUNT*CENTRAL_LINE_INDENT)/CENTRAL_LINE_ELEMENT_COUNT;

	for (int i = 0; i < CENTRAL_LINE_ELEMENT_COUNT; i++) {
		RectangleShape temp(Vector2f(CENTRAL_LINE_WIDTH, centralElementHeight));
		temp.setPosition(WIDTH/2-CENTRAL_LINE_WIDTH/2, i*(centralElementHeight+CENTRAL_LINE_INDENT) + BORDER_INDENT + BORDER_WIDTH);
		field[i+4] = temp;
	}

	field[0] = leftBorder;
	field[1] = topBorder;
	field[2] = rightBorder;
	field[3] = bottomBorder;

	return field;

}

int main() {
	srand(time(NULL));
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	Font font;

	if (!font.loadFromFile("Ubuntu-Bold.ttf")) {
    	
	}

	Text text1, text2, win1, win2, pressR;
	text1.setFont(font);
	text1.setString("0");
	text1.setCharacterSize(48);
	text1.setPosition(WIDTH/2-CENTRAL_LINE_WIDTH/2 - TEXT_INDENT, TEXT_INDENT/2);
	text2.setFont(font);
	text2.setString("0");
	text2.setCharacterSize(48);
	text2.setPosition(WIDTH/2-CENTRAL_LINE_WIDTH/2 + TEXT_INDENT - 26, TEXT_INDENT/2);
	win1.setFont(font);
	win1.setString("PLAYER 1 WON");
	win1.setCharacterSize(70);
	win1.setPosition(WIDTH/2 - 4*65, TEXT_INDENT + 30);
	win2.setFont(font);
	win2.setString("PLAYER 2 WON");
	win2.setCharacterSize(70);
	win2.setPosition(WIDTH/2 - 4*65, TEXT_INDENT);
	pressR.setFont(font);
	pressR.setString("press R to restart the game or ESC to finish it");
	pressR.setCharacterSize(23);
	pressR.setPosition(WIDTH/2 - 4*65 + 5, TEXT_INDENT*2 + 70);

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Ping Pong", Style::Default, settings);

    RectangleShape player1(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    RectangleShape player2(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    CircleShape ball(BALL_SIZE,50);
    ball.setPosition(WIDTH/2, (rand() % HEIGHT/2) + HEIGHT / 4);
    ball.setOrigin(BALL_SIZE, BALL_SIZE);

    float dx;
	float dy;

	int temp1 = rand() % 2;
	int temp2 = rand() % 2;

	if (temp1 == 0) 
		dx = BALL_SPEED;
	else
		dx = -BALL_SPEED;

	if (temp2 == 0)
		dy = BALL_SPEED;
	else
		dy = -BALL_SPEED;

    player1.setPosition(BORDER_INDENT+BORDER_WIDTH+BORDER_PLAYER_INDENT, HEIGHT/2 - PLAYER_HEIGHT/2);
    player2.setPosition(WIDTH - BORDER_INDENT - BORDER_WIDTH - BORDER_PLAYER_INDENT - PLAYER_WIDTH, HEIGHT/2 - PLAYER_HEIGHT/2);

    window.setVerticalSyncEnabled(true);

	vector<RectangleShape> gameField = createGameField();

	for (int i = 0; i < gameField.size(); i++) {
		window.draw(gameField[i]);
    }

	window.draw(player1);
    window.draw(player2);
   	window.draw(ball);
    window.draw(text1);
    window.draw(text2);

    window.display();

    usleep(2000000);

    while (window.isOpen()) {

    	Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
            	isFinished = true;
                window.close();
            }

            if (event.type == Event::KeyPressed) {

            	if (event.key.code == Keyboard::Escape) {
            		if (counter1 == 5 || counter2 == 5) {
            			isFinished = true;
            			window.close();
            		}
            	}

            	if (event.key.code == Keyboard::R) {
            		if (counter1 == 5 || counter2 == 5) {
            			counter1 = 0;
            			counter2 = 0;
            			text1.setString(to_string(counter1));
            			text2.setString(to_string(counter2));
            			text1.setFillColor(Color::White);
            			text2.setFillColor(Color::White);
            		}
            	}

            }

        }

    	if (counter1 == 5) {
    		window.clear(Color::Black);
    		window.draw(win1);
    		window.draw(pressR);
    		for (int i = 0; i < 4; i++) {
    			window.draw(gameField[i]);
    		}

    		window.display();

    		continue;

    	} else if (counter2 == 5) {
    		window.clear(Color::Black);
    		window.draw(win2);
    		window.draw(pressR);
    		for (int i = 0; i < 4; i++) {
    			window.draw(gameField[i]);
    		}

    		window.display();

    		continue;
    	}


    	if (isFinished) {
    		window.clear(Color::Black);
    		for (int i = 0; i < gameField.size(); i++) {
    			window.draw(gameField[i]);
    		}
    		window.draw(player1);
    		window.draw(player2);
    		window.draw(ball);
    		window.draw(text1);
    		window.draw(text2);
    		isFinished = false;
    		window.display();
    		usleep(2000000);
    	}

        if (Keyboard::isKeyPressed(Keyboard::S)) {
        	if (player1.getPosition().y <= HEIGHT - BORDER_WIDTH - BORDER_INDENT - PLAYER_HEIGHT)
        		player1.move(Vector2f(0, SPEED));
        }

        if (Keyboard::isKeyPressed(Keyboard::W)) {
        	if (player1.getPosition().y > BORDER_WIDTH + BORDER_INDENT)
        		player1.move(Vector2f(0, -SPEED));
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
        	if (player2.getPosition().y <= HEIGHT - BORDER_WIDTH - BORDER_INDENT - PLAYER_HEIGHT)
        		player2.move(Vector2f(0, SPEED));
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
        	if (player2.getPosition().y > BORDER_WIDTH + BORDER_INDENT)
        		player2.move(Vector2f(0, -SPEED));
        }

        window.clear(Color::Black);

    	for (int i = 0; i < gameField.size(); i++) {
    		window.draw(gameField[i]);
    	}

    	if (ball.getPosition().x <= BORDER_INDENT + BORDER_WIDTH + BALL_SIZE) {

    		ball.setPosition(WIDTH/2, (rand() % HEIGHT/2) + HEIGHT / 4);

			temp1 = rand() % 2;
			temp2 = rand() % 2;

			if (temp1 == 0) 
				dx = BALL_SPEED;
			else
				dx = -BALL_SPEED;

			if (temp2 == 0)
				dy = BALL_SPEED;
			else
				dy = -BALL_SPEED;

			player1.setPosition(BORDER_INDENT+BORDER_WIDTH+BORDER_PLAYER_INDENT, HEIGHT/2 - PLAYER_HEIGHT/2);
    		player2.setPosition(WIDTH - BORDER_INDENT - BORDER_WIDTH - BORDER_PLAYER_INDENT - PLAYER_WIDTH, HEIGHT/2 - PLAYER_HEIGHT/2);

    		counter2++;
    		if (counter2 == 4)
    			text2.setFillColor(Color::Red);
    		string temp = to_string(counter2);
    		text2.setString(temp);

    		isFinished = true;
    		continue;

    	}

    	if (ball.getPosition().x >= WIDTH - BORDER_INDENT - BORDER_WIDTH - BALL_SIZE) {

    		ball.setPosition(WIDTH/2, (rand() % HEIGHT/2) + HEIGHT / 4);

			temp1 = rand() % 2;
			temp2 = rand() % 2;

			if (temp1 == 0) 
				dx = BALL_SPEED;
			else
				dx = -BALL_SPEED;

			if (temp2 == 0)
				dy = BALL_SPEED;
			else
				dy = -BALL_SPEED;

			player1.setPosition(BORDER_INDENT+BORDER_WIDTH+BORDER_PLAYER_INDENT, HEIGHT/2 - PLAYER_HEIGHT/2);
    		player2.setPosition(WIDTH - BORDER_INDENT - BORDER_WIDTH - BORDER_PLAYER_INDENT - PLAYER_WIDTH, HEIGHT/2 - PLAYER_HEIGHT/2);

    		counter1++;
    		if (counter1 == 4)
    			text1.setFillColor(Color::Red);
    		string temp = to_string(counter1);
    		text1.setString(temp);

    		isFinished = true;
    		continue;

    	}

    	ball.move(dx,dy);

    	if (ball.getPosition().y <= BORDER_INDENT+BORDER_WIDTH + BALL_SIZE || 
    		ball.getPosition().y >= HEIGHT - BORDER_INDENT - BORDER_WIDTH - BALL_SIZE) {
    		dy = -dy;
    		changeDirection = true;
    	}

    	if ((ball.getPosition().y >= player1.getPosition().y - BALL_SIZE && 
    		ball.getPosition().y <= player1.getPosition().y + PLAYER_HEIGHT + BALL_SIZE &&
    		ball.getPosition().x >= player1.getPosition().x && 
    		ball.getPosition().x <= player1.getPosition().x + PLAYER_WIDTH) ||
    		(ball.getPosition().y >= player2.getPosition().y - BALL_SIZE && 
    		ball.getPosition().y <= player2.getPosition().y + PLAYER_HEIGHT + BALL_SIZE &&
    		ball.getPosition().x >= player2.getPosition().x && 
    		ball.getPosition().x <= player2.getPosition().x + PLAYER_WIDTH)) {
    		if (changeDirection == true) {
    			dy = -dy;
    			changeDirection = false;
    		}
    	}
    	

    	if ((ball.getPosition().x <= BORDER_INDENT + BORDER_WIDTH + BORDER_PLAYER_INDENT + PLAYER_WIDTH + BALL_SIZE && 
    		ball.getPosition().y >= player1.getPosition().y && 
    		ball.getPosition().y <= player1.getPosition().y + PLAYER_HEIGHT) ||
    		(ball.getPosition().x >= WIDTH - BORDER_INDENT - BORDER_WIDTH - BORDER_PLAYER_INDENT - PLAYER_WIDTH - BALL_SIZE && 
    		ball.getPosition().y >= player2.getPosition().y && 
    		ball.getPosition().y <= player2.getPosition().y + PLAYER_HEIGHT)) {
    		if (changeDirection == true) {
    			dx = -dx;
    			changeDirection = false;
    		}

    	}
    	

    	window.draw(player1);
    	window.draw(player2);
    	window.draw(ball);
    	window.draw(text1);
    	window.draw(text2);

    	window.display();


    }


}
