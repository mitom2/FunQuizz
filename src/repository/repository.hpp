/// @file repository.hpp
/// @brief Contains definitions for repositories that manage quiz questions.

#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <random>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include "question.hpp"

/// @namespace fq
/// @brief Contains classes and structures related to quiz questions and answers.
///
/// The fq namespace encapsulates all types and logic for representing questions,
/// answers, and scoring mechanisms in a quiz application. It provides support for
/// single-choice, multiple-choice, and negative scoring questions, as well as
/// skippable variants.
namespace fq
{

    /// @brief Base class for repositories that manage a collection of questions.
    /// @details This class provides a common interface for different types of question repositories.
    class Repository
    {
    protected:
        /// @brief Question collection loaded from the JSON file.
        std::vector<fq::Question *> questions;

        /// @brief The path to the JSON file containing the questions.
        std::string path;

        /// @brief The type of the repository, used for saving.
        /// @details This is used to determine the type of repository when creating it from a JSON file.
        /// It must be set in the constructor of the derived classes.
        std::string jsonType;

        /// @brief Flag to disable the standard destructor.
        /// @details This is used to prevent the standard destructor from being called, allowing for custom
        /// cleanup logic in derived classes.
        bool disableStdDestructor;

    public:
        /// @brief Constructs a Repository with the specified path to the JSON file.
        /// @param path The path to the JSON file containing the questions.
        /// @throws std::runtime_error if the file cannot be opened or if the JSON format is invalid.
        Repository(const std::string &path);

        /// @brief Returns question from the repository.
        /// @return A pointer to a Question object.
        virtual fq::Question *getQuestion() = 0;

        /// @brief Returns a question back to the repository with its score.
        /// @details This method allows the repository to handle the question based on its score.
        /// @param question A pointer to the Question object to be returned.
        /// @param score The score gained by the user from the question.
        virtual void returnQuestion(fq::Question *question, double score) = 0;

        /// @brief Returns the number of questions in the repository.
        /// @return The number of questions available in the repository.
        std::size_t getQuestionCount() const;

        /// @brief Factory function to create a repository based on the specified path.
        /// @param path The path to the JSON file containing the questions.
        /// @return A pointer to a Repository object.
        /// @throws std::runtime_error if the file cannot be opened or if the JSON format is invalid.
        static Repository *createRepository(const std::string &path);

        /// @brief Returns the collection of questions in the repository.
        /// @return A vector of pointers to Question objects.
        std::vector<fq::Question *> getQuestions() const { return questions; }

        /// @brief Sets the collection of questions in the repository.
        /// @param questions_ A vector of pointers to Question objects to be set in the repository.
        virtual void setQuestions(const std::vector<fq::Question *> &questions_);

        /// @brief Virtual destructor for the Repository class.
        virtual ~Repository();
    };

    /// @brief Class representing a repository that provides questions randomly.
    class RandomRepository : public Repository
    {
    public:
        /// @brief Constructs a RandomRepository with the specified path to the JSON file.
        /// @param path The path to the JSON file containing the questions.
        /// @throws std::runtime_error if the file cannot be opened or if the JSON format is invalid.
        RandomRepository(const std::string &path);

        /// @brief Returns a random question from the repository.
        /// @return A pointer to a randomly selected Question object.
        /// @throws std::runtime_error if there are no questions available in the repository.
        virtual fq::Question *getQuestion() override;

        /// @brief Returns a question back to the repository with its score.
        /// @details In this implementation, this function does nothing, as questions are not returned to the repository.
        /// @param question A pointer to the Question object to be returned.
        /// @param score The score gained by the user from the question.
        virtual void returnQuestion(fq::Question *question, double score) override {};
    };

    /// @brief Class representing a repository that provides questions randomly without repeating them.
    class RandomNonRepeatingRepository : public Repository
    {
        /// @brief A collection of remaining questions that have not been asked yet.
        std::vector<fq::Question *> remainingQuestions;

    public:
        /// @brief Constructs a RandomNonRepeatingRepository with the specified path to the JSON file.
        /// @param path The path to the JSON file containing the questions.
        /// @throws std::runtime_error if the file cannot be opened or if the JSON format is invalid.
        RandomNonRepeatingRepository(const std::string &path);

        /// @brief Returns a random question from the repository without repeating previously asked questions, unless all questions have been asked.
        /// @return A pointer to a randomly selected Question object.
        /// @throws std::runtime_error if there are no questions available in the repository.
        virtual fq::Question *getQuestion() override;

        /// @brief Returns a question back to the repository with its score.
        /// @details In this implementation, this function does nothing, as questions are not returned to the repository.
        /// @param question A pointer to the Question object to be returned.
        /// @param score The score gained by the user from the question.
        virtual void returnQuestion(fq::Question *question, double score) override {};

        /// @brief Sets the collection of questions in the repository.
        /// @param questions_ A vector of pointers to Question objects to be set in the repository.
        virtual void setQuestions(const std::vector<fq::Question *> &questions_) override;
    };

    /// @brief Class representing a repository that provides questions intelligently based on user performance.
    class IntelligentRepository : public Repository
    {
        /// @brief A collection of remaining questions that have not been asked yet.
        std::vector<fq::Question *> remainingQuestions;

        /// @brief A collection of hard questions that the user has struggled with.
        /// @details Hard questions are those that the user has scored less than 1.0 on.
        std::vector<fq::Question *> hardQuestions;

    public:
        /// @brief Constructs an IntelligentRepository with the specified path to the JSON file.
        /// @param path The path to the JSON file containing the questions.
        IntelligentRepository(const std::string &path);

        /// @brief Returns a random question from the repository. If there are no remaining questions, it will select from hard questions.
        /// @details If the user has answered all questions, it will select from hard questions that the user has struggled with.
        /// If there are no hard questions remaining, it will select from all questions.
        /// @return A pointer to a randomly selected Question object.
        /// @throws std::runtime_error if there are no questions available in the repository.
        virtual fq::Question *getQuestion() override;

        /// @brief Returns a question back to the repository with its score.
        /// @details If the score is less than 1.0, the question is added to the hard questions collection for future consideration.
        virtual void returnQuestion(fq::Question *question, double score) override;

        /// @brief Sets the collection of questions in the repository.
        /// @param questions_ A vector of pointers to Question objects to be set in the repository.
        virtual void setQuestions(const std::vector<fq::Question *> &questions_) override;
    };
}