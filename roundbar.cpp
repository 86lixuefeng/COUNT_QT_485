#include "roundbar.h"

StorageDisplay::StorageDisplay(QWidget *parent)
{
    setParent(parent);
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);

    setAutoFillBackground(false);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0xFF,0xFF,0xFF,0xFF));
    setPalette(pal);

    startValueLabel = new QLabel(tr("0%"), parent);
    startValueLabel->setFont(QFont("Arial", 11, QFont::Normal));
    startValueLabel->setStyleSheet("color:#898989");

    endValueLabel = new QLabel(tr("100%"),parent);
    endValueLabel->setFont(QFont("Arial", 11, QFont::Normal));
    endValueLabel->setStyleSheet("color:#898989");

    dispayValueLabel = new QLabel(parent);
    dispayValueLabel->setStyleSheet("color:#349BDA");

    CurrentValueLabel = new QLabel(parent);
    CurrentValueLabel->setStyleSheet("color:#349BDA");
    PlaneValueLabel = new QLabel(parent);
    PlaneValueLabel->setStyleSheet("color:#349BDA");

}

StorageDisplay::~StorageDisplay()
{
    currentValue = 0;
}

void StorageDisplay::setUsedValue(int value)
{
    userdVaule = value;
}

void StorageDisplay::get_currentvalue(int value)
{
    currentValue = value;
}

void StorageDisplay::move_place(int x, int y)
{
    resize(x, y);
}

//void StorageDisplay::setSize(int width, int height)
//{
//    setSize(width,height);
//}

void StorageDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor usedColor(165, 220, 62);
    QColor freeColor(215, 215, 215);
    painter.drawPixmap(QRect(backGround.width(),backGround.height(), backGround.width(), backGround.height()) , backGround);

    painter.translate(width() / 2, height() / 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.save();
    painter.rotate(42);
    painter.setPen(QPen(usedColor, 2));
    double tmp = (double)currentValue/userdVaule;
    for (int i = 0; i < (int) (tmp*100) ; ++i) {
        painter.drawLine(0, 70, 0, 90);
        painter.rotate(2.8);
    }
    painter.setPen(QPen(freeColor, 3));
    for (int i = (int) (tmp*100); i < 100 ; ++i) {
        painter.drawLine(0, 70, 0, 80);
        painter.rotate(2.8);
    }
        dispayValueLabel->setFont(QFont("Arial", 15, QFont::Bold));
        dispayValueLabel->setText(tr("%1%").arg(int(tmp*100)));
        CurrentValueLabel->setFont(QFont("Arial", 18, QFont::Bold));
        CurrentValueLabel->setText(tr("实时产量:%1").arg(currentValue));
        PlaneValueLabel->setFont(QFont("Arial", 18, QFont::Bold));
        PlaneValueLabel->setText(tr("计划产量:%1").arg(userdVaule));

    QFontMetrics metrics(dispayValueLabel->font());
    int textwidth = metrics.width(dispayValueLabel->text());
    int textheight = metrics.height();
    dispayValueLabel->setGeometry((width() - textwidth)/2, (height() - textheight)/2 , textwidth, textheight);
    CurrentValueLabel->setGeometry((width() - textwidth)/2-50, (height() - textheight)/2 , textwidth+190, textheight+199);
    PlaneValueLabel->setGeometry((width() - textwidth)/2-50, (height() - textheight)/2 +30, textwidth+190, textheight+199);
    startValueLabel->setGeometry((width() - textwidth)/2-35, (height() - textheight)/2+60 , textwidth+25, textheight+20);
    endValueLabel->setGeometry((width() - textwidth)/2+35, (height() - textheight)/2+60 , textwidth+50, textheight+20);
    painter.restore();
//    startValueLabel->setGeometry(35, 140, 25, 20);
//    endValueLabel->setGeometry(97, 140, 50, 20);

    painter.translate(-width()/2, -height()/2);
    painter.setBrush(QColor(233, 233, 233));
    painter.setPen(QPen(QColor(233, 233, 233), 15));
    painter.drawEllipse(QRectF((width()/2 - 55), (height()/2 - 55), 110, 110));

    QConicalGradient conicalGradient(width()/2, height()/2, 90);
    conicalGradient.setColorAt(0, QColor(45, 204, 112));
    conicalGradient.setColorAt(1.0, QColor(51, 152, 219));
    painter.setPen(QPen(QBrush(conicalGradient), 30));
    painter.drawEllipse(QRectF((width()/2 - 35), (height()/2 - 35), 70, 70));

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(249, 249, 249));
    painter.drawEllipse(QRectF((width()/2 - 30), (height()/2 - 30), 60, 60));
}
