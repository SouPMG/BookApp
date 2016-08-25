#ifndef READINGTIMERWINDOW_H
#define READINGTIMERWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>

namespace Ui {
	class ReadingTimerWindow;
}

class ReadingTimerWindow : public QDialog {
		Q_OBJECT

	private:
		Ui::ReadingTimerWindow *ui;

		QLCDNumber *counter;

	public:
		explicit ReadingTimerWindow(QWidget *parent = 0);
		~ReadingTimerWindow();

	signals:
		void quitSession(int);

	private slots:
		void startCounting();
		void pauseCounting();
		void stopCounting();

		void updateCounter();

};

#endif // READINGTIMERWINDOW_H
