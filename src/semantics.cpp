//
// Created by Nil on 04/05/2026.
//

#include "semantics.hpp"
#include <stdexcept>

namespace cee {
  // Symbol Table
  void SymbolTable::push_scope() { scopes.emplace_back(); }
  void SymbolTable::pop_scope() { scopes.pop_back(); }
  void SymbolTable::declare(const Symbol &symbol) {
    auto &current_scope = scopes.back();
    if (current_scope.count(symbol.name)) {
      throw std::runtime_error("Duplicate declaration: '" + symbol.name + "'");
    }
    current_scope[symbol.name] = symbol;
  }
  Symbol *SymbolTable::lookup(const std::string &name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      auto found = it->find(name);
      if (found != it->end())
        return &found->second;
    }
    return nullptr;
  }

  // Semantic Analyser
  void SemanticAnalyser::analyse(ASTNode *node) { analyse_program(dynamic_cast<ProgramNode *>(node)); }

  void SemanticAnalyser::analyse_program(const ProgramNode *node) {
    symbol_table.push_scope();
    for (const auto &statement: node->statements) {
      analyse_statement(statement.get());
    }
    symbol_table.pop_scope();
  }

  void SemanticAnalyser::analyse_function(const FunctionNode *node) {
    symbol_table.push_scope();
    analyse_block(dynamic_cast<BlockNode *>(node->body.get()));
    symbol_table.pop_scope();
  }

  void SemanticAnalyser::analyse_block(const BlockNode *node) {
    symbol_table.push_scope();
    for (const auto &statement: node->statements) {
      analyse_statement(statement.get());
    }
    symbol_table.pop_scope();
  }

  void SemanticAnalyser::analyse_var_decl(const VariableDeclarationNode *node) {
    analyse_expression(node->initializer.get());
    symbol_table.declare({node->type, node->name});
  }

  void SemanticAnalyser::analyse_return(const ReturnNode *node) { analyse_expression(node->value.get()); }

  void SemanticAnalyser::analyse_expression(ASTNode *node) {
    if (const auto *identifier_node = dynamic_cast<IdentifierNode *>(node)) {
      if (!symbol_table.lookup(identifier_node->name)) {
        throw std::runtime_error("Undeclared variable: '" + identifier_node->name + "'");
      }
    } else if (const auto *binary_op_node = dynamic_cast<BinaryOpNode *>(node)) {
      analyse_expression(binary_op_node->left.get());
      analyse_expression(binary_op_node->right.get());
    }
  }

  void SemanticAnalyser::analyse_statement(ASTNode *node) {
    if (const auto *function_node = dynamic_cast<FunctionNode *>(node)) {
      analyse_function(function_node);
    } else if (const auto *variable_declaration_node = dynamic_cast<VariableDeclarationNode *>(node)) {
      analyse_var_decl(variable_declaration_node);
    } else if (const auto *return_node = dynamic_cast<ReturnNode *>(node)) {
      analyse_return(return_node);
    } else if (auto *binary_op_node = dynamic_cast<BinaryOpNode *>(node)) {
      analyse_expression(binary_op_node);
    } else if (auto *identifier_node = dynamic_cast<IdentifierNode *>(node)) {
      analyse_expression(identifier_node);
    }
  }

} // namespace cee
