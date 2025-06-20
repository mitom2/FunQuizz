# FunQuizz

FunQuizz is a Qt-based quiz application that allows you to create, manage, and take quizzes using customizable repositories of questions.

## Features

- **Multiple repository types**: Random, Non-repeating, and Intelligent repositories for different quiz experiences.
- **Question management**: Add, edit, and remove questions with support for single choice, multiple choice, and negative score multiple choice.
- **Rich UI**: User-friendly interface built with Qt Widgets.
- **Progress tracking**: Real-time score and grading.
- **Explanations**: Each question can include an explanation shown after answering.
- **Repository creation**: Easily create new repositories and select their type.

## Getting Started

### Prerequisites

- [Qt 6](https://www.qt.io/download) >=6.4.2 (Core and Widgets modules)
- CMake 3.16 or newer
- C++17 compatible compiler (e.g., MSVC, GCC, Clang)

### Building

Clone the repository:

```bash
  git clone https://github.com/mitom2/FunQuizz.git
  cd FunQuizz
  mkdir build
  cd build
  cmake ..
  make
```

### Running

- Launch the application.
- Use the **Repository** menu to open or create a quiz repository (`.json` file).
- Use the **Questions** menu to manage questions in the repository.
- Answer questions and track your score.

## Repository Types

- **Random repository**: Questions are selected randomly.
- **Non-repeating repository**: Each question is asked once until all are used.
- **Intelligent repository**: Each question is asked once until all are used, then questions which you answered incorrectly are repeated.

## Question Types

- **Single Choice**: Only one correct answer.
- **Multiple Choice**: Multiple correct answers, partial credit possible.
- **Negative Score Multiple Choice**: Incorrect answers reduce your score.

## Creating a Repository

1. Go to **Repository > New repository**.
2. Choose a location and type.
3. Add questions using the **Questions > Manage Questions** menu.

## License

This project is mainly licensed under the MIT License, with some parts licensed under GNU Lesser General Public License (LGPL) version 3. See [LICENSE](LICENSE) for details.
