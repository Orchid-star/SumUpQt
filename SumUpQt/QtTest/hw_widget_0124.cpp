#include "hw_widget_0124.h"
#include <QtConcurrent/qtconcurrentrun.h>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>


void time_sleep() {
	for (int i = 0; i < 1000; ++i) {
		for (int j = 0; j < 1000; ++j) {
			for (int k = 0; k < 1000; ++k) {
			}
		}
	}
}

CHwWidget0124::CHwWidget0124(QWidget* parent)
	: QWidget(parent)
	, m_text("")
	, m_break_flag(false)
{

	create_layout();
}

void CHwWidget0124::update_text(QString line)
{
	m_text += (line + "\n");
	m_plain_text.setPlainText(m_text);
}

void CHwWidget0124::on_start()
{
	QtConcurrent::run(this, &CHwWidget0124::create_line);
}

void CHwWidget0124::on_flag()
{
	m_break_flag = !m_break_flag;
	qDebug() << QThread::currentThreadId();
}

void CHwWidget0124::create_line()
{
	qDebug() << QThread::currentThreadId();
	while (true)
	{
		time_sleep();
		if (m_break_flag) return;
		QString time = QTime::currentTime().toString("hh:mm:ss.zzz");
		emit fresh_string(time);
	}
}

void CHwWidget0124::create_layout()
{
	QVBoxLayout* lay_main = new QVBoxLayout(this);
	QHBoxLayout* lay = new QHBoxLayout();
	lay->addWidget(&m_btn_flag);
	lay->addWidget(&m_btn_start);
	m_btn_flag.setText("Flag");
	m_btn_start.setText("Start");
	lay_main->addLayout(lay);
	lay_main->addWidget(&m_plain_text);

	connect(&m_btn_flag, &QPushButton::clicked, this, &CHwWidget0124::on_flag);
	connect(&m_btn_start, &QPushButton::clicked, this, &CHwWidget0124::on_start);
	//connect(this, &CHwWidget0124::fresh_string, this, &CHwWidget0124::update_text);
}

CHwDataHanlde0124::CHwDataHanlde0124()
{
}

void CHwDataHanlde0124::set_data(QString data)
{
	emit sig_data(QString("CHwDataHanlde0124:") + data);
}

CHwMainWindow0124::CHwMainWindow0124()
{
	setCentralWidget(&m_main_widget);
	m_data_handle.moveToThread(&m_data_thread);
	//m_data_handle.deleteLater();
	connect(&m_data_handle, &CHwDataHanlde0124::sig_data, &m_main_widget, &CHwWidget0124::update_text);
	connect(&m_main_widget, &CHwWidget0124::fresh_string, &m_data_handle, &CHwDataHanlde0124::set_data);
	m_data_thread.start();
}
