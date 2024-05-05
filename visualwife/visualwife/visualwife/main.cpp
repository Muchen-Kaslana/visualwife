#include<qapplication.h>
#include "Widget.h"
int main(int argc, char* argv[])
{  
	//创建一个窗口
	QApplication a(argc,argv);
	Widget w;
	w.show();

	return a.exec();//逻辑死循环，卡住不退出
}