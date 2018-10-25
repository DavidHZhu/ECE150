// Title: Intervals.cpp calculator
// Author: David Zhu
// Description: Interval calculator using classes
// Updates: Oct 20: Classes and functions setup(check for initialization and divide by 0
//                  Working: exit, enter, negate, ms, mr, mc, m+ (mplus), m- (msubt),
//                  scalar_add, scalar_subtract, scalar_multiply, scalar_divide, scalar_divided_by
//          Oct 21: interval_add, interval_subtract, interval_multiply, interval_divide
//                  intersect, integers and cartesian_integers
// Problems: Need to check and swap if the numbers after an + or - (fixed)
//
//=================================================================================================
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

// Class Declaration
//=================================================================================================
class Operators{
private:
    // NAN means Not a Number and I used it while testing to determine if it is initialized
    double immediate[2] = {NAN,NAN};
    double memory[2] = {NAN,NAN};
    bool isInitI=false;
    bool isInitM=false;

public:
    void printI();
    bool divideby0();
    void enter(double a, double b);
    void negate();
    void invert();
    void ms();
    void mr();
    void mc();
    void mAdd();
    void mSub();
    void sAdd(double c);
    void sSub(double c);
    void sMultiply(double c);
    void sDivide(double c);
    void sDividedBy(double c);
    void intAdd(double c, double d);
    void intSub(double c, double d);
    void intMultiply(double c, double d);
    void intDivide(double c, double d);
    void intersect(double c, double d);
    void integers();
    void cartIntegers(double c, double d);
};

// Class methods and definitions
//=================================================================================================
void Operators::printI() {
    std::cout << "[" << immediate[0] << ", " << immediate[1] << "]" << std::endl;

}

bool Operators::divideby0() {
    if (immediate[0] <= 0 && immediate[1] >= 0){
        std::cout << "Error: division by zero " << std::endl;
        return true;
    } else {
        return false;
    }
}

void Operators::enter(double a, double b) {
    if (a > b){
        std::cout << "Error: invalid interval as " << a <<" > " << b << std::endl;
        std::cout << "--" << std::endl;
        isInitI = false;
        return;
    } else {
        isInitI = true;
        immediate[0] = a;
        immediate[1] = b;
        printI();
        return;
    }

}

void Operators::negate() {
    if (!isInitI){
        std::cout << "--" << std::endl;
        return;
    } else {
        double temp = -immediate[0];
        immediate[0] = -immediate[1];
        immediate[1] = temp;
        printI();
    }
}

void Operators::invert() {
    if (!isInitI){
        std::cout << "--" << std::endl;
        return;
    } else if (divideby0()){
        std::cout << "--" << std::endl;
        return;
    } else {
        double temp = 1.0/immediate[0];
        immediate[0] = 1.0/immediate[1];
        immediate[1] = temp;
        printI();
        return;
    }
}

void Operators::ms() {
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
    } else {
        memory[0] = immediate[0];
        memory[1] = immediate[1];
        isInitM = true;
        printI();
        return;
    }
}

void Operators::mr() {
    if (isInitI){
        if (isInitM){
            immediate[0] = memory[0];
            immediate[1] = memory[1];
        }
        printI();
    } else {
        std::cout << "--" << std::endl;
    }
}

void Operators::mc() {
    memory[0] = NAN;
    memory[1] = NAN;
    printI();
    isInitM = false;
}

void Operators::mAdd() {
    // Checks for valid initialization and changes memory
    if (isInitI && isInitM){
        memory[0] += immediate[0];
        memory[1] += immediate[1];
        if (memory[0] > memory[1]){
            std::swap(memory[0],memory[1]);
        }
        printI();
        return;
    } else {
        std::cout << "--" << std::endl;
        return;
    }
}

void Operators::mSub() {
    // Checks for valid input and adds to memory, otherwise do nothing
    if (isInitI && isInitM){
        memory[0] -= immediate[0];
        memory[1] -= immediate[1];
        if (memory[0] > memory[1]){
            std::swap(memory[0],memory[1]);
        }
        printI();
        return;
    // This part checks if the memory is not intialized and corrects for [-0,-0]
    } else if(!isInitM && isInitI) {
        if (immediate[0] == 0) {
            memory[0] = 0;
        }
        if (immediate[1] == 0) {
            memory[1] = 0;
        }
        if (immediate[0] != 0 && immediate[1] != 0) {
            memory[0] = -immediate[0];
            memory[1] = -immediate[1];
        }
        printI();
        return;
    } else {
        std::cout << "--" << std::endl;
        return;
    }
}

void Operators::sAdd(double c) {
    // Checks if input is valid and states error messages:
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
     // Otherwise, print out new immediate interval
    } else {
        immediate[0] += c;
        immediate[1] += c;
        if (immediate[0] > immediate[1]){
            std::swap(immediate[0],immediate[1]);
        }
        printI();
        return;
    }
}

void Operators::sSub(double c) {
    // Check if input is valid and states error messages:
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
     // Otherwise, print out the immediate interval
    } else {
        immediate[0] -= c;
        immediate[1] -= c;
        if (immediate[0] > immediate[1]){
            std::swap(immediate[0],immediate[1]);
        }
        printI();
        return;
    }
}

void Operators::sMultiply(double c) {
    // Checks for valid input and states error messages:
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
     // Otherwise output the new immediate interval
    } else if (c > 0){
        immediate[0] *= c;
        immediate[1] *= c;
        printI();
        return;
     // This part checks if they are trying to multiply by a negative and corrects [-0,-0]
    } else {
        if (immediate[0] == 0) {
            immediate[0] = 0;
        }
        if (immediate[1] == 0) {
            immediate[1] == 0;
        }
        if (immediate[0] != 0 && immediate[1] != 0){
            double temp = immediate[0] * c;
            immediate[0] = immediate[1] * c;
            immediate[1] = temp;
        }
        printI();
        return;
    }
}

void Operators::sDivide(double c) {
    // Checks if input is valid and states error messages:
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
    } else if (c == 0){
        std::cout << "Error: division by zero " << std::endl;
        std::cout << "--" <<std::endl;
        isInitI = false;
        return;
        // Otherwise, print out the new immediate interval
    } else if (c > 0) {
        immediate[0] /= c;
        immediate[1] /= c;
        printI();
        return;
        // This part checks if they try dividing by a negative and corrects for [-0,-0]
    } else {
        if (immediate[0] == 0) {
            immediate[0] = 0;
        }
        if (immediate[1] == 0) {
            immediate[1] == 0;
        }
        if (immediate[0] !=0 && immediate[1] !=0) {
            double temp = immediate[0] / c;
            immediate[0] = immediate[1] / c;
            immediate[1] = temp;
        }
        printI();
        return;
    }
}

void Operators::sDividedBy(double c) {
    // Checks if input is valid and states error messages:
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
    } else if (divideby0()){
        return;
     // Otherwise, prints out new interval
    } else if (c > 0){
        immediate[0] = c / immediate[0];
        immediate[1] = c / immediate[1];
        printI();
        return;
    } else{
        double temp = c / immediate[0];
        immediate[0] = c / immediate[1];
        immediate[1] = temp;
        printI();
        return;
    }
}

void Operators::intAdd(double c, double d) {
    // Checks if input is valid and states error messages
    if (c > d){
        std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
        if (isInitI){
            printI();
        } else{
            std::cout << "--" << std::endl;
        }
    }
    else if (!isInitI){
        std::cout << "--" << std::endl;
    }
    // Otherwise, print out the new immediate interval
    if(isInitI && c < d){
        immediate[0] += c;
        immediate[1] += d;
        if (immediate[0] > immediate[1]){
            std::swap(immediate[0],immediate[1]);
        }
        printI();
    }

}

void Operators::intSub(double c, double d) {
    // Checks if input is valid and states error messages:
    if (c > d){
        std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
        if (isInitI){
            printI();
        } else{
            std::cout << "--" << std::endl;
        }
    }
    else if (!isInitI){
        std::cout << "--" << std::endl;
    }
    // Otherwise, prints new immediate interval
    if(isInitI && c < d){
        immediate[0] -= d;
        immediate[1] -= c;
        if (immediate[0] > immediate[1]){
            std::swap(immediate[0],immediate[1]);
        }
        printI();
    }

}

void Operators::intMultiply(double c, double d) {
    // Check for valid input and states error messages:
    if (c > d){
        std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
        if (isInitI){
            printI();
        } else{
            std::cout << "--" << std::endl;
        }
    }
    else if (!isInitI){
        std::cout << "--" << std::endl;
    }
    // Otherwise it prints the new immediate interval
    if (isInitI && c < d) {
        double temp = std::max({c*immediate[0],c*immediate[1],d*immediate[0],d*immediate[1]});
        immediate[0] = std::min({c*immediate[0],c*immediate[1],d*immediate[0],d*immediate[1]});
        immediate[1] = temp;
        printI();
    }

}

void Operators::intDivide(double c, double d) {
    // Checks for valid input and states error messages:
    if (c > d){
        std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
        if (isInitI){
            printI();
        } else{
            std::cout << "--" << std::endl;
        }
        return;
    }
    else if (!isInitI){
        std::cout << "--" << std::endl;
        return;
    }
    else if (c <= 0 && d >= 0){
        std::cout << "Error: division by zero" << std::endl;
        std::cout << "--" << std::endl;
        immediate[0] = NAN;
        immediate[1] = NAN;
        isInitI = false;
        return;
    }
    // Otherwise, prints new immediate interval
    if (isInitI && c < d){
        double temp = std::max({immediate[0]/c,immediate[0]/d,immediate[1]/c,immediate[1]/d});
        immediate[0] = std::min({immediate[0]/c,immediate[0]/d,immediate[1]/c,immediate[1]/d});
        immediate[1] = temp;
        printI();
    }
}

void Operators::intersect(double c, double d) {
    // Checks if valid and states error messages:
    if (c > d){
        std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
        if (isInitI){
            printI();
        } else{
            std::cout << "--" << std::endl;
        }
        return;
    }
    else if (!isInitI){
        std::cout << "--" << std::endl;
        return;
    }
    // Otherwise, check for intersection and print it out
    if (isInitI && c < d){
        if (c > immediate[1] || immediate[0] > d){
            std::cout << "--" << std::endl;
            immediate[0] = NAN;
            immediate[1] = NAN;
            isInitI = false;
            return;
        } else {
            immediate[0] = std::max(immediate[0],c);
            immediate[1] = std::min(immediate[1],d);
            printI();
        }
    }
}

void Operators::integers() {
    // Check if initialized otherwise print out each integer in range
    if(!isInitI){
        std::cout << "--" << std::endl;
        return;
    } else{
        for (int i = std::ceil(immediate[0]); i <= std::ceil(immediate[1]); i++){
            std::cout << i;
            if (i == std::ceil(immediate[1])){
                std::cout << " " << std::endl;
            } else {
                std::cout<<", ";
            }
        }
        printI();
    }
}

void Operators::cartIntegers(double c, double d) {
    // Checks if valid, and states error messages:
    if (c > d){
        std::cout << "Error: invalid interval as " << c << " > " << d << std::endl;
        if (isInitI){
            printI();
        } else{
            std::cout << "--" << std::endl;
        }
        return;
    }
    else if (!isInitI){
        std::cout << "--" << std::endl;
        return;
    }
    // Otherwise, print out cartesian integers
    if(isInitI && c <= d){
        for (int i = 0; i <= (std::floor(immediate[1])-std::ceil(immediate[0])); ++i){
            for (int j = std::ceil(c); j <= std::floor(d); ++j) {
                std::cout << "(" << std::ceil(immediate[0]) + i << "," << j << ")";
                if (i == (std::floor(immediate[1])-std::ceil(immediate[0])) && j == std::floor(d)){
                    std::cout << std::endl;
                } else{
                    std::cout << ", ";
                }
            }
        }
        printI();
    }
}
// Primary function that creates an instance of the class Operators
//=================================================================================================
void interval_calculator(){

    // Create an instance of the class Operators
    Operators calculator;

    bool Exit = false;
    std::string command="";
    double x,y = 0;

    // Continues until user asks to quit:
    while(!Exit) {

        // Flushes istream
        std::cin.clear();

        std::cout << "input :> ";
        std::cin >> command;

        // No operand commands:
        if (command == "exit"){
            Exit = true;
            break;
        } else if (command == "negate"){
            calculator.negate();

        } else if (command == "invert"){
            calculator.invert();

        } else if (command == "ms"){
            calculator.ms();

        } else if (command == "mr"){
            calculator.mr();

        } else if (command == "mc"){
            calculator.mc();

        } else if (command == "m+"){
            calculator.mAdd();

        } else if (command == "m-"){
            calculator.mSub();

        } else if (command == "integers"){
            calculator.integers();
        }

        // Two operand methods
        else if (command == "enter"){
            std::cin >> x >> y;
            calculator.enter(x,y);
        } else if (command == "interval_add") {
            std::cin >> x >> y;
            calculator.intAdd(x,y);
        } else if (command == "interval_subtract"){
            std::cin >> x >> y;
            calculator.intSub(x,y);
        } else if (command == "interval_multiply"){
            std::cin >> x >> y;
            calculator.intMultiply(x,y);
        } else if (command == "interval_divide"){
            std::cin >> x >> y;
            calculator.intDivide(x,y);
        } else if (command == "intersect") {
            std::cin >> x >> y;
            calculator.intersect(x,y);
        } else if (command == "cartesian_integers"){
            std::cin >> x >> y;
            calculator.cartIntegers(x,y);
        }

        // One operand methods
        else if (command == "scalar_add") {
            std::cin >> x;
            calculator.sAdd(x);

        } else if (command == "scalar_subtract"){
            std::cin >> x;
            calculator.sSub(x);

        } else if (command == "scalar_multiply") {
            std::cin >> x;
            calculator.sMultiply(x);

        } else if (command == "scalar_divide") {
            std::cin >> x;
            calculator.sDivide(x);

        } else if (command == "scalar_divided_by"){
            std::cin >> x;
            calculator.sDividedBy(x);

        } else{
            std::cout << "Error: illegal command." << std::endl;
        }

    }

    // Upon Exit
    if(Exit)
        std::cout <<"Bye bye: Terminating interval calculator program.";
}

// Does not need ifndef Marmoset_testing
int main() {
    interval_calculator();
    return 0;
}