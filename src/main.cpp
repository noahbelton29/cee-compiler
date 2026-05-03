//
// Created by Nil on 03/05/2026.
//

#include <iostream>

#include "lexer.hpp"
#include "utils.hpp"

int main() {
  cee::Lexer lexer("int x = 5;");
  auto       tokens = lexer.tokenise();

  for (auto &[token_type, value]: tokens) {
    std::cout << cee::token_type_name(token_type) << " -> \"" << value << "\"\n";
  }
}
