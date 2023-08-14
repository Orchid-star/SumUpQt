#include "stdafx.h"
#include "ch_menubar_decorator.h"
#include "ch_global_define.h"
#include <QMenuBar>
#include <QMenu>
#include <QApplication>
#include <QFile>
#include <QWidget>

CHMenuBarDecorator::CHMenuBarDecorator(QWidget* wg)
	:m_p_menu_parent(wg)
{
}

void CHMenuBarDecorator::decorate(QMenuBar* menubar, QString config)
{
	CH_NULLPTR_RETURN(menubar)
	QDomDocument doc;
	QDomElement root;
	QDomNodeList node_list;
	QDomElement ele;
	QFile file(config);
	if (file.open(QIODevice::ReadOnly)) {
		doc.setContent(&file);
		root = doc.documentElement();
		node_list = root.childNodes();
		for (int i = 0; i < node_list.size(); ++i) {
			if (node_list.at(i).isElement()) {
				ele = node_list.at(i).toElement();
				menubar->addMenu(create_menu(ele));
			}
		}
		file.close();
	}
}

QMenu* CHMenuBarDecorator::create_menu(const QDomElement& ele)
{
	QMenu* menu = new QMenu(ele.attribute("text"));
	QDomNodeList node_list = ele.childNodes();
	QDomElement e;

	for (int i = 0; i < node_list.size(); ++i) {
		if (node_list.at(i).isElement()) {
			e = node_list.at(i).toElement();
			if (e.tagName() == QString("QMenu")) {
				menu->addMenu(create_menu(e));
			} else if (e.tagName() == QString("QAction")) {
				QAction* ac = new QAction(e.attribute("text"), m_p_menu_parent);
				ac->setIcon(QIcon(SOURCE_DIR + e.attribute("icon")));
				ac->setObjectName(e.attribute("obj"));
				ac->setShortcut(QKeySequence(e.attribute("shortcut")));
				menu->addAction(ac);
			} else if (e.tagName() == QString("QSeprator")) {
				menu->addSeparator();
			}
		}
	}
	return menu;
}
