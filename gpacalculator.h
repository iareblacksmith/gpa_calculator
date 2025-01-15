// validate number of credit hours???
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <regex>

struct Subject
{
    std::string letter_grade;
    std::string old_letter_grade;
    float number_grade;
    float old_number_grade;
    int credit_hours;
    float grade_points;
    bool repeated;
};

std::regex letter("(?![AFaf][+]|[Ff][-])[A-Da-dFf][-+]?");
std::regex repeated_regex("[NnYy]");

class Gpa_Calculator
{
public:
    Gpa_Calculator();
    ~Gpa_Calculator();

    void title_screen();              // just the title screen
    void userset_initial_variables(); // userset nos, cumh, cumgpa
    void fileset_initial_variables(); // fileset nos, cumh, cumgpa
    void calculate_grade_points(Subject[]);
    void update_gpa_repeated(); // take out grade points of repeated subjects
    void calculate_semester_gpa();
    void calculate_new_gpa();
    void print();

    void run();

private:
    std::ifstream inputFile;
    Subject subjects[100];
    int number_of_subjects, cumulative_hours;
    float grade_points_total, cumulative_gpa, new_gpa, semester_gpa;
    std::string evaluation;
};

Gpa_Calculator::Gpa_Calculator()
{
    inputFile.close();
    number_of_subjects = 0;
    cumulative_hours = 0;
    grade_points_total = 0.0;
    cumulative_gpa = 0.0;
    new_gpa = 0.0;
    semester_gpa = 0.0;
    evaluation = "null";
}

Gpa_Calculator::~Gpa_Calculator()
{
}

void Gpa_Calculator::title_screen()
{
    std::cout << " ██████  ██████   █████       ██████  █████  ██       ██████ "
              << "██    ██ ██       █████  ████████  ██████  ██████\n"
              << "██       ██   ██ ██   ██     ██      ██   ██ ██      ██      "
              << "██    ██ ██      ██   ██    ██    ██    ██ ██   ██\n"
              << "██   ███ ██████  ███████     ██      ███████ ██      ██      "
              << "██    ██ ██      ███████    ██    ██    ██ ██████\n"
              << "██    ██ ██      ██   ██     ██      ██   ██ ██      ██      "
              << "██    ██ ██      ██   ██    ██    ██    ██ ██   ██\n"
              << " ██████  ██      ██   ██      ██████ ██   ██ ███████  ██████ "
              << " ██████  ███████ ██   ██    ██     ██████  ██   ██\n";

    std::cout << "**************************************************************"
              << "*************************************************\n\n";
}

void Gpa_Calculator::userset_initial_variables()
{
    std::cout << "what is your cumulative GPA? ";
    std::cin >> cumulative_gpa;
    std::cout << "\ncumulative hours? ";
    std::cin >> cumulative_hours;
    std::cout << "\nhow many subjects are you calculating? ";
    std::cin >> number_of_subjects;

    for (int i = 0; i < number_of_subjects; i++)
    {
        std::cout << "\n***********************\n\n";

        std::cout << "enter subject (" << i + 1 << ") letter: ";
        std::cin >> subjects[i].letter_grade;
        while (!regex_match(subjects[i].letter_grade, letter))
        {
            std::cout << "invalid input, please try again... ";
            std::cin >> subjects[i].letter_grade;
        }

        // -----------------------

        std::cout << "enter subject (" << i + 1 << ") credit hours: ";
        std::cin >> subjects[i].credit_hours;

        // -----------------------

        std::string input_repeated;
        std::cout << "subject (" << i + 1 << ") repeated (y, n)? ";
        std::cin >> input_repeated;
        while (!regex_match(input_repeated, repeated_regex))
        {
            std::cout << "invalid input, please try again... ";
            std::cin >> input_repeated;
        }
        if (input_repeated == "y" || input_repeated == "Y")
        {
            subjects[i].repeated = true;
        }
        else
        {
            subjects[i].repeated = false;
        }

        // -----------------------

        // THERE HAS TO BE A MORE EFFICIENT WAYYYY
        // can you repeat a function but for a different parameter?
        if (subjects[i].repeated)
        {
            std::cout << "enter subject (" << i + 1 << ") repeated repeated grade: ";
            std::cin >> subjects[i].old_letter_grade;
            while (!regex_match(subjects[i].old_letter_grade, letter))
            {
                std::cout << "invalid input, please try again... ";
                std::cin >> subjects[i].old_letter_grade;
            }
        }

        // -----------------------
    }
}

void Gpa_Calculator::fileset_initial_variables()
{
    inputFile.open("gpa.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "gpa.txt could not be opened!\n";
        return;
    }

    inputFile >> cumulative_gpa;
    inputFile >> cumulative_hours;
    inputFile >> number_of_subjects;

    for (int i = 0; i < number_of_subjects; i++)
    {
        inputFile >> subjects[i].letter_grade;
        if (!regex_match(subjects[i].letter_grade, letter))
        {
            std::cerr << "error when reading file\n";
            return;
        }

        // -----------------------

        inputFile >> subjects[i].credit_hours;

        // -----------------------

        std::string input_repeated;
        inputFile >> input_repeated;
        if (!regex_match(input_repeated, repeated_regex))
        {
            std::cerr << "error when reading file\n";
            return;
        }

        if (input_repeated == "y" || input_repeated == "Y")
        {
            subjects[i].repeated = true;
        }
        else
        {
            subjects[i].repeated = false;
        }

        // -----------------------

        if (subjects[i].repeated)
        {
            inputFile >> subjects[i].old_letter_grade;
            if (!regex_match(subjects[i].old_letter_grade, letter))
            {
                std::cerr << "error when reading file\n";
                return;
            }
        }
    }

    inputFile.close();
}

void Gpa_Calculator::calculate_grade_points(Subject subjects[])
{
    // TRANSLATE STRING INTO FLOAT
    for (int i = 0; i < number_of_subjects; i++)
    {

        switch (subjects[i].letter_grade[0])
        {
        case 'a':
        case 'A':
            subjects[i].number_grade = 4.0;
            break;
        case 'b':
        case 'B':
            subjects[i].number_grade = 3.0;
            break;
        case 'c':
        case 'C':
            subjects[i].number_grade = 2.0;
            break;
        case 'd':
        case 'D':
            subjects[i].number_grade = 1.0;
            break;
        case 'f':
        case 'F':
            subjects[i].number_grade = 0.0;
            break;
        default:
            std::cerr << "you entered goofy letter, quitting program\n";
            return;
        }

        /*incrementing and decrementing by 0.25
        based on second letter of string*/
        // this is kinda fucked up but
        if (subjects[i].letter_grade.length() == 2)
        {
            switch (subjects[i].letter_grade[1])
            {
            case '+':
                subjects[i].number_grade += 0.50;
                break;
            case '-':
                subjects[i].number_grade -= 0.25;
                break;
            default:
                break;
            }
        }

        // -----------------------

        switch (subjects[i].old_letter_grade[0])
        {
        case 'a':
        case 'A':
            subjects[i].old_number_grade = 4.0;
            break;
        case 'b':
        case 'B':
            subjects[i].old_number_grade = 3.0;
            break;
        case 'c':
        case 'C':
            subjects[i].old_number_grade = 2.0;
            break;
        case 'd':
        case 'D':
            subjects[i].old_number_grade = 1.0;
            break;
        case 'f':
        case 'F':
            subjects[i].old_number_grade = 0.0;
            break;
        default:
            std::cerr << "you entered goofy letter, quitting program\n";
            return;
        }

        /*incrementing and decrementing by 0.25
        based on second letter of string*/
        if (subjects[i].old_letter_grade.length() == 2)
        {
            switch (subjects[i].old_letter_grade[1])
            {
            case '+':
                subjects[i].old_number_grade += 0.50;
                break;
            case '-':
                subjects[i].old_number_grade -= 0.25;
                break;
            default:
                break;
            }
        }
        subjects[i].grade_points = subjects[i].old_number_grade
    }
}

void Gpa_Calculator::update_gpa_repeated()
{
}

void Gpa_Calculator::calculate_semester_gpa()
{
}

void Gpa_Calculator::calculate_new_gpa()
{
}

void Gpa_Calculator::print()
{
}

void Gpa_Calculator::run()
{
}
