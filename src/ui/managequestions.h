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

class ManageQuestions : public QDialog
{
    Q_OBJECT

    fq::Repository *repository;

    std::unordered_map<std::string, fq::Question *> questions;

    void removeQuestions();

    void updateQuestionsList();

    void addQuestions();

    void saveAndClose();

public:
    explicit ManageQuestions(fq::Repository *repository, QWidget *parent = nullptr);
    ~ManageQuestions();

private:
    Ui::ManageQuestions *ui;
};

#endif // MANAGEQUESTIONS_H
