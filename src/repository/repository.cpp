#include "repository.hpp"

fq::Repository::Repository(const std::string &path) : path(path), disableStdDestructor(false), jsonType("unknown")
{
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Failed to open file: " + path);
    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    if (!json.contains("questions") || !json["questions"].isArray())
        throw std::runtime_error("Invalid JSON format: 'questions' not found or is not an array");
    QJsonArray questionsArray = json["questions"].toArray();
    for (const QJsonValue &value : questionsArray)
    {
        if (!value.isObject())
            throw std::runtime_error("Invalid question format in JSON");
        QJsonObject questionObj = value.toObject();
        Question *question = fq::Question::fromJSON(questionObj);
        questions.push_back(question);
    }
}

std::size_t fq::Repository::getQuestionCount() const
{
    return questions.size();
}

fq::RandomRepository::RandomRepository(const std::string &path) : Repository(path)
{
    jsonType = "random";
}

fq::Question *fq::RandomRepository::getQuestion()
{
    if (questions.empty())
        throw std::runtime_error("No questions available in the repository");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, questions.size() - 1);
    int index = dis(gen);
    return questions[index];
}

fq::RandomNonRepeatingRepository::RandomNonRepeatingRepository(const std::string &path) : Repository(path)
{
    jsonType = "random_non_repeating";
    remainingQuestions = questions;
}

fq::Question *fq::RandomNonRepeatingRepository::getQuestion()
{
    if (questions.empty())
        throw std::runtime_error("No questions available in the repository");
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!remainingQuestions.size())
        remainingQuestions = questions;
    std::uniform_int_distribution<> dis(0, remainingQuestions.size() - 1);
    int index = dis(gen);
    return remainingQuestions[index];
}

fq::IntelligentRepository::IntelligentRepository(const std::string &path) : Repository(path)
{
    jsonType = "intelligent";
    remainingQuestions = questions;
}

fq::Question *fq::IntelligentRepository::getQuestion()
{
    if (questions.empty())
        throw std::runtime_error("No questions available in the repository");
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!remainingQuestions.size())
    {
        remainingQuestions = hardQuestions.empty() ? questions : hardQuestions;
        hardQuestions.clear();
    }
    std::uniform_int_distribution<> dis(0, remainingQuestions.size() - 1);
    int index = dis(gen);
    return remainingQuestions[index];
}

void fq::IntelligentRepository::returnQuestion(Question *question, double score)
{
    if (score < 1.0)
        hardQuestions.push_back(question);
}

fq::Repository *fq::Repository::createRepository(const std::string &path)
{
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Failed to open file: " + path);
    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    if (!json.contains("type") || !json["type"].isString())
        throw std::runtime_error("Invalid JSON format: 'type' not found or is not a string");

    QString type = json["type"].toString();
    if (type == "random")
        return new RandomRepository(path);
    else if (type == "random_non_repeating")
        return new RandomNonRepeatingRepository(path);
    else if (type == "intelligent")
        return new IntelligentRepository(path);

    throw std::runtime_error("Unknown repository type: " + type.toStdString());
}

void fq::Repository::setQuestions(const std::vector<fq::Question *> &questions_)
{
    for (auto &question : questions)
    {
        if (std::find(questions_.begin(), questions_.end(), question) == questions_.end())
            delete question;
    }
    questions = questions_;
}

fq::Repository::~Repository()
{
    if (!disableStdDestructor)
    {
        QJsonArray questionsArray;
        for (const auto &question : questions)
        {
            QJsonObject questionObj = question->toJSON();
            questionsArray.append(questionObj);
        }
        QJsonObject json;
        json["questions"] = questionsArray;
        json["type"] = QString::fromStdString(jsonType);
        QJsonDocument doc(json);
        QFile file(QString::fromStdString(path));
        if (!file.open(QIODevice::WriteOnly))
            QMessageBox::critical(nullptr, "Error", QString::fromStdString("Failed to save repository: " + path));
        else
            file.write(doc.toJson());
        file.close();
    }
    for (auto &question : questions)
    {
        delete question;
    }
}

void fq::RandomNonRepeatingRepository::setQuestions(const std::vector<fq::Question *> &questions_)
{
    for (auto &question : questions)
    {
        if (std::find(questions_.begin(), questions_.end(), question) == questions_.end())
            delete question;
    }
    questions = questions_;
    remainingQuestions = questions;
}

void fq::IntelligentRepository::setQuestions(const std::vector<fq::Question *> &questions_)
{
    for (auto &question : questions)
    {
        if (std::find(questions_.begin(), questions_.end(), question) == questions_.end())
            delete question;
    }
    questions = questions_;
    remainingQuestions = questions;
    hardQuestions.clear();
}