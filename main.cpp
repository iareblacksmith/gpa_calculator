#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

ifstream FileGpa("gpa.txt");

void getInitialVariables(float &, int &, int &);
void getLetterCredit(string[], int[], int);
void calcSubjectValue(float[], string[], int);
void calcWeightedValues(float[], float[], int[], int);
void sum(float &, float[], int);
void intSum(int &, int[], int);
void getEvaluation(string &, float);
void print(float, float, float, string);

int main()
{
    // title screen
    cout << " ██████  ██████   █████       ██████  █████  ██       ██████ "
         << "██    ██ ██       █████  ████████  ██████  ██████\n"
         << "██       ██   ██ ██   ██     ██      ██   ██ ██      ██      "
         << "██    ██ ██      ██   ██    ██    ██    ██ ██   ██\n"
         << "██   ███ ██████  ███████     ██      ███████ ██      ██      "
         << "██    ██ ██      ███████    ██    ██    ██ ██████\n"
         << "██    ██ ██      ██   ██     ██      ██   ██ ██      ██      "
         << "██    ██ ██      ██   ██    ██    ██    ██ ██   ██\n"
         << " ██████  ██      ██   ██      ██████ ██   ██ ███████  ██████ "
         << " ██████  ███████ ██   ██    ██     ██████  ██   ██\n";

    cout << "**************************************************************"
         << "*************************************************\n\n";

    int num_of_subjects = 0, cumHours = 0;
    float cumGPA = 0.0;

    getInitialVariables(cumGPA, cumHours, num_of_subjects);

    // declaring arrays based on user input
    string subjectLetter[num_of_subjects];
    int subjectCredit[num_of_subjects];

    getLetterCredit(subjectLetter, subjectCredit, num_of_subjects);

    /*calculating subject values
    based on first letter of string*/
    float subjectValue[num_of_subjects];

    calcSubjectValue(subjectValue, subjectLetter, num_of_subjects);

    // calculating weighted values
    float weightedValues[num_of_subjects];
    calcWeightedValues(weightedValues, subjectValue, subjectCredit, num_of_subjects);

    // summing up weighted values
    float weightedValuesSum = 0.0;
    sum(weightedValuesSum, weightedValues, num_of_subjects);

    // adding initial weighted value
    float finalWeightedValuesSum = weightedValuesSum + cumGPA * cumHours;

    // summing up the weight
    int creditSum = 0;
    intSum(creditSum, subjectCredit, num_of_subjects);

    // adding cumulative hours to credit sum to get final weight
    int finalWeight = creditSum + cumHours;

    // calculating new cumGPA
    float newCumGPA = finalWeightedValuesSum / finalWeight;

    // calculating semester GPA
    float semesterGPA = weightedValuesSum / creditSum;

    // getting evaluation
    string evaluation;
    getEvaluation(evaluation, newCumGPA);

    // final output
    print(semesterGPA, cumGPA, newCumGPA, evaluation);

    return 0;
}

// **********************************
// **********************************
// *********IMPLEMENTATION***********
// **********************************
// **********************************

void getInitialVariables(float &cgpa, int &chours, int &numofsub)
{
    // getting initial info from user
    cout << "what is your cumulative GPA? ";
    cin >> cgpa;
    cout << "\ncumulative hours? ";
    cin >> chours;
    cout << "\nhow many subjects are you calculating? ";
    cin >> numofsub;
}

void getLetterCredit(string sl[], int sc[], int numofsub)
{
    // getting arrays values
    for (int i = 0; i < numofsub; i++)
    {
        cout << "\n***********************\n\n";
        cout << "enter subject No." << i + 1 << " letter: ";
        cin >> sl[i];
        while (sl[i] != "A" &&
               sl[i] != "A-" &&
               sl[i] != "B+" &&
               sl[i] != "B" &&
               sl[i] != "B-" &&
               sl[i] != "C+" &&
               sl[i] != "C" &&
               sl[i] != "C-" &&
               sl[i] != "D+" &&
               sl[i] != "D" &&
               sl[i] != "D-" &&
               sl[i] != "F")
        {
            cout << "you entered an invalid letter, try again. ";
            cin >> sl[i];
        }
        cout << "enter subject No." << i + 1 << " credit hours: ";
        cin >> sc[i];
    }
}

void calcSubjectValue(float sv[], string sl[], int numofsub)
{
    for (int i = 0; i < numofsub; i++)
    {
        for (int i = 0; i < numofsub; i++)
        {
            switch (sl[i][0])
            {
            case 'A':
                sv[i] = 4.0;
                break;
            case 'B':
                sv[i] = 3.0;
                break;
            case 'C':
                sv[i] = 2.0;
                break;
            case 'D':
                sv[i] = 1.0;
                break;
            case 'F':
                sv[i] = 0.0;
                break;
            default:
                cout << "you entered goofy letter, quitting program";
                break;
            }
        }
    }

    /*incrementing and decrementing by 0.25
    based on second letter of string*/
    for (int i = 0; i < numofsub; i++)
    {
        switch (sl[i][1])
        {
        case '+':
            sv[i] += 0.25;
            break;
        case '-':
            sv[i] -= 0.25;
            break;
        default:
            break;
        }
    }
}

void calcWeightedValues(float wv[], float sv[], int sc[], int numofsub)
{
    for (int i = 0; i < numofsub; i++)
    {
        wv[i] = sv[i] * sc[i];
    }
}

void sum(float &sum, float arr[], int numofsub)
{
    for (int i = 0; i < numofsub; i++)
    {
        sum += arr[i];
    }
}

void intSum(int &sum, int arr[], int numofsub)
{
    for (int i = 0; i < numofsub; i++)
    {
        sum += arr[i];
    }
}

void getEvaluation(string &eva, float ncgpa)
{
    if (ncgpa >= 1.0 && ncgpa < 2)
    {
        eva = "weak";
    }
    else if (ncgpa >= 2 && ncgpa < 2.5)
    {
        eva = "okay";
    }
    else if (ncgpa >= 2.5 && ncgpa < 3)
    {
        eva = "good";
    }
    else if (ncgpa >= 3 && ncgpa < 3.65)
    {
        eva = "very good";
    }
    else if (ncgpa >= 3.65 && ncgpa <= 4.0)
    {
        eva = "excellent";
    }
    else
    {
        eva = "null";
    }
}

void print(float sgpa, float cgpa, float ncgpa, string eva)
{
    cout << "\n***********************\n\n-----------------------";
    cout << "\nyour semester GPA = " << setprecision(4) << sgpa << "\n";
    cout << "\nyour old stinky cumulative GPA = " << cgpa << "\n";
    cout << "\nyour new shiny cumulative GPA = " << setprecision(4) << ncgpa << "\n";
    cout << "\nevaluation: " << eva << "\n";
    cout << "-----------------------\n\n";
}
/*
 ██████  ██████   █████       ██████  █████  ██       ██████ ██    ██ ██       █████  ████████  ██████  ██████
██       ██   ██ ██   ██     ██      ██   ██ ██      ██      ██    ██ ██      ██   ██    ██    ██    ██ ██   ██
██   ███ ██████  ███████     ██      ███████ ██      ██      ██    ██ ██      ███████    ██    ██    ██ ██████
██    ██ ██      ██   ██     ██      ██   ██ ██      ██      ██    ██ ██      ██   ██    ██    ██    ██ ██   ██
 ██████  ██      ██   ██      ██████ ██   ██ ███████  ██████  ██████  ███████ ██   ██    ██     ██████  ██   ██
*/