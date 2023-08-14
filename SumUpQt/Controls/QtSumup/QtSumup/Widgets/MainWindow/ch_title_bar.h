#pragma once
#include <qwidget.h>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QEvent>

class CHSearchEdit;

class CHTitleBar : public QWidget
{
	friend class CHMainWindow;
public:
	CHTitleBar(QWidget* parent);
	QMenuBar& menu_bar() { return m_menubar; };
	void add_widget(int index, QWidget* wg);

private:
	QToolButton m_icon;
	QMenuBar m_menubar;
	QToolButton m_min;
	QToolButton m_max;
	QToolButton m_close;
	QHBoxLayout m_main_hlay;
	CHMainWindow* m_p_mainwindow;

	void init();
	void bind_events();
	void update_size();
	void update_icons(QEvent::Type type);
	void update_layout(QEvent::Type type);

private:
	bool m_left_btn_pressed;
	QPoint m_pt_start;
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};

