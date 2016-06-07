/*#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
*/

#include <iostream>
#include <string>

#include "book.h"

using namespace std;

int main(int argc, char *argv[]) {
	book *myBook = new book ("ISBN");
	cout << myBook->getIsbn() << endl;
}
