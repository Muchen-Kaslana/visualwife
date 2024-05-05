#pragma once

#include <QWidget>
#include <Qpixmap>
#include <qlabel.h>
#include <QPushButton>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    QLabel* roleLabel;
    qint8 curFrame;
    QPushButton* closeBtn;
    QPushButton* cutBtn;
    QPushButton* openBtn;

    void initBin();
    void updateRoleAnimation();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

  //¶¨Òå²ÛÉùÃ÷
public slots:
    void switchImage();
    void openFileDialog();
};
  