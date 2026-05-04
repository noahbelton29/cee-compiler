//
// Created by Nil on 03/05/2026.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace cee {
  struct ASTNode {
    virtual ~ASTNode() = default;
  };

  using NodePtr = std::unique_ptr<ASTNode>;

  struct ProgramNode : ASTNode {
    std::vector<NodePtr> statements;
  };

  struct NumberNode : ASTNode {
    int value;
    explicit NumberNode(int value);
  };

  struct BinaryOpNode : ASTNode {
    char    op;
    NodePtr left, right;
    BinaryOpNode(char op, NodePtr left, NodePtr right);
  };

  struct IdentifierNode : ASTNode {
    std::string name;
    explicit IdentifierNode(std::string name);
  };

  struct BlockNode : ASTNode {
    std::vector<NodePtr> statements;
    explicit BlockNode(std::vector<NodePtr> statements);
  };

  struct FunctionNode : ASTNode {
    std::string return_type;
    std::string name;
    NodePtr     body;
    FunctionNode(std::string return_type, std::string name, NodePtr body);
  };

  struct VariableDeclarationNode : ASTNode {
    std::string type;
    std::string name;
    NodePtr     initializer;

    VariableDeclarationNode(std::string type, std::string name, NodePtr initializer);
  };

  struct ReturnNode : ASTNode {
    NodePtr value;
    explicit ReturnNode(NodePtr value);
  };
} // namespace cee
