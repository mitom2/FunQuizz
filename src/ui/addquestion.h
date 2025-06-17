#ifndef ADDQUESTION_H
#define ADDQUESTION_H

#include <QDialog>
#include <QListWidget>
#include <QFont>
#include <unordered_map>
#include "question.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AddQuestion;
}
QT_END_NAMESPACE

class AddQuestion : public QDialog
{
    Q_OBJECT
    std::unordered_map<std::string, fq::Question *> &questions;

    void save();

    void cancel();

    void addAnswer();

    void removeAnswers();

public:
    explicit AddQuestion(std::unordered_map<std::string, fq::Question *> &questions, QWidget *parent = nullptr);
    ~AddQuestion();

private:
    Ui::AddQuestion *ui;
};

#endif // ADDQUESTION_H
