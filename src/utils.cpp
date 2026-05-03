//
// Created by Nil on 03/05/2026.
//

#include "../include/utils.hpp"

namespace cee {
  std::string token_type_name(const TokenType token_type) {
    switch (token_type) {
      case TokenType::NUMBER:
        return "NUMBER";
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
      case TokenType::END_OF_FILE:
        return "EOF";
    }
    return "Unknown token type";
  }
} // namespace cee
