//
// Created by Nil on 03/05/2026.
//

#include "utils.hpp"

namespace cee {
  std::string token_type_name(const TokenType token_type) {
    switch (token_type) {
      case TokenType::NUMBER_LITERAL:
        return "NUMBER";
      case TokenType::IDENTIFIER:
        return "IDENTIFIER";
      case TokenType::KW_INT:
        return "KW_INT";
      case TokenType::KW_FLOAT:
        return "KW_FLOAT";
      case TokenType::KW_CHAR:
        return "KW_CHAR";
      case TokenType::KW_VOID:
        return "KW_VOID";
      case TokenType::KW_RETURN:
        return "KW_RETURN";
      case TokenType::KW_IF:
        return "KW_IF";
      case TokenType::KW_ELSE:
        return "KW_ELSE";
      case TokenType::KW_WHILE:
        return "KW_WHILE";
      case TokenType::KW_FOR:
        return "KW_FOR";
      case TokenType::PLUS:
        return "PLUS";
      case TokenType::MINUS:
        return "MINUS";
      case TokenType::STAR:
        return "STAR";
      case TokenType::SLASH:
        return "SLASH";
      case TokenType::LPAREN:
        return "LPAREN";
      case TokenType::RPAREN:
        return "RPAREN";
      case TokenType::EQUALS:
        return "EQUALS";
      case TokenType::SEMICOLON:
        return "SEMICOLON";
      case TokenType::END_OF_FILE:
        return "EOF";
    }
    return "Unknown token type";
  }
} // namespace cee
