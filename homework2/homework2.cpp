#include <iostream>
#include <string>
using namespace std;

// print required student and class info
void student_information()
{
    string department = "Computer Science";
    string course = "COSC 2347 - Special Topics";
    string student = " Jake Derkowski     ID: 000664315     jad084@shsu.edu ";
    string info = "|\t\t   " + department + "\t\t\t |\n|\t\t" + course + "\t\t |\n| " + student + " |\n";
    string border = "+********************************************************+\n";
    string displayInfo = border + info + border;
    cout << displayInfo;
}

// check top base: in range 1-17, and is odd & ptint errors
bool check_top_base(int top)
{
    bool ValidTop = true; // default value to make the do-while loop run
    int min = 1; // values of the accepted range
    int max = 17;
    if ((top >= min)&&(top <= max)) { // if in range
        if (top % 2 == 1) { // 1 is the remainder when / 2 = it is odd
            ValidTop = false; // top base is valid
        }
        else {
            cout << "Must enter an odd integer\n";
        }
    }
    else {
        cout << "Inter must be in range 1-17\n";
    }
    return ValidTop; // value will stay true until the all conditions are met
}

// check bottom base in range 3-19, if odd, if > top & prints error message
bool check_bottom_base(int top, int bottom)
{
    bool ValidBottom = true; // this means invalid bottom
    int min = 3; // values for the accepted range
    int max = 19;
    if ((bottom >= min)&&(bottom <= max)) { // is it in range
        if (bottom % 2 == 1) { // if true then it is odd
            if (bottom > top) { // must be larger than the bottom
                ValidBottom = false;    // bottom satisfies all of the conditions
            }
            else {
                cout << "Bottom must be larger than top.\n";
            }
        }
        else {
            cout << "Input must be an odd integer.\n";
        }
    }
    else {
        cout << "Bottom must be within the range 3-19\n";
    }
    return ValidBottom; // value will stay true until the all conditions are met
}

// calculate the height necessary to satisfy user values
int calc_height(int top, int bottom)
{
    int height; // total number of rows including bottom
    height = ((bottom - top) / 2) + 1; // must add 1 for the bottom base
    return height;
}

// // uses the user's input and the calculated aread function
void print_trapezoid(int bottom, int height, char symbol)
{
    for (int row = 0; row < height; ++row) {
        for (int col = height - row; col > 0; --col) {
            cout << " ";
        }
        for (int col = 0; col < (bottom + 2 * row); ++col) {
            cout << symbol;
        }
        cout << endl;
    }
}

// calcualtes the area of a trapezoid using the formula
int calc_trapezoid_area(int base_one, int base_two, int height)
{
    int area; // store area of trapezoid    // int, float, double???
    area = ((base_one + base_two) * height) / 2;
    return area;
}

int main()
{ // main function
    int top_base, bottom_base; // user input
    bool top_check, bottom_check; // verify the user's input using bool function
    int height; // the total number of rows in trapezoid 

    char letter; // this will be used to draw the trapezoid
    int area; // store the calculated area

    student_information(); // print required student information

    // getting user defined dimensions
    // TOP
    do {
        cout << "\nEnter odd integer (1-17) for base 1:  ";
        cin >> top_base;
        top_check = check_top_base(top_base); // invalid input = return true
    } while(top_check);

    // BOTTOM
    do {
        cout << "\nEnter odd integer (3-19) for base 2:  ";
        cin >> bottom_base;
        bottom_check = check_bottom_base(top_base, bottom_base);
    } while(bottom_check);

    // HEIGHT
    height = calc_height(top_base, bottom_base); // calculate total number of rows

    cout << "\nEnter character you would like to draw with:  "; cin >> letter;

    // DISPLAY DIMENSIONS TO USER
    cout << "\nCalclulating the area of the trapezoid with the following dimensions: " << endl;
    cout << "  Base one:  " << top_base << "\t\tBase two:  " << bottom_base << "\t\tHeight  :  " << height << "\n\n";

    // PERFORM CALCULATION
    area = calc_trapezoid_area(top_base, bottom_base, height); // storing of the calc area

    // PRINT TRAPEZOID REPORT THE AREA  
    print_trapezoid(bottom_base, height, letter); // calls function that prints trapezoid & prints area
    cout << "\nThe are of this trapezoid is :  " << area << " " << letter << " units squared." << endl;
}

