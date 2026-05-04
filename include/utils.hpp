//
// Created by Nil on 03/05/2026.
//

#pragma once

#include "ast.hpp"
#include "lexer.hpp"

#include <string>

namespace cee {
  std::string token_type_name(TokenType token_type);
  void        print_ast(const NodePtr &node, int indent = 0);
} // namespace cee
