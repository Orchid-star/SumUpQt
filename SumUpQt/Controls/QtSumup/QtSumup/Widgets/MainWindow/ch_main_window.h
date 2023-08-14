#pragma once
#include <qmainwindow.h>
#include "ch_title_bar.h"

class CHMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CHMainWindow(QWidget* parent = nullptr);
	~CHMainWindow();

private:
	void init();
	void bind_events();
	void init_interface();
	void init_stylesheet();

private:
	void create_menu();
	CHTitleBar *m_p_title_bar;
	enum CursorPos {
		NONE = 0x0000,
		LEFT = 0x0001,
		TOP = 0x0010,
		RIGHT = 0x0100,
		BOTTOM = 0x1000,
	};
	bool m_adjust_flag;
	QPoint m_cursor_pos;
	int m_cursor_type;

signals:
	void window_state_changed(QEvent::Type);

private slots:
	void on_file_exit_triggered(); 
	void on_file_update_style_triggered();

protected:
	void paintEvent(QPaintEvent* event);
	void moveEvent(QMoveEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void changeEvent(QEvent* event);
};

