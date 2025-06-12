#ifndef MANAGEQUESTIONS_H
#define MANAGEQUESTIONS_H

#include <QDialog>
#include "repository.hpp"

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

    std::vector<fq::Question *> questions;

public:
    explicit ManageQuestions(fq::Repository *repository, QWidget *parent = nullptr);
    ~ManageQuestions();

private:
    Ui::ManageQuestions *ui;
};

#endif // MANAGEQUESTIONS_H
