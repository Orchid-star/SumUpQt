#pragma once
#include <qwidget.h>

class QLineEdit;
class QToolButton;
class QHBoxLayout;

class CHSearchEdit : public QWidget
{
public:
	CHSearchEdit(QWidget *parent = nullptr);
	~CHSearchEdit();

private:
	void init_param();
	void init_interface();
	void bind_event();
	void create_layout();
	
	QLineEdit* m_p_edit;
	QToolButton* m_p_icon;
};

