//
// Created by Nil on 03/05/2026.
//

#include "lexer.hpp"

#include <iostream>
#include <unordered_map>

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

  Token Lexer::read_identifier() {
    std::string ident;
    while (isalnum(peek()) || peek() == '_') {
      ident += advance();
    }

    // keyword lookup table
    static const std::unordered_map<std::string, TokenType> keywords = {
            {"int", TokenType::KW_INT},   {"float", TokenType::KW_FLOAT},   {"char", TokenType::KW_CHAR},
            {"void", TokenType::KW_VOID}, {"return", TokenType::KW_RETURN}, {"if", TokenType::KW_IF},
            {"else", TokenType::KW_ELSE}, {"while", TokenType::KW_WHILE},   {"for", TokenType::KW_FOR},
    };

    if (const auto it = keywords.find(ident); it != keywords.end()) {
      return {it->second, ident};
    }

    return {TokenType::IDENTIFIER, ident};
  }

  Token Lexer::read_number() {
    std::string number;
    while (isdigit(peek())) {
      number += advance();
    }
    return {TokenType::NUMBER_LITERAL, number};
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

      // number detection
      if (isdigit(current_char)) {
        tokens.push_back(read_number());
        continue;
      }

      // identifier detection
      if (isalpha(current_char) || current_char == '_') {
        tokens.push_back(read_identifier());
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
        case '=':
          tokens.push_back({TokenType::EQUALS, "="});
          break;
        case ';':
          tokens.push_back({TokenType::SEMICOLON, ";"});
          break;
        case '{':
          tokens.push_back({TokenType::LBRACE, "{"});
          break;
        case '}':
          tokens.push_back({TokenType::RBRACE, "}"});
          break;
        default:
          std::cerr << "Unknown character: " << current_char << "\n";
      }
    }

    return tokens;
  }
} // namespace cee
