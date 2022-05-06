#include "Lexer.h"
#include "Token.h"
#include "Tag.h"
#include "Num.h"
#include "WordToken.h"
#include <fstream>

int main(int argc, const char** argv){

  // Ensure that a filename has been entered
  if (argc != 2){

    std::cerr << "[USAGE]:\n\t./Lexer <filename>\n";
    return 1;

  }

  std::fstream sourceCode(argv[1], std::fstream::in); // Open given file
  
  // Ensure that the file exists
  if (!sourceCode.is_open()){

    std::cerr << "The file " << argv[1] << " cannot be found\n";
    return 1;

  }

    Lexer lexer;
    while (sourceCode){
        lexer.scan(sourceCode);
    }

    return 0;

}