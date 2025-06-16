#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::okClicked(bool checked)
{
    if (!isAnswered)
    {
        std::vector<fq::Answer> chosenAnswers;
        for (int i = 0; i < ui->answers->count(); ++i)
        {
            auto answerWidget = qobject_cast<QAbstractButton *>(ui->answers->itemAt(i)->widget());
            if (answerWidget && answerWidget->isChecked())
            {
                chosenAnswers.push_back(currentAnswers[i]);
            }
        }
        try
        {
            auto score = currentQuestion->getScore(chosenAnswers);
            repository->returnQuestion(currentQuestion, score);
            isAnswered = true;
            totalQuestions++;
            totalScore += score;
            ui->score->setText(QString::number(totalScore) + "/" + QString::number(totalQuestions));
            auto percentage = static_cast<int>(totalScore * 100 / static_cast<double>(totalQuestions));
            ui->scoreBar->setValue(percentage);
            QColor barColor = QColor(255 - 255 * percentage / 100, 255 * percentage / 100, 0);
            QString style = QString("QProgressBar::chunk {background-color: %1;width: 20px;}").arg(barColor.name());
            ui->scoreBar->setStyleSheet(style);
            ui->ok->setText("Next");
            ui->explanation->setText(QString::fromStdString(currentQuestion->getExplanation()));
            for (int i = 0; i < ui->answers->count(); ++i)
            {
                auto answerWidget = qobject_cast<QAbstractButton *>(ui->answers->itemAt(i)->widget());
                answerWidget->setEnabled(false);
                if (answerWidget)
                {
                    if (currentAnswers[i].isCorrect)
                    {
                        answerWidget->setStyleSheet("QAbstractButton { color: green; }");
                    }
                    else
                    {
                        answerWidget->setStyleSheet("QAbstractButton { color: red; }");
                    }
                }
            }
        }
        catch (const std::invalid_argument &e)
        {
            QMessageBox::warning(this, "Hold up!", QString::fromStdString(e.what()));
            return;
        }
    }
    else
    {
        loadQuestion();
    }
}

void MainWindow::loadQuestion()
{
    try
    {
        currentQuestion = repository->getQuestion();
        ui->question->setText(currentQuestion->getQuestion().c_str());
        currentAnswers = currentQuestion->getAnswers();
        removeAnswers();
        for (std::size_t i = 0; i < currentAnswers.size(); ++i)
        {
            const auto &answer = currentAnswers[i];
            if (currentQuestion->isSingleChoice())
            {
                auto answerWidget = new QRadioButton(QString::fromStdString(answer.text), this);
                connect(answerWidget, &QRadioButton::toggled, this, &MainWindow::answerToggled);
                answerWidget->setFont(ui->question->font());
                ui->answers->addWidget(answerWidget);
            }
            else
            {
                auto answerWidget = new QCheckBox(QString::fromStdString(answer.text), this);
                connect(answerWidget, &QCheckBox::toggled, this, &MainWindow::answerToggled);
                answerWidget->setFont(ui->question->font());
                ui->answers->addWidget(answerWidget);
            }
        }
        ui->ok->setText("Skip");
        ui->ok->setEnabled(true);
        ui->explanation->setText("");
        isAnswered = false;
        selectedAnswers = 0;
        return;
    }
    catch (const std::invalid_argument &e)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
    catch (const std::runtime_error &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
    ui->score->setText("0/0");
    ui->scoreBar->setValue(0);
    ui->explanation->setText("");
    ui->totalQuestions->setText("Total questions in repository: " + QString::number(repository->getQuestionCount()));
    ui->ok->setEnabled(false);
    ui->ok->setText("");
    ui->question->setText("No questions available");
    removeAnswers();
}

void MainWindow::removeAnswers()
{
    QLayoutItem *answer;
    while ((answer = ui->answers->takeAt(0)) != nullptr)
    {
        delete answer->widget();
        delete answer;
    }
}

void MainWindow::answerToggled(bool checked)
{
    if (checked)
        selectedAnswers++;
    else
        selectedAnswers--;

    if (!selectedAnswers)
        ui->ok->setText("Skip");
    else
        ui->ok->setText("OK");
}

void MainWindow::repositoryAction(QAction *action)
{
    try
    {
        if (action == ui->openRepository)
        {
            QString fileName = QFileDialog::getOpenFileName(this, "Open Repository", "", "JSON Files (*.json);;All Files (*)");
            if (!fileName.isEmpty())
            {
                loadRepository(fileName.toStdString());
            }
        }
        else if (action == ui->newRepository)
        {
        }
    }
    catch (const std::invalid_argument &e)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
    catch (const std::runtime_error &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::helpAction(QAction *action)
{
    if (action == ui->about)
    {
        About *about = new About(this);
        about->setAttribute(Qt::WA_DeleteOnClose);
        about->show();
    }
}

void MainWindow::manageQuestions(QAction *action)
{
    try
    {
        if (action == ui->manageQuestions)
        {
            ManageQuestions *manageQuestions = new ManageQuestions(repository, this);
            manageQuestions->setAttribute(Qt::WA_DeleteOnClose);
            manageQuestions->exec();
            ui->score->setText("0/0");
            ui->scoreBar->setValue(0);
            ui->explanation->setText("");
            ui->totalQuestions->setText("Total questions in repository: " + QString::number(repository->getQuestionCount()));
            loadQuestion();
        }
    }
    catch (const std::invalid_argument &e)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
    catch (const std::runtime_error &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::loadRepository(const std::string &repositoryPath)
{
    try
    {
        removeAnswers();
        delete repository;
        repository = fq::Repository::createRepository(repositoryPath);
        ui->score->setText("0/0");
        ui->scoreBar->setValue(0);
        ui->explanation->setText("");
        ui->totalQuestions->setText("Total questions in repository: " + QString::number(repository->getQuestionCount()));
        loadQuestion();
        ui->manageQuestions->setEnabled(true);
        return;
    }
    catch (const std::invalid_argument &e)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        return;
    }
    catch (const std::runtime_error &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
        return;
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
        return;
    }
    delete repository;
    repository = nullptr;
}

void MainWindow::fontSizeChanged(int value)
{
    QFont font = ui->explanation->font();
    font.setPointSize(value);
    ui->explanation->setFont(font);
    ui->score->setFont(font);
    ui->totalQuestions->setFont(font);
    ui->ok->setFont(font);
    ui->question->setFont(font);
    ui->scoreBar->setFont(font);
    ui->menuBar->setFont(font);
    ui->questions->setFont(font);
    ui->repository->setFont(font);
    ui->help->setFont(font);
    ui->about->setFont(font);
    ui->manageQuestions->setFont(font);
    ui->newRepository->setFont(font);
    ui->openRepository->setFont(font);
    for (int i = 0; i < ui->answers->count(); ++i)
    {
        auto answerWidget = qobject_cast<QAbstractButton *>(ui->answers->itemAt(i)->widget());
        if (answerWidget)
            answerWidget->setFont(font);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), isAnswered(false), currentQuestion(nullptr), selectedAnswers(0), totalQuestions(0), totalScore(0.0), repository(nullptr)
{
    ui->setupUi(this);
    connect(ui->ok, &QPushButton::clicked, this, &MainWindow::okClicked);
    connect(ui->repository, &QMenu::triggered, this, &MainWindow::repositoryAction);
    connect(ui->questions, &QMenu::triggered, this, &MainWindow::manageQuestions);
    connect(ui->help, &QMenu::triggered, this, &MainWindow::helpAction);
    connect(ui->explanationSize, &QSlider::valueChanged, this, &MainWindow::fontSizeChanged);
    QColor barColor = QColor(0, 0, 0);
    QString style = QString("QProgressBar::chunk {background-color: %1;width: 20px;}").arg(barColor.name());
    ui->scoreBar->setStyleSheet(style);
    ui->score->setText("0/0");
    ui->scoreBar->setValue(0);
    ui->explanation->setText("Welcome to the FunQuizz! Use repository menu to load a quiz repository and start answering questions.");
    ui->totalQuestions->setText("Repository not loaded yet.");
    ui->manageQuestions->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete repository;
}
