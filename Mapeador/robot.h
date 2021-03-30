//Header that includes robot properties

#ifndef ROBOTH
#define ROBOTH

typedef struct _robot robot;

//units of properties given in metrical system
struct _robot {

	struct velocity {
		double lineal, angular;
	}velocity1;

	struct acceleration {
		double lineal, angular;
	}acceleration1;	

	struct dimensions {
		double length, width, height, wheel_radius;
	}dimension1;

	struct mass {
		double structure, wheel;
	}mass1;

};

robot robot_scanf_s(void);
void robot_print(robot robot1, unsigned char precision);

#endif