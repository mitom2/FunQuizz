#include "managequestions.h"
#include "ui_managequestions.h"

void ManageQuestions::removeQuestions()
{
    auto toRemove = ui->questions->selectedItems();
    for (auto &it : toRemove)
    {
        if (!questions.erase(it->text().toStdString()))
            throw std::runtime_error("Failed to remove question: " + it->text().toStdString());
    }
    updateQuestionsList();
}

void ManageQuestions::updateQuestionsList()
{
    ui->questions->clear();
    for (auto &it : questions)
    {
        ui->questions->addItem(QString::fromStdString(it.first));
    }
}

void ManageQuestions::saveAndClose()
{
    std::vector<fq::Question *> qvec;
    qvec.reserve(questions.size());
    for (const auto &pair : questions)
        qvec.push_back(pair.second);
    repository->setQuestions(qvec);
    close();
}

ManageQuestions::ManageQuestions(fq::Repository *repository, QWidget *parent)
    : QDialog(parent), ui(new Ui::ManageQuestions), repository(repository)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    if (repository == nullptr)
        throw std::invalid_argument("Repository cannot be null");
    auto q = repository->getQuestions();
    for (auto &it : q)
    {
        questions[it->getQuestion()] = it;
    }
    updateQuestionsList();
    connect(ui->removeQuestion, &QPushButton::clicked, this, &ManageQuestions::removeQuestions);
    connect(ui->save, &QPushButton::clicked, this, &ManageQuestions::saveAndClose);
}

ManageQuestions::~ManageQuestions()
{
    delete ui;
}
