#include "elevator.h"

Request::Request(int floor, bool direction) {
	this->floor = floor;
	this->direction = direction;
}

Carriage newcarriage(int id) {
	Carriage c;
	c.idle = 1;
	c.floor = 0;
	c.direction = STOP;
	c.x = id ? GUI_MARGIN : elevator2_left;
	c.y = panel_bottom - floor_height;
	return c;
}

void Carriage::update() {
	static int sleeptime = 0;
	request.sort([](const Request & a, const Request & b) { return a.floor < b.floor; });
	if (request.size() && idle) {
		floor = request.front().floor;
		direction = request.front().direction;
		request.pop_front();
		dest_y = getfloorheight(floor);
		idle = 0;
	}
	if (!idle) {
		if (abs(y - dest_y) < 0.1) {
			direction = STOP;
			sleeptime++;
			if (sleeptime == 60) {
				sleeptime = 0;
				idle = 1;
			}
			return;
		}
		y += dest_y > y ? 1 : -1;
	}
}

void Carriage::draw(PIMAGE carriage) {
	putimage_transparent(NULL, carriage, x, y, BLACK);
}

int getfloorheight(int floor) {
	return panel_bottom - (floor + 1) * floor_height;
}

void clicklistener(Carriage &c1, Carriage &c2) {
	int floor_id = -1;
	bool is_up = 0;
	// check for mouse click event
	if (mousemsg()) {
		mouse_msg mouse = getmouse();
		if (mouse.is_up()) {
			for (int i = GUI_MARGIN; i < GUI_HEIGHT - GUI_MARGIN - floor_height; i += floor_height) {
				if (mouse.x > panel_left && mouse.x < panel_left + button_width
					&& mouse.y > i + BUTTON_MARGIN && mouse.y < i + floor_height - BUTTON_MARGIN) {
					floor_id = 8 - (i - GUI_MARGIN) / floor_height;
					is_up = true;
					break;
				}
				if(mouse.x > panel_right - button_width && mouse.x < panel_right
					&& mouse.y > i + BUTTON_MARGIN && mouse.y < i + floor_height - BUTTON_MARGIN) {
					floor_id = 8 - (i - GUI_MARGIN) / floor_height;
					break;
				}
			}
		}
	}
	// handle events
	if (floor_id >= 0)
		requesthandler(c1, c2, floor_id, is_up);
	flushmouse();
}

void requesthandler(Carriage &c1, Carriage &c2, int requestfloor, bool is_up) {
	// 如果电梯均未运行 则近者先服务
	// 如果请求方向与一电梯运行方向相同，则该电梯为之服务
	// 若均逆向，加入待定队列
	if (c1.idle && c2.idle) {
		if (abs(c1.y - getfloorheight(requestfloor)) > abs(c2.y - getfloorheight(requestfloor)))
			c2.request.push_back(*new Request(requestfloor, is_up));
		else
			c1.request.push_back(*new Request(requestfloor, is_up));
	} else if(c2.idle){
		if((c1.y - c1.dest_y)*(c1.y -getfloorheight(requestfloor))>0 && c1.direction != !is_up )
			c1.request.push_back(*new Request(requestfloor, is_up));
		else
			c2.request.push_back(*new Request(requestfloor, is_up));
	} else {
		if ((c2.y - c2.dest_y)*(c2.y - getfloorheight(requestfloor)) > 0 && c1.direction != !is_up)
			c2.request.push_back(*new Request(requestfloor, is_up));
		else
			c1.request.push_back(*new Request(requestfloor, is_up));
	}
}

