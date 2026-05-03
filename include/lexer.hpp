//
// Created by Nil on 03/05/2026.
//

#pragma once

#include <string>
#include <vector>

namespace cee {
  enum class TokenType {
    NUMBER_LITERAL,
    IDENTIFIER,

    // keywords
    KW_INT,
    KW_FLOAT,
    KW_CHAR,
    KW_VOID,
    KW_RETURN,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_FOR,

    // operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    EQUALS,
    SEMICOLON,
    END_OF_FILE
  };

  struct Token {
    TokenType   token_type;
    std::string value;
  };

  class Lexer {
    std::string source;
    size_t      position = 0;

  public:
    explicit Lexer(std::string source);
    std::vector<Token> tokenise();

  private:
    [[nodiscard]] char peek() const;
    char               advance();
    void               skip_whitespace();
    Token              read_number();
    Token              read_identifier();
  };
} // namespace cee
