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
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    AS = 259,                      /* AS  */
    ASC = 260,                     /* ASC  */
    BY = 261,                      /* BY  */
    CREATE = 262,                  /* CREATE  */
    DROP = 263,                    /* DROP  */
    EXISTS = 264,                  /* EXISTS  */
    GROUP = 265,                   /* GROUP  */
    HAVING = 266,                  /* HAVING  */
    ORDER = 267,                   /* ORDER  */
    TABLE = 268,                   /* TABLE  */
    TABLES = 269,                  /* TABLES  */
    INDEX = 270,                   /* INDEX  */
    CALC = 271,                    /* CALC  */
    SELECT = 272,                  /* SELECT  */
    DESC = 273,                    /* DESC  */
    SHOW = 274,                    /* SHOW  */
    SYNC = 275,                    /* SYNC  */
    INSERT = 276,                  /* INSERT  */
    DELETE = 277,                  /* DELETE  */
    UPDATE = 278,                  /* UPDATE  */
    LBRACE = 279,                  /* LBRACE  */
    RBRACE = 280,                  /* RBRACE  */
    COMMA = 281,                   /* COMMA  */
    TRX_BEGIN = 282,               /* TRX_BEGIN  */
    TRX_COMMIT = 283,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 284,            /* TRX_ROLLBACK  */
    INT_T = 285,                   /* INT_T  */
    IN = 286,                      /* IN  */
    STRING_T = 287,                /* STRING_T  */
    FLOAT_T = 288,                 /* FLOAT_T  */
    DATE_T = 289,                  /* DATE_T  */
    TEXT_T = 290,                  /* TEXT_T  */
    VECTOR_T = 291,                /* VECTOR_T  */
    NOT = 292,                     /* NOT  */
    UNIQUE = 293,                  /* UNIQUE  */
    NULL_T = 294,                  /* NULL_T  */
    LIMIT = 295,                   /* LIMIT  */
    NULLABLE = 296,                /* NULLABLE  */
    HELP = 297,                    /* HELP  */
    EXIT = 298,                    /* EXIT  */
    DOT = 299,                     /* DOT  */
    INTO = 300,                    /* INTO  */
    VALUES = 301,                  /* VALUES  */
    FROM = 302,                    /* FROM  */
    WHERE = 303,                   /* WHERE  */
    AND = 304,                     /* AND  */
    OR = 305,                      /* OR  */
    SET = 306,                     /* SET  */
    ON = 307,                      /* ON  */
    LOAD = 308,                    /* LOAD  */
    DATA = 309,                    /* DATA  */
    INFILE = 310,                  /* INFILE  */
    EXPLAIN = 311,                 /* EXPLAIN  */
    STORAGE = 312,                 /* STORAGE  */
    FORMAT = 313,                  /* FORMAT  */
    INNER = 314,                   /* INNER  */
    JOIN = 315,                    /* JOIN  */
    EQ = 316,                      /* EQ  */
    LT = 317,                      /* LT  */
    GT = 318,                      /* GT  */
    LE = 319,                      /* LE  */
    GE = 320,                      /* GE  */
    NE = 321,                      /* NE  */
    LIKE = 322,                    /* LIKE  */
    IS = 323,                      /* IS  */
    NUMBER = 324,                  /* NUMBER  */
    FLOAT = 325,                   /* FLOAT  */
    ID = 326,                      /* ID  */
    SSS = 327,                     /* SSS  */
    UMINUS = 328                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 165 "yacc_sql.y"

  ParsedSqlNode *                            sql_node;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<std::vector<Value>> *          values_list;
  SetClauseSqlNode *                         set_clause;
  std::vector<SetClauseSqlNode> *            set_clauses;
  JoinSqlNode *                              join_clauses;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<RelationNode> *                relation_list;
  OrderBySqlNode *                           orderby_unit;
  std::vector<OrderBySqlNode> *              orderby_list;
  LimitSqlNode *                             limited_info;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       nullable_info;
  std::vector<std::string> *                 index_attr_list;
  bool                                       unique;

#line 164 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
