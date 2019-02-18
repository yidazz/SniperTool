#pragma once
#ifndef SNIPERTOOL_H
#define SNIPERTOOL_H

#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "S_SerialPort.h"  
#include "S_OutSideComm.h"
#include "S_ThreadWatchDog.h"
#include "S_Retrans.h"

class SniperTool : public QWidget
{
	Q_OBJECT

public:
	SniperTool(QWidget *parent = 0);
	~SniperTool();

	void createView();

	public slots:
	void ClickButton1();
	void ClickButton2();
	void ClickButton3();
	void ClickButton4();
	void ClickButton5();
	void ClickButton6();
	void ClickButton7();
	void ClickButton8();

private:
	QVBoxLayout *mainLayout;
};

#endif // SNIPERTOOL_H
