//
// Created by Nil on 03/05/2026.
//

#include "utils.hpp"
#include "ast.hpp"

#include <iostream>

namespace cee {
  void print_ast(const NodePtr &node, const int indent) {
    const std::string pad(indent * 2, ' ');

    if (const auto *number_node = dynamic_cast<cee::NumberNode *>(node.get())) {
      std::cout << pad << "NumberNode(" << number_node->value << ")\n";
    } else if (const auto *binary_op_node = dynamic_cast<cee::BinaryOpNode *>(node.get())) {
      std::cout << pad << "BinaryOpNode('" << binary_op_node->op << "')\n";
      std::cout << pad << "  left:\n";
      print_ast(binary_op_node->left, indent + 2);
      std::cout << pad << "  right:\n";
      print_ast(binary_op_node->right, indent + 2);
    } else if (const auto *var_decl_node = dynamic_cast<cee::VariableDeclarationNode *>(node.get())) {
      std::cout << pad << "VariableDeclarationNode(" << var_decl_node->type << " " << var_decl_node->name << ")\n";
      std::cout << pad << "  initializer:\n";
      print_ast(var_decl_node->initializer, indent + 2);
    } else if (const auto *return_node = dynamic_cast<cee::ReturnNode *>(node.get())) {
      std::cout << pad << "ReturnNode\n";
      std::cout << pad << "  value:\n";
      print_ast(return_node->value, indent + 2);
    } else if (const auto *identifier_node = dynamic_cast<cee::IdentifierNode *>(node.get())) {
      std::cout << pad << "IdentifierNode(" << identifier_node->name << ")\n";
    } else if (const auto *function_node = dynamic_cast<cee::FunctionNode *>(node.get())) {
      std::cout << pad << "FunctionNode(" << function_node->return_type << " " << function_node->name << ")\n";
      std::cout << pad << "  body:\n";
      print_ast(function_node->body, indent + 2);
    } else if (const auto *block_node = dynamic_cast<cee::BlockNode *>(node.get())) {
      std::cout << pad << "BlockNode\n";
      for (const auto &statement: block_node->statements) {
        print_ast(statement, indent + 2);
      }
    } else if (const auto *program_node = dynamic_cast<cee::ProgramNode *>(node.get())) {
      std::cout << pad << "ProgramNode\n";
      for (const auto &statement: program_node->statements) {
        print_ast(statement, indent + 2);
      }
    } else {
      std::cout << pad << "UnknownNode\n";
    }
  }

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
      case TokenType::LBRACE:
        return "LBRACE";
      case TokenType::RBRACE:
        return "RBRACE";
      case TokenType::END_OF_FILE:
        return "EOF";
    }
    return "Unknown token type";
  }
} // namespace cee
