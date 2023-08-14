#pragma once
#include <QString>
#include <QDomDocument>

class QMenuBar;
class QMenu;
class QWidget;

class CHMenuBarDecorator
{
public:
	CHMenuBarDecorator(QWidget *wg);
	void decorate(QMenuBar *menubar, QString config);

private:
	QMenu* create_menu(const QDomElement& ele);
	QWidget* m_p_menu_parent;
};

