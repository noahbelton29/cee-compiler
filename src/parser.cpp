//
// Created by Nil on 03/05/2026.
//

#include "parser.hpp"

#include <stdexcept>

namespace cee {
  Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

  Token &Parser::peek() { return tokens[position]; }

  Token &Parser::advance() { return tokens[position++]; }

  NodePtr Parser::parse() { return parse_expression(); }

  NodePtr Parser::parse_primary() {
    if (peek().token_type == TokenType::NUMBER_LITERAL) {
      auto [token_type, value] = advance();
      return std::make_unique<NumberNode>(std::stod(value));
    }

    if (peek().token_type == TokenType::LPAREN) {
      advance();
      NodePtr expression = parse_expression();
      if (peek().token_type != TokenType::RPAREN) {
        throw std::runtime_error("Expected ')'");
      }
      advance();
      return expression;
    }

    throw std::runtime_error("Unexpected token: " + peek().value);
  }

  NodePtr Parser::parse_expression(const int min_precedence) {
    NodePtr left = parse_primary();

    while (true) {
      const TokenType op         = peek().token_type;
      const int       precedence = get_precedence(op);

      if (precedence < min_precedence)
        break;
      char    op_char = advance().value[0];
      NodePtr right   = parse_expression(precedence + 1);
      left            = std::make_unique<BinaryOpNode>(op_char, std::move(left), std::move(right));
    }

    return left;
  }

  int Parser::get_precedence(const TokenType token_type) {
    switch (token_type) {
      case TokenType::PLUS:
      case TokenType::MINUS:
        return 1;
      case TokenType::STAR:
      case TokenType::SLASH:
        return 2;
      default:
        return -1;
    }
  }
} // namespace cee
