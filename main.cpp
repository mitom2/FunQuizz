#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    try
    {
        // Create a QApplication object
        QApplication app(argc, argv);
        // Create an instance of MainWindow
        MainWindow mainWindow;
        // Show the main window
        mainWindow.show();
        // Execute the application event loop
        return app.exec();
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(nullptr, "Error", QString::fromStdString(e.what()));
        return 1;
    }
    catch (...)
    {
        QMessageBox::critical(nullptr, "Error", "An unexpected error occurred.");
        return 1;
    }
    return 0;
}
