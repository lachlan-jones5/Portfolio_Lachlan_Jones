#include <iostream>
#include <fstream>

// Gives a Syntax error
void throwSyntaxError(int& counter){

    std::cerr << "Syntax error at character " << counter << "\n";
    exit(1);

}

// This matches the current lookahead to the given string, and ends the program with a syntax error if the characters don't match
void match(char& lookahead, int& counter, std::fstream& sourceCodeStream){

  if (!(sourceCodeStream >> std::noskipws >> lookahead)) {

      std::cout << "File was successfully parsed." << std::endl;
      exit(0);

  }

}

// Parse the given string
void stmt(char& lookahead, int& counter, std::fstream& sourceCodeStream){

  switch(lookahead){

    case 'a':
      match(lookahead, counter, sourceCodeStream);
      break;
    case '+':
      match(lookahead, counter, sourceCodeStream);
      stmt(lookahead, counter, sourceCodeStream);
      stmt(lookahead, counter, sourceCodeStream);
      break;
    case '-':
      match(lookahead, counter, sourceCodeStream);
      stmt(lookahead, counter, sourceCodeStream);
      stmt(lookahead, counter, sourceCodeStream);
      break;
    case 10:
      std::cout << "File was successfully parsed." << std::endl;
      exit(0);
      break;
    default:
      throwSyntaxError(counter);
      break;

  }

  counter++;

}

void parseFile(char* filename){

  char c;
  int counter = 0;
  std::fstream sourceCodeStream(filename, std::fstream::in);
  if (!sourceCodeStream.is_open()) {

    std::cerr << "The file " << filename << " does not exist\n";
    exit(1); 

  }

  sourceCodeStream >> std::noskipws >> c;
  while(sourceCodeStream) stmt(c, counter, sourceCodeStream);

}

int main(int argc, char** argv){

  parseFile(argv[1]);
  return 0;

}
