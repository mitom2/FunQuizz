#include "managequestions.h"
#include "ui_managequestions.h"

ManageQuestions::ManageQuestions(fq::Repository *repository, QWidget *parent)
    : QDialog(parent), ui(new Ui::ManageQuestions), repository(repository)
{
    ui->setupUi(this);
    if (repository == nullptr)
        throw std::invalid_argument("Repository cannot be null");
    questions = repository->getQuestions();
    for (std::size_t i = 0; i < questions.size(); ++i)
    {
        ui->questions->addItem(QString::fromStdString(questions[i]->getQuestion()));
    }
}

ManageQuestions::~ManageQuestions()
{
    delete ui;
}
