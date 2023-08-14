#include "stdafx.h"
#include "main_window.h"
#include <QLabel>
#include <QDockWidget>
#include <QPainter>
#include <qmath.h>
#include <QMenuBar>
#include <QLineEdit>
#include <QSizePolicy>
#include <QLayout>

#define MAIN_SIZE QSize(800, 600)
#define BORDER_WIDTH (7)

CMainWindow::CMainWindow()
{
	init();
}

void CMainWindow::init()
{
	//setWindowFlag(Qt::FramelessWindowHint);
	resize(MAIN_SIZE);
	QLabel* p_label = new QLabel;
	p_label->setStyleSheet("QWidget{background:#0f0;}");
	p_label->setFixedSize(MAIN_SIZE);
	setCentralWidget(p_label);
	setStyleSheet("QWidget{background:#f00;}");

	QLabel* pp = new QLabel;
	pp->setStyleSheet("QWidget{background:#ff0;}");
	QDockWidget* p_dock = new QDockWidget;
	p_dock->setWidget(pp);

	QLineEdit* p_edit = new QLineEdit;

	p_bar = new CMenuBar;
	//p_bar->setFixedWidth(500);
	//p_bar->addAction("file");
	p_bar->setStyleSheet("QWidget{background-color:transparent;}");
	//setMenuBar(p_bar);
	setMenuWidget(p_bar);

	addDockWidget(Qt::LeftDockWidgetArea, p_dock);


	setContentsMargins(30, 30, 80, 30);
	layout()->setContentsMargins(30, 30, 80, 30);
	//layout()->setMargin(50);
}

void CMainWindow::paintEvent(QPaintEvent* event)
{
	int wd = width();
	int ht = height();
	QColor color(241, 72, 76, 10);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);

	for (int i = 0; i < BORDER_WIDTH; i++) {
		QRect rc1(i, i, wd - 1 - i * 2, ht - 1 - i * 2);
		color.setAlpha(qSqrt(i) * 10);
		painter.setBrush(color);
		painter.drawRect(rc1);
	}


	//QRect rc2(BORDER_WIDTH, BORDER_WIDTH, wd - BORDER_WIDTH * 2 - 1, ht - BORDER_WIDTH * 2 - 1);
	//painter.setBrush(QColor(255, 255, 255, 255));
	//painter.drawRect(rc2);
}

void CMainWindow::resizeEvent(QResizeEvent* event)
{
	//p_bar->setGeometry(30, 30, event->size().width() - 90, 48);
	//p_bar->setMaximumWidth(event->size().width() - 90);
}
