#include "snipertool.h"
using namespace std;

//#define NormalTest
#define SerialPortTest

OutSideCommModule *SS3 = new OutSideCommModule;
ThreadWatchDogModule *SS4 = new ThreadWatchDogModule;
RetransModule *SS5 = new RetransModule;

SniperTool::SniperTool(QWidget *parent)
	: QWidget(parent)
{
	createView();
}

SniperTool::~SniperTool()
{

}

void SniperTool::createView()
{
	/*UI½çÃæ*/
	mainLayout = new QVBoxLayout(this);
	QPushButton *btn1 = new QPushButton(tr("Btn1"));
	QPushButton *btn2 = new QPushButton(tr("Btn2"));
	QPushButton *btn3 = new QPushButton(tr("Btn3"));
	QPushButton *btn4 = new QPushButton(tr("Btn4"));
	QPushButton *btn5 = new QPushButton(tr("Btn5"));
	QPushButton *btn6 = new QPushButton(tr("Btn6"));
	QPushButton *btn7 = new QPushButton(tr("Btn7"));
	QPushButton *btn8 = new QPushButton(tr("Btn8"));
	mainLayout->addWidget(btn1);
	mainLayout->addWidget(btn2);
	mainLayout->addWidget(btn3);
	mainLayout->addWidget(btn4);
	mainLayout->addWidget(btn5);
	mainLayout->addWidget(btn6);
	mainLayout->addWidget(btn7);
	mainLayout->addWidget(btn8);
	mainLayout->addStretch();
	connect(btn1, SIGNAL(clicked(bool)), this, SLOT(ClickButton1()));
	connect(btn2, SIGNAL(clicked(bool)), this, SLOT(ClickButton2()));
	connect(btn3, SIGNAL(clicked(bool)), this, SLOT(ClickButton3()));
	connect(btn4, SIGNAL(clicked(bool)), this, SLOT(ClickButton4()));
	connect(btn5, SIGNAL(clicked(bool)), this, SLOT(ClickButton5()));
	connect(btn6, SIGNAL(clicked(bool)), this, SLOT(ClickButton6()));
	connect(btn7, SIGNAL(clicked(bool)), this, SLOT(ClickButton7()));
	connect(btn8, SIGNAL(clicked(bool)), this, SLOT(ClickButton8()));
}

#ifdef NormalTest

void SniperTool::ClickButton1()
{
	qDebug() << "Click1";
}

void SniperTool::ClickButton2()
{
	qDebug() << "Click2";
}

void SniperTool::ClickButton3()
{
	qDebug() << "Click3";
}

void SniperTool::ClickButton4()
{
	qDebug() << "Click4";
}

void SniperTool::ClickButton5()
{
	qDebug() << "Click5";
}

void SniperTool::ClickButton6()
{
	qDebug() << "Click6";
}

void SniperTool::ClickButton7()
{
	qDebug() << "Click7";
}

void SniperTool::ClickButton8()
{
	qDebug() << "Click8";
}
#endif

#ifdef SerialPortTest

void SniperTool::ClickButton1()
{
	//qDebug() << "Click1";
	//qDebug() << SS3->InitPort();
}

void SniperTool::ClickButton2()
{
	//qDebug() << "Click2";
	//qDebug() << SS3->OpenRecThread();
}

void SniperTool::ClickButton3()
{
	//qDebug() << "Click3";
	//qDebug() << SS3->CloseRecThread();
}

void SniperTool::ClickButton4()
{
	//qDebug() << "Click4";
	//qDebug() << SS3->OpenSendThread();
}

void SniperTool::ClickButton5()
{
	//qDebug() << "Click5";
	//qDebug() << SS3->CloseSendThread();
}

void SniperTool::ClickButton6()
{
	//qDebug() << "Click6";
	//uchar data[3] = { 0x01,0x02,0x0A };
	//qDebug() << SS3->WriteData(data,3);
}

void SniperTool::ClickButton7()
{
	//qDebug() << "Click7";
	qDebug() << SS3->InitOSCM();
	qDebug() << SS3->OpenSerialPort();
	qDebug() << SS5->InitRTM();
	qDebug() << SS4->InitTWDM();
}

void SniperTool::ClickButton8()
{
	//qDebug() << "Click8";
	qDebug() << SS4->EndTWDM();
	qDebug() << SS3->EndOSCM();
	qDebug() << SS3->CloseSerialPort();
	qDebug() << SS5->EndRTM();
}
#endif