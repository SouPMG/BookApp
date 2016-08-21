#ifndef EDITITEMWINDOW_H
#define EDITITEMWINDOW_H

#include <QDialog>

namespace Ui {
    class EditItemWindow;
}

class EditItemWindow : public QDialog {
    Q_OBJECT

    private:
        Ui::EditItemWindow *ui;

    public:
        explicit EditItemWindow(QWidget *parent = 0);
        ~EditItemWindow();

};

#endif // EDITITEMWINDOW_H
