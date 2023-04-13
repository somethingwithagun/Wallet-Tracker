#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->addPayment_button, &QPushButton::clicked, this, &MainWindow::startPaymentWindow);
    QObject::connect(ui->dayPayments_button, &QPushButton::clicked, this, &MainWindow::startDisplayWindow);
    QObject::connect(ui->monthPayments_button, &QPushButton::clicked, this, &MainWindow::startDisplayWindow);

    this->setCurrentDate();
    this->scanData();
}

// sets current date
void MainWindow::setCurrentDate()
{
    currentDate = Date::getCurrentDate("%d.%m.%y");
    currentMonth = currentDate.substr(3, currentDate.size() - 3); // mm.yy

    ui->currentDate_label->setText("Current date: " + QString::fromStdString(currentDate));
}

void MainWindow::startDisplayWindow()
{
    QString a = sender()->objectName();
    if (sender()->objectName() == "dayPayments_button")
    {
        DisplayWindow displayWindow(
            QString::fromStdString((Filesystem::readFromFile(DATA_PATH + currentDate + ".txt"))));
        this->hide();
        displayWindow.exec();
        this->show();
    }

    else if (sender()->objectName() == "monthPayments_button")
    {
        DisplayWindow displayWindow(
            QString::fromStdString((Filesystem::readFromFile(DATA_PATH + currentMonth + ".txt"))));
        this->hide();
        displayWindow.exec();
        this->show();
    }
}

void MainWindow::startPaymentWindow()
{
    PaymentWindow window(currentDate, currentMonth);
    this->hide();
    window.exec();
    this->show();
    scanData();
    displayStats();
}

void MainWindow::displayStats()
{
    ui->dayDisplay_value->setText(QString::fromStdString(std::to_string(dayPaymentsSum)));
    ui->monthDisplay_value->setText(QString::fromStdString(std::to_string(monthPaymentsSum)));
}

void MainWindow::scanData()
{
    dayPaymentsSum = 0;
    monthPaymentsSum = 0;

    std::string dayPayments = Filesystem::readFromFile(std::string(DATA_PATH) + currentDate + ".txt");

    std::string paymentSum = "";

    if (dayPayments == ".txt")
        dayPaymentsSum = 0;
    else
    {
        for (int j = 0; j < dayPayments.size(); j++)
        {
            if (dayPayments[j] == '\n')
            {
                dayPaymentsSum += std::stoi(paymentSum);
                paymentSum = "";
            }
            if ((int)dayPayments[j] <= 57 && (int)dayPayments[j] >= 48) // is digit
                paymentSum += dayPayments[j];
        }
    }

    // get month payments
    // std::string monthPaymentsfilepath =
    //   Filesystem::readFromFile(std::string(DATA_PATH) + currentDate.substr(4, currentDate.size() - 2) + ".txt");
    std::string monthPayments = Filesystem::readFromFile(std::string(DATA_PATH) + currentMonth + ".txt");
    if (monthPayments == ".txt")
        monthPaymentsSum = 0;
    else
    {
        paymentSum = "";
        for (int j = 0; j < monthPayments.size(); j++)
        {
            if (monthPayments[j] == '\n')
            {
                monthPaymentsSum += std::stoi(paymentSum);
                paymentSum = "";
            }
            if ((int)monthPayments[j] <= 57 && (int)monthPayments[j] >= 48) // is digit
                paymentSum += monthPayments[j];
        }
    }

    displayStats();
}

MainWindow::~MainWindow()
{
    delete ui;
}
