//
// Created by Nil on 03/05/2026.
//

#include <fstream>
#include <iostream>
#include <sstream>

#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "semantics.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: cee <file>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error: could not open file '" << argv[1] << "'\n";
    return 1;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  const std::string source = buffer.str();

  cee::Lexer lexer(source);
  auto       tokens = lexer.tokenise();

  std::cout << "Tokens:\n";
  for (auto &[token_type, value]: tokens) {
    std::cout << cee::token_type_name(token_type) << " -> \"" << value << "\"\n";
  }
  std::cout << "\n";

  std::cout << "AST:\n";
  cee::Parser parser(tokens);
  const auto  ast = parser.parse();
  cee::print_ast(ast);

  try {
    cee::SemanticAnalyser analyser;
    analyser.analyse(ast.get());
    std::cout << "Semantic analysis passed\n\n";
  } catch (const std::runtime_error &e) {
    std::cerr << "Semantic error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
