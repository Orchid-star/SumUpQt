#include "stdafx.h"
#include "menu_bar.h"
#include <QHBoxLayout>

CMenuBar::CMenuBar()
{
	init();
}

void CMenuBar::init()
{
	QWidget* widget = new QWidget;
	QHBoxLayout* p_lay = new QHBoxLayout(this);
	p_lay->setContentsMargins(0, 0, 110, 0);
	p_lay->addWidget(widget);
	widget->setFixedHeight(48);
	widget->setStyleSheet("QWidget{background-color:#f0f;}");
}


