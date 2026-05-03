cmake_minimum_required(VERSION 4.1)
project(cee)

add_executable(cee
  src/main.cpp
  src/lexer.cpp
  src/utils.cpp
  src/ast.cpp
)

target_include_directories(cee PUBLIC include/)