//
// Created by Nil on 03/05/2026.
//

#pragma once

#include <vector>
#include "ast.hpp"
#include "lexer.hpp"

namespace cee {
  class Parser {
    std::vector<Token> tokens;
    size_t             position = 0;

  public:
    explicit Parser(std::vector<Token> tokens);
    NodePtr parse();

  private:
    Token     &peek();
    Token     &advance();
    NodePtr    parse_expression(int min_precedence = 0);
    NodePtr    parse_statement();
    NodePtr    parse_primary();
    NodePtr    parse_variable_declaration();
    NodePtr    parse_return();
    NodePtr    parse_block();
    NodePtr    parse_function();
    static int get_precedence(TokenType token_type);
  };
} // namespace cee
