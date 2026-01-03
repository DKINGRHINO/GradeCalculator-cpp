/*============================================================================
 |       Author:  Christopher Otto
 |     Language:  c++
 |   To Compile:  g++ gc.cpp -o "Grade Calculator"
 |   To Execute:  c++    -> ./"Grade Calculator"
 +===========================================================================*/

// Preprocessor directives
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

// Prototypes
void basicGradeCalculator();
int basicGradeCalcMenuSys(int numCategories, double ** grades, double * categoryWeights, std::string * categoryNames);
void updateCategoryGrades(std::string ** assignmentNames, double ** grades, double ** perfectGrades, int menuChoice, std::string * categoryNames, int * numGrades, int numCategories);

// Function definitions
int main()
{
    basicGradeCalculator();

    return 0;
}

// Create all required variables, prompt user for input, and calculate grade and what ifs
void basicGradeCalculator()
{
    int numCategories;
    double gradeCalculation = 0;
    double categoryGradeCalculationNumerator = 0;
    double categoryGradeCalculationDenominator = 0;

    // Ask user for the number of grade categories
    std::cout << "Enter the number of categories (i.e., tests are 20%, hw is 80%, so there are 2 categories): ";

    // Get input from user
    while(!(std::cin >> numCategories))
    {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
        std::cout << "Invalid input! Try again: "; // Prompt user to try again
    }

    // Dynamically allocate memory for an array of arrays of double values for grades
    double ** grades = nullptr;
    grades = new double * [numCategories];

    double ** perfectGrades = nullptr;
    perfectGrades = new double * [numCategories];

    int * numGrades = new int [numCategories];

    // Dynamically allocate memory for arrays of strings to keep track of the names
    std::string ** assignmentNames = nullptr;
    assignmentNames = new std::string * [numCategories];

    std::string * categoryNames = nullptr;
    categoryNames = new std::string[numCategories];

    for(int i = 0; i < numCategories; ++i)
    {
        grades[i] = nullptr;
        perfectGrades[i] = nullptr;
        assignmentNames[i] = nullptr;
        numGrades[i] = 0;
    }

    // Dynamically allocate memory for an array of doubles to hold the category weights
    double * categoryWeights = nullptr;
    categoryWeights = new double[numCategories];

    // Ask user for the names of each category
    std::cout << "Enter each category name (one word) (no spaces), then press enter (enter them separately):" << std::endl;

    std::string curStringName;

    // Get names of each category from user
    for(int i = 0; i < numCategories; ++i)
    {
        std::cin >> curStringName;
        categoryNames[i] = curStringName;
    }

    std::cout << std::endl; // Formatting space

    // Ask user for the weights of each category
    std::cout << "Enter the double percentage weights of each category respectively (enter them separately) (e.g., input = \"20.5\" to represent 20.5%, then press enter and enter the next percentage)." << std::endl;
    std::cout << "Ensure they add up to 100%" << std::endl;

    // Get weights for each category from user as doubles
    for(int i = 0; i < numCategories; ++i)
    {
        while(!(std::cin >> categoryWeights[i]))
        {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input! Try again: "; // Prompt user to try again
        }
    }

    std::cout << std::endl; // Formatting space

    int menuChoice = 0;

    while(menuChoice != numCategories + 1) // While choice is not exit
    {
        // Display the menu and save the returned choice
        menuChoice = basicGradeCalcMenuSys(numCategories, grades, categoryWeights, categoryNames);

        // Break out of loop now if choice is to exit
        if(menuChoice == numCategories + 1) break;

        if(menuChoice == numCategories) // Calculate grade percentage based on grades entered
        {
            std::cout << "-----------------------------------------" << std::endl; // Formatting bar

            // Reset for new calculation
            gradeCalculation = 0;

            // Compute the percentage grade based on current grades for all categories
            for(int curCategory = 0; curCategory < numCategories; ++curCategory)
            {
                // Reset for new calculation
                categoryGradeCalculationNumerator = 0;
                categoryGradeCalculationDenominator = 0;

                // The summation of all the numerators and the summation of all the denominators is saved
                for(int curGrade = 0; curGrade < numGrades[curCategory]; ++curGrade)
                {
                    categoryGradeCalculationNumerator += grades[curCategory][curGrade];
                    categoryGradeCalculationDenominator += perfectGrades[curCategory][curGrade];
                }

                // Increment grade calculation by category contribution if there are grade(s)
                if(numGrades[curCategory] != 0)
                    gradeCalculation += categoryGradeCalculationNumerator / categoryGradeCalculationDenominator * categoryWeights[curCategory];
            }

            // Display calculated grade
            std::cout << "Grade: " << std::fixed << std::setprecision(2) << gradeCalculation << "%" << std::endl;

            std::cout << "-----------------------------------------" << std::endl; // Formatting bar
            std::cout << std::endl; // Formatting space
        }
        else // Add, remove, or edit grades in a category
        {
            updateCategoryGrades(assignmentNames, grades, perfectGrades, menuChoice, categoryNames, numGrades, numCategories);
        }
    }

    // Delete allocated memory
    for(int curCategory = 0; curCategory < numCategories; ++curCategory)
    {
        delete[] grades[curCategory];
        delete[] perfectGrades[curCategory];
        delete[] assignmentNames[curCategory];
    }

    delete[] grades;
    delete[] perfectGrades;
    delete[] assignmentNames;
    delete[] numGrades;
    delete[] categoryNames;
    delete[] categoryWeights;
}

// Print a menu of all categories and support going into each category and changing grades and weight percentage
int basicGradeCalcMenuSys(int numCategories, double ** grades, double * categoryWeights, std::string * categoryNames)
{
    int menuChoice = 0;

    std::cout << "-----------------------------------------" << std::endl; // Formatting bar

    // Select an option by entering the corresponding number
    std::cout << "Select an option by entering the corresponding number" << std::endl;

    std::cout << std::endl; // Formatting space

    // Display the category names and percentages in the menu
    for(int categoryNum = 1; categoryNum <= numCategories; ++categoryNum)
    {
        std::cout << "  " << categoryNum << ". " << categoryNames[categoryNum - 1] << " (" << categoryWeights[categoryNum - 1] << "%)" << std::endl;
    }

    std::cout << "  " << numCategories + 1 << ". " << "Calculate grades based on current information" << std::endl;
    std::cout << "  " << numCategories + 2 << ". " << "Exit program" << std::endl;

    std::cout << "-----------------------------------------" << std::endl; // Formatting bar

    // Prompt user to give menu choice
    std::cout << "Enter an integer: ";
    
    // Get menu choice from user
    while(!(std::cin >> menuChoice))
    {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
        std::cout << "Invalid input! Try again: "; // Prompt user to try again
    }

    // On final program exit, no space
    if(menuChoice != numCategories + 2)
    {
        std::cout << std::endl; // Formatting space
    }

    return --menuChoice;
}

// Add, remove, and edit grades of a category
void updateCategoryGrades(std::string ** assignmentNames, double ** grades, double ** perfectGrades, int menuChoice, std::string * categoryNames, int * numGrades, int numCategories)
{
    // Menu choices
    int categoryMenuChoice = 0;
    int gradeMenuChoice = 0;
    char gradeMenuCharChoice;

    // For use in changing grades
    double * newGrades = nullptr;
    double * newPerfectGrades = nullptr;
    std::string * newAssignmentNames = nullptr;

    // While choice is not to exit menu
    while(categoryMenuChoice != 4)
    {
        // Display grades in a formatted way
        std::cout << "-----------------------------------------" << std::endl; // Formatting bar
        std::cout << "Grades for " << categoryNames[menuChoice] << ":" << std::endl;

        if(numGrades[menuChoice] == 0)
        {
            std::cout << "You have no grades here yet" << std::endl;
        }
        else
        {
            // Display each grade
            for(int i = 0; i < numGrades[menuChoice]; ++i)
            {
                std::cout << "  " << i + 1 << ". " << assignmentNames[menuChoice][i] << " - " << grades[menuChoice][i] << " out of " << perfectGrades[menuChoice][i] 
                << " = " << std::fixed << std::setprecision(2) << grades[menuChoice][i] / perfectGrades[menuChoice][i] * 100 << "%" << std::endl;
            }
        }

        std::cout << "-----------------------------------------" << std::endl; // Formatting bar
        std::cout << std::endl; // Formatting space

        // Choice menu
        std::cout << "-----------------------------------------" << std::endl; // Formatting bar
        std::cout << "Select an option by entering the corresponding number" << std::endl; // Menu prompt
        std::cout << " " << std::endl; // Formatting space

        std::cout << "  " << 1 << ". " << "Add grade" << std::endl;
        std::cout << "  " << 2 << ". " << "Remove grade" << std::endl;
        std::cout << "  " << 3 << ". " << "Edit grade" << std::endl;
        std::cout << "  " << 4 << ". " << "Exit menu" << std::endl;

        std::cout << "-----------------------------------------" << std::endl; // Formatting bar

        // Prompt user to give menu choice
        std::cout << "Enter and integer: ";
    
        // Get menu choice from user
        while(!(std::cin >> categoryMenuChoice))
        {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input! Try again: "; // Prompt user to try again
        }

        std::cout << std::endl; // Formatting space
        
        if(categoryMenuChoice != 4) // Not exiting menu
        {
            if(categoryMenuChoice == 1) // Add a grade
            {
                // Allocate space for new arrays of grades
                newGrades = new double [numGrades[menuChoice] + 1];
                newPerfectGrades = new double [numGrades[menuChoice] + 1];
                newAssignmentNames = new std::string [numGrades[menuChoice] + 1];

                // Copy the old arrays to the new ones
                for(int i = 0; i < numGrades[menuChoice]; ++i)
                {
                    newGrades[i] = grades[menuChoice][i];
                    newPerfectGrades[i] = perfectGrades[menuChoice][i];
                    newAssignmentNames[i] = assignmentNames[menuChoice][i];
                }

                // Prompt the user to enter the assignment name
                std::cout << "Enter the assignment name (no spaces): ";
                std::cin >> newAssignmentNames[numGrades[menuChoice]];

                // Prompt the user for the score
                std::cout << "Enter the score as a double (i.e., if x / y * 100 = z%, what is x): ";

                // Get the score from the user
                while(!(std::cin >> newGrades[numGrades[menuChoice]]))
                {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                std::cout << "Invalid input! Try again: "; // Prompt user to try again
                }

                // Prompt the user for the perfect score
                std::cout << "Enter the perfect score as a double (i.e., if x / y * 100 = z%, what is y): ";

                // Get the perfect score from the user
                while(!(std::cin >> newPerfectGrades[numGrades[menuChoice]]))
                {
                    std::cin.clear(); // clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                    std::cout << "Invalid input! Try again: "; // Prompt user to try again
                }

                // Delete old grade arrays
                delete[] grades[menuChoice];
                delete[] perfectGrades[menuChoice];
                delete[] assignmentNames[menuChoice];
                
                // Reassign old grade arrays
                grades[menuChoice] = newGrades;
                perfectGrades[menuChoice] = newPerfectGrades;
                assignmentNames[menuChoice] = newAssignmentNames;

                // Set newGrade arrays to null again
                newGrades = nullptr;
                newPerfectGrades = nullptr;
                newAssignmentNames = nullptr;

                // Increment number of grades
                numGrades[menuChoice]++;

                std::cout << std::endl; // Formatting space
            }
            else if(categoryMenuChoice == 2) // Remove a grade
            {
                if(numGrades[menuChoice] == 0)
                {
                    std::cout << "You have no grades to remove!" << std::endl;
                }
                else
                {
                    // Prompt user to enter the grade to edit
                    std::cout << "Enter the number corresponding to the grade which you wish to remove: ";
                    
                    // Get grade to remove
                    while(!(std::cin >> gradeMenuChoice))
                    {
                        std::cin.clear(); // clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                        std::cout << "Invalid input! Try again: "; // Prompt user to try again
                    }

                    gradeMenuChoice--; // Allign w/ 0-indexed

                    // Allocate space for new arrays of grades
                    newGrades = new double [numGrades[menuChoice] - 1];
                    newPerfectGrades = new double [numGrades[menuChoice] - 1];
                    newAssignmentNames = new std::string [numGrades[menuChoice] - 1];

                    // Remove the grade from every array by creating smaller copies of the arrays and assigning them to the originals
                    for(int i = 0; i < numGrades[menuChoice]; ++i)
                    {
                        if(i == gradeMenuChoice) continue; // Skip copying removed grade
                        
                        // Place new grade in proper index
                        if(i > gradeMenuChoice)
                        {
                            // Copy grades to new arrays
                            newGrades[i - 1] = grades[menuChoice][i];
                            newPerfectGrades[i - 1] = perfectGrades[menuChoice][i];
                            newAssignmentNames[i - 1] = assignmentNames[menuChoice][i];
                        }
                        else
                        {
                            newGrades[i] = grades[menuChoice][i];
                            newPerfectGrades[i] = perfectGrades[menuChoice][i];
                            newAssignmentNames[i] = assignmentNames[menuChoice][i];
                        }
                    }

                    // Delete old grade arrays
                    delete[] grades[menuChoice];
                    delete[] perfectGrades[menuChoice];
                    delete[] assignmentNames[menuChoice];
                    
                    // Reassign old grade arrays
                    grades[menuChoice] = newGrades;
                    perfectGrades[menuChoice] = newPerfectGrades;
                    assignmentNames[menuChoice] = newAssignmentNames;

                    // Set newGrade arrays to null again
                    newGrades = nullptr;
                    newPerfectGrades = nullptr;
                    newAssignmentNames = nullptr;
                    
                    // Decrement number of grades
                    numGrades[menuChoice]--;
                }

                std::cout << std::endl; // Formatting space
            }
            else // Edit grade
            {
                if(numGrades[menuChoice] == 0)
                {
                    std::cout << "You have no grades to edit!" << std::endl;
                }
                else
                {
                    // Prompt user to enter the grade to edit
                    std::cout << "Enter the number corresponding to the grade which you wish to edit: " << std::endl;

                    // Get grade to edit
                    while(!(std::cin >> gradeMenuChoice))
                    {
                        std::cin.clear(); // clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                        std::cout << "Invalid input! Try again: "; // Prompt user to try again
                    }

                    gradeMenuChoice--; // Allign w/ 0-indexed

                    // Prompt user to decide if they'd like to edit x in x / y * 100 = z% (their grade on the assignent)
                    std::cout << "Would you like to edit YOUR score (i.e. If x / y * 100 = z%, do you want to edit x)? Enter y for yes or n for no: ";

                    // Get menu choice from user
                    while(!(std::cin >> gradeMenuCharChoice))
                    {
                        std::cin.clear(); // clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                        std::cout << "Invalid input! Try again: "; // Prompt user to try again
                    }

                    if(gradeMenuCharChoice == 'y')
                    {
                        // Prompt user to enter the new grade for x in x / y * 100 = z% (their grade)
                        std::cout << "Enter the new grade: ";

                        // Get score from user
                        while(!(std::cin >> grades[menuChoice][gradeMenuChoice]))
                        {
                            std::cin.clear(); // clear the error flag
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                            std::cout << "Invalid input! Try again: "; // Prompt user to try again
                        }
                    }

                    // Prompt user to decide if they'd like to edit y in x / y * 100 = z% (their grade on the assignent)
                    std::cout << "Would you like to edit the perfect score (i.e. If x / y * 100 = z%, do you want to edit y)? Enter y for yes or n for no: ";

                    // Get menu choice from user
                    while(!(std::cin >> gradeMenuCharChoice))
                    {
                        std::cin.clear(); // clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                        std::cout << "Invalid input! Try again: "; // Prompt user to try again
                    }

                    if(gradeMenuCharChoice == 'y')
                    {
                        // Prompt user to enter the new grade for y in x / y * 100 = z% (their grade)
                        std::cout << "Enter the new grade: ";

                        // Get score from user
                        while(!(std::cin >> perfectGrades[menuChoice][gradeMenuChoice]))
                        {
                            std::cin.clear(); // clear the error flag
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                            std::cout << "Invalid input! Try again: "; // Prompt user to try again
                        }
                    }
                }

                std::cout << std::endl; // Formatting space
            }
        }
    }
}