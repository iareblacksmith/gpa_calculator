#include <iostream>
#include <string>

using namespace std;

int main()
{
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

    cout << "what is your cumulative GPA? ";
    cin >> cumGPA;
    cout << "cumulative hours? ";
    cin >> cumHours;
    cout << "how many subjects are you calculating? ";
    cin >> num_of_subjects;

    string subjectLetter[num_of_subjects];
    int subjectCredit[num_of_subjects];

    for (int i = 0; i < num_of_subjects; i++)
    {
        cout << "enter subject No." << i + 1 << " letter: ";
        cin >> subjectLetter[i];
        while (subjectLetter[i] != "A" &&
               subjectLetter[i] != "A-" &&
               subjectLetter[i] != "B+" &&
               subjectLetter[i] != "B" &&
               subjectLetter[i] != "B-" &&
               subjectLetter[i] != "C+" &&
               subjectLetter[i] != "C" &&
               subjectLetter[i] != "C-" &&
               subjectLetter[i] != "D+" &&
               subjectLetter[i] != "D" &&
               subjectLetter[i] != "D-" &&
               subjectLetter[i] != "F")
        {
            cout << "you entered an invalid letter, try again. ";
            cin >> subjectLetter[i];
        }
        cout << "enter subject No." << i + 1 << " credit hours: ";
        cin >> subjectCredit[i];
        cout << "***********************\n";
    }

    float subjectValue[num_of_subjects];

    for (int i = 0; i < num_of_subjects; i++)
    {
        for (int i = 0; i < num_of_subjects; i++)
        {
            switch (subjectLetter[i][0])
            {
            case 'A':
                subjectValue[i] = 4.0;
                break;
            case 'B':
                subjectValue[i] = 3.0;
                break;
            case 'C':
                subjectValue[i] = 2.0;
                break;
            case 'D':
                subjectValue[i] = 1.0;
                break;
            case 'F':
                subjectValue[i] = 0.0;
                break;
            default:
                cout << "you entered goofy letter, quitting program";
                return 0;
                break;
            }
        }
    }

    for (int i = 0; i < num_of_subjects; i++)
    {
        switch (subjectLetter[i][1])
        {
        case '+':
            subjectValue[i] += 0.25;
            break;
        case '-':
            subjectValue[i] -= 0.25;
            break;
        default:
            break;
        }
    }

    float weightedValues[num_of_subjects];

    for (int i = 0; i < num_of_subjects; i++)
    {
        weightedValues[i] = subjectValue[i] * subjectCredit[i];
    }

    float weightedValuesSum = 0.0;

    for (int i = 0; i < num_of_subjects; i++)
    {
        weightedValuesSum += weightedValues[i];
    }

    weightedValuesSum += cumGPA * cumHours;

    int creditSum = 0;

    for (int i = 0; i < num_of_subjects; i++)
    {
        creditSum += subjectCredit[i];
    }

    int finalWeight = creditSum + cumHours;

    cout << "your old stinky GPA = " << cumGPA << "\n";
    cout << "your new shiny GPA = " << weightedValuesSum / finalWeight << "\n";

    return 0;
}

/*
 ██████  ██████   █████       ██████  █████  ██       ██████ ██    ██ ██       █████  ████████  ██████  ██████
██       ██   ██ ██   ██     ██      ██   ██ ██      ██      ██    ██ ██      ██   ██    ██    ██    ██ ██   ██
██   ███ ██████  ███████     ██      ███████ ██      ██      ██    ██ ██      ███████    ██    ██    ██ ██████
██    ██ ██      ██   ██     ██      ██   ██ ██      ██      ██    ██ ██      ██   ██    ██    ██    ██ ██   ██
 ██████  ██      ██   ██      ██████ ██   ██ ███████  ██████  ██████  ███████ ██   ██    ██     ██████  ██   ██
*/