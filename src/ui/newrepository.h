/// @file newrepository.h
/// @brief Header file for the CreateRepository dialog in the application.

#ifndef CREATEREPOSITORY_H
#define CREATEREPOSITORY_H

#include <QDialog>
#include <string>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "repository.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class CreateRepository;
}
QT_END_NAMESPACE

/// @brief Dialog that allows users to create a new repository for quiz questions.
/// It provides functionality to select a path, choose the type of repository, and create the repository.
class CreateRepository : public QDialog
{
    Q_OBJECT

    /// @brief Handles the selection of a path for the repository.
    /// @details This function opens a file dialog to select a path for the repository.
    void selectPath();

    /// @brief Creates a new repository based on the selected path and type.
    /// @details This function retrieves the selected path and type from the UI, creates a JSON object representing the repository,
    /// and writes it to a file. If the path is empty or invalid, it shows a warning message.
    /// If the repository is created successfully, it updates the initialPath and closes the dialog.
    void createRepository();

    /// @brief A reference to the initial path where the repository will be created.
    /// @details This is used to store the path selected by the user for the new repository from the initial dialog.
    /// It is updated when the repository is created successfully.
    std::string &initialPath;

public:
    /// @brief Constructs a CreateRepository dialog with the specified initial path and parent widget.
    /// @param initialPath A reference to the string where the path of the created repository will be stored (can be changed).
    /// @param parent The parent widget for the dialog. Defaults to nullptr.
    explicit CreateRepository(std::string &initialPath, QWidget *parent = nullptr);

    /// @brief Destroys the CreateRepository dialog.
    ~CreateRepository();

private:
    /// @brief Pointer to the UI elements of the CreateRepository dialog.
    Ui::CreateRepository *ui;
};

#endif // CREATEREPOSITORY_H
