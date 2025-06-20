/// @file managequestions.h
/// @brief Header file for the ManageQuestions dialog in the application.

#ifndef MANAGEQUESTIONS_H
#define MANAGEQUESTIONS_H

#include <QDialog>
#include <unordered_map>
#include <stdexcept>
#include "repository.hpp"
#include "addquestion.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ManageQuestions;
}
QT_END_NAMESPACE

/// @brief Dialog that allows users to manage questions in the quiz repository.
/// It provides functionality to remove and save questions in the repository. It can also open AddQuestion window.
class ManageQuestions : public QDialog
{
    Q_OBJECT

    /// @brief Pointer to the repository that contains the questions for the quiz.
    /// @details This repository is used to fetch, add, and remove questions.
    fq::Repository *repository;

    /// @brief A collection of questions currently loaded from the repository.
    /// @details This unordered_map holds the questions with their text as keys and pointers to Question objects as values.
    /// It allows for quick access and modification of questions.
    std::unordered_map<std::string, fq::Question *> questions;

    /// @brief Removes selected questions from the questions list.
    /// @details This function retrieves the selected items from the questions list widget and removes them from the
    /// questions collection. It updates the questions list after removal.
    void removeQuestions();

    /// @brief Updates the questions list in the UI.
    /// @details This function clears the current questions list widget and repopulates it with the
    /// questions from the questions collection. It ensures that the UI reflects the current state of the questions.
    /// It is called after adding or removing questions to keep the UI in sync with the underlying data.
    void updateQuestionsList();

    /// @brief Opens the AddQuestion dialog to add new questions.
    /// @details This function creates an instance of the AddQuestion dialog, passing the current questions collection.
    /// It sets the dialog to delete itself when closed and executes it. After adding a question, it updates the questions list to reflect the new state.
    void addQuestions();

    /// @brief Saves the current state of questions and closes the dialog.
    /// @details This function collects all questions from the questions collection, sets them in the repository,
    /// and then closes the dialog. It ensures that any changes made to the questions are saved.
    void saveAndClose();

public:
    /// @brief Constructs a ManageQuestions dialog with the specified repository and parent widget.
    /// @param repository A pointer to the repository that contains the questions for the quiz.
    /// @param parent The parent widget for the dialog. Defaults to nullptr.
    /// @throws std::invalid_argument if the repository is null.
    explicit ManageQuestions(fq::Repository *repository, QWidget *parent = nullptr);

    /// @brief Destroys the ManageQuestions dialog.
    ~ManageQuestions();

private:
    /// @brief Pointer to the UI elements of the ManageQuestions dialog.
    Ui::ManageQuestions *ui;
};

#endif // MANAGEQUESTIONS_H
