cmake_minimum_required(VERSION 3.10)

project(Lili++)

find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(include/)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
link_directories(${LLVM_BUILD_LIBRARY_DIR})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++14")

set(CMAKE_MODULE_PATH ${LLVM_CMAKE_DIR} ${MLIR_CMAKE_DIR})

include(AddLLVM)
include(TableGen)
include(AddMLIR)

# Now build our tools
add_executable(${PROJECT_NAME} Lili++.cpp)
llvm_update_compile_flags(${PROJECT_NAME})

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
message(dialects=${dialect_libs})

set(LIBS
${dialect_libs}
${conversion_libs}
MLIRAnalysis
MLIRDialect
MLIROptLib
MLIRParser
MLIRPass
MLIRSPIRV
MLIRSPIRVTestPasses
MLIRSPIRVTransforms
MLIRTransforms
MLIRTransformUtils
MLIRTestDialect
MLIRTestIR
MLIRTestPass
MLIRTestTransforms
MLIRSupport
MLIRIR
MLIROptLib
LLVMSupport
LLVMCore
LLVMAsmParser
)

target_link_libraries(${PROJECT_NAME} ${LIBS})