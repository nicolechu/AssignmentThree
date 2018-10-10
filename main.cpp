/* Nicole Chu
* 2290152
* nichu@chapman.edu
* 350-01
* Assignment #3
*/

/*
 * This file iterates through the user's input file to determine if there are any mismatched
   delimiters. Any left-side delimiters (e.g. '(', '[', '{') are pushed onto a character stack
   and their corresponding line numbers are pushed to an integer stack. Right-side delimiters
   are compared to the delimiter at the top of the char stack. If the delimiters match, the char
   and int stacks are popped. If not, an error message is displayed to the user and the program
   terminates.
 */

#include <iostream>
#include <fstream>
#include "GenStack.h"

using namespace std;

int main(int argc, char* argv[])
{
  GenStack<char> charStack(50);
  GenStack<int> lineStack(50);
  string fileName;

  /*
   * This switch case reads the user's command line argument. If they include their file in
     the command line, the file name is assigned the fileName string. If they do not include
     the file in the command line, they are prompted to enter their file name. If they put
     more than one file name, an error message is displayed.
   */
  switch(argc)
  {
    case 1:
      cout << "Please enter the name of your file: ";
      cin >> fileName;
      break;
    case 2:
      fileName = argv[1];
      break;
    default:
      cout << "ERROR: Please enter one file name." << endl;
      exit;
  }

  /*
   * The while loop runs while process is true. If the user's file has no mismatched delimiters,
     they are asked if they would like to process another file. If they choose not to, process is
     set to false and the loop ends.
   */
  bool process = true;

  while(process)
  {
    ifstream inputFile(fileName);
    string line;
    int lineCount = 0;

    /*
     * After the user's file is opened using the ifsream object, this while loop iterates through
       the lines of the file.
     */
    while(getline(inputFile, line))
    {
      /*
       * lineCount is incremented to keep track of which line each delimiter is on.
       */
      lineCount++;

      /*
       * The for loop iterates through each character of the lines of the file to look for delimiters
         in each line.
       */
      for(int i = 0; i < line.length(); i++)
      {
        /*
         * If the line contains a left-side delimiter, it is pushed onto the charStack and its line
           number is pushed onto the lineStack.
         */
        if(line[i] == '(' || line[i] == '[' || line[i] =='{')
        {
          charStack.push(line[i]);
          lineStack.push(lineCount);
        }

        if(line[i] == ')')
        {
          /*
           * If the line finds a right-side parenthesis, various tests take place.
           * If the stack is empty, an error message is output saying that a left parenthesis is expected.
           * If the stack contains a left parenthesis on top, charStack and lineStack are popped.
           * If the stack does not contain a left parenthesis on top, respective error messages are displayed.
           * After error messages are displayed, the program exits.
           */
          if(charStack.isEmpty())
          {
            cout << "Line " << lineCount << ": Expected (" << endl;
            return 0;
          }
          else if(charStack.peek() == '(')
          {
            charStack.pop();
            lineStack.pop();
          }
          else if(charStack.peek() == '[')
          {
            cout << "Line " << lineStack.peek() << ": Expected ] and found )" << endl;
            return 0;
          }
          else if(charStack.peek() == '{')
          {
            cout << "Line " << lineStack.peek() << ": Expected } and found )" << endl;
            return 0;
          }
        }

        if(line[i] == ']')
        {
          /*
           * If the line finds a right-side bracket, various tests take place.
           * If the stack is empty, an error message is output saying that a left bracket is expected.
           * If the stack contains a left bracket on top, charStack and lineStack are popped.
           * If the stack does not contain a left bracket on top, respective error messages are displayed.
           * After error messages are displayed, the program exits.
           */
          if(charStack.isEmpty())
          {
            cout << "Line " << lineCount << ": Expected [" << endl;
            return 0;
          }
          else if(charStack.peek() == '[')
          {
            charStack.pop();
            lineStack.pop();
          }
          else if(charStack.peek() == '(')
          {
            cout << "Line " << lineStack.peek() << ": Expected ) and found ]" << endl;
            return 0;
          }
          else if(charStack.peek() == '{')
          {
            cout << "Line " << lineStack.peek() << ": Expected } and found ]" << endl;
            return 0;
          }
        }

        if(line[i] == '}')
        {
          /*
           * If the line finds a right-side brace, various tests take place.
           * If the stack is empty, an error message is output saying that a left brace is expected.
           * If the stack contains a left brace on top, charStack and lineStack are popped.
           * If the stack does not contain a left brace on top, respective error messages are displayed.
           * After error messages are displayed, the program exits.
           */
          if(charStack.isEmpty())
          {
            cout << "Line " << lineCount << ": Expected {" << endl;
            return 0;
          }
          else if(charStack.peek() == '{')
          {
            charStack.pop();
            lineStack.pop();
          }
          else if(charStack.peek() == '[')
          {
            cout << "Line " << lineStack.peek() << ": Expected ] and found }" << endl;
            return 0;
          }
          else if(charStack.peek() == '(')
          {
            cout << "Line " << lineStack.peek() << ": Expected ) and found }" << endl;
            return 0;
          }
        }
      }
    }

    /*
     * After looping through the file, the program checks if charStack is empty. If not, error
       messages are displayed according to which delimiter is needed. For any remaining braces,
       the error message displayed depends on if there is only one delimiter left on charStack
       or not. If there is only one character left on charStack, the user is informed that the
       program has reached the end of the file and requires one more right brace.
     */
    if(!charStack.isEmpty())
    {
      if(charStack.peek() == '(')
      {
        cout << "Line " << lineStack.peek() << ": Expected )" << endl;
        return 0;
      }
      if(charStack.peek() == '[')
      {
        cout << "Line " << lineStack.peek() << ": Expected ]" << endl;
        return 0;
      }
      if(charStack.peek() == '{' && charStack.getTop() > 0)
      {
        cout << "Line " << lineStack.peek() << ": Expected }" << endl;
        return 0;
      }
      if(charStack.peek() == '{' && charStack.getTop() == 0)
      {
        cout << "Reached end of file. Expected }" << endl;
        return 0;
      }
    }
    else
    {
      /*
       * If there are no errors, the user is told there are no mismatched delimiters and is
         asked if they would like to process another file. If yes, they are asked to enter the
         name of their next file and the while loop repeats. If not, process is set to false and
         the program breaks out of the loop.
       */
      cout << "Reached end of file. No mismatched delimeters." << endl;
      string input;
      cout << "Would you like to process another file? (y/n): ";
      cin >> input;
      if(input == "N" || input == "n")
        process = false;
      else
      {
        cout << "Please enter the name of your next file: ";
        cin >> fileName;
      }
    }
  }

  return 0;
}
