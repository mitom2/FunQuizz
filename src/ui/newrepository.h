#ifndef CREATEREPOSITORY_H
#define CREATEREPOSITORY_H

#include <QDialog>
#include <string>
#include <QWidget>
#include <QFileDialog>
#include "repository.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class CreateRepository;
}
QT_END_NAMESPACE

class CreateRepository : public QDialog
{
    Q_OBJECT

    fq::Repository *repository;

    void selectPath();

public:
    explicit CreateRepository(fq::Repository *repository, const std::string &initialPath = "", QWidget *parent = nullptr);
    ~CreateRepository();

private:
    Ui::CreateRepository *ui;
};

#endif // CREATEREPOSITORY_H
