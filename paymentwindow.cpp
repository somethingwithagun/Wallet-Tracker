#include "paymentwindow.h"

PaymentWindow::PaymentWindow(std::string date, std::string month,QWidget *parent)
    : QDialog{parent}
{
    this->setMinimumSize(465, 646);

    std::string previousDate = Filesystem::readFromFile(std::string(DATA_PATH) + DAY_CONF_PATH);
    std::string previousMonth = Filesystem::readFromFile(std::string(DATA_PATH) + MONTH_CONF_PATH);
    
    this->currentDate = date;
    this->currentMonth = month;

    if (previousDate != currentDate + '\n')
    {
        Filesystem::replaceInto(DATA_PATH, DAY_CONF_PATH, currentDate);
        if(previousDate != "")
            Filesystem::rm(DATA_PATH, previousDate.substr(0, previousDate.size() - 1) + ".txt"); // to avoid the '\n'
    }    
    if (previousMonth != currentMonth + '\n')
    {
        Filesystem::replaceInto(DATA_PATH, MONTH_CONF_PATH, currentMonth);
        if(previousMonth != "")
            Filesystem::rm(DATA_PATH, previousMonth.substr(0,previousMonth.size()-1)+".txt"); // to avoid the '\n'
    }

    spacer1 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
    spacer2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout = new QVBoxLayout;
    payment_label = new QLabel;
    paymentName_label = new QLabel;
    sum_label = new QLabel;
    paymentName_field = new QLineEdit;
    sum_field = new QLineEdit;
    submit_button = new QPushButton;
    cancel_button = new QPushButton;
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Text, Qt::black);

    QFont h1;
    QFont h2;
    h1.setPointSize(20);
    h2.setPointSize(15);

    payment_label->setText("Add new payment");
    payment_label->setFont(h1);
    payment_label->setAlignment(Qt::AlignHCenter);

    paymentName_label->setText("Enter payment name:");
    paymentName_label->setFont(h2);
    paymentName_label->setStyleSheet("QLabel{color:#000000;");

    paymentName_field->setMinimumSize(QSize(0, 40));
    paymentName_field->setPalette(darkPalette);

    sum_label->setText("Enter sum:");
    sum_label->setFont(h2);
    sum_label->setStyleSheet("QLabel{color:#000000;");

    sum_field->setValidator( new QIntValidator( 1, 99999, this ));
    sum_field->setMinimumSize(QSize(0, 40));
    sum_field->setPalette(darkPalette);

    submit_button->setText("Submit");
    submit_button->setMinimumSize(QSize(0, 60));
    submit_button->setFont(h2);
    cancel_button->setText("Cancel");
    cancel_button->setFont(h2);
    cancel_button->setMinimumSize(QSize(0, 60));


    verticalLayout->addItem(spacer1);
    verticalLayout->addWidget(payment_label);
    verticalLayout->addItem(spacer2);
    verticalLayout->addWidget(paymentName_label);
    verticalLayout->addWidget(paymentName_field);
    verticalLayout->addWidget(sum_label);
    verticalLayout->addWidget(sum_field);
    verticalLayout->addWidget(submit_button);
    verticalLayout->addWidget(cancel_button);

    this->setLayout(verticalLayout);

    QObject::connect(submit_button, &QPushButton::clicked, this, &PaymentWindow::addPayment);
    QObject::connect(cancel_button, &QPushButton::clicked, this, &PaymentWindow::close);
}
void PaymentWindow::addPayment()
{
    this->paymentName = paymentName_field->text();
    this->paymentSum = sum_field->text().toInt();

    uint16_t validationResult = this->isValid();

    if(validationResult == 0)
    {
        paymentName_label->setStyleSheet("QLabel{ color:#FFFFFF; } ");
        sum_label->setStyleSheet("QLabel{ color:#FFFFFF; } ");

        std::string log = (paymentName + ':' + sum_field->text()).toStdString();

        // write into day
        Filesystem::writeInto(DATA_PATH, currentDate + ".txt", log);

        // write into month too
        Filesystem::writeInto(DATA_PATH, currentMonth+ ".txt", log);
    }
    else if(validationResult == 1)
    {
        // normalize the sum label
        sum_label->setStyleSheet("QLabel{ color:#FFFFFF; } ");
        paymentName_label->setStyleSheet("QLabel{ color: red; }");
        this->paymentName = "";
    }
    else if(validationResult == 2)
    {
        // normalise the payment name label
        paymentName_label->setStyleSheet("QLabel{ color: #FFFFFF; }");
        sum_label->setStyleSheet("QLabel{ color: red; }");
        this->paymentSum = 0;
    }
    else
    {
        paymentName_label->setStyleSheet("QLabel { color: red;} ");
        sum_label->setStyleSheet("QLabel{ color: red;} ");
        this->paymentName = "";
        this->paymentSum = 0;
    }
}
uint16_t PaymentWindow::isValid()
{
    QString paymentName_data = paymentName_field->text();
    QString sum_data = sum_field->text();

    if(paymentName_data.isEmpty() && sum_data.isEmpty())
        return 3;
    else if(paymentName_data.isEmpty())
        return 1;
    else if(sum_data.isEmpty())
        return 2;
    return 0;
}
uint32_t PaymentWindow::getPaymentSum()
{
    return this->paymentSum;
}

QString PaymentWindow::getPaymentName()
{
    return this->paymentName;
}

PaymentWindow::~PaymentWindow()
{
    delete payment_label;
    delete paymentName_label;
    delete paymentName_field;
    delete sum_field;
    delete sum_label;
    delete cancel_button;
    delete submit_button;
    delete verticalLayout;
}
