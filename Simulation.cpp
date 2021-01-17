#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Car.h"
#include "Intersection.h"
#include "Path.h"

using namespace std;

int main();
int spawnCar(int prevNum, std::vector<Car>& toCars);
int pickDes(int x);
void drawBg(sf::RenderWindow& window);

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Simulation");
	window.setFramerateLimit(100);

	sf::Event event;

	sf::Transform transform;

	std::vector<Car> toCars;
	std::vector<Car> inCars;
	std::vector<Car> outCars;

	Intersection itst(800, 160, 1.f);

	int prevNum = 0;

	while (window.isOpen()) {
		//Draw background
		drawBg(window);

		prevNum = spawnCar(prevNum, toCars);


		if (toCars.size() > 0) {
			for (int i = 0; i < toCars.size(); i++) {
				int x = toCars[i].getX();
				int y = toCars[i].getY();

				if (toCars[i].getOrg() == 0 || toCars[i].getOrg() == 2) {
					sf::RectangleShape obj(sf::Vector2f(30, 60));
					obj.setFillColor(sf::Color(60, 245, 255));
					obj.setPosition(x - 15, y - 30);
					window.draw(obj);
				}
				else if (toCars[i].getOrg() == 1 || toCars[i].getOrg() == 3) {
					sf::RectangleShape obj(sf::Vector2f(60, 30));
					obj.setFillColor(sf::Color(60, 245, 255));
					obj.setPosition(x - 30, y - 15);
					window.draw(obj);
				}

				toCars[i].update();
			}
		}

		if (inCars.size() > 0) {
			for (int i = 0; i < inCars.size(); i++) {
				int x = inCars[i].getX();
				int y = inCars[i].getY();

				transform.rotate(0, sf::Vector2f(x, y));

				if (inCars[i].getOrg() == 0 || inCars[i].getOrg() == 2) {
					sf::RectangleShape obj(sf::Vector2f(30, 60));
					obj.setFillColor(sf::Color(60, 245, 255));
					obj.setPosition(x - 15, y - 30);

					if (inCars[i].getOrg() == 0) {
						if (inCars[i].getPathType() == 1) {
							double angle = inCars[i].getAng();
							transform.rotate(-angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
						else if (inCars[i].getPathType() == 2) {
							double angle = inCars[i].getAng();
							transform.rotate(angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
					}
					else if (inCars[i].getOrg() == 2) {
						if (inCars[i].getPathType() == 1) {
							double angle = inCars[i].getAng();
							transform.rotate(angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
						else if (inCars[i].getPathType() == 2) {
							double angle = inCars[i].getAng();
							transform.rotate(-angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
					}
					window.draw(obj, transform);
				}
				else if (inCars[i].getOrg() == 1 || inCars[i].getOrg() == 3) {
					sf::RectangleShape obj(sf::Vector2f(60, 30));
					obj.setFillColor(sf::Color(60, 245, 255));
					obj.setPosition(x - 30, y - 15);

					if (inCars[i].getOrg() == 1) {
						if (inCars[i].getPathType() == 0) {
							double angle = inCars[i].getAng();
							transform.rotate(angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
						else if (inCars[i].getPathType() == 2) {
							double angle = inCars[i].getAng();
							transform.rotate(-angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
					}
					else if (inCars[i].getOrg() == 3) {
						if (inCars[i].getPathType() == 0) {
							double angle = inCars[i].getAng();
							transform.rotate(-angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
						else if (inCars[i].getPathType() == 2) {
							double angle = inCars[i].getAng();
							transform.rotate(angle, sf::Vector2f(x, y));
							inCars[i].setAng(0.025);
						}
					}
					window.draw(obj, transform);
				}

				inCars[i].update();
			}
		}

		if (outCars.size() > 0) {
			for (int i = 0; i < outCars.size(); i++) {
				int x = outCars[i].getX();
				int y = outCars[i].getY();

				if (outCars[i].getDes() == 0 || outCars[i].getDes() == 2) {
					sf::RectangleShape obj(sf::Vector2f(30, 60));
					obj.setFillColor(sf::Color(60, 245, 255));
					obj.setPosition(x - 15, y - 30);
					window.draw(obj);
				}
				else if (outCars[i].getDes() == 1 || outCars[i].getDes() == 3) {
					sf::RectangleShape obj(sf::Vector2f(60, 30));
					obj.setFillColor(sf::Color(60, 245, 255));
					obj.setPosition(x - 30, y - 15);
					window.draw(obj);
				}

				outCars[i].update();
			}
		}

		itst.inInt(toCars, inCars);
		itst.outInt(outCars, inCars);

		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
	}
	return 0;
}

int spawnCar(int prevNum, std::vector<Car> &toCars) {
	int rtNum = prevNum;

	//Spawn car at random intervals and entry points
	if (rand() % 300 == 0) {
		int randNum = rand() % (4);
		if (randNum != prevNum) {
			rtNum = randNum;

			int org = randNum;
			int des = pickDes(org);

			Car car(800, 160, org, des, 1);
			toCars.push_back(car);
			std::cout << "New car" << endl;
		}
	}
	return rtNum;
}

int pickDes(int x) {
	int a, b, c;
	if (x == 0) {
		a = 1;
		b = 2;
		c = 3;
	}
	else if (x == 1) {
		a = 0;
		b = 2;
		c = 3;
	}
	else if (x == 2) {
		a = 0;
		b = 1;
		c = 3;
	}
	else if (x == 3) {
		a = 0;
		b = 1;
		c = 2;
	}
	std::vector<int> list{a, b, c};
	int index = rand() % 3;
	return list[index];
}

void drawBg(sf::RenderWindow &window) {
	window.clear(sf::Color(50, 50, 50)); //Set street colour

	//Create sidewalks
	sf::RectangleShape topLeft(sf::Vector2f(320, 320));
	topLeft.setFillColor(sf::Color(220, 220, 220));
	topLeft.setPosition(0, 0);

	sf::RectangleShape topRight(sf::Vector2f(320, 320));
	topRight.setFillColor(sf::Color(220, 220, 220));
	topRight.setPosition(480, 0);

	sf::RectangleShape botLeft(sf::Vector2f(320, 320));
	botLeft.setFillColor(sf::Color(220, 220, 220));
	botLeft.setPosition(0, 480);

	sf::RectangleShape botRight(sf::Vector2f(320, 320));
	botRight.setFillColor(sf::Color(220, 220, 220));
	botRight.setPosition(480, 480);


	//Create grass
	sf::RectangleShape topLeftGrass(sf::Vector2f(270, 270));
	topLeftGrass.setFillColor(sf::Color(24, 125, 40));
	topLeftGrass.setPosition(0, 0);

	sf::RectangleShape topRightGrass(sf::Vector2f(270, 270));
	topRightGrass.setFillColor(sf::Color(24, 125, 40));
	topRightGrass.setPosition(530, 0);

	sf::RectangleShape botLeftGrass(sf::Vector2f(270, 270));
	botLeftGrass.setFillColor(sf::Color(24, 125, 40));
	botLeftGrass.setPosition(0, 530);

	sf::RectangleShape botRightGrass(sf::Vector2f(270, 270));
	botRightGrass.setFillColor(sf::Color(24, 125, 40));
	botRightGrass.setPosition(530, 530);


	//Create street lines
	sf::RectangleShape hLines(sf::Vector2f(140, 10));
	hLines.setFillColor(sf::Color::Yellow);

	sf::RectangleShape vLines(sf::Vector2f(10, 140));
	vLines.setFillColor(sf::Color::Yellow);


	//Draw on screen
	window.draw(topLeft);
	window.draw(topRight);
	window.draw(botLeft);
	window.draw(botRight);
	window.draw(topLeftGrass);
	window.draw(topRightGrass);
	window.draw(botLeftGrass);
	window.draw(botRightGrass);

	hLines.setPosition(0, 395);
	window.draw(hLines);
	hLines.setPosition(180, 395);
	window.draw(hLines);
	hLines.setPosition(480, 395);
	window.draw(hLines);
	hLines.setPosition(660, 395);
	window.draw(hLines);

	vLines.setPosition(395, 0);
	window.draw(vLines);
	vLines.setPosition(395, 180);
	window.draw(vLines);
	vLines.setPosition(395, 480);
	window.draw(vLines);
	vLines.setPosition(395, 660);
	window.draw(vLines);
}