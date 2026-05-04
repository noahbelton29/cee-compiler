//
// Created by Nil on 03/05/2026.
//

#include "ast.hpp"

namespace cee {
  NumberNode::NumberNode(const int value) : value(value) {}

  BinaryOpNode::BinaryOpNode(const char op, NodePtr left, NodePtr right) :
    op(op), left(std::move(left)), right(std::move(right)) {}

  IdentifierNode::IdentifierNode(std::string name) : name(std::move(name)) {}

  VariableDeclarationNode::VariableDeclarationNode(std::string type, std::string name, NodePtr initializer) :
    type(std::move(type)), name(std::move(name)), initializer(std::move(initializer)) {}

  ReturnNode::ReturnNode(NodePtr value) : value(std::move(value)) {}
} // namespace cee
