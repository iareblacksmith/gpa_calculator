// validate number of credit hours???
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <regex>
#include <limits>

struct Subject
{
    std::string letter_grade;
    std::string old_letter_grade;
    float number_grade;
    float old_number_grade;
    int credit_hours;
    float grade_points;
    float old_grade_points;
    bool repeated;
};

std::regex letter("(?![AFaf][+]|[Ff][-])[A-Da-dFf][-+]?");
std::regex yesorno("[NnYy]");

template <typename T>
void input_validation(T &, T, T);

class Gpa_Calculator
{
public:
    Gpa_Calculator();
    ~Gpa_Calculator();

    void title_screen(); // just the title screen
    void calculate_grade_points(Subject[]);
    void calculate_semester_gpa();
    void calculate_new_gpa();
    void get_evaluation();
    void userset_variables(); // userset nos, cumh, cumgpa
    void fileset_variables(); // fileset nos, cumh, cumgpa
    void print();

    void run();
    void file_run();

private:
    std::ifstream inputFile;
    Subject subjects[100];
    int number_of_subjects, cumulative_hours;
    float grade_points_total, cumulative_gpa, new_gpa, semester_gpa;
    std::string evaluation;
};