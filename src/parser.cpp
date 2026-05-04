//
// Created by Nil on 03/05/2026.
//

#include "parser.hpp"

#include <stdexcept>

namespace cee {
  Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

  Token &Parser::peek() { return tokens[position]; }

  Token &Parser::advance() { return tokens[position++]; }

  NodePtr Parser::parse() {
    auto program = std::make_unique<ProgramNode>();
    while (peek().token_type != TokenType::END_OF_FILE) {
      program->statements.push_back(parse_statement());
    }
    return program;
  }

  NodePtr Parser::parse_primary() {
    if (peek().token_type == TokenType::NUMBER_LITERAL) {
      auto [token_type, value] = advance();
      return std::make_unique<NumberNode>(std::stod(value));
    }

    if (peek().token_type == TokenType::IDENTIFIER) {
      auto [token_type, value] = advance();
      return std::make_unique<IdentifierNode>(value);
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

  NodePtr Parser::parse_function() {
    const std::string return_type = advance().value;

    if (peek().token_type != TokenType::IDENTIFIER) {
      throw std::runtime_error("Expected function name");
    }
    const std::string name = advance().value;

    if (peek().token_type != TokenType::LPAREN) {
      throw std::runtime_error("Expected '(' after function name");
    }
    advance();

    // TODO: params
    if (peek().token_type != TokenType::RPAREN) {
      throw std::runtime_error("Expected ')'");
    }
    advance();

    NodePtr body = parse_block();

    return std::make_unique<FunctionNode>(return_type, name, std::move(body));
  }

  NodePtr Parser::parse_block() {
    if (peek().token_type != TokenType::LBRACE) {
      throw std::runtime_error("Expected '{'");
    }
    advance();

    std::vector<NodePtr> statements;
    while (peek().token_type != TokenType::RBRACE) {
      if (peek().token_type == TokenType::END_OF_FILE) {
        throw std::runtime_error("Expected '}' but got EOF");
      }
      statements.push_back(parse_statement());
    }

    advance();
    return std::make_unique<BlockNode>(std::move(statements));
  }

  NodePtr Parser::parse_return() {
    advance();

    NodePtr expression = parse_expression();

    if (peek().token_type != TokenType::SEMICOLON) {
      throw std::runtime_error("Expected ';' after return value");
    }
    advance();

    return std::make_unique<ReturnNode>(std::move(expression));
  }

  NodePtr Parser::parse_variable_declaration() {
    const std::string type = advance().value;

    if (peek().token_type != TokenType::IDENTIFIER) {
      throw std::runtime_error("Expected variable name after type");
    }
    const std::string name = advance().value;

    if (peek().token_type != TokenType::EQUALS) {
      throw std::runtime_error("Expected '=' after variable name");
    }
    advance();
    NodePtr initializer = parse_expression();

    if (peek().token_type != TokenType::SEMICOLON) {
      throw std::runtime_error("Expected ';' after initializer");
    }
    advance();

    return std::make_unique<VariableDeclarationNode>(type, name, std::move(initializer));
  }

  NodePtr Parser::parse_statement() {
    if (peek().token_type == TokenType::KW_INT || peek().token_type == TokenType::KW_FLOAT ||
        peek().token_type == TokenType::KW_CHAR || peek().token_type == TokenType::KW_VOID) {

      if (position + 2 < tokens.size() && tokens[position + 2].token_type == TokenType::LPAREN) {
        return parse_function();
      }
      return parse_variable_declaration();
    }

    if (peek().token_type == TokenType::KW_RETURN) {
      return parse_return();
    }

    return parse_expression();
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
