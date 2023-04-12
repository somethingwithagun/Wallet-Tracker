#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ctime>
#include <cinttypes>

#include "date.h"
#include "paymentwindow.h"
#include "fileConstants.h"
#include "fsystem.h"
#include "displaywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    // scans data from the month and day payments files
    // and gets it to the string to display in future    
    void scanData();

    // sets current date to the screen
    void setCurrentDate();

    // opens payment appending window
    void startPaymentWindow();
    
    // opens display window
    void startDisplayWindow();
    
    // displays month and day payment sum
    void displayStats();

  private:
    uint32_t dayPaymentsSum = 0;
    uint32_t monthPaymentsSum = 0;
    std::string currentDate = "";
    std::string currentMonth = "";
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
