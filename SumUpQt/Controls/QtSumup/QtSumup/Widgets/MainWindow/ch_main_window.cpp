#include "stdafx.h"
#include "ch_main_window.h"
#include "ch_menubar_decorator.h"
#include "ch_global_define.h"
#include <QMargins>
#include <QSize>
#include <QFile>
#include <qapplication.h>
#include <QPainter>
#include <qmath.h>
#include <QScreen>
#include <QTextCodec>
#include <QPlainTextEdit>
#include <QDockWidget>
#include <QPushButton>
#include <QEvent>


#define MAIN_SIZE QSize(1000, 600)
#define BORDER_WIDTH 3
#define BORDER_DRAW_WIDTH 5
#define BORDER_COLOR QColor(113, 96, 232, 0)

CHMainWindow::CHMainWindow(QWidget* parent)
	:QMainWindow(parent)
    , m_adjust_flag(false)
    , m_cursor_pos(QPoint(0, 0))
    , m_cursor_type(0)
{
	init();
	init_stylesheet();
}

CHMainWindow::~CHMainWindow()
{

}

void CHMainWindow::init()
{
	m_p_title_bar = new CHTitleBar(this);
    setMouseTracking(true);
	setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
	resize(MAIN_SIZE);
	setMenuWidget(m_p_title_bar);
	setObjectName("app_main");
}

void CHMainWindow::bind_events()
{
}

void CHMainWindow::init_interface()
{
	create_menu();
	QMetaObject::connectSlotsByName(this);
}

void CHMainWindow::init_stylesheet()
{
	QFile file(QCoreApplication::applicationDirPath() + "/stylesheet/style.css");
	if (file.open(QIODevice::ReadOnly)) {
		qApp->setStyleSheet(QString(file.readAll()));
		file.close();
	}
}

void CHMainWindow::create_menu()
{
	CHMenuBarDecorator menu_decorator(this);
	QMenuBar& menuBar = m_p_title_bar->menu_bar();
	QString config = CONFIG_DIR + QString("title_bar.xml");
	menu_decorator.decorate(&menuBar, config);
}

void CHMainWindow::on_file_exit_triggered()
{
	exit(0);
}

void CHMainWindow::on_file_update_style_triggered()
{
	init_stylesheet();
}

void CHMainWindow::paintEvent(QPaintEvent* event)
{
    QColor color = BORDER_COLOR;
    int border_wd = BORDER_DRAW_WIDTH;
    int w = width(), h = height();
    QPainter painter(this);
    QBrush bkg = palette().background();
    QRect rc = isMaximized() ? QRect(-1, -1, w + 1, h + 1) : QRect(border_wd, border_wd, w - border_wd*2, h - border_wd*2);

    if (!isMaximized()) {
		for (int i = 0; i < border_wd; ++i) {
			QVector<QLine> lines = {};
			lines.push_back(QLine(i, i, w - i, i));
			lines.push_back(QLine(i, i, i, h - i));
			lines.push_back(QLine(i, h - i, w - i, h - i));
			lines.push_back(QLine(w - i, i, w - i, h - i));
			color.setAlpha( i * 100 / border_wd);
			painter.setPen(color);
			painter.drawLines(lines);
		}
    }
    painter.setBrush(bkg);
    painter.drawRect(rc);
}

void CHMainWindow::moveEvent(QMoveEvent* event)
{

}

void CHMainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pt = event->pos();

    static QMap<int, Qt::CursorShape> shapes = {
        {CursorPos::NONE, Qt::ArrowCursor},
        {CursorPos::LEFT, Qt::SizeHorCursor},
        {CursorPos::RIGHT, Qt::SizeHorCursor},
        {CursorPos::TOP, Qt::SizeVerCursor},
        {CursorPos::BOTTOM, Qt::SizeVerCursor},
        {CursorPos::LEFT | CursorPos::TOP, Qt::SizeFDiagCursor},
        {CursorPos::RIGHT | CursorPos::BOTTOM, Qt::SizeFDiagCursor},
        {CursorPos::LEFT | CursorPos::BOTTOM, Qt::SizeBDiagCursor},
        {CursorPos::RIGHT | CursorPos::TOP, Qt::SizeBDiagCursor},
    };
    if (isMaximized()) return;
    if (!m_adjust_flag) {
        m_cursor_type = 0;
        if (pt.x() <= BORDER_WIDTH) {
            m_cursor_type |= CursorPos::LEFT;
        }
        if (pt.y() <= BORDER_WIDTH) {
            m_cursor_type |= CursorPos::TOP;
        }
        if (pt.x() >= width() - BORDER_WIDTH) {
            m_cursor_type |= CursorPos::RIGHT;
        }
        if (pt.y() >= height() - BORDER_WIDTH) {
            m_cursor_type |= CursorPos::BOTTOM;
        }
        if (shapes.contains(m_cursor_type)) {
            setCursor(shapes[m_cursor_type]);
        }
    }
    else {
        QRect geo = geometry();
        int x1, y1, x2, y2;
        x1 = geo.x();
        y1 = geo.y();
        x2 = x1 + geo.width();
        y2 = y1 + geo.height();
        if (m_cursor_type & CursorPos::TOP) {
            y1 -= (y1 - cursor().pos().y());
        }
        if (m_cursor_type & CursorPos::BOTTOM) {
            y2 -= (y2 - cursor().pos().y());
        }
        if (m_cursor_type & CursorPos::LEFT) {
            x1 -= (x1 - cursor().pos().x());
        }
        if (m_cursor_type & CursorPos::RIGHT) {
            x2 -= (x2 - cursor().pos().x());
        }
        setGeometry(x1, y1, qAbs(x2 - x1), qAbs(y2 - y1));
    }
}

void CHMainWindow::mousePressEvent(QMouseEvent* event)
{
    if (m_cursor_type != 0) {
        m_adjust_flag = true;
        m_cursor_pos = event->pos();
    }
}

void CHMainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    m_adjust_flag = false;
}

void CHMainWindow::changeEvent(QEvent* event)
{
	emit window_state_changed(event->type());
}
