/*

  This program is my attempt at answering the second question (question b) in the "Exercises for Section 2.4" in the book "Compilers: Principles, Techniques & Tools"

  This program is a recursive-descent parser for the grammar with the following productions:
  
    S -> S(S)S | (epsilon)

  This grammar is actually impossible to program due to the left recursion problem stated in the book (Section 2.4.5). An equivalent (and programmable) grammar is as follows:

    S -> R
    R -> (S)S | (epsilon)

  To use this program, create a text file with a string that is either a member of this grammar or not.

  Legal strings:

    (empty string)
    ()
    ()()
    ()(())()
    (())

  Illegal Strings:

    )(
    (()
    ()(
    (((()
    ))))

  To compile:

    clang++ ex241b.cpp -o ex241b

  To run:

    ./ex241b <filename>

  If the file contains a legal string, the program will print "[COMPLETE]: The file was parsed successfully".
  
  If there is a syntax error, the file will print "[ERROR]: Syntax Error at character x", where x is the index of the syntax error.

  A bash script for testing all the given test files is also included. You can run it using the following commands:

    chmod 755 ex241b.sh
    ./ex241b.sh

*/
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::cerr;
using std::fstream;
using std::noskipws;

// This function prints a syntax error to the screen.
void syntaxError(int& counter){

  cerr << "[ERROR]: Syntax Error at character " << counter << "\n";
  exit(1);

}

// Moves the lookahead pointer ahead to the next character in the given file IFF the lookahead is a legitimate symbol
// This function is only called IFF the lookahead symbol is a recognised symbol within the grammar, which is why we don't actually match the lookahead with any symbols - it has to be matched to call this function
// This can be seen through the use of the switch statement in the stmt() function
void match(char& lookahead, int& counter, fstream& sourceCode){

  if (!(sourceCode >> noskipws >> lookahead)) syntaxError(counter);
  ++counter;

}

// Recursive funtion that parses the string
void stmt(char& lookahead, int& counter, fstream& sourceCode){

  switch(lookahead){

    case '(':
      match(lookahead, counter, sourceCode);
      stmt(lookahead, counter, sourceCode);
      match(lookahead, counter, sourceCode);
      stmt(lookahead, counter, sourceCode);
      break;
    case ')':
      break;
    case 10:
      break;
    case 0:
      break;
    default:
      syntaxError(counter);
      break;

  }

}

int main(int argc, char** argv){

  // Ensure that a filename has been entered
  if (argc != 2){

    cerr << "[USAGE]:\n\t./ex241b <filename>\n";
    return 1;

  }

  fstream sourceCode(argv[1], fstream::in); // Open given file
  
  // Ensure that the file exists
  if (!sourceCode.is_open()){

    cerr << "The file " << argv[1] << " cannot be found\n";
    return 1;

  }

  char lookahead; // This variable will hold the current symbol we are parsing
  int counter = 0; // Counts the indexes to return a syntax error where appropriate

  sourceCode >> noskipws >> lookahead; // Read in the first character
  stmt(lookahead, counter, sourceCode); // Calling this recursive function parsing in the string

  // If we haven't reached the end of the string but the parsing process is complete, then this string is malformed
  if (lookahead != 10 && lookahead != 0) syntaxError(counter);

  // If we make it to the end of the program, then the string is a legal string
  cout << "[COMPLETE]: The file was parsed successfully" << endl;

  return 0;

}
