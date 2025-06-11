#include <iostream>
#include "repository.hpp"

int main(int, char **)
{
    fq::Repository *repository = fq::Repository::createRepository("questions.json");
    return 0;
}
