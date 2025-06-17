/// @file question.hpp
/// @brief Contains definitions for quiz questions and answers.

#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <random>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>

/// @namespace fq
/// @brief Contains classes and structures related to quiz questions and answers.
///
/// The fq namespace encapsulates all types and logic for representing questions,
/// answers, and scoring mechanisms in a quiz application. It provides support for
/// single-choice, multiple-choice, and negative scoring questions, as well as
/// skippable variants.
namespace fq
{

    /// @brief Represents an answer to a question in the quiz.
    struct Answer
    {
        /// @brief The text of the question.
        std::string text;

        /// @brief Indicates whether the answer to the question is correct.
        /// true if the answer is correct; false otherwise.
        bool isCorrect;
    };

    /// @brief Represents a question in the quiz.
    /// @details This class provides a common interface for different types of questions.
    class Question
    {
    protected:
        /// @brief A collection of answers associated with a question.
        std::vector<Answer> answers;

        /// @brief The text of the question to be presented to the user.
        std::string questionText;

        /// @brief An explanation of the question, which can be used to provide additional context or information.
        std::string explanation;

    public:
        /// @brief Constructs a Question with the specified text and answers.
        /// @param question The text of the question.
        /// @param answers A vector of possible answers associated with the question.
        /// @param explanation An explanation for the question.
        /// @throws std::invalid_argument if the answers vector is empty.
        /// @throws std::invalid_argument if the question text is empty.
        Question(const std::string &question, const std::vector<Answer> &answers, const std::string &explanation);

        /// @brief Returns the answers associated with the question.
        /// @return A vector of answers associated with the question.
        std::vector<Answer> getAnswers() const { return answers; }

        /// @brief Returns the text of the question.
        /// @return The text of the question.
        std::string getQuestion() const { return questionText; }

        /// @brief Returns the score based on the selected answers. Score is calculated based on the question type.
        /// @param selectedAnswers A vector of answers selected by the user.
        /// @return The score based on the selected answers.
        virtual double getScore(const std::vector<Answer> &selectedAnswers) = 0;

        /// @brief Checks if the question is a single-choice question.
        /// @return true if the question is a single-choice question; false otherwise.
        virtual bool isSingleChoice() const = 0;

        /// @brief Returns the explanation for the question.
        /// @return A string containing the explanation for the question.
        /// @details The explanation can provide additional context or information about the question.
        std::string getExplanation() const;

        /// @brief Creates a Question object from a JSON object.
        /// @param json The JSON object containing question data.
        /// @return A pointer to a Question object created from the JSON data.
        /// @throws std::invalid_argument if the JSON object does not contain valid question data.
        static Question *fromJSON(const QJsonObject &json);

        /// @brief Creates a Question object from parameters.
        /// @param question The text of the question.
        /// @param answers A vector of answers associated with the question.
        /// @param explanation An explanation for the question.
        /// @param type The type of the question.
        /// @return A pointer to a Question object created from the parameters.
        /// @throws std::invalid_argument if the answers vector is empty.
        /// @throws std::invalid_argument if the question text is empty.
        /// @throws std::invalid_argument if the type is not recognized.
        /// @details The type parameter determines the specific type of question to create (e.g., single-choice, multiple-choice).
        static Question *fromParameters(const std::string &question, const std::vector<Answer> &answers, std::string explanation, const std::string &type);
    };

    /// @brief Represents a single-choice question in the quiz.
    class SingleChoiceQuestion : public Question
    {
    public:
        /// @brief Constructs a SingleChoiceQuestion with the specified text and answers.
        /// @param question The text of the question.
        /// @param answers A vector of answers associated with the question.
        /// @param explanation An explanation for the question.
        /// @throws std::invalid_argument if the answers vector is empty.
        /// @throws std::invalid_argument if the question text is empty.
        SingleChoiceQuestion(const std::string &question, const std::vector<Answer> &answers, const std::string &explanation)
            : Question(question, answers, explanation) {}

        /// @brief Returns the score based on the selected answers. Awards a score of 1 for the correct answer and 0 for incorrect answers.
        /// @param selectedAnswers A vector of answers selected by the user.
        /// @return The score based on the selected answers.
        /// @throws std::invalid_argument if multiple answers are selected.
        virtual double getScore(const std::vector<Answer> &selectedAnswers) override;

        /// @brief Checks if the question is a single-choice question.
        /// @return true, as this is a single-choice question.
        virtual bool isSingleChoice() const override { return true; }
    };

    /// @brief Represents a multiple-choice question in the quiz.
    class MultipleChoiceQuestion : public Question
    {
    public:
        /// @brief Constructs a MultipleChoiceQuestion with the specified text and answers.
        /// @param question The text of the question.
        /// @param answers A vector of answers associated with the question.
        /// @param explanation An explanation for the question.
        /// @throws std::invalid_argument if the answers vector is empty.
        /// @throws std::invalid_argument if the question text is empty.
        /// @return The score based on the selected answers.
        MultipleChoiceQuestion(const std::string &question, const std::vector<Answer> &answers, const std::string &explanation)
            : Question(question, answers, explanation) {}

        /// @brief Returns the score based on the selected answers. Awards points for correct answers and deducts points for incorrect answers.
        /// The score is calculated based on the number of correct answers. Score is normalized based on the number of correct answers.
        /// Score can never be negative.
        /// @param selectedAnswers A vector of answers selected by the user.
        /// @return The score based on the selected answers.
        virtual double getScore(const std::vector<Answer> &selectedAnswers) override;

        /// @brief Checks if the question is a single-choice question.
        /// @return false, as this is a multiple-choice question.
        virtual bool isSingleChoice() const override { return false; }
    };

    /// @brief Represents a multiple-choice question with negative scoring in the quiz.
    class NegativeScoreMultipleChoiceQuestion : public Question
    {
    public:
        /// @brief Constructs a NegativeScoreMultipleChoiceQuestion with the specified text and answers.
        /// @param question The text of the question.
        /// @param answers A vector of answers associated with the question.
        /// @param explanation An explanation for the question.
        /// @throws std::invalid_argument if the answers vector is empty.
        /// @throws std::invalid_argument if the question text is empty.
        /// @return The score based on the selected answers.
        NegativeScoreMultipleChoiceQuestion(const std::string &question, const std::vector<Answer> &answers, const std::string &explanation)
            : Question(question, answers, explanation) {}

        /// @brief Returns the score based on the selected answers. Awards points for correct answers and deducts points for incorrect answers.
        /// The score is calculated based on the number of correct answers. Score is normalized based on the number of correct answers.
        /// Score can be negative.
        /// @param selectedAnswers A vector of answers selected by the user.
        /// @return The score based on the selected answers.
        virtual double getScore(const std::vector<Answer> &selectedAnswers) override;

        /// @brief Checks if the question is a single-choice question.
        /// @return false, as this is a multiple-choice question.
        virtual bool isSingleChoice() const override { return false; }
    };

}