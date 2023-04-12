#include "displaywindow.h"

DisplayWindow::DisplayWindow(const QString dataToDisplay,QWidget* parent)
{
    this->setMinimumSize(465, 646);
    field = new QTextEdit;
    layout = new QVBoxLayout;
    
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    field->setSizePolicy(sizePolicy);
    field->setReadOnly(true);

    // fill the field with information
    field->setText(dataToDisplay);

    layout->addWidget(field);
    this->setLayout(layout);
}
DisplayWindow::~DisplayWindow()
{
    delete field;
    delete layout;
}