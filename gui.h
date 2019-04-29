#pragma once

#include<graphics.h>

#define GUI_WIDTH		600
#define GUI_HEIGHT		600
#define GUI_MARGIN		50
#define GUI_SIDEBAR		200
#define GUI_DEPTH		40
#define BUTTON_MARGIN	8

#define FLOOR_NUM		9

const float panel_left = GUI_WIDTH - GUI_SIDEBAR;
const float panel_right = GUI_WIDTH - GUI_MARGIN;
const float panel_bottom = GUI_HEIGHT - GUI_MARGIN;
const float button_width = (panel_right - panel_left - BUTTON_MARGIN) / 2;
const float floor_height = (GUI_HEIGHT - 2 * GUI_MARGIN) / FLOOR_NUM;
const float elevator_width = (GUI_WIDTH - GUI_SIDEBAR - 3 * GUI_MARGIN) / 2;
const float evevator1_right = GUI_MARGIN + elevator_width;
const float elevator2_left = 2 * GUI_MARGIN + elevator_width;
const float evevator2_right = elevator2_left + elevator_width;

PIMAGE getbackground();

void setforeground();

PIMAGE getcarriage();