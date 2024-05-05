//创建一个QT类，以Widget为父类
#include <Widget.h>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPixmap>
#include <QStringList>
#include <QFileDialog>



Widget::Widget(QWidget *parent)
	: QWidget(parent)
	,roleLabel(new QLabel(this)) 
	, curFrame(0)//将当前帧初始化为0
{   //去掉窗口的边框，和让背景透明
	setWindowFlags(Qt::WindowType::FramelessWindowHint);//让边框尽量少
	setAttribute(Qt::WA_TranslucentBackground);//让背景透明
	

	//给窗口设置阴影，增加立体感
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 231, 232, 220));//设置阴影颜色
	effect->setBlurRadius(5);//设置模糊半径
	this->setGraphicsEffect(effect);

	this->installEventFilter(this);//安装事件过滤器到自身
	
	roleLabel->resize(500,500);//设置图片大小
}
 
Widget::~Widget()
{
  }
//更新人物动作
void Widget::updateRoleAnimation()
{
	QString qss("background - repeat:no - repeat; ");//不重复输出同一张图片
	roleLabel -> setStyleSheet(qss+QString("background-image:url(:/resource/assets/images/png/learn.png);").arg(curFrame));//加载图片路径
	curFrame = (curFrame + 1) % 6;
}

//控制移动
bool Widget::eventFilter(QObject* watched, QEvent* event)
{
	QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);

	static QPoint lastPos;
	if (event->type() == QEvent::MouseButtonPress && mouseEvent)
	{
		// 使用 toPoint() 转换 QPointF 到 QPoint
		lastPos = mouseEvent->globalPosition().toPoint() - this->pos();
	}
	else if (event->type() == QEvent::MouseMove && (mouseEvent->buttons() & Qt::LeftButton))
	{
		// 同样使用 toPoint() 进行转换
		this->move(mouseEvent->globalPosition().toPoint() - lastPos);
	}

	return QWidget::eventFilter(watched, event);
}
//设置按钮
void Widget::initBin()
{
	closeBtn = new QPushButton(this);
	cutBtn = new QPushButton(this);
	openBtn = new QPushButton(this);

	//设置按钮大小
	closeBtn->setGeometry(300, 200, 32, 32);
	cutBtn->setGeometry(300, 240, 32, 32);
	openBtn->setGeometry(300, 280, 32, 32);
	closeBtn ->setObjectName("closeBtn");

	//加载按钮的图片
	closeBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg)");
	cutBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg)");
	openBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg)");
	
	//将按钮背景设置为白色，边框设置为圆角矩形。用颜色变化作为点击closeBtn的反馈
	this->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border:none; border - radius:5px;}\
		QPushButton#closeBtn:hover{ background - color:rgb(233,31,48);}");
	
	



	void Widget::switchImage()
	{
		// 示例切换图片操作，可根据需要进行修改
		curFrame = (curFrame + 1) % 6; // 循环切换图片
		updateRoleAnimation();         // 更新显示的图片
	}
	void Widget::openFileDialog()
	{
		// 打开文件对话框选择图片
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
		if (!fileName.isEmpty())
		{
			// 设置 roleLabel 显示新图片
			QString qss = QString("background-repeat:no-repeat; background-image:url(%1);").arg(fileName);
			roleLabel->setStyleSheet(qss);
		}
	}
	
	
	//连接槽函数
	// 连接切换图片按钮
	connect(cutBtn, &QPushButton::clicked, this, &Widget::switchImage);
	// 连接打开文件对话框按钮
	connect(openBtn, &QPushButton::clicked, this, &Widget::openFileDialog);

}


