#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

using namespace std;

class Path {
public:
	int width, rdw, org;
	double x, y;
	double pi = M_PI;
	int angle;

	Path() {

	}

	Path(int width, int rdw, int org) {
		this->width = width;
		this->rdw = rdw;
		this->org = org;
		angle = 0;

		setStart();
	}

	void setStart() {
		//North
		if (org == 0) {
			x = (double) width / 2 - rdw / 4;
			y = 0;
		} //East
		else if (org == 1) {
			x = width;
			y = (double) width / 2 - rdw / 4;
		} //South
		else if (org == 2) {
			x = (double) width / 2 + rdw / 4;
			y = width;
		} //West
		else if (org == 3) {
			x = 0;
			y = (double) width / 2 + rdw / 4;
		}
	}

	void move(double rate, int relPos) {}

	void setX(double d) {
		this->x += d;
	}

	void setY(double d) {
		this->y += d;
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}
};

class StraightPath : public Path {
public:
	StraightPath() {

	}

	StraightPath(int width, int rdw, int org) : Path(width, rdw, org) {}

	void move(double rate, int relPos, double &cx, double &cy) {
		if (org == 0) {
			cy += rate;
		}
		else if (org == 1) {
			cx -= rate;
		}
		else if (org == 2) {
			cy -= rate;
		}
		else if (org == 3) {
			cx += rate;
		}
	}
};

class LeftPath : public Path {
public:
	LeftPath() {

	}

	LeftPath(int width, int rdw, int org) : Path(width, rdw, org) {}

	void move(double rate, int relPos, double& cx, double& cy) {
		if (relPos == -1) {
			if (org == 0) {
				cy += rate;
			}
			else if (org == 1) {
				cx -= rate;
			}
			else if (org == 2) {
				cy -= rate;
			}
			else if (org == 3) {
				cx += rate;
			}
		}
		else if (relPos == 0) {
			if (org == 0) {
				cx += 1.4 * pi / 2 * sin(angle * pi / 180);
				cy += 1.4 * pi / 2 * cos(angle * pi / 180);
				angle = angle + rate;
			}
			else if (org == 1) {
				cx -= 1.4 * pi / 2 * cos(angle * pi / 180);
				cy += 1.4 * pi / 2 * sin(angle * pi / 180);
				angle = angle + rate;
			}
			else if (org == 2) {
				cx -= 1.4 * pi / 2 * sin(angle * pi / 180);
				cy -= 1.4 * pi / 2 * cos(angle * pi / 180);
				angle = angle + rate;
			}
			else if (org == 3) {
				cx += 1.4 * pi / 2 * cos(angle * pi / 180);
				cy -= 1.4 * pi / 2 * sin(angle * pi / 180);
				angle = angle + rate;
			}
		}
		else if (relPos == 1) {
			if (org == 0) {
				cx += rate;
			}
			else if (org == 1) {
				cy += rate;
			}
			else if (org == 2) {
				cx -= rate;
			}
			else if (org == 3) {
				cy -= rate;
			}
		}
	}
};

class RightPath : public Path {
public:
	RightPath() {

	}

	RightPath(int width, int rdw, int org) : Path(width, rdw, org) {}

	void move(double rate, int relPos, double& cx, double& cy) {
		if (relPos == -1) {
			if (org == 0) {
				cy += rate;
			}
			else if (org == 1) {
				cx -= rate;
			}
			else if (org == 2) {
				cy -= rate;
			}
			else if (org == 3) {
				cx += rate;
			}
		}
		else if (relPos == 0) {
			if (org == 0) {
				cx -= 2 / pi * sin(angle * pi / 180);
				cy += 2 / pi * cos(angle * pi / 180);
				angle = angle + rate;
			}
			else if (org == 1) {
				cx -= 2 / pi * cos(angle * pi / 180);
				cy -= 2 / pi * sin(angle * pi / 180);
				angle = angle + rate;
			}
			else if (org == 2) {
				cx += 2 / pi * sin(angle * pi / 180);
				cy -= 2 / pi * cos(angle * pi / 180);
				angle = angle + rate;
			}
			else if (org == 3) {
				cx += 2 / pi * cos(angle * pi / 180);
				cy += 2 / pi * sin(angle * pi / 180);
				angle = angle + rate;
			}
		}
		else if (relPos == 1) {
			if (org == 0) {
				cx -= rate;
			}
			else if (org == 1) {
				cy -= rate;
			}
			else if (org == 2) {
				cx += rate;
			}
			else if (org == 3) {
				cy += rate;
			}
		}
	}
};