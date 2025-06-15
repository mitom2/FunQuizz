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

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    fq::Repository *repository;

    std::vector<fq::Answer> currentAnswers;

    fq::Question *currentQuestion;

    void okClicked(bool checked);

    void loadQuestion();

    void removeAnswers();

    void answerToggled(bool checked);

    bool isAnswered;

    int selectedAnswers;

    double totalScore;

    int totalQuestions;

    void repositoryAction(QAction *action);

    void manageQuestions(QAction *action);

    void loadRepository(const std::string &repositoryPath);

    void fontSizeChanged(int value);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
