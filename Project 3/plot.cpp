#include "grid.h"
#include <iostream>
#include <cctype>
#include <cassert>
#include <string>
using namespace std;
int charToInt(string dHV);//Functions
bool Command(string check, int pos1);
bool checkSyntaxError(string commandString, int& badPos);
bool processHorVstep(string text, int& pos, int& realNum);
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
const int FG = 0; //Definition of global variables
const int BG = 1;
const int VERT = 1;
const int HORIZ = 0;

///////////////////////////////////////////////////////////////////////////
// prototype ⬆️
///////////////////////////////////////////////////////////////////////////


int main()
{
    setSize(20, 30);
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
    int position;
    int status = performCommands(cmd, currentChar, currentMode, position);
    switch (status)
    {
      case 0:
        draw();
        break;
      case 1:
            cout << "Syntax error at position " << position+1 << endl;
        break;
      case 2:
            cout << "Cannot perform command at position " << position+1 << endl;
        break;
      default:
          // It should be impossible to get here.
            cerr << "performCommands returned " << status << "!" << endl;
    }
    }
}

///////////////////////////////////////////////////////////////////////////
// implementation ⬇️
///////////////////////////////////////////////////////////////////////////


int performCommands(string commandString, char& plotChar, int& mode, int& badPos) // Definition of the main function (performCommands). Last three variables are called by references beacuse they will be changed along with the program.
{
    int pos = 0; int realNum = 0; int row = 1; int column = 1; int temp = 0; // Initialization of variables

    for (;pos < commandString.size();pos++) // Check each characters with the length of the code. First check the syntax error
        {
            
            if (not (Command(commandString, pos) && (pos != commandString.size()))) // If the end of string has not reached and a not command word is performed, return syntax error.
            {
            badPos = pos;
            return 1;
            }
            if (commandString[pos] == 'H' || commandString[pos] == 'h' || commandString[pos] == 'V' || commandString[pos] == 'v')
            {
                pos++; // Check for the first digit
                if (not processHorVstep(commandString, pos, realNum)) // Perform for a H or V command.
                {
                    badPos = pos;
                    return 1; // If not true, syntax error will be spotted by the processHorVstep function.
                }
                else
                {
                    pos--;
                }
            }
            if (commandString[pos] == 'F' || commandString[pos] == 'f' || commandString[pos] == 'B' || commandString[pos] == 'b') // Check for syntax in Foreground or background mode.
            {
                pos++;
                if (not (isprint(commandString[pos]))) // Check whether the assigned character is printable.
                {
                    badPos = pos;
                    return 1;
                }
            }
            if (commandString[pos] == 'C' || commandString[pos] == 'c') // No other characters should be present after C except the string reaches the end or another command word is called.
            {
                if (not (Command(commandString, pos) && (pos != commandString.size())))
                {
                badPos = pos;
                return 1;
                }
            }
        }
    pos = 0; realNum = 0; row = 1; column = 1; temp = 0; // give these values to default.
    
    while (pos < commandString.size()) // Plot the line
    {
        if (commandString[pos] == 'H' || commandString[pos] == 'h') // When detects the horizontal line command, check for following digits.
        {
            temp = pos; // Temporary copy of pos. If the line is out of grid, this variable will give the position of 'H'.
            pos++; // Check for the first digit
            if (processHorVstep(commandString, pos, realNum)) // Perform for a H or V command.
            {
                if (mode == FG) // Foreground
                {
                    if(plotLine(row, column, realNum, HORIZ, plotChar, FG)) // Plotline
                    {
                    column += realNum; //If true, chenge the current position.
                    }
                    else {
                        badPos = temp;
                        return 2; // If out of grid. The variable "temp" will give the position of 'H'.
                    }
                }
                else // Background
                {
                    if(plotLine(row, column, realNum, HORIZ, plotChar, BG))
                    {
                    column += realNum; //If true, chenge the current position.
                    }
                    else
                    {
                        badPos = temp;
                        return 2; // Out of grid. The variable "temp" will give the position of 'H'.
                    }
                }
            }
        }
        if (commandString[pos] == 'V' || commandString[pos] == 'v') // V is basically the same as H.
        {
            temp = pos; // Temporary copy of pos. If the line is out of grid, this variable will give the position of 'H'.
            pos++;
            if (processHorVstep(commandString, pos, realNum))
            {
                if (mode == FG) // Foreground
                {
                    if(plotLine(row, column, realNum, VERT, plotChar, FG))
                    {
                    row += realNum; //If true, chenge the current position.
                    }
                    else {
                        badPos = temp;
                        return 2; // If out of grid. The variable "temp" will give the position of 'H'.
                    }
                }
                else
                {
                    if(plotLine(row, column, realNum, VERT, plotChar, BG))
                    {
                    row += realNum; //If true, chenge the current position.
                    }
                    else {
                        badPos = temp;
                        return 2; // Out of grid. The variable "temp" will give the position of 'H'.
                    }
                }
            }
        }
        if (commandString[pos] == 'F' || commandString[pos] == 'f') // Check for Foreground or background mode.
        {
            mode = FG; // Foreground
            pos++;
            plotChar = commandString[pos];
            pos++; // If the command is excuted, move to next position.
        }
        else if (commandString[pos] == 'B' || commandString[pos] == 'b') //Basically the same as the F.
        {
            mode = BG; // Background
            pos++;
            plotChar = commandString[pos];
            pos++; // If the command is excuted, move to next position.
        }
        if (commandString[pos] == 'C' || commandString[pos] == 'c') // Clear and reset.
        {
            clearGrid();
            row = 1;
            column = 1;
            pos++;
            mode = FG;
            plotChar = '*';
        }
    }
    return 0;
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) // Plot the line function.
{
    bool notOutOfGrid;
    if (dir == VERT) // The check for vertical outline should be rows.
    {
        if (r + distance > 0 && r + distance <= getRows()) // Not outofgrid up or down direction.
            notOutOfGrid = true;
        else
            return false;
    }
    else if (dir == HORIZ) // The check for vertical outline should be columns.
    {
        if (c + distance > 0 && c + distance <= getCols()) // Not outofgrid left or right direction.
            notOutOfGrid = true;
        else
            return false;
    }
    else
        return false;
    if (notOutOfGrid && (fgbg == BG || fgbg == FG) && (isprint(plotChar))) // If not out of the grid, plot each character.
    {
        if (dir == VERT) // Vertically
        {
            if (distance < 0) // Upwards
            {
                for (int count = 0; count >= distance; count--) // Loop to plot each character for a line.
                    if (fgbg == FG || (fgbg == BG && getChar(r + count,c) == ' ')) // If foreground or background and current position is a space, plot the character.
                    setChar(r + count,c,plotChar);
            }
            else if (distance > 0) // Downwards
            {
                for (int count = 0; count <= distance; count++)
                    if (fgbg == FG || (fgbg == BG && getChar(r + count,c) == ' '))
                    setChar(r + count,c,plotChar);
            }
            else // If the distance is equal to 0, plot the current position.
            {
                if (fgbg == FG || (fgbg == 1 && getChar(r,c) == ' '))
                setChar(r,c,plotChar);
            }
        }
        if (dir == HORIZ) //Horizontally
        {
            if (distance < 0) // Basically the same as (dir == VERT).
            {
                for (int count = 0; count >= distance; count--)
                    if (fgbg == FG || (fgbg == BG && getChar(r,c + count) == ' '))
                    setChar(r,c + count,plotChar);
            }
            else if (distance > 0)
            {
                for (int count = 0; count <= distance; count++)
                    if (fgbg == FG || (fgbg == BG && getChar(r,c + count) == ' '))
                    setChar(r,c + count,plotChar);
            }
            else
            {
                if (fgbg == 0 || (fgbg == BG && getChar(r,c) == ' '))
                setChar(r,c,plotChar);
            }
        }
        return true;
    }
    else
        return false;
}

bool processHorVstep(string commandString, int& pos, int& realNum) // Turn strings into executable commands.
{
    int minus = pos; string distanceH = ""; // The string to record the characters.
    if (commandString[minus] == '-') // If the distance is negative, record the negative sign and move on.
    {
        distanceH += commandString[minus];
        pos++;
    }
    for (int count = 0; count < 2; count++) // Only check for two numbers
    {
        if (isdigit(commandString[pos])) // If at this position, the digit is detected, record the digit.
        {
            distanceH += commandString[pos];
            pos++;
        }
        else if (pos == commandString.size()) //If the position is at the last digit of the string.
        {
            if (distanceH.size() == 0 || (distanceH.size() == 1 && distanceH[0] == '-')) // If the 'H' or 'V' or '-' is the last character, syntax error.
            {
                return false;
            }
                realNum = charToInt(distanceH); // If the there is already digits, turn the string into integers and return the call by reference variable.
                return true;
        }
        else if (Command(commandString, pos)) // If a letter is met, if it is a command letter (vhbfc)
        {
            if (distanceH.size() == 0) // If at this position, no digit is not recorded, syntax error.
            {
                return false;
            }
                realNum = charToInt(distanceH); // If another command character is met, it represents the end of the current command. Return the value.
                return true;
        }
        else
        {
            return false; // If at this position, the digit is not detected, syntax error.
        }
    }
    realNum = charToInt(distanceH);
    return true;
}

bool Command(string check, int pos1) // Check for command character.
{
    if ((check[pos1] == 'v' || check[pos1] == 'h' || check[pos1] == 'f' || check[pos1] == 'b' || check[pos1] == 'c' || check[pos1] == 'V' || check[pos1] == 'H' || check[pos1] == 'F' || check[pos1] == 'B' || check[pos1] == 'F' || check[pos1] == 'C'))
    {
        return true;
    }
    return false;
}

int charToInt(string dHV) // Change each character in the string into a integer.
{
    int sum = 0; // Variable for the integer that's gonna be returned.
    if (dHV[0] == '-') // If the minus sign is met, the whole value is negative.
    {
        for (int count = 1; count < dHV.size();count++) // Check digits after the minus sign.
        {
            char a = dHV[count];
            int f = ((int)a) - ((int)'0'); // The character code is consecutive, to '0' is the basic (Like a integer minus zero).
            sum = sum*10 + f; // Give hundredth, tenth position
        }
        sum = (-1) * sum;
    }
    else
    {
        for (int count = 0; count < dHV.size();count++) // Similar to with minus sign.
        {
            char a = dHV[count];
            int f = (a) - ('0');
            sum = sum*10 + f;
        }
    }
    return sum;
}
// End of project 3. Name: Wenjie Mo Email: martinmo@ucla.edu
