/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundFunctionExpr *create_aggregate_expression(const char *function_name,
                                                 std::vector<std::unique_ptr<Expression>> child,
                                                 const char *sql_string,
                                                 YYLTYPE *llocp)
{
  UnboundFunctionExpr *expr = new UnboundFunctionExpr(function_name, std::move(child));
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

ParsedSqlNode *create_table_sql_node(char *table_name,
                                     AttrInfoSqlNode* attr_def,
                                     std::vector<AttrInfoSqlNode> *attrinfos,
                                     char* storage_format,
                                     ParsedSqlNode *create_table_select)
{
    ParsedSqlNode *parsed_sql_node = new ParsedSqlNode(SCF_CREATE_TABLE);
    CreateTableSqlNode &create_table = parsed_sql_node->create_table;
    create_table.relation_name = table_name;

    if (attrinfos) {
        create_table.attr_infos.swap(*attrinfos);
        delete attrinfos;
    }
    if (attr_def) {
        create_table.attr_infos.emplace_back(*attr_def);
        std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
        delete attr_def;
    }
    if (storage_format != nullptr) {
        create_table.storage_format = storage_format;
        free(storage_format);
    }

    if (create_table_select) {
        create_table.create_table_select = std::make_unique<SelectSqlNode>(std::move(create_table_select->selection));
    }

    return parsed_sql_node;
}

#line 155 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_AS = 4,                         /* AS  */
  YYSYMBOL_ASC = 5,                        /* ASC  */
  YYSYMBOL_BY = 6,                         /* BY  */
  YYSYMBOL_CREATE = 7,                     /* CREATE  */
  YYSYMBOL_DROP = 8,                       /* DROP  */
  YYSYMBOL_EXISTS = 9,                     /* EXISTS  */
  YYSYMBOL_GROUP = 10,                     /* GROUP  */
  YYSYMBOL_HAVING = 11,                    /* HAVING  */
  YYSYMBOL_ORDER = 12,                     /* ORDER  */
  YYSYMBOL_TABLE = 13,                     /* TABLE  */
  YYSYMBOL_TABLES = 14,                    /* TABLES  */
  YYSYMBOL_INDEX = 15,                     /* INDEX  */
  YYSYMBOL_CALC = 16,                      /* CALC  */
  YYSYMBOL_SELECT = 17,                    /* SELECT  */
  YYSYMBOL_DESC = 18,                      /* DESC  */
  YYSYMBOL_SHOW = 19,                      /* SHOW  */
  YYSYMBOL_SYNC = 20,                      /* SYNC  */
  YYSYMBOL_INSERT = 21,                    /* INSERT  */
  YYSYMBOL_DELETE = 22,                    /* DELETE  */
  YYSYMBOL_UPDATE = 23,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_LSBRACE = 26,                   /* LSBRACE  */
  YYSYMBOL_RSBRACE = 27,                   /* RSBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 29,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 30,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 31,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_IN = 33,                        /* IN  */
  YYSYMBOL_TRUE = 34,                      /* TRUE  */
  YYSYMBOL_FALSE = 35,                     /* FALSE  */
  YYSYMBOL_STRING_T = 36,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 37,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 38,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 39,                    /* TEXT_T  */
  YYSYMBOL_VECTOR_T = 40,                  /* VECTOR_T  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_UNIQUE = 42,                    /* UNIQUE  */
  YYSYMBOL_NULL_T = 43,                    /* NULL_T  */
  YYSYMBOL_LIMIT = 44,                     /* LIMIT  */
  YYSYMBOL_NULLABLE = 45,                  /* NULLABLE  */
  YYSYMBOL_HELP = 46,                      /* HELP  */
  YYSYMBOL_QUOTE = 47,                     /* QUOTE  */
  YYSYMBOL_EXIT = 48,                      /* EXIT  */
  YYSYMBOL_DOT = 49,                       /* DOT  */
  YYSYMBOL_INTO = 50,                      /* INTO  */
  YYSYMBOL_VALUES = 51,                    /* VALUES  */
  YYSYMBOL_FROM = 52,                      /* FROM  */
  YYSYMBOL_WHERE = 53,                     /* WHERE  */
  YYSYMBOL_AND = 54,                       /* AND  */
  YYSYMBOL_OR = 55,                        /* OR  */
  YYSYMBOL_SET = 56,                       /* SET  */
  YYSYMBOL_ON = 57,                        /* ON  */
  YYSYMBOL_INFILE = 58,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 59,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 60,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 61,                    /* FORMAT  */
  YYSYMBOL_INNER = 62,                     /* INNER  */
  YYSYMBOL_JOIN = 63,                      /* JOIN  */
  YYSYMBOL_VIEW = 64,                      /* VIEW  */
  YYSYMBOL_EQ = 65,                        /* EQ  */
  YYSYMBOL_LT = 66,                        /* LT  */
  YYSYMBOL_GT = 67,                        /* GT  */
  YYSYMBOL_LE = 68,                        /* LE  */
  YYSYMBOL_GE = 69,                        /* GE  */
  YYSYMBOL_NE = 70,                        /* NE  */
  YYSYMBOL_LIKE = 71,                      /* LIKE  */
  YYSYMBOL_IS = 72,                        /* IS  */
  YYSYMBOL_NUMBER = 73,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 74,                     /* FLOAT  */
  YYSYMBOL_ID = 75,                        /* ID  */
  YYSYMBOL_SSS = 76,                       /* SSS  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '*'  */
  YYSYMBOL_80_ = 80,                       /* '/'  */
  YYSYMBOL_UMINUS = 81,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_commands = 83,                  /* commands  */
  YYSYMBOL_command_wrapper = 84,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 85,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 86,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 87,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 88,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 89,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 90,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 91,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 92,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 93,           /* desc_table_stmt  */
  YYSYMBOL_show_index_stmt = 94,           /* show_index_stmt  */
  YYSYMBOL_create_index_stmt = 95,         /* create_index_stmt  */
  YYSYMBOL_opt_unique = 96,                /* opt_unique  */
  YYSYMBOL_attr_list = 97,                 /* attr_list  */
  YYSYMBOL_drop_index_stmt = 98,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 99,         /* create_table_stmt  */
  YYSYMBOL_create_view_stmt = 100,         /* create_view_stmt  */
  YYSYMBOL_drop_view_stmt = 101,           /* drop_view_stmt  */
  YYSYMBOL_attr_def_list = 102,            /* attr_def_list  */
  YYSYMBOL_attr_def = 103,                 /* attr_def  */
  YYSYMBOL_nullable_constraint = 104,      /* nullable_constraint  */
  YYSYMBOL_type = 105,                     /* type  */
  YYSYMBOL_insert_stmt = 106,              /* insert_stmt  */
  YYSYMBOL_values_list = 107,              /* values_list  */
  YYSYMBOL_digits = 108,                   /* digits  */
  YYSYMBOL_digits_list = 109,              /* digits_list  */
  YYSYMBOL_value_list = 110,               /* value_list  */
  YYSYMBOL_value = 111,                    /* value  */
  YYSYMBOL_nonnegative_value = 112,        /* nonnegative_value  */
  YYSYMBOL_storage_format = 113,           /* storage_format  */
  YYSYMBOL_delete_stmt = 114,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 115,              /* update_stmt  */
  YYSYMBOL_set_clauses = 116,              /* set_clauses  */
  YYSYMBOL_set_clause = 117,               /* set_clause  */
  YYSYMBOL_select_stmt = 118,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 119,                /* calc_stmt  */
  YYSYMBOL_expression_list = 120,          /* expression_list  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_alias = 122,                    /* alias  */
  YYSYMBOL_func_expr = 123,                /* func_expr  */
  YYSYMBOL_sub_query_expr = 124,           /* sub_query_expr  */
  YYSYMBOL_rel_attr = 125,                 /* rel_attr  */
  YYSYMBOL_relation = 126,                 /* relation  */
  YYSYMBOL_rel_list = 127,                 /* rel_list  */
  YYSYMBOL_join_clauses = 128,             /* join_clauses  */
  YYSYMBOL_where = 129,                    /* where  */
  YYSYMBOL_condition = 130,                /* condition  */
  YYSYMBOL_comp_op = 131,                  /* comp_op  */
  YYSYMBOL_opt_order_by = 132,             /* opt_order_by  */
  YYSYMBOL_sort_list = 133,                /* sort_list  */
  YYSYMBOL_sort_unit = 134,                /* sort_unit  */
  YYSYMBOL_group_by = 135,                 /* group_by  */
  YYSYMBOL_opt_having = 136,               /* opt_having  */
  YYSYMBOL_opt_limit = 137,                /* opt_limit  */
  YYSYMBOL_explain_stmt = 138,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 139,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 140             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   272,   272,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   305,   311,   316,   322,   328,
     334,   340,   347,   353,   361,   371,   386,   387,   391,   397,
     406,   416,   420,   424,   428,   432,   439,   447,   459,   469,
     472,   485,   503,   532,   536,   540,   545,   551,   552,   553,
     554,   555,   556,   560,   570,   584,   590,   597,   601,   605,
     609,   618,   621,   626,   634,   637,   643,   651,   654,   658,
     665,   669,   673,   679,   682,   685,   688,   695,   698,   705,
     717,   731,   736,   743,   753,   791,   824,   830,   839,   842,
     851,   867,   870,   873,   876,   879,   887,   890,   895,   901,
     904,   907,   910,   917,   920,   923,   928,   936,   943,   948,
     958,   964,   974,   991,   998,  1010,  1013,  1019,  1023,  1030,
    1034,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1054,  1059,  1062,  1070,  1075,  1083,
    1089,  1095,  1105,  1108,  1116,  1119,  1127,  1130,  1138,  1146,
    1157
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "AS",
  "ASC", "BY", "CREATE", "DROP", "EXISTS", "GROUP", "HAVING", "ORDER",
  "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "LSBRACE", "RSBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "IN",
  "TRUE", "FALSE", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T", "VECTOR_T",
  "NOT", "UNIQUE", "NULL_T", "LIMIT", "NULLABLE", "HELP", "QUOTE", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "INNER", "JOIN", "VIEW", "EQ",
  "LT", "GT", "LE", "GE", "NE", "LIKE", "IS", "NUMBER", "FLOAT", "ID",
  "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "show_index_stmt", "create_index_stmt", "opt_unique",
  "attr_list", "drop_index_stmt", "create_table_stmt", "create_view_stmt",
  "drop_view_stmt", "attr_def_list", "attr_def", "nullable_constraint",
  "type", "insert_stmt", "values_list", "digits", "digits_list",
  "value_list", "value", "nonnegative_value", "storage_format",
  "delete_stmt", "update_stmt", "set_clauses", "set_clause", "select_stmt",
  "calc_stmt", "expression_list", "expression", "alias", "func_expr",
  "sub_query_expr", "rel_attr", "relation", "rel_list", "join_clauses",
  "where", "condition", "comp_op", "opt_order_by", "sort_list",
  "sort_unit", "group_by", "opt_having", "opt_limit", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-199)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     121,     8,    14,   219,   219,   -55,    80,  -199,   -20,    44,
     -23,  -199,  -199,  -199,  -199,  -199,    45,   121,    66,   127,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,    49,  -199,    61,   134,    86,    87,    89,   139,
     -18,  -199,  -199,  -199,  -199,  -199,   -10,  -199,   219,  -199,
    -199,  -199,    12,  -199,  -199,  -199,   114,  -199,  -199,   116,
      95,    96,   122,   118,  -199,  -199,  -199,  -199,    -6,    27,
     104,  -199,   124,  -199,   219,   159,   160,  -199,  -199,    40,
    -199,   107,   219,    22,  -199,   111,  -199,   219,   219,   219,
     219,   164,   113,   113,    -5,   138,   119,    -9,   125,   132,
      20,   182,   126,   145,   128,   114,  -199,  -199,  -199,  -199,
    -199,   -18,   185,  -199,  -199,  -199,    67,    67,  -199,  -199,
     219,  -199,    11,   138,  -199,   126,   183,   163,  -199,   144,
       0,  -199,    84,  -199,  -199,   184,   197,   146,   182,  -199,
    -199,   199,   215,   169,  -199,  -199,  -199,  -199,   186,   218,
     237,   223,    -9,   222,  -199,  -199,    -1,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,   210,    38,   105,   219,   219,   119,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,    16,
     125,   227,   180,  -199,   126,   252,   233,   113,   113,   253,
     247,   209,    10,  -199,   239,  -199,  -199,  -199,  -199,   219,
     163,   163,    -3,    -3,  -199,   188,   221,  -199,  -199,  -199,
     197,   205,  -199,  -199,   182,   126,   211,   138,    18,  -199,
     219,   163,   254,   183,  -199,    -9,    -9,    -3,  -199,   213,
     244,  -199,  -199,    32,  -199,   245,   163,   237,  -199,   105,
     265,   228,   222,  -199,   120,    82,   182,  -199,  -199,    57,
    -199,   219,   200,  -199,  -199,  -199,  -199,   212,     5,  -199,
     246,  -199,   113,  -199,  -199,   219,  -199,  -199
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    37,     0,    98,    98,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
      24,    23,    17,    18,    19,    20,     9,    10,    11,    14,
      12,    13,     8,    15,    16,     5,     7,     6,     3,     4,
      21,    22,     0,    36,     0,     0,     0,     0,     0,    98,
      71,    83,    84,    85,    80,    81,   118,    82,     0,   109,
     107,    96,   113,   111,   112,   108,    97,    33,    32,     0,
       0,     0,     0,     0,   158,     1,   160,     2,    87,     0,
       0,    31,     0,    48,    98,     0,     0,    67,    69,     0,
      72,     0,    98,     0,   106,     0,   114,     0,     0,     0,
       0,    99,     0,     0,     0,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   105,    68,    70,
      86,     0,     0,   119,   110,   115,   101,   102,   103,   104,
      98,   120,   113,   125,    34,     0,     0,     0,    89,     0,
     125,    91,     0,   159,    77,     0,    49,     0,     0,    45,
      46,    38,     0,     0,    40,    73,   116,   100,     0,   121,
     152,     0,    74,    63,   143,   141,     0,   131,   132,   133,
     134,   135,   136,   139,   137,     0,   126,     0,     0,     0,
      90,    78,    79,    57,    58,    59,    60,    61,    62,    56,
       0,     0,     0,    44,     0,     0,     0,     0,     0,     0,
     154,     0,     0,    75,     0,   144,   142,   140,   138,     0,
       0,     0,   128,    93,    92,     0,     0,    55,    54,    52,
      49,    87,    88,    39,     0,     0,     0,   125,   113,   122,
      98,     0,   145,     0,    65,     0,    74,   127,   129,   130,
       0,    53,    50,    43,    47,     0,     0,   152,   153,   155,
       0,   156,    64,    76,     0,    56,     0,    42,    35,   123,
      95,     0,     0,    94,    66,    51,    41,     0,   149,   146,
     147,   157,     0,   151,   150,     0,   124,   148
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -199,  -199,   259,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -126,  -199,  -199,  -199,  -199,
      58,    90,    24,  -199,  -199,    48,   156,  -199,    46,  -102,
    -104,    62,  -199,  -199,  -199,   106,   -48,  -199,    -4,   -56,
     224,  -199,  -199,  -199,   -96,    91,    15,  -129,  -198,   109,
    -199,    13,  -199,    43,  -199,  -199,  -199,  -199,  -199
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    45,   152,    31,    32,    33,    34,
     191,   146,   219,   189,    35,   163,    90,    91,   202,   203,
      60,   110,    36,    37,   140,   141,    38,    39,    61,    62,
     159,    63,    64,    65,   226,   133,   227,   138,   176,   177,
     251,   269,   270,   200,   232,   263,    40,    41,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    85,    94,   144,   160,   143,   132,   134,   205,   161,
     273,   180,   238,   239,    92,    95,    95,    50,   108,   135,
      67,    42,    95,   274,   148,    51,    52,    46,   179,    47,
      70,   111,   206,   249,    53,   234,   256,    84,   235,    93,
     215,   126,   127,   128,   129,    86,   136,   164,   259,    84,
      43,   112,    72,   137,   109,    87,    88,   216,   144,   217,
      89,   218,   149,   150,    54,    55,    75,    57,   223,   142,
     207,   165,    44,   158,    97,    98,    99,   100,    48,   166,
     115,   175,    97,    98,    99,   100,    96,    96,   122,    97,
      98,    99,   100,    96,    68,    69,    71,   123,   247,   245,
     193,   124,   228,   167,   168,   169,   170,   171,   172,   173,
     174,   210,   211,   118,   119,    97,    98,    99,   100,   267,
      73,   212,   213,   216,    78,   217,   157,   218,     1,     2,
      76,   144,   144,   253,   120,   121,    79,     3,     4,     5,
       6,     7,     8,     9,    10,   264,    99,   100,   235,    80,
      11,    12,    13,   237,   175,   175,    84,   181,   182,   210,
     211,    81,    82,    49,    83,    50,   102,    14,   103,    15,
     104,   105,   164,    51,    52,   175,   244,    16,   106,   113,
      17,   114,    53,   107,   116,   117,   125,    49,   131,    50,
     175,   137,   130,   147,   139,   257,   165,    51,    52,    84,
     145,   151,   153,   154,   166,   268,    53,   162,   266,   178,
     156,   192,    54,    55,    56,    57,   183,    58,    59,   268,
     184,   185,   186,   187,   188,   190,   248,   194,   167,   168,
     169,   170,   171,   172,   173,   174,    54,    55,    56,    57,
     195,    58,    59,    49,   196,    50,   198,   199,   201,   197,
     204,   208,   221,    51,    52,   222,   224,   225,   231,   230,
     233,   240,    53,   236,   241,   109,   250,   210,   246,   255,
     258,   261,   262,   271,   275,   272,    74,   155,   242,   265,
     220,   252,   254,   243,   209,   214,   101,   276,   277,   229,
     260,     0,    54,    55,    56,    57,     0,    58,    59
};

static const yytype_int16 yycheck[] =
{
       4,    49,    58,   107,   133,   107,   102,   103,     9,   135,
       5,   140,   210,   211,    24,     4,     4,    26,    24,    24,
      75,    13,     4,    18,     4,    34,    35,    13,    28,    15,
      50,     4,    33,   231,    43,    25,     4,    17,    28,    49,
      24,    97,    98,    99,   100,    49,    51,     9,   246,    17,
      42,    24,    75,    53,    60,    73,    74,    41,   162,    43,
      78,    45,   110,   111,    73,    74,     0,    76,   194,    78,
      71,    33,    64,    62,    77,    78,    79,    80,    64,    41,
      84,   137,    77,    78,    79,    80,    75,    75,    92,    77,
      78,    79,    80,    75,    14,    15,    52,    75,   227,   225,
     148,    79,   198,    65,    66,    67,    68,    69,    70,    71,
      72,    54,    55,    73,    74,    77,    78,    79,    80,    62,
      75,   177,   178,    41,    75,    43,   130,    45,     7,     8,
       3,   235,   236,   235,    27,    28,    75,    16,    17,    18,
      19,    20,    21,    22,    23,    25,    79,    80,    28,    15,
      29,    30,    31,   209,   210,   211,    17,    73,    74,    54,
      55,    75,    75,    24,    75,    26,    52,    46,    52,    48,
      75,    75,     9,    34,    35,   231,   224,    56,    56,    75,
      59,    57,    43,    65,    25,    25,    75,    24,    75,    26,
     246,    53,    28,    61,    75,   243,    33,    34,    35,    17,
      75,    75,    57,    75,    41,   261,    43,    24,   256,    65,
      25,    65,    73,    74,    75,    76,    32,    78,    79,   275,
      36,    37,    38,    39,    40,    28,   230,    28,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      25,    78,    79,    24,    75,    26,    28,    10,    25,    63,
      28,    41,    25,    34,    35,    75,     4,    24,    11,     6,
      51,    73,    43,    24,    43,    60,    12,    54,    57,    25,
      25,     6,    44,    73,    28,    63,    17,   121,   220,   255,
     190,   233,   236,   221,   175,   179,    62,   272,   275,   198,
     247,    -1,    73,    74,    75,    76,    -1,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    16,    17,    18,    19,    20,    21,    22,
      23,    29,    30,    31,    46,    48,    56,    59,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    98,    99,   100,   101,   106,   114,   115,   118,   119,
     138,   139,    13,    42,    64,    96,    13,    15,    64,    24,
      26,    34,    35,    43,    73,    74,    75,    76,    78,    79,
     112,   120,   121,   123,   124,   125,   120,    75,    14,    15,
      50,    52,    75,    75,    84,     0,     3,   140,    75,    75,
      15,    75,    75,    75,    17,   118,   120,    73,    74,    78,
     108,   109,    24,    49,   121,     4,    75,    77,    78,    79,
      80,   122,    52,    52,    75,    75,    56,    65,    24,    60,
     113,     4,    24,    75,    57,   120,    25,    25,    73,    74,
      27,    28,   120,    75,    79,    75,   121,   121,   121,   121,
      28,    75,   126,   127,   126,    24,    51,    53,   129,    75,
     116,   117,    78,   111,   112,    75,   103,    61,     4,   118,
     118,    75,    97,    57,    75,   108,    25,   120,    62,   122,
     129,    97,    24,   107,     9,    33,    41,    65,    66,    67,
      68,    69,    70,    71,    72,   121,   130,   131,    65,    28,
     129,    73,    74,    32,    36,    37,    38,    39,    40,   105,
      28,   102,    65,   118,    28,    25,    75,    63,    28,    10,
     135,    25,   110,   111,    28,     9,    33,    71,    41,   131,
      54,    55,   121,   121,   117,    24,    41,    43,    45,   104,
     103,    25,    75,    97,     4,    24,   126,   128,   126,   127,
       6,    11,   136,    51,    25,    28,    24,   121,   130,   130,
      73,    43,   102,   113,   118,    97,    57,   129,   120,   130,
      12,   132,   107,   111,   110,    25,     4,   118,    25,   130,
     135,     6,    44,   137,    25,   104,   118,    62,   121,   133,
     134,    73,    63,     5,    18,    28,   128,   133
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    96,    97,    97,
      98,    99,    99,    99,    99,    99,   100,   100,   101,   102,
     102,   103,   103,   104,   104,   104,   104,   105,   105,   105,
     105,   105,   105,   106,   106,   107,   107,   108,   108,   108,
     108,   109,   109,   109,   110,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   113,   113,   114,
     115,   116,   116,   117,   118,   118,   119,   119,   120,   120,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   122,   122,   123,   124,   125,   125,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   133,   133,   134,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   139,
     140
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     4,     9,     1,     0,     1,     3,
       5,    10,     9,     8,     6,     5,     5,     8,     3,     0,
       3,     6,     3,     2,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     5,     8,     3,     5,     1,     2,     1,
       2,     0,     1,     3,     0,     1,     3,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     4,
       5,     1,     3,     3,     9,     9,     2,     2,     0,     2,
       4,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       3,     1,     1,     0,     1,     2,     4,     3,     1,     3,
       1,     2,     4,     3,     6,     0,     2,     3,     2,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     1,     2,     0,     3,     1,     3,     1,
       2,     2,     0,     3,     0,     2,     0,     2,     2,     4,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 273 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1899 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 305 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1908 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 311 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1916 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 316 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1924 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 322 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 328 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1940 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 334 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1948 "yacc_sql.cpp"
    break;

  case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 340 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1958 "yacc_sql.cpp"
    break;

  case 32: /* show_tables_stmt: SHOW TABLES  */
#line 347 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1966 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 353 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 34: /* show_index_stmt: SHOW INDEX FROM relation  */
#line 362 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = (yyval.sql_node)->show_index;
      show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1987 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE attr_list RBRACE  */
#line 372 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.unique = (yyvsp[-7].unique); // 用 opt_unique 的返回值来确定是否 UNIQUE
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_name.swap(*(yyvsp[-1].index_attr_list)); // $8 是 vector<string> 类型
      delete (yyvsp[-1].index_attr_list); // 释放指针
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 36: /* opt_unique: UNIQUE  */
#line 386 "yacc_sql.y"
           { (yyval.unique) = true; }
#line 2009 "yacc_sql.cpp"
    break;

  case 37: /* opt_unique: %empty  */
#line 387 "yacc_sql.y"
                { (yyval.unique) = false; }
#line 2015 "yacc_sql.cpp"
    break;

  case 38: /* attr_list: ID  */
#line 392 "yacc_sql.y"
    {
      (yyval.index_attr_list) = new std::vector<std::string>; // 创建一个新的 vector
      (yyval.index_attr_list)->emplace_back((yyvsp[0].string)); // 将列名加入 vector
      free((yyvsp[0].string));
    }
#line 2025 "yacc_sql.cpp"
    break;

  case 39: /* attr_list: ID COMMA attr_list  */
#line 398 "yacc_sql.y"
    {
      (yyval.index_attr_list) = (yyvsp[0].index_attr_list); // 使用现有的 vector
      (yyval.index_attr_list)->emplace((yyval.index_attr_list)->begin(), (yyvsp[-2].string)); // 将新列名加入 vector 开头
      free((yyvsp[-2].string));
    }
#line 2035 "yacc_sql.cpp"
    break;

  case 40: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 407 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2047 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt  */
#line 417 "yacc_sql.y"
    {
        (yyval.sql_node) = create_table_sql_node((yyvsp[-7].string), (yyvsp[-5].attr_info), (yyvsp[-4].attr_infos), (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2055 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 421 "yacc_sql.y"
    {
        (yyval.sql_node) = create_table_sql_node((yyvsp[-6].string), (yyvsp[-4].attr_info), (yyvsp[-3].attr_infos), (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2063 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 425 "yacc_sql.y"
    {
        (yyval.sql_node) = create_table_sql_node((yyvsp[-5].string), (yyvsp[-3].attr_info), (yyvsp[-2].attr_infos), (yyvsp[0].string), nullptr);
    }
#line 2071 "yacc_sql.cpp"
    break;

  case 44: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 429 "yacc_sql.y"
    {
        (yyval.sql_node) = create_table_sql_node((yyvsp[-3].string), nullptr, nullptr, (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2079 "yacc_sql.cpp"
    break;

  case 45: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 433 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node((yyvsp[-2].string), nullptr, nullptr, (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 46: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 440 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name = (yyvsp[-2].string);
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-2].string));
    }
#line 2099 "yacc_sql.cpp"
    break;

  case 47: /* create_view_stmt: CREATE VIEW ID LBRACE attr_list RBRACE AS select_stmt  */
#line 448 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name = (yyvsp[-5].string);
      create_view.attribute_names = std::move(*(yyvsp[-3].index_attr_list));
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-5].string));
    }
#line 2112 "yacc_sql.cpp"
    break;

  case 48: /* drop_view_stmt: DROP VIEW ID  */
#line 460 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2122 "yacc_sql.cpp"
    break;

  case 49: /* attr_def_list: %empty  */
#line 469 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2130 "yacc_sql.cpp"
    break;

  case 50: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 473 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 51: /* attr_def: ID type LBRACE NUMBER RBRACE nullable_constraint  */
#line 486 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      if ((yyval.attr_info)->type == AttrType::CHARS) {
        (yyval.attr_info)->length = (yyvsp[-2].number);
      } else if ((yyval.attr_info)->type == AttrType::VECTORS) {
        (yyval.attr_info)->length = sizeof(float) * (yyvsp[-2].number);
      } else {
        ASSERT(false, "$$->type is invalid.");
      }
      (yyval.attr_info)->nullable = (yyvsp[0].nullable_info);
      if ((yyval.attr_info)->nullable) {
        (yyval.attr_info)->length++;
      }
      free((yyvsp[-5].string));
    }
#line 2166 "yacc_sql.cpp"
    break;

  case 52: /* attr_def: ID type nullable_constraint  */
#line 504 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if ((yyval.attr_info)->type == AttrType::INTS) {
        (yyval.attr_info)->length = sizeof(int);
      } else if ((yyval.attr_info)->type == AttrType::FLOATS) {
        (yyval.attr_info)->length = sizeof(float);
      } else if ((yyval.attr_info)->type == AttrType::DATES) {
        (yyval.attr_info)->length = sizeof(int);
      } else if ((yyval.attr_info)->type == AttrType::CHARS) {
        (yyval.attr_info)->length = sizeof(char);
      } else if ((yyval.attr_info)->type == AttrType::VECTORS) {
        (yyval.attr_info)->length = sizeof(float) * 1;
      } else if ((yyval.attr_info)->type == AttrType::TEXTS) {
        (yyval.attr_info)->length = 65535;
      } else {
        ASSERT(false, "$$->type is invalid.");
      }
      (yyval.attr_info)->nullable = (yyvsp[0].nullable_info);  // 处理NULL/NOT NULL标记
      if ((yyval.attr_info)->nullable) {
        (yyval.attr_info)->length++;
      }
      free((yyvsp[-2].string));
    }
#line 2196 "yacc_sql.cpp"
    break;

  case 53: /* nullable_constraint: NOT NULL_T  */
#line 533 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // NOT NULL 对应的可空性为 false
    }
#line 2204 "yacc_sql.cpp"
    break;

  case 54: /* nullable_constraint: NULLABLE  */
#line 537 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULLABLE 对应的可空性为 true 2022
    }
#line 2212 "yacc_sql.cpp"
    break;

  case 55: /* nullable_constraint: NULL_T  */
#line 541 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULL 对应的可空性也为 true 2023
    }
#line 2220 "yacc_sql.cpp"
    break;

  case 56: /* nullable_constraint: %empty  */
#line 545 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // 默认情况为 NULL
    }
#line 2228 "yacc_sql.cpp"
    break;

  case 57: /* type: INT_T  */
#line 551 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::INTS);   }
#line 2234 "yacc_sql.cpp"
    break;

  case 58: /* type: STRING_T  */
#line 552 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::CHARS);  }
#line 2240 "yacc_sql.cpp"
    break;

  case 59: /* type: FLOAT_T  */
#line 553 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2246 "yacc_sql.cpp"
    break;

  case 60: /* type: DATE_T  */
#line 554 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::DATES);  }
#line 2252 "yacc_sql.cpp"
    break;

  case 61: /* type: TEXT_T  */
#line 555 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::TEXTS);  }
#line 2258 "yacc_sql.cpp"
    break;

  case 62: /* type: VECTOR_T  */
#line 556 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::VECTORS);  }
#line 2264 "yacc_sql.cpp"
    break;

  case 63: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 561 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-2].string));
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 64: /* insert_stmt: INSERT INTO ID LBRACE attr_list RBRACE VALUES values_list  */
#line 571 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->insertion.attr_names = std::move(*(yyvsp[-3].index_attr_list));
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-5].string));
    }
#line 2293 "yacc_sql.cpp"
    break;

  case 65: /* values_list: LBRACE value_list RBRACE  */
#line 585 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 66: /* values_list: values_list COMMA LBRACE value_list RBRACE  */
#line 591 "yacc_sql.y"
    {
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2312 "yacc_sql.cpp"
    break;

  case 67: /* digits: NUMBER  */
#line 598 "yacc_sql.y"
    {
      (yyval.digits) = float((yyvsp[0].number));
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 68: /* digits: '-' NUMBER  */
#line 602 "yacc_sql.y"
    {
      (yyval.digits) = float(-(yyvsp[0].number));
    }
#line 2328 "yacc_sql.cpp"
    break;

  case 69: /* digits: FLOAT  */
#line 606 "yacc_sql.y"
    {
      (yyval.digits) = (yyvsp[0].floats);
    }
#line 2336 "yacc_sql.cpp"
    break;

  case 70: /* digits: '-' FLOAT  */
#line 610 "yacc_sql.y"
    {
      (yyval.digits) = (yyvsp[0].floats);
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 71: /* digits_list: %empty  */
#line 618 "yacc_sql.y"
    {
      (yyval.digits_list) = new std::vector<float>();
    }
#line 2352 "yacc_sql.cpp"
    break;

  case 72: /* digits_list: digits  */
#line 622 "yacc_sql.y"
    {
      (yyval.digits_list) = new std::vector<float>();
      (yyval.digits_list)->push_back((yyvsp[0].digits));
    }
#line 2361 "yacc_sql.cpp"
    break;

  case 73: /* digits_list: digits_list COMMA digits  */
#line 627 "yacc_sql.y"
    {
      (yyval.digits_list)->push_back((yyvsp[0].digits));
    }
#line 2369 "yacc_sql.cpp"
    break;

  case 74: /* value_list: %empty  */
#line 634 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
    }
#line 2377 "yacc_sql.cpp"
    break;

  case 75: /* value_list: value  */
#line 638 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2387 "yacc_sql.cpp"
    break;

  case 76: /* value_list: value_list COMMA value  */
#line 644 "yacc_sql.y"
    {
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2396 "yacc_sql.cpp"
    break;

  case 77: /* value: nonnegative_value  */
#line 651 "yacc_sql.y"
                      {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2404 "yacc_sql.cpp"
    break;

  case 78: /* value: '-' NUMBER  */
#line 654 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2413 "yacc_sql.cpp"
    break;

  case 79: /* value: '-' FLOAT  */
#line 658 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2422 "yacc_sql.cpp"
    break;

  case 80: /* nonnegative_value: NUMBER  */
#line 665 "yacc_sql.y"
           {
      (yyval.value) = new Value((yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2431 "yacc_sql.cpp"
    break;

  case 81: /* nonnegative_value: FLOAT  */
#line 669 "yacc_sql.y"
            {
      (yyval.value) = new Value((yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2440 "yacc_sql.cpp"
    break;

  case 82: /* nonnegative_value: SSS  */
#line 673 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 83: /* nonnegative_value: TRUE  */
#line 679 "yacc_sql.y"
           {
      (yyval.value) = new Value(true);
    }
#line 2459 "yacc_sql.cpp"
    break;

  case 84: /* nonnegative_value: FALSE  */
#line 682 "yacc_sql.y"
            {
      (yyval.value) = new Value(false);
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 85: /* nonnegative_value: NULL_T  */
#line 685 "yacc_sql.y"
             {
      (yyval.value) = new Value(NullValue());
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 86: /* nonnegative_value: LSBRACE digits_list RSBRACE  */
#line 688 "yacc_sql.y"
                                  {
      (yyval.value) = new Value(*(yyvsp[-1].digits_list));
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 87: /* storage_format: %empty  */
#line 695 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2491 "yacc_sql.cpp"
    break;

  case 88: /* storage_format: STORAGE FORMAT EQ ID  */
#line 699 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 89: /* delete_stmt: DELETE FROM ID where  */
#line 706 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.condition = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-1].string));
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 90: /* update_stmt: UPDATE ID SET set_clauses where  */
#line 718 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.set_clauses.swap(*(yyvsp[-1].set_clauses));
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-3].string));
      delete (yyvsp[-1].set_clauses);
    }
#line 2527 "yacc_sql.cpp"
    break;

  case 91: /* set_clauses: set_clause  */
#line 732 "yacc_sql.y"
    {
      (yyval.set_clauses) = new std::vector<SetClauseSqlNode>;
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 92: /* set_clauses: set_clauses COMMA set_clause  */
#line 737 "yacc_sql.y"
    {
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2544 "yacc_sql.cpp"
    break;

  case 93: /* set_clause: ID EQ expression  */
#line 744 "yacc_sql.y"
    {
      (yyval.set_clause) = new SetClauseSqlNode;
      (yyval.set_clause)->field_name = (yyvsp[-2].string);
      (yyval.set_clause)->value = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2555 "yacc_sql.cpp"
    break;

  case 94: /* select_stmt: SELECT expression_list FROM rel_list where group_by opt_having opt_order_by opt_limit  */
#line 754 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }

      (yyval.sql_node)->selection.conditions = nullptr;

      if ((yyvsp[-4].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = std::unique_ptr<Expression>((yyvsp[-4].expression));
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
      }

      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.having_conditions = std::unique_ptr<Expression>((yyvsp[-2].expression));
      }

      if ((yyvsp[-1].orderby_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].orderby_list));
        delete (yyvsp[-1].orderby_list);
      }

      if ((yyvsp[0].limited_info) != nullptr) {
        (yyval.sql_node)->selection.limit = std::make_unique<LimitSqlNode>(*(yyvsp[0].limited_info));
        delete (yyvsp[0].limited_info);
      }
    }
#line 2597 "yacc_sql.cpp"
    break;

  case 95: /* select_stmt: SELECT expression_list FROM relation INNER JOIN join_clauses where group_by  */
#line 792 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].string) != nullptr) {
        (yyval.sql_node)->selection.relations.emplace_back((yyvsp[-5].string));
        free((yyvsp[-5].string));
      }

      if ((yyvsp[-2].join_clauses) != nullptr) {
        for (auto it = (yyvsp[-2].join_clauses)->relations.rbegin(); it != (yyvsp[-2].join_clauses)->relations.rend(); ++it) {
          (yyval.sql_node)->selection.relations.emplace_back(std::move(*it));
        }
        (yyval.sql_node)->selection.conditions = std::move((yyvsp[-2].join_clauses)->conditions);
      }

      if ((yyvsp[-1].expression) != nullptr) {
        auto ptr = (yyval.sql_node)->selection.conditions.release();
        (yyval.sql_node)->selection.conditions = std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-1].expression));
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 96: /* calc_stmt: CALC expression_list  */
#line 825 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2641 "yacc_sql.cpp"
    break;

  case 97: /* calc_stmt: SELECT expression_list  */
#line 831 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 98: /* expression_list: %empty  */
#line 839 "yacc_sql.y"
                {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 99: /* expression_list: expression alias  */
#line 843 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2672 "yacc_sql.cpp"
    break;

  case 100: /* expression_list: expression alias COMMA expression_list  */
#line 852 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if (nullptr != (yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(),std::move((yyvsp[-3].expression)));
      free((yyvsp[-2].string));
    }
#line 2689 "yacc_sql.cpp"
    break;

  case 101: /* expression: expression '+' expression  */
#line 867 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 102: /* expression: expression '-' expression  */
#line 870 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2705 "yacc_sql.cpp"
    break;

  case 103: /* expression: expression '*' expression  */
#line 873 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2713 "yacc_sql.cpp"
    break;

  case 104: /* expression: expression '/' expression  */
#line 876 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2721 "yacc_sql.cpp"
    break;

  case 105: /* expression: LBRACE expression_list RBRACE  */
#line 879 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().get();
      } else {
        (yyval.expression) = new ListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 106: /* expression: '-' expression  */
#line 887 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 107: /* expression: nonnegative_value  */
#line 890 "yacc_sql.y"
                        {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 108: /* expression: rel_attr  */
#line 895 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 109: /* expression: '*'  */
#line 901 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 110: /* expression: ID DOT '*'  */
#line 904 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2779 "yacc_sql.cpp"
    break;

  case 111: /* expression: func_expr  */
#line 907 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);      // AggrFuncExpr
    }
#line 2787 "yacc_sql.cpp"
    break;

  case 112: /* expression: sub_query_expr  */
#line 910 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression); // SubQueryExpr
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 113: /* alias: %empty  */
#line 917 "yacc_sql.y"
                {
      (yyval.string) = nullptr;
    }
#line 2803 "yacc_sql.cpp"
    break;

  case 114: /* alias: ID  */
#line 920 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2811 "yacc_sql.cpp"
    break;

  case 115: /* alias: AS ID  */
#line 923 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 116: /* func_expr: ID LBRACE expression_list RBRACE  */
#line 929 "yacc_sql.y"
    {
        (yyval.expression) = new UnboundFunctionExpr((yyvsp[-3].string), std::move(*(yyvsp[-1].expression_list)));
        (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2828 "yacc_sql.cpp"
    break;

  case 117: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 937 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2836 "yacc_sql.cpp"
    break;

  case 118: /* rel_attr: ID  */
#line 943 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 119: /* rel_attr: ID DOT ID  */
#line 948 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2858 "yacc_sql.cpp"
    break;

  case 120: /* relation: ID  */
#line 958 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2866 "yacc_sql.cpp"
    break;

  case 121: /* rel_list: relation alias  */
#line 964 "yacc_sql.y"
                   {
      (yyval.relation_list) = new std::vector<RelationNode>();
      if(nullptr!=(yyvsp[0].string)){
        (yyval.relation_list)->emplace_back((yyvsp[-1].string),(yyvsp[0].string));
        free((yyvsp[0].string));
      }else{
        (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      }
      free((yyvsp[-1].string));
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 122: /* rel_list: relation alias COMMA rel_list  */
#line 974 "yacc_sql.y"
                                    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationNode>;
      }
      if(nullptr!=(yyvsp[-2].string)){
        (yyval.relation_list)->insert((yyval.relation_list)->begin(), RelationNode((yyvsp[-3].string),(yyvsp[-2].string)));
        free((yyvsp[-2].string));
      }else{
        (yyval.relation_list)->insert((yyval.relation_list)->begin(), RelationNode((yyvsp[-3].string)));
      }
      free((yyvsp[-3].string));
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 123: /* join_clauses: relation ON condition  */
#line 992 "yacc_sql.y"
    {
      (yyval.join_clauses) = new JoinSqlNode;
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-2].string));
      (yyval.join_clauses)->conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2911 "yacc_sql.cpp"
    break;

  case 124: /* join_clauses: relation ON condition INNER JOIN join_clauses  */
#line 999 "yacc_sql.y"
    {
      (yyval.join_clauses) = (yyvsp[0].join_clauses);
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-5].string));
      auto ptr = (yyval.join_clauses)->conditions.release();
      (yyval.join_clauses)->conditions = std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-3].expression));
      free((yyvsp[-5].string));
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 125: /* where: %empty  */
#line 1010 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 126: /* where: WHERE condition  */
#line 1013 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2939 "yacc_sql.cpp"
    break;

  case 127: /* condition: expression comp_op expression  */
#line 1020 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 128: /* condition: comp_op expression  */
#line 1024 "yacc_sql.y"
    {
      Value val;
      val.set_null(true);
      ValueExpr *temp_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp),temp_expr, (yyvsp[0].expression));
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 129: /* condition: condition AND condition  */
#line 1031 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 130: /* condition: condition OR condition  */
#line 1035 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: EQ  */
#line 1041 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2980 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: LT  */
#line 1042 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2986 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: GT  */
#line 1043 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2992 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: LE  */
#line 1044 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2998 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: GE  */
#line 1045 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3004 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: NE  */
#line 1046 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3010 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: IS  */
#line 1047 "yacc_sql.y"
         { (yyval.comp) = IS_OP; }
#line 3016 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: IS NOT  */
#line 1048 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_OP; }
#line 3022 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: LIKE  */
#line 1049 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3028 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: NOT LIKE  */
#line 1050 "yacc_sql.y"
               {(yyval.comp) = NOT_LIKE_OP;}
#line 3034 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: IN  */
#line 1051 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3040 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: NOT IN  */
#line 1052 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3046 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: EXISTS  */
#line 1053 "yacc_sql.y"
             { (yyval.comp) = EXISTS_OP; }
#line 3052 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: NOT EXISTS  */
#line 1054 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_OP; }
#line 3058 "yacc_sql.cpp"
    break;

  case 145: /* opt_order_by: %empty  */
#line 1059 "yacc_sql.y"
    {
      (yyval.orderby_list) = nullptr;
    }
#line 3066 "yacc_sql.cpp"
    break;

  case 146: /* opt_order_by: ORDER BY sort_list  */
#line 1063 "yacc_sql.y"
    {
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
      std::reverse((yyval.orderby_list)->begin(),(yyval.orderby_list)->end());
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 147: /* sort_list: sort_unit  */
#line 1071 "yacc_sql.y"
        {
      (yyval.orderby_list) = new std::vector<OrderBySqlNode>;
      (yyval.orderby_list)->emplace_back(std::move(*(yyvsp[0].orderby_unit)));
	}
#line 3084 "yacc_sql.cpp"
    break;

  case 148: /* sort_list: sort_unit COMMA sort_list  */
#line 1076 "yacc_sql.y"
        {
      (yyvsp[0].orderby_list)->emplace_back(std::move(*(yyvsp[-2].orderby_unit)));
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
	}
#line 3093 "yacc_sql.cpp"
    break;

  case 149: /* sort_unit: expression  */
#line 1084 "yacc_sql.y"
        {
      (yyval.orderby_unit) = new OrderBySqlNode();
      (yyval.orderby_unit)->expr = std::unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.orderby_unit)->is_asc = true;
	}
#line 3103 "yacc_sql.cpp"
    break;

  case 150: /* sort_unit: expression DESC  */
#line 1090 "yacc_sql.y"
        {
      (yyval.orderby_unit) = new OrderBySqlNode();
      (yyval.orderby_unit)->expr = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = false;
	}
#line 3113 "yacc_sql.cpp"
    break;

  case 151: /* sort_unit: expression ASC  */
#line 1096 "yacc_sql.y"
        {
      (yyval.orderby_unit) = new OrderBySqlNode(); // 默认是升序
      (yyval.orderby_unit)->expr = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = true;
	}
#line 3123 "yacc_sql.cpp"
    break;

  case 152: /* group_by: %empty  */
#line 1105 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3131 "yacc_sql.cpp"
    break;

  case 153: /* group_by: GROUP BY expression_list  */
#line 1109 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3139 "yacc_sql.cpp"
    break;

  case 154: /* opt_having: %empty  */
#line 1116 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3147 "yacc_sql.cpp"
    break;

  case 155: /* opt_having: HAVING condition  */
#line 1120 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3155 "yacc_sql.cpp"
    break;

  case 156: /* opt_limit: %empty  */
#line 1127 "yacc_sql.y"
    {
      (yyval.limited_info) = nullptr;
    }
#line 3163 "yacc_sql.cpp"
    break;

  case 157: /* opt_limit: LIMIT NUMBER  */
#line 1131 "yacc_sql.y"
    {
      (yyval.limited_info) = new LimitSqlNode();
      (yyval.limited_info)->number = (yyvsp[0].number);
    }
#line 3172 "yacc_sql.cpp"
    break;

  case 158: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1139 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3181 "yacc_sql.cpp"
    break;

  case 159: /* set_variable_stmt: SET ID EQ value  */
#line 1147 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3193 "yacc_sql.cpp"
    break;


#line 3197 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1159 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
