#include "newrepository.h"
#include "ui_newrepository.h"

void CreateRepository::selectPath()
{
    QString selectedPath = QFileDialog::getSaveFileName(this, "Select Repository Path", ui->path->text(), "JSON Files (*.json);;All Files (*)");
    if (!selectedPath.isEmpty() && !selectedPath.isNull())
    {
        if (selectedPath.right(5) != ".json")
        {
            selectedPath += ".json";
        }
        ui->path->setText(selectedPath);
    }
}

CreateRepository::CreateRepository(fq::Repository *repository, const std::string &initialPath, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateRepository), repository(repository)
{
    ui->setupUi(this);
    ui->path->setText(QString::fromStdString(initialPath));
    connect(ui->selectPath, &QPushButton::clicked, this, &CreateRepository::selectPath);
}

CreateRepository::~CreateRepository()
{
    delete ui;
}
