#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


int signNumber(int);

const int height = 100;
const int width = 10;
const int radius = 10;
sf::Vector2f step(signNumber(5),signNumber(3));
int counter = 0;
bool move = true;
int score = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "game");
	window.setFramerateLimit(60);

	// Load backgrounnd
	sf::Texture background;
	if (!background.loadFromFile("pictures/space.jpg")) {
		std::cerr << "ERROR: cannot load  a picture\n";
		return 1;
	}
	
	// Load font
	sf::Font font;
	if (!font.loadFromFile("recource/ARIAL.TTF")) {
		std::cerr << "ERROR: cannot load font\n";
		return 1;
	}
	
	// Score
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(350,0);

	// Set background
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setPosition(0,0);

	sf::RectangleShape line(sf::Vector2f(width,height));
	sf::RectangleShape line2(sf::Vector2f(width,height));
	sf::CircleShape ball(radius);

	ball.setOrigin(radius, radius);

	line.setFillColor(sf::Color::Red);
	line2.setFillColor(sf::Color::Red);

	sf::Vector2f linePosition;
	sf::Vector2f linePosition2;
	sf::Vector2f ballPosition;

	line.setPosition(0,240);
	line2.setPosition(800 - width,240);
	ball.setPosition(400,300);

    while (window.isOpen())
    {
		linePosition = line.getPosition();
		linePosition2 = line2.getPosition();
		ballPosition = ball.getPosition();
		scoreText.setString("SCORE: " + std::to_string(score));
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (event.type == sf::Event::Closed)
                window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (linePosition.y >= 20) {
					line.move(0,-10);
					//std::cout << "Positon X: "<< linePosition.x << " Y: " << linePosition.y << std::endl;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				if (linePosition.y <= 580 - height) {
					line.move(0,10);
					//std::cout << "Positon X: "<< linePosition.x << " Y: " << linePosition.y << std::endl;
				}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				if (linePosition2.y >= 20) {
					line2.move(0,-10);
					//std::cout << "Positon2 X: "<< linePosition2.x << " Y: " << linePosition2.y << std::endl;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
				if (linePosition2.y <= 580 - height) {
					line2.move(0,10);
					//std::cout << "Positon2 X: "<< linePosition2.x << " Y: " << linePosition2.y << std::endl;
				}
			}

        }
		counter++;
		if ((counter == 3) && move) {
			ball.move(step);
			counter = 0; 
		}

		// collizion detection i think
		if ((ballPosition.x == (800 - width - radius)) && (ballPosition.y  > linePosition2.y) && (ballPosition.y < (linePosition2.y + 100))){
			step.x  = -step.x;
			ball.move(step);	
			score++;
		}
		else if (ballPosition.x > (800 - width - radius)) {
			move = false;
		}

		if ((ballPosition.x == (width + radius)) && (ballPosition.y  > linePosition.y) && (ballPosition.y < (linePosition.y + 100))){
			step.x = -step.x;
			ball.move(step);	
		}
		else if (ballPosition.x < (width + radius)) {
			move = false;
		}

		if ((ballPosition.y - radius) < 0 || (ballPosition.y + radius) > 600) {
			step.y = -step.y;
			ball.move(step);
			score++;
		}

        window.clear();
		window.draw(sprite);
        window.draw(line);
		window.draw(line2);
		window.draw(ball);
		window.draw(scoreText);
        window.display();
    }

    return 0;
}

int signNumber(int number){
	srand(time(nullptr));
	if (rand() % 2){
		return number;
	}
	return -number;
}

