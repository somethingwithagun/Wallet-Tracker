#include "displaywindow.h"

DisplayWindow::DisplayWindow(const QString dataToDisplay,QWidget* parent)
{
    this->setMinimumSize(465, 646);
    field = new QTextEdit;
    layout = new QVBoxLayout;
    cancel_button = new QPushButton("Cancel");

    QFont h2;
    h2.setPointSize(15);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    field->setSizePolicy(sizePolicy);
    field->setReadOnly(true);
    field->setFont(h2);

    // fill the field with information
    if(dataToDisplay != "")
        field->setText(dataToDisplay);
    else
        field->setText("Nothing to show yet...");
        
    cancel_button->setMinimumSize(QSize(0, 60));
    cancel_button->setFont(h2);

    layout->addWidget(field);
    layout->addWidget(cancel_button);
    this->setLayout(layout);

    QObject::connect(cancel_button, &QPushButton::clicked, this, &DisplayWindow::close);
}
DisplayWindow::~DisplayWindow()
{
    delete cancel_button;
    delete field;
    delete layout;
}