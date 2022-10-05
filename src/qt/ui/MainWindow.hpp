#pragma once

#include "ui_MainWindow.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = {});
    virtual ~MainWindow();

private:
  Ui::MainWindow ui;

private slots:
  void onLoad();
};