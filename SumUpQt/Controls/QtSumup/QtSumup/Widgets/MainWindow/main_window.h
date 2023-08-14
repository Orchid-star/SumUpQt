#pragma once
#include <qmainwindow.h>
#include <QResizeEvent>
#include <menu_bar.h>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
//height 48px
class CMainWindow : public QMainWindow
{
public:
	CMainWindow();

private:
	void init();
	QWidget* p_bar;

protected:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
};


class CHMenuBar : public QWidget
{
public:
	CHMenuBar() {
		create_layout();
		setStyleSheet("QWidget{background-color:rgba(255,0,0,100);}");
	}

	void create_layout() {
		QHBoxLayout* p_main_lay = new QHBoxLayout(this);
		QMenu* menu1 = new QMenu("File", this);
		QMenu* menu2 = new QMenu("File", this);
		QMenu* menu3 = new QMenu("File", this);

		menu1->setStyleSheet("QWidget{background-color:rgba(0,255,0,100);}");

		p_main_lay->addWidget(menu1);
		p_main_lay->addWidget(menu2);
		p_main_lay->addWidget(menu3);
	}
};

