#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QString>
#include <QVBoxLayout>
#include "fileConstants.h"
#include "fsystem.h"

class DisplayWindow : public QDialog
{
public:
  DisplayWindow(const QString dataToDisplay,QWidget* parent = nullptr);
  ~DisplayWindow();

private:
  QVBoxLayout *layout = nullptr;
  QTextEdit* field = nullptr;
};

#endif