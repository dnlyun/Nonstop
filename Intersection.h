#include <iostream>
#include <vector>
#include "Car.h"
#include "Path.h"

using namespace std;

/*
* Handle cars moving through intersection
*/
class Intersection {
private:
	int x1, x2, y1, y2;
	double rate;

	/*
	* x1             x2
	* ----------------- y1
	* -               -
	* -               -
	* -               -
	* -               -
	* -               -
	* -               -
	* -               -
	* ----------------- y2
	*/

public:
	Intersection(int width, int rdw, double rate) {
		x1 = width / 2 - rdw / 2;
		x2 = width / 2 + rdw / 2;

		y1 = width / 2 - rdw / 2;
		y2 = width / 2 + rdw / 2;

		this->rate = rate;
	}

	/*
	* Assume two cars from same road do not occupy the intersecting area together (for safety and realistic reasons)
	* Assume two cars from different roads do not enter the intersecting area at the EXACT same time (tick)
	* FIFO
	*/
	void inInt(std::vector<Car>& cars, std::vector<Car>& inCars) {
		if (cars.size() > 0) {
			Car car = cars[0];
			if (car.getX() > x1 && car.getX() < x2) {
				if (car.getY() > y1 && car.getY() < y2) {
					car.setRelPos(0);
					inCars.push_back(car);
					cars.erase(cars.begin());
					checkCol(inCars);
				}
			}
		}
	}

	void outInt(std::vector<Car>& cars, std::vector<Car>& inCars) {
		if (inCars.size() > 0) {
			Car car = inCars[0];
			if (car.getX() < x1 || car.getX() > x2 || car.getY() < y1 || car.getY() > y2) {
				car.rstRate();
				car.setRelPos(1);
				cars.push_back(car);
				inCars.erase(inCars.begin());
				std::cout << "A car left the intersection" << endl;

				if (inCars.size() > 0) {
					inCars[0].setAccel(true);
					inCars[0].setDecel(false);
					inCars[0].rstRate();
				}
			}
		}
	}

	bool checkOrg(int org, std::vector<Car>& inCars) {
		for (Car car : inCars) {
			if (car.getOrg() == org) {
				return true;
			}
		}
		return false;
	}

	bool checkDes(int des, std::vector<Car>& inCars) {
		for (Car car : inCars) {
			if (car.getDes() == des) {
				return true;
			}
		}
		return false;
	}

	Car getOrgCar(int org, std::vector<Car>& inCars) {
		for (Car car : inCars) {
			if (car.getOrg() == org) {
				return car;
			}
		}
	}

	/*
	* Control speed of entering cars to avoid collisions
	*/
	void checkCol(std::vector<Car>& inCars) {
		//If equal to 0, don't change speed
		if (inCars.size() > 2) {
			Car temp = inCars.back();
			temp.setDecel(true);
		}
		else if (inCars.size() == 2) {
			Car temp1 = inCars[0];
			Car temp2 = inCars[1];

			/*
			* 0 - straight
			* 1 - left
			* 2 - right
			*/
			if (temp1.getPathType() == 0 && temp2.getPathType() == 0) {
				if (temp1.getOrg() == 0 && temp2.getOrg() == 2) {
					//No speed change
				}
				else if (temp1.getOrg() == 2 && temp2.getOrg() == 0) {
					//No speed change
				}
				else if (temp1.getOrg() == 1 && temp2.getOrg() == 3) {
					//No speed change
				}
				else if (temp1.getOrg() == 3 && temp2.getOrg() == 1) {
					//No speed change
				}
				else {
					temp2.setDecel(true);
				}
			}
			else if (temp1.getPathType() == 2 && temp2.getPathType() == 2) {
				//No speed change
			}
			else if (temp1.getPathType() == 0 && temp2.getPathType() == 2) {
				if (temp1.getOrg() == 0) {
					if (temp2.getOrg() == 1 || temp2.getOrg() == 2) {
						//No speed change
					}
					else {
						temp2.setDecel(true);
					}
				}
				else if (temp1.getOrg() == 1) {
					if (temp2.getOrg() == 2 || temp2.getOrg() == 3) {
						//No speed change
					}
					else {
						temp2.setDecel(true);
					}
				}
				else if (temp1.getOrg() == 2) {
					if (temp2.getOrg() == 0 || temp2.getOrg() == 3) {
						//No speed change
					}
					else {
						temp2.setDecel(true);
					}
				}
				else if (temp1.getOrg() == 3) {
					if (temp2.getOrg() == 0 || temp2.getOrg() == 1) {
						//No speed change
					}
					else {
						temp2.setDecel(true);
					}
				}
			}
			else if (temp2.getPathType() == 0 && temp1.getPathType() == 2) {
				if (temp2.getOrg() == 0) {
					if (temp1.getOrg() == 1 || temp1.getOrg() == 2) {
						//No speed change
					}
					else {
						temp1.setDecel(true);
					}
				}
				else if (temp2.getOrg() == 1) {
					if (temp1.getOrg() == 2 || temp1.getOrg() == 3) {
						//No speed change
					}
					else {
						temp1.setDecel(true);
					}
				}
				else if (temp2.getOrg() == 2) {
					if (temp1.getOrg() == 0 || temp1.getOrg() == 3) {
						//No speed change
					}
					else {
						temp1.setDecel(true);
					}
				}
				else if (temp2.getOrg() == 3) {
					if (temp1.getOrg() == 0 || temp1.getOrg() == 1) {
						//No speed change
					}
					else {
						temp1.setDecel(true);
					}
				}
			}
			else {
				temp2.setDecel(true);
			}
		}
		else if (inCars.size() == 1) {
			//No speed change
		}
	}
};