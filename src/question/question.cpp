#include "question.hpp"

fq::Question::Question(const std::string &question, const std::vector<Answer> &answers, const std::string &explanation)
    : questionText(question), answers(answers), explanation(explanation)
{
    if (answers.empty())
        throw std::invalid_argument("Question must have at least one answer");
    if (question.empty())
        throw std::invalid_argument("Question text cannot be empty");
}

double fq::SingleChoiceQuestion::getScore(const std::vector<Answer> &selectedAnswers)
{
    if (selectedAnswers.empty())
        return 0.0;
    if (selectedAnswers.size() > 1)
        throw std::invalid_argument("Multiple answers selected for a single choice question");
    if (selectedAnswers[0].isCorrect)
        return 1.0;
    return 0.0;
}

double fq::MultipleChoiceQuestion::getScore(const std::vector<Answer> &selectedAnswers)
{
    double score = 0.0;
    double correctsCount = 0.0;
    for (const auto &answer : answers)
    {
        if (answer.isCorrect)
            correctsCount += 1.0;
    }
    double answerValue = 1.0;
    if (correctsCount == 0.0)
        answerValue /= answers.size();
    else
        answerValue /= correctsCount;
    for (const auto &answer : selectedAnswers)
    {
        if (answer.isCorrect)
            score += answerValue;
        else
            score -= answerValue;
    }
    return score < 0.0 ? 0.0 : score;
}

double fq::NegativeScoreMultipleChoiceQuestion::getScore(const std::vector<Answer> &selectedAnswers)
{
    double score = 0.0;
    double correctsCount = 0.0;
    for (const auto &answer : answers)
    {
        if (answer.isCorrect)
            correctsCount += 1.0;
    }
    double answerValue = 1.0;
    if (correctsCount == 0.0)
        answerValue /= answers.size();
    else
        answerValue /= correctsCount;
    for (const auto &answer : selectedAnswers)
    {
        if (answer.isCorrect)
            score += answerValue;
        else
            score -= answerValue;
    }
    return score;
}

fq::Question *fq::Question::fromJSON(const QJsonObject &json)
{
    if (!json.contains("type") || !json["type"].isString())
        throw std::invalid_argument("JSON object does not contain a valid 'type' field");

    std::string type = json["type"].toString().toStdString();
    std::vector<Answer> answers;
    auto answersArray = json["answers"].toArray();
    std::string explanation = json.contains("explanation") ? json["explanation"].toString().toStdString() : "No explanation provided";
    for (const QJsonValue &value : answersArray)
    {
        if (!value.isObject())
            throw std::invalid_argument("Invalid answer format in JSON");
        QJsonObject answerObj = value.toObject();
        if (!answerObj.contains("text") || !answerObj.contains("is_correct"))
            throw std::invalid_argument("Answer object must contain 'text' and 'is_correct' fields");
        Answer answer;
        answer.text = answerObj["text"].toString().toStdString();
        answer.isCorrect = answerObj["is_correct"].toBool();
        answers.push_back(answer);
    }
    if (answers.empty())
        throw std::invalid_argument("Question must have at least one answer");
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(answers.begin(), answers.end(), g);
    if (type == "single")
        return new SingleChoiceQuestion(json["text"].toString().toStdString(),
                                        answers, explanation);
    else if (type == "multiple")
        return new MultipleChoiceQuestion(json["text"].toString().toStdString(),
                                          answers, explanation);
    else if (type == "negative_multiple")
        return new NegativeScoreMultipleChoiceQuestion(json["text"].toString().toStdString(),
                                                       answers, explanation);
    throw std::invalid_argument("Unknown question type: " + type);
}

std::string fq::Question::getExplanation() const
{
    return explanation;
}