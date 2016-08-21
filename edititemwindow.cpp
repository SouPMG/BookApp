#include "edititemwindow.h"
#include "ui_edititemwindow.h"

EditItemWindow::EditItemWindow(LibraryItem *item, QWidget *parent) : QDialog(parent), ui(new Ui::EditItemWindow) {
    ui->setupUi(this);
    setModal(true);

    setUpEditForm(item);
}

EditItemWindow::~EditItemWindow() {
    delete ui;
}

void EditItemWindow::setUpEditForm(LibraryItem *item) {
    QLineEdit *isbnEditData = new QLineEdit(item->getIsbn());

    QFormLayout *editFormLayout = new QFormLayout();
    editFormLayout->addRow("ISBN:", isbnEditData);

    setLayout(editFormLayout);
}
