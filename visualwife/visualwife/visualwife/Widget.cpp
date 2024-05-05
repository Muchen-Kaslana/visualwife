//����һ��QT�࣬��WidgetΪ����
#include <Widget.h>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPixmap>
#include <QStringList>
#include <QFileDialog>



Widget::Widget(QWidget *parent)
	: QWidget(parent)
	,roleLabel(new QLabel(this)) 
	, curFrame(0)//����ǰ֡��ʼ��Ϊ0
{   //ȥ�����ڵı߿򣬺��ñ���͸��
	setWindowFlags(Qt::WindowType::FramelessWindowHint);//�ñ߿�����
	setAttribute(Qt::WA_TranslucentBackground);//�ñ���͸��
	

	//������������Ӱ�����������
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 231, 232, 220));//������Ӱ��ɫ
	effect->setBlurRadius(5);//����ģ���뾶
	this->setGraphicsEffect(effect);

	this->installEventFilter(this);//��װ�¼�������������
	
	roleLabel->resize(500,500);//����ͼƬ��С
}
 
Widget::~Widget()
{
  }
//�������ﶯ��
void Widget::updateRoleAnimation()
{
	QString qss("background - repeat:no - repeat; ");//���ظ����ͬһ��ͼƬ
	roleLabel -> setStyleSheet(qss+QString("background-image:url(:/resource/assets/images/png/learn.png);").arg(curFrame));//����ͼƬ·��
	curFrame = (curFrame + 1) % 6;
}

//�����ƶ�
bool Widget::eventFilter(QObject* watched, QEvent* event)
{
	QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);

	static QPoint lastPos;
	if (event->type() == QEvent::MouseButtonPress && mouseEvent)
	{
		// ʹ�� toPoint() ת�� QPointF �� QPoint
		lastPos = mouseEvent->globalPosition().toPoint() - this->pos();
	}
	else if (event->type() == QEvent::MouseMove && (mouseEvent->buttons() & Qt::LeftButton))
	{
		// ͬ��ʹ�� toPoint() ����ת��
		this->move(mouseEvent->globalPosition().toPoint() - lastPos);
	}

	return QWidget::eventFilter(watched, event);
}
//���ð�ť
void Widget::initBin()
{
	closeBtn = new QPushButton(this);
	cutBtn = new QPushButton(this);
	openBtn = new QPushButton(this);

	//���ð�ť��С
	closeBtn->setGeometry(300, 200, 32, 32);
	cutBtn->setGeometry(300, 240, 32, 32);
	openBtn->setGeometry(300, 280, 32, 32);
	closeBtn ->setObjectName("closeBtn");

	//���ذ�ť��ͼƬ
	closeBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg)");
	cutBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg)");
	openBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg)");
	
	//����ť��������Ϊ��ɫ���߿�����ΪԲ�Ǿ��Ρ�����ɫ�仯��Ϊ���closeBtn�ķ���
	this->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border:none; border - radius:5px;}\
		QPushButton#closeBtn:hover{ background - color:rgb(233,31,48);}");
	
	



	void Widget::switchImage()
	{
		// ʾ���л�ͼƬ�������ɸ�����Ҫ�����޸�
		curFrame = (curFrame + 1) % 6; // ѭ���л�ͼƬ
		updateRoleAnimation();         // ������ʾ��ͼƬ
	}
	void Widget::openFileDialog()
	{
		// ���ļ��Ի���ѡ��ͼƬ
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
		if (!fileName.isEmpty())
		{
			// ���� roleLabel ��ʾ��ͼƬ
			QString qss = QString("background-repeat:no-repeat; background-image:url(%1);").arg(fileName);
			roleLabel->setStyleSheet(qss);
		}
	}
	
	
	//���Ӳۺ���
	// �����л�ͼƬ��ť
	connect(cutBtn, &QPushButton::clicked, this, &Widget::switchImage);
	// ���Ӵ��ļ��Ի���ť
	connect(openBtn, &QPushButton::clicked, this, &Widget::openFileDialog);

}


