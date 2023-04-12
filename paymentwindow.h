#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include "./fileConstants.h"
#include "./fsystem.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>
#include <cinttypes>
#include <fstream>

class PaymentWindow : public QDialog
{
    Q_OBJECT
  public:
    explicit PaymentWindow(std::string date, std::string month, QWidget *parent = nullptr);
    ~PaymentWindow();
    void addPayment();

    uint32_t getPaymentSum();
    QString getPaymentName();

  private:
    uint16_t isValid();

  private:
    QSpacerItem *spacer1 = nullptr;
    QSpacerItem *spacer2 = nullptr;
    QLabel *payment_label = nullptr;
    QLabel *paymentName_label = nullptr;
    QLabel *sum_label = nullptr;
    QLineEdit *paymentName_field = nullptr;
    QLineEdit *sum_field = nullptr;
    QPushButton *submit_button = nullptr;
    QPushButton *cancel_button = nullptr;
    QVBoxLayout *verticalLayout = nullptr;

    uint32_t paymentSum = 0;
    QString paymentName;
    std::string currentDate = "";
    std::string currentMonth = "";
  signals:
};

#endif // PAYMENTWINDOW_H
