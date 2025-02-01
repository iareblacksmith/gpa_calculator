#include "gpa_calculator.h"
#include <iostream>
#include <iomanip>
#include <limits>

std::regex letter("^[A-Da-d][-+]?|[Ff]$");
std::regex yesorno("^[YyNn]$");

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

void Gpa_Calculator::calculate_grade_points(Subject subjects[])
{
    for (int i = 0; i < number_of_subjects; i++)
    {
        if (subjects[i].repeated)
        {

            grade_points_total -= subjects[i].old_grade_points;
            cumulative_hours -= subjects[i].credit_hours;
        }

        subjects[i].number_grade = grade_map[subjects[i].letter_grade];
        /*adding grade points of subjects to the total
        and credit hours to cumulative hours*/
        subjects[i].grade_points = subjects[i].number_grade * subjects[i].credit_hours;
        grade_points_total += subjects[i].grade_points;
        cumulative_hours += subjects[i].credit_hours;
    }
}

void Gpa_Calculator::calculate_semester_gpa()
{
    float semester_grade_points = 0;
    int semester_credit_hours = 0;
    for (int i = 0; i < number_of_subjects; i++)
    {
        semester_grade_points += subjects[i].grade_points;
        semester_credit_hours += subjects[i].credit_hours;
    }
    semester_gpa = semester_grade_points / semester_credit_hours;
}

void Gpa_Calculator::calculate_new_gpa()
{
    new_gpa = grade_points_total / cumulative_hours;
}

void Gpa_Calculator::get_evaluation()
{

    if (new_gpa >= 1.0 && new_gpa < 2)
    {
        evaluation = "weak";
    }
    else if (new_gpa >= 2 && new_gpa < 2.5)
    {
        evaluation = "okay";
    }
    else if (new_gpa >= 2.5 && new_gpa < 3)
    {
        evaluation = "good";
    }
    else if (new_gpa >= 3 && new_gpa < 3.65)
    {
        evaluation = "very good";
    }
    else if (new_gpa >= 3.65 && new_gpa <= 4.0)
    {
        evaluation = "excellent";
    }
    else
    {
        evaluation = "null";
    }
}

void Gpa_Calculator::userset_variables()
{
    std::cout << "what is your cumulative GPA? ";
    input_validation(cumulative_gpa, 0.0f, 4.0f);
    std::cout << "\ncumulative hours? ";
    input_validation(cumulative_hours, 0, 200);
    std::cout << "\nhow many subjects are you calculating? ";
    input_validation(number_of_subjects, 1, 100);

    grade_points_total = cumulative_gpa * cumulative_hours;

    for (int i = 0; i < number_of_subjects; i++)
    {
        std::cout << "\n***********************\n\n";

        std::cout << "enter subject (" << i + 1 << ") letter: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, subjects[i].letter_grade);
        while (!regex_match(subjects[i].letter_grade, letter))
        {
            std::cout << "invalid input, please try again... ";
            getline(std::cin, subjects[i].letter_grade);
        }
        subjects[i].letter_grade = std::toupper(subjects[i].letter_grade[0]);

        // -----------------------

        std::cout << "enter subject (" << i + 1 << ") credit hours: ";
        input_validation(subjects[i].credit_hours, 0, 6);

        // -----------------------

        std::string input_repeated;
        std::cout << "is subject (" << i + 1 << ") repeated (y, n)? ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, subjects[i].letter_grade);
        ////////////// LEFT OFF HERE
        while (!regex_match(input_repeated, yesorno))
        {
            std::cout << "invalid input, please try again... ";
            std::cin >> input_repeated;
        }

        subjects[i].repeated = (std::tolower(input_repeated[0]) == 'y');

        // -----------------------

        // THERE HAS TO BE A MORE EFFICIENT WAYYYY
        // can you repeat a function but for a different parameter?
        if (subjects[i].repeated)
        {
            std::cout << "enter repeated subject (" << i + 1 << ") old grade: ";
            std::cin >> subjects[i].old_letter_grade;
            while (!regex_match(subjects[i].old_letter_grade, letter))
            {
                std::cout << "invalid input, please try again... ";
                std::cin >> subjects[i].old_letter_grade;
            }
            subjects[i].old_letter_grade = std::toupper(subjects[i].old_letter_grade[0]);
        }
    }

    calculate_grade_points(subjects);

    calculate_semester_gpa();

    calculate_new_gpa();

    get_evaluation();
}

void Gpa_Calculator::fileset_variables()
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

    grade_points_total = cumulative_gpa * cumulative_hours;

    for (int i = 0; i < number_of_subjects; i++)
    {

        inputFile >> subjects[i].letter_grade;
        if (!regex_match(subjects[i].letter_grade, letter))
        {
            std::cerr << "error when reading file, exiting function\n";
            return;
        }

        // -----------------------

        inputFile >> subjects[i].credit_hours;

        // -----------------------

        std::string input_repeated;
        inputFile >> input_repeated;

        if (!regex_match(input_repeated, yesorno))
        {
            std::cerr << "error when reading file, exiting function\n";
            return;
        }

        if (input_repeated == "y" || input_repeated == "Y")
        {
            subjects[i].repeated = true;
        }
        else if (input_repeated == "n" || input_repeated == "N")
        {
            subjects[i].repeated = false;
        }
        else
        {
            std::cerr << "wtf? how did you get passed the regex?";
            return;
        }

        // -----------------------

        // THERE HAS TO BE A MORE EFFICIENT WAYYYY
        // can you repeat a function but for a different parameter?
        if (subjects[i].repeated)
        {
            inputFile >> subjects[i].old_letter_grade;
            if (!regex_match(subjects[i].old_letter_grade, letter))
            {
                std::cerr << "error when reading file, exiting function\n";
                return;
            }
        }

        // -----------------------
    }
    inputFile.close();

    calculate_grade_points(subjects);

    calculate_semester_gpa();

    calculate_new_gpa();

    get_evaluation();
}

void Gpa_Calculator::print()
{
    std::cout << "\n-----------------------";
    std::cout << "\nyour semester GPA = " << std::setprecision(4) << semester_gpa << "\n";
    std::cout << "\nyour old cumulative GPA = " << cumulative_gpa << "\n";
    std::cout << "\nyour new cumulative GPA = " << std::setprecision(4) << new_gpa << "\n";
    std::cout << "\nevaluation: " << evaluation << "\n";
    std::cout << "-----------------------\n\n";
}

void Gpa_Calculator::run()
{
    title_screen();
    userset_variables();
    print();
}

void Gpa_Calculator::file_run()
{
    title_screen();
    fileset_variables();
    print();
}

template <typename T>
void input_validation(T &variable, T lower, T upper)
{
    while (!((std::cin >> variable) && (variable >= lower) && (variable <= upper)))
    {
        std::cout << "invalid input, please try again (" << lower << "-" << upper << "): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}