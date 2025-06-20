/// @file mainwindow.h
/// @brief Header file for the MainWindow class, which serves as the main UI screen of the application.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QColor>
#include <QString>
#include <QFileDialog>
#include <QSlider>
#include <QFont>
#include "repository.hpp"
#include "managequestions.h"
#include "about.h"
#include "newrepository.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/// @brief MainWindow class that serves as the main UI screen of the application.
/// It allows users to interact with the quiz repository, answer questions, and view scores.
class MainWindow : public QMainWindow
{
    Q_OBJECT

    /// @brief Pointer to the repository that contains the questions for the quiz.
    /// @details This repository is used to fetch questions and manage the quiz state.
    fq::Repository *repository;

    /// @brief A collection of answers currently loaded from the repository.
    /// @details This vector holds the answers for the current question being displayed.
    std::vector<fq::Answer> currentAnswers;

    /// @brief Pointer to the current question being displayed in the UI.
    fq::Question *currentQuestion;

    /// @brief Loads the next question from the repository or shows and explanation and updates the UI accordingly.
    /// @param checked A boolean indicating whether the button was checked or not. Not used in this context.
    /// @details If the question is answered, it updates the score and displays the explanation.
    void okClicked(bool checked);

    /// @brief Loads a new question from the repository and updates the UI.
    /// @details This function fetches a new question from the repository, updates the question text,
    /// and populates the answers in the UI. It also resets the state for answering the question.
    /// If no questions are available, it displays a message in the UI indicating that.
    void loadQuestion();

    /// @brief Removes all answer widgets from the UI.
    /// @details This function clears the layout containing the answer widgets, effectively removing all answers.
    void removeAnswers();

    /// @brief Handles the toggling of an answer widget.
    /// @param checked A boolean indicating whether the answer widget is checked or not.
    /// @details This function updates the count of selected answers and enables or disables the OK button based on the selection.
    void answerToggled(bool checked);

    /// @brief Indicates whether the current question has been answered.
    /// @details This boolean flag is used to track if the user has answered the current question.
    bool isAnswered;

    /// @brief The number of answers selected by the user for the current question.
    /// @details This integer keeps track of how many answers the user has selected for the current question.
    /// It is used to determine if the user can submit their answer.
    int selectedAnswers;

    /// @brief The total score accumulated by the user across all answered questions.
    double totalScore;

    /// @brief The total number of questions displayed to the user.
    /// Used to calculate the score percentage.
    int totalQuestions;

    /// @brief Handles menu actions related to the repository.
    /// @param action The QAction that triggered the repository action.
    /// @details This function processes actions such as opening a repository and creating a new repository.
    void repositoryAction(QAction *action);

    /// @brief Handles the help action triggered from the menu.
    /// @param action The QAction that triggered the help action.
    void helpAction(QAction *action);

    /// @brief Handles menu actions related to the questions.
    /// @param action The QAction that triggered the questions management action.
    /// @details This function allows the user to manage questions, such as adding or removing questions.
    void manageQuestions(QAction *action);

    /// @brief Loads a repository from the specified path.
    /// @param repositoryPath The path to the repository file.
    void loadRepository(const std::string &repositoryPath);

    /// @brief Changes the font size of various UI elements.
    /// @param value The new font size (in points).
    void fontSizeChanged(int value);

public:
    /// @brief Constructs the MainWindow with the specified parent widget.
    /// @param parent The parent widget for the MainWindow. Defaults to nullptr.
    explicit MainWindow(QWidget *parent = nullptr);

    /// @brief Destroys the MainWindow and cleans up resources.
    ~MainWindow();

private:
    /// @brief Pointer to the UI elements of the MainWindow.
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
