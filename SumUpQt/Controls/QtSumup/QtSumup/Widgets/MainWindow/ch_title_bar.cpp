#include "stdafx.h"
#include "ch_global_define.h"
#include "ch_title_bar.h"
#include <QApplication>
#include <QMouseEvent>
#include <QWindow>
#include "ch_main_window.h"
#include "ch_search_edit.h"

#define MAIN_MARGIN1 QMargins(0, 0, 0, 0)
#define MAIN_MARGIN2 QMargins(5, 5, 5, 5)
#define TITLE_BAR_MARGIN1 QMargins(10, 0, 10, 0)
#define TITLE_BAR_MARGIN2 QMargins(10, 3, 10, 5)

CHTitleBar::CHTitleBar(QWidget* parent)
	: QWidget(parent)
	, m_left_btn_pressed(false)
	, m_p_mainwindow(qobject_cast<CHMainWindow *>(parent))
{
	init();
	bind_events();
}

void CHTitleBar::add_widget(int index, QWidget* wg)
{
	if (wg != nullptr) {
		m_main_hlay.insertWidget(index, wg);
	}
}

void CHTitleBar::init()
{
	QVector<QWidget*> wgs = { &m_icon, &m_menubar, &m_min, &m_max, &m_close };
	QMap<QWidget*, QString> wgs_info = {
		{&m_icon, "tb_icon"},
		{&m_menubar, "tb_menubar"},
		{&m_min, "tb_min"},
		{&m_max, "tb_max"},
		{&m_close, "tb_close"},
	};
	for (auto iter = wgs.begin(); iter != wgs.end(); iter++) {
		m_main_hlay.addWidget(*iter);
		(*iter)->setObjectName(wgs_info[*iter]);
	}
	m_menubar.hide();
	m_icon.setIcon(QIcon(SOURCE_DIR + "icons/icon.svg"));
	m_min.setIcon(QIcon(SOURCE_DIR + "icons/window_min.svg"));
	m_max.setIcon(QIcon(SOURCE_DIR + "icons/window_restore.svg"));
	m_close.setIcon(QIcon(SOURCE_DIR + "icons/window_close.svg"));
	m_main_hlay.setSpacing(0);
	m_main_hlay.insertStretch(2);
	update_size();
	setLayout(&m_main_hlay);
	setObjectName("title_bar");
}

void CHTitleBar::bind_events()
{
	auto window_state_switch = [=]() ->void {
		m_p_mainwindow->isMaximized() ? m_p_mainwindow->showNormal() : m_p_mainwindow->showMaximized();
		/*if (m_p_mainwindow->isMaximized()) {
			m_p_mainwindow->showNormal();
		} else {
			m_p_mainwindow->showMaximized();
		}*/
	};
	connect(&m_close, &QToolButton::clicked, m_p_mainwindow, &CHMainWindow::close);
	connect(&m_max, &QToolButton::clicked, m_p_mainwindow, window_state_switch);
	connect(&m_min, &QToolButton::clicked, m_p_mainwindow, &CHMainWindow::showMinimized);
	connect(m_p_mainwindow, &CHMainWindow::window_state_changed, this, &CHTitleBar::update_layout);
}

void CHTitleBar::update_size()
{
	m_icon.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_min.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_max.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_close.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_menubar.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	m_main_hlay.setContentsMargins(10, 5, 5, 10);
}

void CHTitleBar::update_icons(QEvent::Type type)
{
	if (type == QEvent::WindowStateChange) {
		QString icon = m_p_mainwindow->isMaximized() ? QString("window_max.svg") \
			: QString("window_restore.svg");
		m_max.setIcon(QIcon(SOURCE_DIR + QString("icons/%1").arg(icon)));
	}
}

void CHTitleBar::update_layout(QEvent::Type type)
{
	QString icon;
	QMargins main_window, title_bar;
	if (QEvent::WindowStateChange == type) {
		if (m_p_mainwindow != nullptr) {
			if (m_p_mainwindow->isMaximized()) {
				icon = QString("window_max.svg");
				main_window = MAIN_MARGIN1;
				title_bar = TITLE_BAR_MARGIN1;
			} else {
				icon = QString("window_restore.svg");
				main_window = MAIN_MARGIN2;
				title_bar = TITLE_BAR_MARGIN2;
			}
			m_p_mainwindow->setContentsMargins(main_window);
		}
		m_max.setIcon(QIcon(SOURCE_DIR + QString("icons/%1").arg(icon)));
		m_main_hlay.setContentsMargins(title_bar);
	}
}

void CHTitleBar::mouseMoveEvent(QMouseEvent* event)
{
	QRect rect;
	int d_x = 0, d_y = 0;
	QWidget* wg = qobject_cast<QWidget*>(parent());

	if (wg != nullptr) {
		if (m_left_btn_pressed) {
			if (wg->isMaximized()) {
				rect = wg->normalGeometry();
				d_x = (event->globalX() - wg->geometry().x()) * rect.width() \
					/ wg->geometry().width();
				d_y = event->globalY();
				rect.moveTopLeft(event->globalPos() - QPoint(d_x, d_y));
				if (m_pt_start != event->globalPos()) {
					wg->showNormal();
					wg->setGeometry(rect);
				}
			}
			if (!wg->isMaximized()) {
				wg->move(wg->geometry().topLeft() + event->globalPos() - m_pt_start);
				m_pt_start = event->globalPos();
			}
		}
	}
}

void CHTitleBar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		m_left_btn_pressed = true;
		m_pt_start = event->globalPos();
	}
}

void CHTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	m_left_btn_pressed = false;
}

