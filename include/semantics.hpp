//
// Created by Nil on 04/05/2026.
//

#pragma once

#include <string>
#include <unordered_map>
#include "ast.hpp"

namespace cee {
  struct Symbol {
    std::string type;
    std::string name;
  };

  class SymbolTable {
    std::vector<std::unordered_map<std::string, Symbol>> scopes;

  public:
    void    push_scope();
    void    pop_scope();
    void    declare(const Symbol &symbol);
    Symbol *lookup(const std::string &name);
  };

  class SemanticAnalyser {
    SymbolTable symbol_table;

  public:
    void analyse(ASTNode *node);

  private:
    void analyse_program(const ProgramNode *node);
    void analyse_function(const FunctionNode *node);
    void analyse_block(const BlockNode *node);
    void analyse_statement(ASTNode *node);
    void analyse_var_decl(const VariableDeclarationNode *node);
    void analyse_return(const ReturnNode *node);
    void analyse_expression(ASTNode *node);
  };
} // namespace cee
