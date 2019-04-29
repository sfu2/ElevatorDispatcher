#pragma once
#include <list>
#include <string>
#include "gui.h"

using namespace std;

#define STOP	2
#define UP		1
#define DOWN	0

struct Request {
	int floor;
	bool direction;
public:
	Request(int floor, bool direction);
};

struct Carriage {
	bool idle;		// is idling
	short direction;// direction
	int x, y;	// current position
	int dest_y;	// destination height
	int floor;	// destination floor
	list<Request> request;
	static list<Request> undecided;
public:
	void update();
	void draw(PIMAGE carriage);
};

Carriage newcarriage(int id);
int getfloorheight(int floor);
void clicklistener(Carriage &c1, Carriage &c2);
void requesthandler(Carriage &c1, Carriage &c2, int requestfloor, bool is_up);