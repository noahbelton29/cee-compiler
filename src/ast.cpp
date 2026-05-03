//
// Created by Nil on 03/05/2026.
//

#include "ast.hpp"

namespace cee {
  NumberNode::NumberNode(const int value) : value(value) {}

  BinaryOpNode::BinaryOpNode(const char op, NodePtr left, NodePtr right) :
    op(op), left(std::move(left)), right(std::move(right)) {}
} // namespace cee
