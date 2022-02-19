// Existing libraries
#include <iostream>

// LLVM || MLIR headers
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Support/TargetSelect.h"

// My headers
#include "Lexer.h"
#include "Context.h"
using namespace Lili;

static llvm::cl::opt<std::string> sourceCodeFile(llvm::cl::Positional, llvm::cl::desc("<input C++ file>"), 
                                                llvm::cl::init("-"), llvm::cl::value_desc("filename"));

int main(int argc, char** argv){

    // Register all command line options
    mlir::registerMLIRContextCLOptions(); // Allows passing of the following flags:
                                                // --mlir-disable-threading
                                                // --mlir-print-op-on-diagnostic
                                                // --mlir-print-stacktrace-on-diagnostic
    mlir::registerPassManagerCLOptions(); // Allows passing of the following flags:
                                                // --pass-pipeline-crash-reproducer
                                                // --pass-pipeline-local-reproducer
    llvm::InitializeAllTargetInfos();

    // Parses command line info and options - filename passed, flags etc.
    llvm::cl::ParseCommandLineOptions(argc, argv);
    std::cout << sourceCodeFile << std::endl;

    return 0;

}