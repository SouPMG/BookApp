#include "edititemwindow.h"
#include "ui_edititemwindow.h"

EditItemWindow::EditItemWindow(QWidget *parent) : QDialog(parent), ui(new Ui::EditItemWindow) {
    ui->setupUi(this);
}

EditItemWindow::~EditItemWindow() {
    delete ui;
}
