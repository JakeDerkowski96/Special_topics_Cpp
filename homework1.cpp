#include <iostream> // allows for input/output to/from user
#include <cmath> // allows for the standard math functions needed
#include <iomanip>
const float PROJECTILE_A = -16.0; // Declare a global variable for the constant.

// print required student and class info
void student_information()
{
    std::string department = "Computer Science";
    std::string course = "COSC 2347 - Special Topics";
    std::string student = " Jake Derkowski     ID: 000664315     jad084@shsu.edu ";
    std::string info = "|\t\t\t" + department + "\t\t |\n|\t\t" + course + "\t\t |\n| " + student + " |\n";
    std::string border = "**********************************************************\n";
    std::string displayInf = border + info + border;

    std::cout << displayInf;
}

/*function to calculate the time it takes for object to hit ground*/
void time_taken(float b, float c, float& time)
{
    // calculate first root
    float xroot1 = (-b + sqrt(b * b - 4 * PROJECTILE_A * c)) / (2 * PROJECTILE_A);
    float xroot2;       // initalize the second root to be calculated if first is not positive
    if (xroot1 > 0)     // checks to see if first is positive
    {
        time = xroot1;  // this is the time_taken
    }
    else if (xroot1 < 0)        // if it is a negative number calculate the second root
    {
        xroot2 = (-b - sqrt(b * b - 4 * PROJECTILE_A * c)) / (2 * PROJECTILE_A);
        if (xroot2 > 0)         // verify that this is positive
        {
            time = xroot2;  // this is the time_taken
        }
        else
        {
            std::cout << "The roots of the input values are imaginary.\n";
            std::cout << "please check your work and reenter your values.\n";
        }
    }
}

/*Max height can be found by calculatiung the vertex of trajectory */
void max_height(float b, float c, float& max_air)
{
    // calculate the time in which the object is at the highest
    float vertex;   // using -b / (2*a)
    vertex = -b / (2*PROJECTILE_A);

    // max is calculated by plugging vertex into the quadradic functions
    max_air = PROJECTILE_A*pow(vertex, 2) + b * vertex + c;
}

int main()
{
    student_information();  // display student+assignment information
    // declaring, grabbing, and storing user input for the inital height
    float init_height;      // == c in the quadradic function
    float init_velocity;    // == b in the quadradic function
    float max_air;          // Highest point reached
    float time;             // result will be stored in time

    // gather input from user
    std::cout << "Enter the initial height of s0 in feet:  ";
    std::cin >> init_height;  // // storing user input of initial height
    std::cout << "Enter the initial velocity of v0 in feet/second:  ";
    std::cin >> init_velocity; // storing user input of velocity

    time_taken(init_velocity, init_height, time);
    max_height(init_velocity, init_height, max_air);
    // print answers
    std::cout << "It will take " << std::fixed << std::setprecision(2) << time << " seconds for object to hit the ground.\n";
    std::cout << "The objects max_airimum height is " << std::fixed << std::setprecision(2) << max_air << " feet.\n";

    return 0;

}
