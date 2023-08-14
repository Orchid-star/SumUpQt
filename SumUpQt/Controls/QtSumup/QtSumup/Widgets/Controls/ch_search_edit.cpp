#include "stdafx.h"
#include "ch_search_edit.h"
#include "qlineedit.h"
#include "qtoolbutton.h"
#include "qboxlayout.h"
#include "ch_global_define.h"

CHSearchEdit::CHSearchEdit(QWidget* parent)
{
	init_param();
	init_interface();
	bind_event();
}

CHSearchEdit::~CHSearchEdit()
{

}

void CHSearchEdit::init_param()
{
}

void CHSearchEdit::init_interface()
{
	create_layout();
}

void CHSearchEdit::bind_event()
{
}

void CHSearchEdit::create_layout()
{
	QHBoxLayout* p_main_lay = new QHBoxLayout(this);

	p_main_lay->setContentsMargins(5, 5, 0, 0);
	p_main_lay->setSpacing(0);
	m_p_edit = new QLineEdit;
	m_p_edit->setInputMask(QString("ËÑË÷(Ctrl+Q)"));
	m_p_edit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	m_p_icon = new QToolButton;
	m_p_icon->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	m_p_icon->setIcon(QIcon(SOURCE_DIR + "icons/window_search.svg"));
	p_main_lay->addWidget(m_p_edit);
	p_main_lay->addWidget(m_p_icon);
	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}
