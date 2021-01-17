#ifndef CAR_HEADER
#define CAR_HEADER

#include "Path.h"

using namespace std;

class Car {
private:
	int width, rdw;
	int org, des;
	double x, y;
	double orgRate, rate;
	Path path;
	bool decel, accel;
	int relPos;
	int pathType;
	double angle;

public:
	Car() {

	}

	Car(int width, int rdw, int org, int des, double rate) {
		this->width = width;
		this->rdw = rdw;
		this->org = org;
		this->des = des;
		this->rate = rate;
		orgRate = rate;
		decel = false;
		accel = false;
		relPos = -1;
		angle = 0;

		if (org == 0) {
			if (des == 1) {
				path = LeftPath(width, rdw, 0);
			}
			else if (des == 2) {
				path = StraightPath(width, rdw, 0);
			}
			else if (des == 3) {
				path = RightPath(width, rdw, 0);
			}
		}
		else if (org == 1) {
			if (des == 0) {
				path = RightPath(width, rdw, 1);
			}
			else if (des == 2) {
				path = LeftPath(width, rdw, 1);
			}
			else if (des == 3) {
				path = StraightPath(width, rdw, 1);
			}
		}
		else if (org == 2) {
			if (des == 0) {
				path = StraightPath(width, rdw, 2);
			}
			else if (des == 1) {
				path = RightPath(width, rdw, 2);
			}
			else if (des == 3) {
				path = LeftPath(width, rdw, 2);
			}
		}
		else if (org == 3) {
			if (des == 0) {
				path = LeftPath(width, rdw, 3);
			}
			else if (des == 1) {
				path = StraightPath(width, rdw, 3);
			}
			else if (des == 2) {
				path = RightPath(width, rdw, 3);
			}
		}

		if (org - des == 2 || org - des == -2) {
			pathType = 0;
		}
		else if (org - des == -1 || org - des == 3) {
			pathType = 1;
		}
		else if (org - des == 1 || org - des == -3) {
			pathType = 2;
		}
		else {
			pathType = -1;
		}

		x = path.getX();
		y = path.getY();
	}

	int getOrg() {
		return org;
	}

	int getDes() {
		return des;
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	void setAng(double x) {
		angle += x;
	}

	double getAng() {
		return angle;
	}

	/*
	* 0 - straight
	* 1 - left
	* 2 - right
	*/
	int getPathType() {
		return pathType;
	}

	void setRate(double rate) {
		this->rate = rate;
	}

	void setAccel(bool foo) {
		accel = foo;
	}

	void setDecel(bool foo) {
		decel = foo;
	}

	void decelerate() {
		this->rate -= 0.05f;
		if (rate == 0) {
			decel = false;
		}
	}

	void rstRate() {
		if (rate == orgRate) {
			accel = false;
		}
		else if (accel) {
			this->rate += 0.05f;
		}
	}

	void setRelPos(int relPos) {
		this->relPos = relPos;
	}

	void update() {
		if (pathType == 0) {
			StraightPath* temp = (StraightPath*)&path;
			temp->move(rate, relPos, x, y);
		}
		else if (pathType == 1) {
			LeftPath* temp = (LeftPath*)&path;
			temp->move(rate, relPos, x, y);
		}
		else if (pathType == 2) {
			RightPath* temp = (RightPath*)&path;
			temp->move(rate, relPos, x, y);
		}
	}
};
#endif