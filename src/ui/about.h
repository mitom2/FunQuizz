/// @file about.h
/// @brief Header file for the About dialog in the application.

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class About;
}
QT_END_NAMESPACE

/// @brief Dialog that displays information about the application.
class About : public QDialog
{
    Q_OBJECT

public:
    /// @brief Constructs an About dialog with the specified parent widget.
    /// @param parent The parent widget for the dialog. Defaults to nullptr.
    explicit About(QWidget *parent = nullptr);

    /// @brief Destroys the About dialog.
    ~About();

private:
    /// @brief Pointer to the UI elements of the About dialog.
    Ui::About *ui;
};

#endif // ABOUT_H
