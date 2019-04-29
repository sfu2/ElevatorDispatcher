#include "elevator.h"

using namespace std;

void mainloop() {
	// Logical Part
	Carriage c1 = newcarriage(0), c2 = newcarriage(1);
	// GUI Part
	setcaption("电梯运行调度模拟");
	PIMAGE background = getbackground();
	PIMAGE carriage = getcarriage();
	for (; is_run(); delay_fps(60)) {
		// Logical Update
		clicklistener(c1, c2);
		c1.update();
		c2.update();

		// GUI Update
		cleardevice();
		putimage(0, 0, background);
		c1.draw(carriage);
		c2.draw(carriage);
		setforeground();
	}
	delimage(background);
	delimage(carriage);
}

int main() {
	setinitmode(0);
	initgraph(GUI_WIDTH, GUI_HEIGHT);   // 图形初始化，窗口尺寸
	setrendermode(RENDER_MANUAL);		// 绘图更新模式设置为手动，避免闪烁
	mainloop();
	return 0;
}
