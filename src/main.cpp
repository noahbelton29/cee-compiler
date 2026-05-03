//
// Created by Nil on 03/05/2026.
//

#include <iostream>

#include "../include/lexer.hpp"
#include "../include/utils.hpp"

int main() {
  cee::Lexer lexer("3 + 5 * (10 - 2)");
  auto       tokens = lexer.tokenise();

  for (auto &[token_type, value]: tokens) {
    std::cout << cee::token_type_name(token_type) << " -> \"" << value << "\"\n";
  }
}
