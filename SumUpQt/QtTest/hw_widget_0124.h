/*
œﬂ≥Ã–≈∫≈≤‚ ‘
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CHwMainWindow0124 w;
	w.show();
	return a.exec();
}
*/
#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <QPlainTextEdit>
#include <QThread>
#include <QMainWindow>

class CHwDataHanlde0124 : public QObject
{
	Q_OBJECT
public:
	CHwDataHanlde0124();
	void set_data(QString data);

signals:
	void sig_data(QString);
};

class CHwWidget0124 : public QWidget
{
	Q_OBJECT
public:
	CHwWidget0124(QWidget* parent = nullptr);
	void update_text(QString line);

private:
	QPushButton m_btn_start;
	QPushButton m_btn_flag;
	QPlainTextEdit m_plain_text;
	QString m_text;
	bool m_break_flag;
	void on_start();
	void on_flag();
	void create_line();
	void create_layout();

signals:
	void fresh_string(QString);
};

class CHwMainWindow0124 : public QMainWindow
{
	Q_OBJECT
public:
	CHwMainWindow0124();
private:
	CHwDataHanlde0124 m_data_handle;
	QThread m_data_thread;
	CHwWidget0124 m_main_widget;
};

