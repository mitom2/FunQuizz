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

void CreateRepository::createRepository()
{
    std::string path = ui->path->text().toStdString();
    if (path.empty())
    {
        QMessageBox::warning(this, "Error", "Repository path cannot be empty.");
        return;
    }

    try
    {
        QFile file(QString::fromStdString(path));
        if (!file.open(QIODevice::WriteOnly))
        {
            throw std::runtime_error("Failed to create file: " + path);
        }
        QJsonObject json;
        if (ui->type->currentText() == "Random repository")
        {
            json["type"] = "random";
        }
        else if (ui->type->currentText() == "Non-repeating repository")
        {
            json["type"] = "random_non_repeating";
        }
        else if (ui->type->currentText() == "Intelligent repository")
        {
            json["type"] = "intelligent";
        }
        else
        {
            throw std::runtime_error("Invalid repository type selected.");
        }
        json["questions"] = QJsonArray();

        QJsonDocument doc(json);
        file.write(doc.toJson());
        file.close();
        initialPath = path;
        QMessageBox::information(this, "Success", "Repository created successfully.");
        accept();
    }
    catch (const std::runtime_error &e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

CreateRepository::CreateRepository(std::string &initialPath, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateRepository), initialPath(initialPath)
{
    ui->setupUi(this);
    ui->path->setText(QString::fromStdString(initialPath));
    connect(ui->selectPath, &QPushButton::clicked, this, &CreateRepository::selectPath);
    connect(ui->cancel, &QPushButton::clicked, this, &CreateRepository::reject);
    connect(ui->create, &QPushButton::clicked, this, &CreateRepository::createRepository);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

CreateRepository::~CreateRepository()
{
    delete ui;
}
