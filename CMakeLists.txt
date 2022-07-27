cmake_minimum_required(VERSION 3.10)

project(mylisp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
  types.cpp     types.h
  repl.cpp      repl.h
  reader.cpp    reader.h
  printer.cpp   printer.h
  evaluer.cpp   evaluer.h
  linenoise.hpp
  main.cpp)

list(TRANSFORM SOURCES PREPEND "${STEP}/")

add_executable(mylisp ${SOURCES})
