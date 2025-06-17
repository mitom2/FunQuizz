#include "addquestion.h"
#include "ui_addquestion.h"

void AddQuestion::save()
{
    std::string questionText = ui->question->text().toStdString();
    auto *answers = ui->answers;
    std::vector<fq::Answer> questionAnswers;
    for (int i = 0; i < answers->count(); ++i)
    {
        QListWidgetItem *item = answers->item(i);
        if (item)
        {
            fq::Answer answer;
            answer.text = item->text().toStdString();
            answer.isCorrect = item->font().bold();
            questionAnswers.push_back(answer);
        }
    }

    std::string type = ui->type->currentText().toStdString();
    if (questionAnswers.empty())
        throw std::invalid_argument("Question must have at least one answer");
    if (questionText.empty())
        throw std::invalid_argument("Question text cannot be empty");
    if (type.empty())
        throw std::invalid_argument("Question type cannot be empty");
    if (questions.find(questionText) != questions.end())
        throw std::invalid_argument("Question with this text already exists");

    if (type == "Single Choice")
        type = "single";
    else if (type == "Multiple Choice")
        type = "multiple";
    else if (type == "Negative Score Multiple Choice")
        type = "negative_multiple";
    else
        throw std::invalid_argument("Unknown question type: " + type);

    questions[questionText] = fq::Question::fromParameters(
        questionText,
        questionAnswers,
        ui->explanation->toPlainText().toStdString(),
        type);
    cancel();
}

void AddQuestion::cancel()
{
    ui->question->clear();
    ui->answers->clear();
    ui->explanation->clear();
    ui->type->setCurrentIndex(0);
    ui->answer->clear();
    ui->correct->setChecked(false);
    ui->removeAnswers->setEnabled(false);
}

void AddQuestion::addAnswer()
{
    QString answerText = ui->answer->text();
    if (answerText.isEmpty())
        throw std::invalid_argument("Answer text cannot be empty");

    QListWidgetItem *item = new QListWidgetItem(answerText);
    QFont font = ui->correct->font();
    font.setBold(ui->correct->isChecked());
    item->setFont(font);
    ui->answers->addItem(item);
    ui->answer->clear();
    ui->correct->setChecked(false);
}

void AddQuestion::removeAnswers()
{
    auto selectedItems = ui->answers->selectedItems();
    for (QListWidgetItem *item : selectedItems)
    {
        delete item; // This will remove the item from the list
    }
    ui->removeAnswers->setEnabled(false);
}

AddQuestion::AddQuestion(std::unordered_map<std::string, fq::Question *> &questions, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddQuestion), questions(questions)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(ui->save, &QPushButton::clicked, this, &AddQuestion::save);
    connect(ui->cancel, &QPushButton::clicked, this, &AddQuestion::cancel);
    connect(ui->addAnswer, &QPushButton::clicked, this, &AddQuestion::addAnswer);
    connect(ui->removeAnswers, &QPushButton::clicked, this, &AddQuestion::removeAnswers);
    connect(ui->answers, &QListWidget::itemSelectionChanged, [this]()
            { ui->removeAnswers->setEnabled(!ui->answers->selectedItems().isEmpty()); });
}

AddQuestion::~AddQuestion()
{
    delete ui;
}