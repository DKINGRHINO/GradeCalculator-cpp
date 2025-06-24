#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

void basicGradeCalculator();
int basicGradeCalcMenuSys(int numCategories, double ** grades, double * categoryWeights, std::string * categoryNames);
void updateCategoryGrades(std::string ** assignmentNames, double ** grades, double ** perfectGrades, int menuChoice, std::string * categoryNames, int * numGrades, int numCategories);

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
    std::cout << "Enter the number of categories (i.e. tests are 20%, hw is 80%, so there are 2 categories): ";

    // Get input from user
    std::cin >> numCategories;

    // Dynamically allocate memory for an array of arrays of double values for grades
    double ** grades = NULL;
    grades = new double * [numCategories];

    double ** perfectGrades = NULL;
    perfectGrades = new double * [numCategories];

    int * numGrades = new int [numCategories];

    // Dynamically allocate memory for arrays of strings to keep track of the names
    std::string ** assignmentNames = NULL;
    assignmentNames = new std::string * [numCategories];

    std::string * categoryNames = NULL;
    categoryNames = new std::string[numCategories];

    for(int i = 0; i < numCategories; ++i)
    {
        grades[i] = NULL;
        perfectGrades[i] = NULL;
        assignmentNames[i] = NULL;
        numGrades[i] = 0;
    }

    // Dynamically allocate memory for an array of doubles to hold the category weights
    double * categoryWeights = NULL;
    categoryWeights = new double[numCategories];

    // Ask user for the names of each category
    std::cout << "Enter each category name, then press enter (enter them separately):" << std::endl;

    std::string curStringName;

    // Get names of each category from user
    for(int i = 0; i < numCategories; ++i)
    {
        std::cin >> curStringName;
        categoryNames[i] = curStringName;
    }

    std::cout << std::endl; // Formatting space

    // Ask user for the weights of each category
    std::cout << "Enter the double percentage weights of each category respectively (enter them separately)." << std::endl;
    std::cout << "Ensure they add up to 100%" << std::endl;

    // Get weights for each category from user as doubles
    for(int i = 0; i < numCategories; ++i)
    {
        std::cin >> categoryWeights[i];
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
                    gradeCalculation += categoryGradeCalculationNumerator / categoryGradeCalculationDenominator * 100 / categoryWeights[curCategory];
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
    std::cout << "Enter and integer: ";
    
    // Get menu choice from user
    std::cin >> menuChoice;

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
    double * newGrades = NULL;
    double * newPerfectGrades = NULL;
    std::string * newAssignmentNames = NULL;

    // While choice is not to exit menu
    while(categoryMenuChoice != 4)
    {
        // Display grades in a formatted way
        std::cout << "-----------------------------------------" << std::endl; // Formatting bar
        std::cout << "Grades: ";

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
        std::cin >> categoryMenuChoice;

        std::cout << std::endl; // Formatting space
        
        if(categoryMenuChoice != 4) // Not exiting menu
        {
            if(categoryMenuChoice == 3) // Add a grade
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
                std::cout << "Enter the assignment name: ";
                std::cin >> newAssignmentNames[numGrades[menuChoice]];

                // Prompt the user for the score
                std::cout << "Enter the score as a double (i.e. If x/y = z%, what is x): ";
                std::cin >> newGrades[numGrades[menuChoice]];

                // Prompt the user for the perfect score
                std::cout << "Enter the perfect score as a double (i.e. If x/y = z%, what is y): ";
                std::cin >> newPerfectGrades[numGrades[menuChoice]];

                // Delete old grade arrays
                delete[] grades[menuChoice];
                delete[] perfectGrades[menuChoice];
                delete[] assignmentNames[menuChoice];
                
                // Reassign old grade arrays
                grades[menuChoice] = newGrades;
                perfectGrades[menuChoice] = newPerfectGrades;
                assignmentNames[menuChoice] = newAssignmentNames;

                // Set newGrade arrays to null again
                newGrades = NULL;
                newPerfectGrades = NULL;
                newAssignmentNames = NULL;

                // Increment number of grades
                numGrades[menuChoice]++;

                std::cout << std::endl; // Formatting space
            }
            else if(categoryMenuChoice == 2) // Remove a grade
            {
                if(numGrades[menuChoice] = 0)
                {
                    std::cout << "You have no grades to remove!" << std::endl;
                }
                else
                {
                    // Prompt user to enter the grade to edit
                    std::cout << "Enter the number corresponding to the grade which you wish to remove: " << std::endl;
                    std::cin >> gradeMenuChoice; // Get grade to remove
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

                        // Delete old grade arrays
                        delete[] grades[menuChoice];
                        delete[] perfectGrades[menuChoice];
                        delete[] assignmentNames[menuChoice];
                        
                        // Reassign old grade arrays
                        grades[menuChoice] = newGrades;
                        perfectGrades[menuChoice] = newPerfectGrades;
                        assignmentNames[menuChoice] = newAssignmentNames;

                        // Set newGrade arrays to null again
                        newGrades = NULL;
                        newPerfectGrades = NULL;
                        newAssignmentNames = NULL;
                        
                        // Decrement number of grades
                        numGrades[menuChoice]--;
                    }
                }

                std::cout << std::endl; // Formatting space
            }
            else // Edit grade
            {
                if(numGrades[menuChoice] = 0)
                {
                    std::cout << "You have no grades to edit!" << std::endl;
                }
                else
                {
                    // Prompt user to enter the grade to edit
                    std::cout << "Enter the number corresponding to the grade which you wish to edit: " << std::endl;
                    std::cin >> gradeMenuChoice; // Get grade to edit
                    gradeMenuChoice--; // Allign w/ 0-indexed

                    std::cout << "Would you like to edit YOUR score (i.e. If x/y = z%, do you want to edit x)? Enter y for yes or n for no: ";
                    std::cin >> gradeMenuCharChoice;

                    if(gradeMenuCharChoice == 'y')
                    {
                        std::cout << "Enter the new grade: ";
                        std::cin >> grades[menuChoice][gradeMenuChoice];
                    }

                    std::cout << "Would you like to edit the perfect score (i.e. If x/y = z%, do you want to edit y)? Enter y for yes or n for no";
                    std::cin >> gradeMenuCharChoice;

                    if(gradeMenuCharChoice == 'y')
                    {
                        std::cout << "Enter the new grade: ";
                        std::cin >> perfectGrades[menuChoice][gradeMenuChoice];
                    }
                }

                std::cout << std::endl; // Formatting space
            }
        }
    }
}