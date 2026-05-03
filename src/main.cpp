//
// Created by Nil on 03/05/2026.
//

#include <iostream>

#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "utils.hpp"

void print_ast(const cee::NodePtr &node, const int indent = 0) {
  const std::string pad(indent * 2, ' ');

  if (const auto *number_node = dynamic_cast<cee::NumberNode *>(node.get())) {
    std::cout << pad << "NumberNode(" << number_node->value << ")\n";
  } else if (const auto *binary_op_node = dynamic_cast<cee::BinaryOpNode *>(node.get())) {
    std::cout << pad << "BinaryOpNode('" << binary_op_node->op << "')\n";
    std::cout << pad << "  left:\n";
    print_ast(binary_op_node->left, indent + 2);
    std::cout << pad << "  right:\n";
    print_ast(binary_op_node->right, indent + 2);
  } else {
    std::cout << pad << "UnknownNode\n";
  }
}

int main() {
  cee::Lexer lexer("3 + 5 * 2");
  auto       tokens = lexer.tokenise();

  std::cout << "Tokens:" << std::endl;
  for (auto &[token_type, value]: tokens) {
    std::cout << cee::token_type_name(token_type) << " -> \"" << value << "\"\n";
  }
  std::cout << std::endl;

  std::cout << "AST:" << std::endl;
  cee::Parser parser(tokens);
  const auto  ast = parser.parse();
  print_ast(ast);
}
