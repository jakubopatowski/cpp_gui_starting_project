#include "MainWindow.hpp"

MainWindow::MainWindow( QWidget* parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {
    ui.setupUi( this );

    connect(ui.actionLoad, &QAction::triggered, this, &MainWindow::onLoad);
}

MainWindow::~MainWindow() {}

void MainWindow::onLoad() {}