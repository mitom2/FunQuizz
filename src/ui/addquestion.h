/// @file addquestion.h
/// @brief Header file for the AddQuestion dialog in the application.

#ifndef ADDQUESTION_H
#define ADDQUESTION_H

#include <QDialog>
#include <QListWidget>
#include <QFont>
#include <QMessageBox>
#include <unordered_map>
#include "question.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AddQuestion;
}
QT_END_NAMESPACE

/// @brief Dialog that allows users to add a new question to the quiz.

class AddQuestion : public QDialog
{
    Q_OBJECT

    /// @brief A reference to the collection of questions in the repository.
    /// @details This is used to store the questions added by the user.
    std::unordered_map<std::string, fq::Question *> &questions;

    /// @brief Validates the input fields for adding a question and saves the question if valid.
    /// @details This function checks if the question text, answers, and type are provided correctly.
    /// If valid, it creates a new question object and adds it to the questions collection.
    /// If any field is invalid, it shows a warning message.
    void save();

    /// @brief Clears the input fields.
    /// @details This function resets the question text, answers, explanation, and type selection to their default states.
    /// It is called when the user cancels the operation or after saving a question.
    void cancel();

    /// @brief Adds a new answer to the list of answers for the question.
    /// @details This function retrieves the text from the answer input field, creates a new list widget item,
    /// and adds it to the answers list. It also sets the font to bold if the answer is marked as correct.
    /// If the answer text is empty, it shows a warning message.
    void addAnswer();

    /// @brief Removes selected answers from the list of answers.
    /// @details This function deletes the selected items from the answers list widget.
    void removeAnswers();

public:
    /// @brief Constructs an AddQuestion dialog with the specified parent widget and a reference to the questions collection.
    /// @param questions A reference to the collection of questions where the new question will be added.
    /// @param parent The parent widget for the dialog. Defaults to nullptr.
    explicit AddQuestion(std::unordered_map<std::string, fq::Question *> &questions, QWidget *parent = nullptr);

    /// @brief Destroys the AddQuestion dialog.
    ~AddQuestion();

private:
    /// @brief Pointer to the UI elements of the AddQuestion dialog.
    Ui::AddQuestion *ui;
};

#endif // ADDQUESTION_H
