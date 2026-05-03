//
// Created by Nil on 03/05/2026.
//

#include "../include/lexer.hpp"

#include <iostream>

namespace cee {
  Lexer::Lexer(std::string source) : source(std::move(source)) {}

  [[nodiscard]] char Lexer::peek() const {
    if (position >= source.size())
      return '\0';
    return source[position];
  }
  char Lexer::advance() { return source[position++]; }

  void Lexer::skip_whitespace() {
    while (isspace(peek()))
      advance();
  }

  Token Lexer::read_number() {
    std::string number;
    while (isdigit(peek())) {
      number += advance();
    }
    return {TokenType::NUMBER, number};
  }

  std::vector<Token> Lexer::tokenise() {
    std::vector<Token> tokens;

    while (true) {
      skip_whitespace();

      if (position >= source.size()) {
        tokens.push_back({TokenType::END_OF_FILE, ""});
        break;
      }

      const char current_char = peek();

      if (isdigit(current_char)) {
        tokens.push_back(read_number());
        continue;
      }

      advance();
      switch (current_char) {
        case '+':
          tokens.push_back({TokenType::PLUS, "+"});
          break;
        case '-':
          tokens.push_back({TokenType::MINUS, "-"});
          break;
        case '*':
          tokens.push_back({TokenType::STAR, "*"});
          break;
        case '/':
          tokens.push_back({TokenType::SLASH, "/"});
          break;
        case '(':
          tokens.push_back({TokenType::LPAREN, "("});
          break;
        case ')':
          tokens.push_back({TokenType::RPAREN, ")"});
          break;
        default:
          std::cerr << "Unknown character: " << current_char << "\n";
      }
    }

    return tokens;
  }
} // namespace cee
