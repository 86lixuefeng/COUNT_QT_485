#ifndef WIDGET_H
#define WIDGET_H

#include <QtCore>
#include <QtGui>
#include <QLabel>
class StorageDisplay : public QWidget
{
    Q_OBJECT
public:
    StorageDisplay(QWidget *parent = 0);
    ~StorageDisplay();
    void setUsedValue(int value);
    void get_currentvalue(int value);
    void move_place(int,int);
    //void setSize(int width, int height);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QPoint beginDrag;
    bool bPressFlag;

    QPixmap backGround;
    int userdVaule;
    int currentValue;
    QLabel *startValueLabel;
    QLabel *endValueLabel;
    QLabel *dispayValueLabel;
    QLabel *CurrentValueLabel;
    QLabel *PlaneValueLabel;
};

#endif // WIDGET_H
