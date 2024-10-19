/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
#define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype
{
  YYEMPTY      = -2,
  YYEOF        = 0,   /* "end of file"  */
  YYerror      = 256, /* error  */
  YYUNDEF      = 257, /* "invalid token"  */
  SEMICOLON    = 258, /* SEMICOLON  */
  AS           = 259, /* AS  */
  ASC          = 260, /* ASC  */
  BY           = 261, /* BY  */
  CREATE       = 262, /* CREATE  */
  DROP         = 263, /* DROP  */
  EXISTS       = 264, /* EXISTS  */
  GROUP        = 265, /* GROUP  */
  HAVING       = 266, /* HAVING  */
  ORDER        = 267, /* ORDER  */
  TABLE        = 268, /* TABLE  */
  TABLES       = 269, /* TABLES  */
  INDEX        = 270, /* INDEX  */
  CALC         = 271, /* CALC  */
  SELECT       = 272, /* SELECT  */
  DESC         = 273, /* DESC  */
  SHOW         = 274, /* SHOW  */
  SYNC         = 275, /* SYNC  */
  INSERT       = 276, /* INSERT  */
  DELETE       = 277, /* DELETE  */
  UPDATE       = 278, /* UPDATE  */
  LBRACE       = 279, /* LBRACE  */
  RBRACE       = 280, /* RBRACE  */
  LSBRACE      = 281, /* LSBRACE  */
  RSBRACE      = 282, /* RSBRACE  */
  COMMA        = 283, /* COMMA  */
  TRX_BEGIN    = 284, /* TRX_BEGIN  */
  TRX_COMMIT   = 285, /* TRX_COMMIT  */
  TRX_ROLLBACK = 286, /* TRX_ROLLBACK  */
  INT_T        = 287, /* INT_T  */
  IN           = 288, /* IN  */
  TRUE         = 289, /* TRUE  */
  FALSE        = 290, /* FALSE  */
  STRING_T     = 291, /* STRING_T  */
  FLOAT_T      = 292, /* FLOAT_T  */
  DATE_T       = 293, /* DATE_T  */
  TEXT_T       = 294, /* TEXT_T  */
  VECTOR_T     = 295, /* VECTOR_T  */
  NOT          = 296, /* NOT  */
  UNIQUE       = 297, /* UNIQUE  */
  NULL_T       = 298, /* NULL_T  */
  LIMIT        = 299, /* LIMIT  */
  NULLABLE     = 300, /* NULLABLE  */
  HELP         = 301, /* HELP  */
  QUOTE        = 302, /* QUOTE  */
  EXIT         = 303, /* EXIT  */
  DOT          = 304, /* DOT  */
  INTO         = 305, /* INTO  */
  VALUES       = 306, /* VALUES  */
  FROM         = 307, /* FROM  */
  WHERE        = 308, /* WHERE  */
  AND          = 309, /* AND  */
  OR           = 310, /* OR  */
  SET          = 311, /* SET  */
  ON           = 312, /* ON  */
  INFILE       = 313, /* INFILE  */
  EXPLAIN      = 314, /* EXPLAIN  */
  STORAGE      = 315, /* STORAGE  */
  FORMAT       = 316, /* FORMAT  */
  INNER        = 317, /* INNER  */
  JOIN         = 318, /* JOIN  */
  VIEW         = 319, /* VIEW  */
  WITH         = 320, /* WITH  */
  DISTANCE     = 321, /* DISTANCE  */
  TYPE         = 322, /* TYPE  */
  LISTS        = 323, /* LISTS  */
  PROBES       = 324, /* PROBES  */
  IVFFLAT      = 325, /* IVFFLAT  */
  EQ           = 326, /* EQ  */
  LT           = 327, /* LT  */
  GT           = 328, /* GT  */
  LE           = 329, /* LE  */
  GE           = 330, /* GE  */
  NE           = 331, /* NE  */
  LIKE         = 332, /* LIKE  */
  IS           = 333, /* IS  */
  NUMBER       = 334, /* NUMBER  */
  FLOAT        = 335, /* FLOAT  */
  ID           = 336, /* ID  */
  SSS          = 337, /* SSS  */
  UMINUS       = 338  /* UMINUS  */
};
typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 175 "yacc_sql.y"

  ParsedSqlNode                            *sql_node;
  Value                                    *value;
  enum CompOp                               comp;
  RelAttrSqlNode                           *rel_attr;
  std::vector<AttrInfoSqlNode>             *attr_infos;
  AttrInfoSqlNode                          *attr_info;
  Expression                               *expression;
  std::vector<std::unique_ptr<Expression>> *expression_list;
  std::vector<Value>                       *value_list;
  std::vector<std::vector<Value>>          *values_list;
  SetClauseSqlNode                         *set_clause;
  std::vector<SetClauseSqlNode>            *set_clauses;
  JoinSqlNode                              *join_clauses;
  std::vector<RelAttrSqlNode>              *rel_attr_list;
  std::vector<RelationNode>                *relation_list;
  OrderBySqlNode                           *orderby_unit;
  std::vector<OrderBySqlNode>              *orderby_list;
  LimitSqlNode                             *limited_info;
  char                                     *string;
  int                                       number;
  float                                     floats;
  bool                                      nullable_info;
  std::vector<std::string>                 *index_attr_list;
  bool                                      unique;
  enum IndexType                            index_type;
  VectorIndexConfig                        *vector_index_config;
  float                                     digits;
  std::vector<float>                       *digits_list;

#line 178 "yacc_sql.hpp"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if !defined YYLTYPE && !defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
#endif

int yyparse(const char *sql_string, ParsedSqlResult *sql_result, void *scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
