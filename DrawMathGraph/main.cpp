#include "DxLib.h"
#include "control.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(800, 600, 16);
	ChangeWindowMode(TRUE);
	//SetBackgroundColor(255, 255, 255);
	SetMainWindowText("DrawMathGraph");
	SetWindowText("DrawMathGraph");
	SetWindowIconID(101);

	if (DxLib_Init() == -1) return -1;  
	

	SetDrawScreen(DX_SCREEN_BACK);

	auto control = new Control();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		control->update();
		control->draw();
	}


	DxLib_End();        

	return 0;  
}
