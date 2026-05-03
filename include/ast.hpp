//
// Created by Nil on 03/05/2026.
//

#pragma once

#include <memory>

namespace cee {
  struct ASTNode {
    virtual ~ASTNode() = default;
  };

  using NodePtr = std::unique_ptr<ASTNode>;

  struct NumberNode : ASTNode {
    int value;
    explicit NumberNode(int value);
  };

  struct BinaryOpNode : ASTNode {
    char    op;
    NodePtr left, right;
    BinaryOpNode(char op, NodePtr left, NodePtr right);
  };
} // namespace cee
