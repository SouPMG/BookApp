#include "readingtimerwindow.h"
#include "ui_readingtimerwindow.h"

ReadingTimerWindow::ReadingTimerWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ReadingTimerWindow) {
	ui->setupUi(this);

	setWindowTitle("Reading timer");
	resize(500, 200);
	setModal(true);

	counter = new QLCDNumber(this);
	timer = new QTimer(this);

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

	connect(timer, SIGNAL(timeout()), this, SLOT(updateCounter()));

	connect(startButton, SIGNAL(clicked()), this, SLOT(startCounting()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseCounting()));
	connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopCounting()));
}

ReadingTimerWindow::~ReadingTimerWindow() {
	delete ui;
}

void ReadingTimerWindow::startCounting() {
	timer->start(1000);
}

void ReadingTimerWindow::pauseCounting() {
	timer->stop();
}

void ReadingTimerWindow::stopCounting() {
	emit quitSession(counter->intValue());
	close();
}

void ReadingTimerWindow::updateCounter() {
	counter->display(QString::number(counter->intValue() + 1));
}
