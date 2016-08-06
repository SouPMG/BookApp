#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddItemWindow) {
	ui->setupUi(this);

	// Setup window
	setWindowTitle("Add a new item to your library");
	setModal(true);
	QDialog::reject(); // Esc closes the window

	setupAddItemForm();
}

AddItemWindow::~AddItemWindow() {
	delete ui;
}

void AddItemWindow::setupAddItemForm() {
	// Create labels and text widgets
	QLabel *isbnLabel = new QLabel("ISBN: ", this);
	QLineEdit *isbnTextField = new QLineEdit(this);

	QLabel *titleLabel = new QLabel("Name: ", this);
	QLineEdit *titleTextField = new QLineEdit(this);

	// Create form layout for form members
	QFormLayout *addItemForm = new QFormLayout();
	addItemForm->addRow(isbnLabel, isbnTextField);
	addItemForm->addRow(titleLabel, titleTextField);

	// Create Ok Cancel buttons
	QPushButton *buttonOk = new QPushButton("Ok");
	QPushButton *buttonCancel = new QPushButton("Cancel");

	// Create DialogButtonBox with previously declared buttons
	QDialogButtonBox *formResponse = new QDialogButtonBox(Qt::Horizontal, this);
	formResponse->addButton(buttonOk, QDialogButtonBox::ActionRole);
	formResponse->addButton(buttonCancel, QDialogButtonBox::ActionRole);

	// Create vertical layout for the base dialog
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(addItemForm);
	mainLayout->addWidget(formResponse);

	setLayout(mainLayout);
}
