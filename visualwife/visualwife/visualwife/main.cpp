#include<qapplication.h>
#include "Widget.h"
int main(int argc, char* argv[])
{  
	//����һ������
	QApplication a(argc,argv);
	Widget w;
	w.show();

	return a.exec();//�߼���ѭ������ס���˳�
}