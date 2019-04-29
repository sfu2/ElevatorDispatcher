#include "gui.h"

PIMAGE getbackground() {
	LOGFONTA f;
	PIMAGE background = newimage();
	getfont(&f);
	f.lfHeight = 22;
	f.lfWeight = 0;
	f.lfWeight = FW_HEAVY;
	f.lfQuality = PROOF_QUALITY;
	setfont(&f);
	setbkcolor(0xffffff);
	setfillcolor(LIGHTGRAY);
	bar3d(GUI_MARGIN, GUI_MARGIN,
		evevator1_right, panel_bottom, GUI_DEPTH, true);
	bar3d(elevator2_left, GUI_MARGIN,
		evevator2_right, panel_bottom, GUI_DEPTH, true);
	setfillcolor(0x03dac6);
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	for (int i = GUI_MARGIN; i< GUI_HEIGHT - GUI_MARGIN - floor_height; i += floor_height) {
		bar(panel_left, i + BUTTON_MARGIN, 
			panel_left + button_width, i + floor_height - BUTTON_MARGIN);
		bar(panel_right - button_width, i + BUTTON_MARGIN,
			panel_right, i + floor_height - BUTTON_MARGIN);
		outtextxy(panel_left + 25, i + BUTTON_MARGIN + 10, "UP");
		outtextxy(panel_right - button_width + 10, i + BUTTON_MARGIN + 10, "DOWN");
	}
	getimage(background, 0, 0, GUI_WIDTH, GUI_HEIGHT);
	cleardevice();
	return background;
}

void setforeground() {
	setcolor(WHITE);
	for (int i = GUI_MARGIN; i < GUI_HEIGHT - GUI_MARGIN - floor_height; i += floor_height) {
		line(GUI_MARGIN + BUTTON_MARGIN, i, evevator1_right - BUTTON_MARGIN, i);
		line(elevator2_left + BUTTON_MARGIN, i, evevator2_right - BUTTON_MARGIN, i);
	}
}

PIMAGE getcarriage() {
	PIMAGE carriage = newimage();
	setfillcolor(0x018786);
	setbkcolor(BLACK);
	bar(BUTTON_MARGIN, BUTTON_MARGIN, 
		elevator_width - BUTTON_MARGIN, floor_height - BUTTON_MARGIN);
	getimage(carriage, 0, 0, elevator_width, floor_height);
	return carriage;
}