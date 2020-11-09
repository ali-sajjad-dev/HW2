//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.

// COMMENT ALL CODE. Problem 1
//***********************************************************

// input/output stream lib
#include <iostream>  
// library to give us a variaty of parameteric manipulators
#include <iomanip>
// input/output stream lib to operate on files
#include <fstream>
// stack header file
#include "mystack.h"
 
// name space for std lib, namely std::operation
using namespace std; 

// void function to evaluate an expression
void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
// void function to evaluate an operation
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
// function to discard an expressionn whenever an error is detected
void discardExp(ifstream& in, ofstream& out, char& ch);
// print out the stack results 
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    // boolean used to determine of expression is legal
    bool expressionOk;
    char ch;
    // generic stack declared as double
    stackType<double> stack(100);
    // infile object to read in
    ifstream infile;
    // outfile object to write out
    ofstream outfile;
 
    // open the file in quotations
    infile.open("RpnData.txt");
    // if opening the file fails it will return false
    // else it will return true
    if (!infile)
    {
       // output error message
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        // terminate current program by returning 1 by main function
        return 1;
    }
    // open the outfile that will be written to 
    outfile.open("RpnOutput.txt");
    
    // sets the floating field for the stream to fixed-point notation
    // format flaq is set so the decimal point is always written for floating point values in the stream.
    outfile << fixed << showpoint;
    // this sets the decimal precision to format floating point values on output operations
    // hence, #include <iomanip>
    outfile << setprecision(2); 
    
    // read in character
    infile >> ch;
    // as long as infile is true
    while (infile)
    {
        // initialize the stack
        stack.initializeStack();
        // set expression to true
        expressionOk = true;
        // read out the character
        outfile << ch;
        // evaluate the entire expression
        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
        // print the expression via stack
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while 
    
    // close both output and input files
    infile.close();
    outfile.close();

    return 0;

} //end main

// This function evaluates each postfix expression
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
    // As long as the expression is not equal to "=" the program will continue
    // Because "=" represents the end of a postfix expression 
    while (ch != '=')
    {
        switch (ch)
        {
        case '#': 
            // read in the number
            inpF >> num;
            // write out the number
            outF << num << " ";
            // As long as the stack is not full push onto the stack
            if (!stack.isFullStack())
                stack.push(num);
            else
            {  
                // if the stack is full, print out error message and terminate the program
                // via returning int from main function
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }
            // break out of the while loop 
            break;
        default: 
            // We want to assume that the character is an operation
            // and evaluate the operation
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch 
         
        // if no errors are found only then continue
        if (isExpOk) 
        {
           // read in the character 
            inpF >> ch;
           // write out the character
            outF << ch;
            if (ch != '#')
                outF << " ";
        }
        else
            // if the expression is not void of errors we must discard it
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression

// This function evaluations the operation by looking at both operands and 
// operands are then put onto the stack, if errors occur the operation is discarded
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;
    
    // if the stack is empty
    if (stack.isEmptyStack())
    {
        // we must output error and set the expression as false or invalid
        // because operations cannot be conducted on an empty stack
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else
    {
        // if the stack is not full, retrieve the top most value
        op2 = stack.top();
        // remove if off the stack
        stack.pop();
        
        // if the stack is now empty due to popping off he top most element
        // we must print error message and set expression to false
        // this is because atleast two operands are required to carry out an operations
        // we cannot for example add or subtract a single operand by itself.
        if (stack.isEmptyStack())
        {
           // print error message and set expression to false
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else
        {
            // If there are atleast two elements int the stack
            // pop off the top most number and store it in double
            op1 = stack.top();
            stack.pop();
            
            // now we determine whether the operation provided is legal
            // hence a switch statment will evaluate all possible cases for the operations
            // In our case only 4 operations are suitible, additions, subtraction, multiplication and division
            switch (ch)
            {
            // if the character from file is "+" then push the result of the operation onto the stack and break out.
            case '+': 
                stack.push(op1 + op2);
                break;
            // if the character from file is "-" then push the result of the operation onto the stack and break;
            case '-': 
                stack.push(op1 - op2);
                break;
            // if the character from file is "*" then push the result of the operation onto the stack and break out.
            case '*': 
                stack.push(op1 * op2);
                break;
            //  if the character from file is "/" then push the result of the operation onto the stack and break out.  
            // also ensures the divisior is legal and not '0' because any value divided by '0' is undefined.
            case '/': 
                if (op2 != 0)
                    stack.push(op1 / op2);
                else
                {
                   // print error message and set expression to false
                   // if the divisor is 0
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            default:
               // the default to out switch statement is if the character from file doesnt match any operation
               // and expression is set to false
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

// This function is used to when an error is discovered inside the expression
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    // reads until the end of expression '='
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

// This function prints out the results of our expression operation from the stack
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;
    
 // as long as expression was set to true it will print the result.
    if (isExpOk)
    {
       // make sure the stack is not empty
       // we cant print an empty stack
        if (!stack.isEmptyStack())
        {
            // set the result to the top most value, we're looking for only one value in the stack, no more than 1.
            result = stack.top();
            // remove the result from the stack
            stack.pop();
            
            // If after popping off the result we still have an operand or value remaining
            // We print error because the stack should only have a single element
            if (stack.isEmptyStack())
                outF << result << endl;
            else
                // write out error if operands other than result
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            // error if the stack was empty to begin with
            outF << " (Error in the expression)" << endl;
    }
    else
        // error if expression was false to begin with.
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult
