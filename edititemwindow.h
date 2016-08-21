#ifndef EDITITEMWINDOW_H
#define EDITITEMWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include "libraryitem.h"

namespace Ui {
    class EditItemWindow;
}

class EditItemWindow : public QDialog {
    Q_OBJECT

    private:
        Ui::EditItemWindow *ui;

        void setUpEditForm(LibraryItem*);

    public:
        explicit EditItemWindow(LibraryItem *item, QWidget *parent = 0);
        ~EditItemWindow();

};

#endif // EDITITEMWINDOW_H
