#include "readingtimerwindow.h"
#include "ui_readingtimerwindow.h"

ReadingTimerWindow::ReadingTimerWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ReadingTimerWindow) {
	ui->setupUi(this);

	setModal(true);
	resize(500, 200);

	counter = new QLCDNumber(this);
	QPushButton *startButton = new QPushButton("Start");
	QPushButton *pauseButton = new QPushButton("Pause");
	QPushButton *stopButton = new QPushButton("Stop");

	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	buttonsLayout->addWidget(startButton);
	buttonsLayout->addWidget(pauseButton);
	buttonsLayout->addWidget(stopButton);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(counter);
	mainLayout->addLayout(buttonsLayout);

	setLayout(mainLayout);

	connect(startButton, SIGNAL(clicked()), this, SLOT(startCounting()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseCounting()));
	connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopCounting()));
}

ReadingTimerWindow::~ReadingTimerWindow() {
	delete ui;
}

void ReadingTimerWindow::startCounting() {
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateCounter()));
	timer->start(1000);
}

void ReadingTimerWindow::pauseCounting() {

}

void ReadingTimerWindow::stopCounting() {
	emit quitSession(0);
	close();
}

void ReadingTimerWindow::updateCounter() {
	//counter->s
}
