#pragma once
#include <string>
#include <fstream>
#include <regex>

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

template <typename T>
void input_validation(T &, T, T);

class Gpa_Calculator
{
public:
    Gpa_Calculator();
    ~Gpa_Calculator();

    void title_screen();
    void title_screen();
    void calculate_grade_points(Subject[]);
    void calculate_semester_gpa();
    void calculate_new_gpa();
    void get_evaluation();
    void userset_variables();
    void fileset_variables();
    void userset_variables();
    void fileset_variables();
    void print();

    void run();
    void file_run();

private:
    std::ifstream inputFile;
    Subject subjects[100];
    int number_of_subjects, cumulative_hours;
    float grade_points_total, cumulative_gpa, new_gpa, semester_gpa;
    std::string evaluation;
    std::unordered_map<std::string, float> grade_map =
        {
            {"A", 4.00f},
            {"A-", 3.75f},
            {"B+", 3.50f},
            {"B", 3.00f},
            {"B-", 2.75f},
            {"C+", 2.50f},
            {"C", 2.00f},
            {"C-", 1.75f},
            {"D+", 1.50f},
            {"D", 1.00f},
            {"D-", 0.75f},
            {"F", 0.00f},
    };
};