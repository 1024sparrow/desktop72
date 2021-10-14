#include "footer.h"
#include "comandlistener.h"
#include <QPainter>
#include <QFont>
#include <QProcess>
#include <QApplication>
#include <QDesktopWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QDateTime>
#include <QPushButton>//

const int Footer::MODE_COUNT = 5;
//const int Footer::MODE_COUNT = 1;//
const int Footer::POINT_SIZE = 4;
const int Footer::POINT_PADDING = 1;
const int Footer::H = Footer::POINT_SIZE * 3;
const int Footer::animDuration = 400;

Footer::Footer()
	//:QWidget(0, Qt::SplashScreen), m_cur('~'), m_mode(0), animationTimerId(0)
	:QWidget(), m_cur('~'), m_mode(0), animationTimerId(0)//
	,m_currentPix(0), m_childrenMode(false)
{
	//setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint); // boris debug commented

	m_comandListener = new ComandListener(this);
	//m_comandListener->moveToThread(&m_comandListenerThread);

	onSwitched('Q');
	animationTimerId = startTimer(animDuration);

	connect(m_comandListener, SIGNAL(sgnSwitch(char)), this, SLOT(onSwitched(char)));
	connect(m_comandListener, SIGNAL(sgnSwitchModeUp()), this, SLOT(onModeSwicthedUp()));
	connect(m_comandListener, SIGNAL(sgnSwitchModeDown()), this, SLOT(onModeSwicthedDown()));
	connect(m_comandListener, SIGNAL(sgnInitialize()), this, SLOT(initialize()));
	m_comandListener->start();

	QBoxLayout *lay = new QHBoxLayout(this);
	lay->setMargin(0);
	lay->addStretch();
	_timeLabel = new QLabel();
	_timeLabel->setStyleSheet("color:yellow");
	lay->addWidget(_timeLabel);
}

void Footer::onSwitched(char id)
{
	int num = desktopNum(id, m_mode);
//	qDebug() << "switch to desktop number: " << num;
	exec(QString("wmctrl -s %1").arg(num));

	/*if (!usingDesktops.contains(num))
	{
		process->start(QString("gnome-terminal"));
		process->waitForFinished();
	}*/

	m_currentPix = 0;
	m_cur = id;
	updatePixmaps();
	if (isVisible())
		repaint();
}

void Footer::onModeSwicthedUp()
{
	m_mode = (m_mode + 1) % MODE_COUNT;

	exec(QString("wmctrl -s %1").arg(desktopNum(m_cur, m_mode)));

	m_currentPix = 2;
	updatePixmaps();
	if (isVisible())
		repaint();
}

void Footer::onModeSwicthedDown()
{
	m_mode = (m_mode + MODE_COUNT - 1) % MODE_COUNT;

	exec(QString("wmctrl -s %1").arg(desktopNum(m_cur, m_mode)));

	m_currentPix = 2;
	updatePixmaps();
	if (isVisible())
		repaint();
}

void Footer::initialize()
{
	exec(QString("wmctrl -n %1").arg(26 * MODE_COUNT));
}

void Footer::toggleChilrenMode()
{
	//
}

void Footer::paintEvent(QPaintEvent *pe)
{
	QPainter painter(this);
	painter.fillRect(rect(), QColor(0,0,0));
	painter.drawPixmap(0, 0, m_pix[m_currentPix]);

	QWidget::paintEvent(pe);

	/*QPainter p(this);
	QFont font;
	font.setPixelSize(H - 2);   , bg
	p.setFont(font);
	p.fillRect(this->rect(), Qt::yellow);
	p.drawText(rect(), QString(m_cur));*/
}

void Footer::timerEvent(QTimerEvent *te)
{
	// boris debug commented
//	QSize SZ = QApplication::desktop()->availableGeometry().size();
//	setFixedSize(SZ.width(), Footer::H + 1);
//	//resize(SZ.width(), Footer::H + 1);
//	move(QPoint(0, QApplication::desktop()->screenGeometry().height() - Footer::H));

	m_currentPix = ++m_currentPix % 4;
	if (isVisible())
		repaint();
	//if (m_currentPix == 3)
	//    updatePixmaps();

	_timeLabel->setText(QDateTime::currentDateTime().toString());
}

void Footer::exec(const QString &cmd)
{
//	QProcess *process = new QProcess(this);
//	process->start(cmd);
//	process->waitForFinished();
}
