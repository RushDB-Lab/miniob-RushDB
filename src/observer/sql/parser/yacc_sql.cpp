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
  error_sql_node->error.error_msg               = msg;
  error_sql_node->error.line                    = llocp->first_line;
  error_sql_node->error.column                  = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(
    ArithmeticExpr::Type type, Expression *left, Expression *right, const char *sql_string, YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundFunctionExpr *create_aggregate_expression(
    const char *function_name, std::vector<std::unique_ptr<Expression>> child, const char *sql_string, YYLTYPE *llocp)
{
  UnboundFunctionExpr *expr = new UnboundFunctionExpr(function_name, std::move(child));
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

ParsedSqlNode *create_table_sql_node(char *table_name, AttrInfoSqlNode *attr_def,
    std::vector<AttrInfoSqlNode> *attrinfos, char *storage_format, ParsedSqlNode *create_table_select)
{
  ParsedSqlNode      *parsed_sql_node = new ParsedSqlNode(SCF_CREATE_TABLE);
  CreateTableSqlNode &create_table    = parsed_sql_node->create_table;
  create_table.relation_name          = table_name;

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

#ifndef YY_CAST
#ifdef __cplusplus
#define YY_CAST(Type, Val) static_cast<Type>(Val)
#define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type>(Val)
#else
#define YY_CAST(Type, Val) ((Type)(Val))
#define YY_REINTERPRET_CAST(Type, Val) ((Type)(Val))
#endif
#endif
#ifndef YY_NULLPTR
#if defined __cplusplus
#if 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#else
#define YY_NULLPTR ((void *)0)
#endif
#endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY             = -2,
  YYSYMBOL_YYEOF               = 0,   /* "end of file"  */
  YYSYMBOL_YYerror             = 1,   /* error  */
  YYSYMBOL_YYUNDEF             = 2,   /* "invalid token"  */
  YYSYMBOL_SEMICOLON           = 3,   /* SEMICOLON  */
  YYSYMBOL_AS                  = 4,   /* AS  */
  YYSYMBOL_ASC                 = 5,   /* ASC  */
  YYSYMBOL_BY                  = 6,   /* BY  */
  YYSYMBOL_CREATE              = 7,   /* CREATE  */
  YYSYMBOL_DROP                = 8,   /* DROP  */
  YYSYMBOL_EXISTS              = 9,   /* EXISTS  */
  YYSYMBOL_GROUP               = 10,  /* GROUP  */
  YYSYMBOL_HAVING              = 11,  /* HAVING  */
  YYSYMBOL_ORDER               = 12,  /* ORDER  */
  YYSYMBOL_TABLE               = 13,  /* TABLE  */
  YYSYMBOL_TABLES              = 14,  /* TABLES  */
  YYSYMBOL_INDEX               = 15,  /* INDEX  */
  YYSYMBOL_CALC                = 16,  /* CALC  */
  YYSYMBOL_SELECT              = 17,  /* SELECT  */
  YYSYMBOL_DESC                = 18,  /* DESC  */
  YYSYMBOL_SHOW                = 19,  /* SHOW  */
  YYSYMBOL_SYNC                = 20,  /* SYNC  */
  YYSYMBOL_INSERT              = 21,  /* INSERT  */
  YYSYMBOL_DELETE              = 22,  /* DELETE  */
  YYSYMBOL_UPDATE              = 23,  /* UPDATE  */
  YYSYMBOL_LBRACE              = 24,  /* LBRACE  */
  YYSYMBOL_RBRACE              = 25,  /* RBRACE  */
  YYSYMBOL_LSBRACE             = 26,  /* LSBRACE  */
  YYSYMBOL_RSBRACE             = 27,  /* RSBRACE  */
  YYSYMBOL_COMMA               = 28,  /* COMMA  */
  YYSYMBOL_TRX_BEGIN           = 29,  /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT          = 30,  /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK        = 31,  /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T               = 32,  /* INT_T  */
  YYSYMBOL_IN                  = 33,  /* IN  */
  YYSYMBOL_STRING_T            = 34,  /* STRING_T  */
  YYSYMBOL_FLOAT_T             = 35,  /* FLOAT_T  */
  YYSYMBOL_DATE_T              = 36,  /* DATE_T  */
  YYSYMBOL_TEXT_T              = 37,  /* TEXT_T  */
  YYSYMBOL_VECTOR_T            = 38,  /* VECTOR_T  */
  YYSYMBOL_NOT                 = 39,  /* NOT  */
  YYSYMBOL_UNIQUE              = 40,  /* UNIQUE  */
  YYSYMBOL_NULL_T              = 41,  /* NULL_T  */
  YYSYMBOL_LIMIT               = 42,  /* LIMIT  */
  YYSYMBOL_NULLABLE            = 43,  /* NULLABLE  */
  YYSYMBOL_HELP                = 44,  /* HELP  */
  YYSYMBOL_EXIT                = 45,  /* EXIT  */
  YYSYMBOL_DOT                 = 46,  /* DOT  */
  YYSYMBOL_INTO                = 47,  /* INTO  */
  YYSYMBOL_VALUES              = 48,  /* VALUES  */
  YYSYMBOL_FROM                = 49,  /* FROM  */
  YYSYMBOL_WHERE               = 50,  /* WHERE  */
  YYSYMBOL_AND                 = 51,  /* AND  */
  YYSYMBOL_OR                  = 52,  /* OR  */
  YYSYMBOL_SET                 = 53,  /* SET  */
  YYSYMBOL_ON                  = 54,  /* ON  */
  YYSYMBOL_INFILE              = 55,  /* INFILE  */
  YYSYMBOL_EXPLAIN             = 56,  /* EXPLAIN  */
  YYSYMBOL_STORAGE             = 57,  /* STORAGE  */
  YYSYMBOL_FORMAT              = 58,  /* FORMAT  */
  YYSYMBOL_INNER               = 59,  /* INNER  */
  YYSYMBOL_JOIN                = 60,  /* JOIN  */
  YYSYMBOL_VIEW                = 61,  /* VIEW  */
  YYSYMBOL_EQ                  = 62,  /* EQ  */
  YYSYMBOL_LT                  = 63,  /* LT  */
  YYSYMBOL_GT                  = 64,  /* GT  */
  YYSYMBOL_LE                  = 65,  /* LE  */
  YYSYMBOL_GE                  = 66,  /* GE  */
  YYSYMBOL_NE                  = 67,  /* NE  */
  YYSYMBOL_LIKE                = 68,  /* LIKE  */
  YYSYMBOL_IS                  = 69,  /* IS  */
  YYSYMBOL_NUMBER              = 70,  /* NUMBER  */
  YYSYMBOL_FLOAT               = 71,  /* FLOAT  */
  YYSYMBOL_ID                  = 72,  /* ID  */
  YYSYMBOL_SSS                 = 73,  /* SSS  */
  YYSYMBOL_74_                 = 74,  /* '+'  */
  YYSYMBOL_75_                 = 75,  /* '-'  */
  YYSYMBOL_76_                 = 76,  /* '*'  */
  YYSYMBOL_77_                 = 77,  /* '/'  */
  YYSYMBOL_UMINUS              = 78,  /* UMINUS  */
  YYSYMBOL_YYACCEPT            = 79,  /* $accept  */
  YYSYMBOL_commands            = 80,  /* commands  */
  YYSYMBOL_command_wrapper     = 81,  /* command_wrapper  */
  YYSYMBOL_exit_stmt           = 82,  /* exit_stmt  */
  YYSYMBOL_help_stmt           = 83,  /* help_stmt  */
  YYSYMBOL_sync_stmt           = 84,  /* sync_stmt  */
  YYSYMBOL_begin_stmt          = 85,  /* begin_stmt  */
  YYSYMBOL_commit_stmt         = 86,  /* commit_stmt  */
  YYSYMBOL_rollback_stmt       = 87,  /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt     = 88,  /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt    = 89,  /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt     = 90,  /* desc_table_stmt  */
  YYSYMBOL_show_index_stmt     = 91,  /* show_index_stmt  */
  YYSYMBOL_create_index_stmt   = 92,  /* create_index_stmt  */
  YYSYMBOL_opt_unique          = 93,  /* opt_unique  */
  YYSYMBOL_attr_list           = 94,  /* attr_list  */
  YYSYMBOL_drop_index_stmt     = 95,  /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt   = 96,  /* create_table_stmt  */
  YYSYMBOL_create_view_stmt    = 97,  /* create_view_stmt  */
  YYSYMBOL_drop_view_stmt      = 98,  /* drop_view_stmt  */
  YYSYMBOL_attr_def_list       = 99,  /* attr_def_list  */
  YYSYMBOL_attr_def            = 100, /* attr_def  */
  YYSYMBOL_nullable_constraint = 101, /* nullable_constraint  */
  YYSYMBOL_type                = 102, /* type  */
  YYSYMBOL_insert_stmt         = 103, /* insert_stmt  */
  YYSYMBOL_values_list         = 104, /* values_list  */
  YYSYMBOL_value_list          = 105, /* value_list  */
  YYSYMBOL_value               = 106, /* value  */
  YYSYMBOL_nonnegative_value   = 107, /* nonnegative_value  */
  YYSYMBOL_storage_format      = 108, /* storage_format  */
  YYSYMBOL_delete_stmt         = 109, /* delete_stmt  */
  YYSYMBOL_update_stmt         = 110, /* update_stmt  */
  YYSYMBOL_set_clauses         = 111, /* set_clauses  */
  YYSYMBOL_setClause           = 112, /* setClause  */
  YYSYMBOL_select_stmt         = 113, /* select_stmt  */
  YYSYMBOL_calc_stmt           = 114, /* calc_stmt  */
  YYSYMBOL_expression_list     = 115, /* expression_list  */
  YYSYMBOL_expression          = 116, /* expression  */
  YYSYMBOL_alias               = 117, /* alias  */
  YYSYMBOL_func_expr           = 118, /* func_expr  */
  YYSYMBOL_sub_query_expr      = 119, /* sub_query_expr  */
  YYSYMBOL_rel_attr            = 120, /* rel_attr  */
  YYSYMBOL_relation            = 121, /* relation  */
  YYSYMBOL_rel_list            = 122, /* rel_list  */
  YYSYMBOL_join_clauses        = 123, /* join_clauses  */
  YYSYMBOL_where               = 124, /* where  */
  YYSYMBOL_condition           = 125, /* condition  */
  YYSYMBOL_comp_op             = 126, /* comp_op  */
  YYSYMBOL_opt_order_by        = 127, /* opt_order_by  */
  YYSYMBOL_sort_list           = 128, /* sort_list  */
  YYSYMBOL_sort_unit           = 129, /* sort_unit  */
  YYSYMBOL_group_by            = 130, /* group_by  */
  YYSYMBOL_opt_having          = 131, /* opt_having  */
  YYSYMBOL_opt_limit           = 132, /* opt_limit  */
  YYSYMBOL_explain_stmt        = 133, /* explain_stmt  */
  YYSYMBOL_set_variable_stmt   = 134, /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon       = 135  /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;

#ifdef short
#undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
#include <limits.h> /* INFRINGES ON USER NAME SPACE */
#if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#define YY_STDINT_H
#endif
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
#undef UINT_LEAST8_MAX
#undef UINT_LEAST16_MAX
#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
#if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#define YYPTRDIFF_T __PTRDIFF_TYPE__
#define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
#elif defined PTRDIFF_MAX
#ifndef ptrdiff_t
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#endif
#define YYPTRDIFF_T ptrdiff_t
#define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
#else
#define YYPTRDIFF_T long
#define YYPTRDIFF_MAXIMUM LONG_MAX
#endif
#endif

#ifndef YYSIZE_T
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned
#endif
#endif

#define YYSIZE_MAXIMUM \
  YY_CAST(YYPTRDIFF_T, (YYPTRDIFF_MAXIMUM < YY_CAST(YYSIZE_T, -1) ? YYPTRDIFF_MAXIMUM : YY_CAST(YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST(YYPTRDIFF_T, sizeof(X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#define YY_(Msgid) dgettext("bison-runtime", Msgid)
#endif
#endif
#ifndef YY_
#define YY_(Msgid) Msgid
#endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_PURE __attribute__((__pure__))
#else
#define YY_ATTRIBUTE_PURE
#endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define YY_ATTRIBUTE_UNUSED
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
#define YY_USE(E) ((void)(E))
#else
#define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && !defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
#if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")
#else
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                            \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"") \
      _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#endif
#define YY_IGNORE_MAYBE_UNINITIALIZED_END _Pragma("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
#define YY_IGNORE_USELESS_CAST_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
#define YY_IGNORE_USELESS_CAST_END _Pragma("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_END
#endif

#define YY_ASSERT(E) ((void)(0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#ifdef YYSTACK_USE_ALLOCA
#if YYSTACK_USE_ALLOCA
#ifdef __GNUC__
#define YYSTACK_ALLOC __builtin_alloca
#elif defined __BUILTIN_VA_ARG_INCR
#include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#elif defined _AIX
#define YYSTACK_ALLOC __alloca
#elif defined _MSC_VER
#include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#define alloca _alloca
#else
#define YYSTACK_ALLOC alloca
#if !defined _ALLOCA_H && !defined EXIT_SUCCESS
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
/* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#endif
#endif
#endif

#ifdef YYSTACK_ALLOC
/* Pacify GCC's 'empty if-body' warning.  */
#define YYSTACK_FREE(Ptr) \
  do { /* empty */        \
    ;                     \
  } while (0)
#ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
   and a page size can be as small as 4096 bytes.  So we cannot safely
   invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
   to allow for a few compiler-allocated temporary stack slots.  */
#define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#endif
#else
#define YYSTACK_ALLOC YYMALLOC
#define YYSTACK_FREE YYFREE
#ifndef YYSTACK_ALLOC_MAXIMUM
#define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#endif
#if (defined __cplusplus && !defined EXIT_SUCCESS && \
     !((defined YYMALLOC || defined malloc) && (defined YYFREE || defined free)))
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#if !defined malloc && !defined EXIT_SUCCESS
void *malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#ifndef YYFREE
#define YYFREE free
#if !defined free && !defined EXIT_SUCCESS
void free(void *); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#endif
#endif /* 1 */

#if (!defined yyoverflow && (!defined __cplusplus || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL && \
                                                         defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE    yyvs_alloc;
  YYLTYPE    yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#define YYSTACK_GAP_MAXIMUM (YYSIZEOF(union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#define YYSTACK_BYTES(N) \
  ((N) * (YYSIZEOF(yy_state_t) + YYSIZEOF(YYSTYPE) + YYSIZEOF(YYLTYPE)) + 2 * YYSTACK_GAP_MAXIMUM)

#define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
  do {                                                                 \
    YYPTRDIFF_T yynewbytes;                                            \
    YYCOPY(&yyptr->Stack_alloc, Stack, yysize);                        \
    Stack      = &yyptr->Stack_alloc;                                  \
    yynewbytes = yystacksize * YYSIZEOF(*Stack) + YYSTACK_GAP_MAXIMUM; \
    yyptr += yynewbytes / YYSIZEOF(*yyptr);                            \
  } while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
#ifndef YYCOPY
#if defined __GNUC__ && 1 < __GNUC__
#define YYCOPY(Dst, Src, Count) __builtin_memcpy(Dst, Src, YY_CAST(YYSIZE_T, (Count)) * sizeof(*(Src)))
#else
#define YYCOPY(Dst, Src, Count)         \
  do {                                  \
    YYPTRDIFF_T yyi;                    \
    for (yyi = 0; yyi < (Count); yyi++) \
      (Dst)[yyi] = (Src)[yyi];          \
  } while (0)
#endif
#endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL 73
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 288

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 57
/* YYNRULES -- Number of rules.  */
#define YYNRULES 150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 268

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 329

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX) \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? YY_CAST(yysymbol_kind_t, yytranslate[YYX]) : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] = {0,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    76,
    74,
    2,
    75,
    2,
    77,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    78};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] = {0,
    265,
    265,
    273,
    274,
    275,
    276,
    277,
    278,
    279,
    280,
    281,
    282,
    283,
    284,
    285,
    286,
    287,
    288,
    289,
    290,
    291,
    292,
    293,
    294,
    298,
    304,
    309,
    315,
    321,
    327,
    333,
    340,
    346,
    354,
    364,
    379,
    380,
    384,
    390,
    399,
    409,
    413,
    417,
    421,
    425,
    432,
    440,
    452,
    462,
    465,
    478,
    496,
    525,
    529,
    533,
    538,
    544,
    545,
    546,
    547,
    548,
    549,
    553,
    563,
    577,
    583,
    590,
    596,
    604,
    607,
    611,
    618,
    622,
    626,
    632,
    635,
    642,
    645,
    652,
    664,
    678,
    683,
    690,
    700,
    738,
    771,
    777,
    786,
    789,
    798,
    814,
    817,
    820,
    823,
    826,
    834,
    837,
    842,
    848,
    851,
    854,
    857,
    864,
    867,
    870,
    875,
    882,
    889,
    894,
    904,
    910,
    920,
    937,
    944,
    956,
    959,
    965,
    969,
    976,
    980,
    987,
    988,
    989,
    990,
    991,
    992,
    993,
    994,
    995,
    996,
    997,
    998,
    999,
    1000,
    1005,
    1008,
    1016,
    1021,
    1029,
    1035,
    1041,
    1051,
    1054,
    1062,
    1065,
    1073,
    1076,
    1084,
    1092,
    1103};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST(yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name(yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {"\"end of file\"",
    "error",
    "\"invalid token\"",
    "SEMICOLON",
    "AS",
    "ASC",
    "BY",
    "CREATE",
    "DROP",
    "EXISTS",
    "GROUP",
    "HAVING",
    "ORDER",
    "TABLE",
    "TABLES",
    "INDEX",
    "CALC",
    "SELECT",
    "DESC",
    "SHOW",
    "SYNC",
    "INSERT",
    "DELETE",
    "UPDATE",
    "LBRACE",
    "RBRACE",
    "LSBRACE",
    "RSBRACE",
    "COMMA",
    "TRX_BEGIN",
    "TRX_COMMIT",
    "TRX_ROLLBACK",
    "INT_T",
    "IN",
    "STRING_T",
    "FLOAT_T",
    "DATE_T",
    "TEXT_T",
    "VECTOR_T",
    "NOT",
    "UNIQUE",
    "NULL_T",
    "LIMIT",
    "NULLABLE",
    "HELP",
    "EXIT",
    "DOT",
    "INTO",
    "VALUES",
    "FROM",
    "WHERE",
    "AND",
    "OR",
    "SET",
    "ON",
    "INFILE",
    "EXPLAIN",
    "STORAGE",
    "FORMAT",
    "INNER",
    "JOIN",
    "VIEW",
    "EQ",
    "LT",
    "GT",
    "LE",
    "GE",
    "NE",
    "LIKE",
    "IS",
    "NUMBER",
    "FLOAT",
    "ID",
    "SSS",
    "'+'",
    "'-'",
    "'*'",
    "'/'",
    "UMINUS",
    "$accept",
    "commands",
    "command_wrapper",
    "exit_stmt",
    "help_stmt",
    "sync_stmt",
    "begin_stmt",
    "commit_stmt",
    "rollback_stmt",
    "drop_table_stmt",
    "show_tables_stmt",
    "desc_table_stmt",
    "show_index_stmt",
    "create_index_stmt",
    "opt_unique",
    "attr_list",
    "drop_index_stmt",
    "create_table_stmt",
    "create_view_stmt",
    "drop_view_stmt",
    "attr_def_list",
    "attr_def",
    "nullable_constraint",
    "type",
    "insert_stmt",
    "values_list",
    "value_list",
    "value",
    "nonnegative_value",
    "storage_format",
    "delete_stmt",
    "update_stmt",
    "set_clauses",
    "setClause",
    "select_stmt",
    "calc_stmt",
    "expression_list",
    "expression",
    "alias",
    "func_expr",
    "sub_query_expr",
    "rel_attr",
    "relation",
    "rel_list",
    "join_clauses",
    "where",
    "condition",
    "comp_op",
    "opt_order_by",
    "sort_list",
    "sort_unit",
    "group_by",
    "opt_having",
    "opt_limit",
    "explain_stmt",
    "set_variable_stmt",
    "opt_semicolon",
    YY_NULLPTR};

static const char *yysymbol_name(yysymbol_kind_t yysymbol) { return yytname[yysymbol]; }
#endif

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {232,
    4,
    5,
    136,
    136,
    -50,
    14,
    -190,
    -17,
    20,
    -15,
    -190,
    -190,
    -190,
    -190,
    -190,
    41,
    232,
    94,
    103,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    43,
    -190,
    70,
    106,
    72,
    73,
    77,
    81,
    29,
    -190,
    -190,
    -190,
    -9,
    -190,
    136,
    -190,
    -190,
    -190,
    12,
    -190,
    -190,
    -190,
    101,
    -190,
    -190,
    109,
    83,
    87,
    90,
    108,
    -190,
    -190,
    -190,
    -190,
    -5,
    22,
    100,
    -190,
    119,
    -190,
    136,
    149,
    150,
    49,
    105,
    -190,
    -190,
    136,
    -45,
    -190,
    104,
    -190,
    136,
    136,
    136,
    136,
    151,
    111,
    111,
    -12,
    128,
    112,
    29,
    113,
    122,
    21,
    172,
    118,
    137,
    120,
    101,
    -190,
    -190,
    -190,
    -190,
    -190,
    29,
    168,
    -190,
    -190,
    -190,
    58,
    58,
    -190,
    -190,
    136,
    -190,
    31,
    128,
    -190,
    118,
    170,
    162,
    -190,
    135,
    -7,
    -190,
    -190,
    129,
    174,
    138,
    172,
    -190,
    -190,
    176,
    173,
    133,
    -190,
    -190,
    -190,
    -190,
    153,
    186,
    205,
    191,
    29,
    189,
    -190,
    -190,
    0,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    180,
    62,
    89,
    136,
    136,
    112,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    8,
    113,
    195,
    164,
    -190,
    118,
    217,
    198,
    111,
    111,
    235,
    212,
    194,
    28,
    219,
    -190,
    -190,
    -190,
    -190,
    136,
    162,
    162,
    -1,
    -1,
    -190,
    175,
    203,
    -190,
    -190,
    -190,
    174,
    190,
    -190,
    -190,
    172,
    118,
    192,
    128,
    19,
    -190,
    136,
    162,
    244,
    170,
    -190,
    29,
    -1,
    -190,
    206,
    233,
    -190,
    -190,
    50,
    -190,
    234,
    162,
    205,
    -190,
    89,
    254,
    222,
    189,
    34,
    71,
    172,
    -190,
    -190,
    57,
    -190,
    136,
    196,
    -190,
    -190,
    -190,
    -190,
    207,
    6,
    -190,
    237,
    -190,
    111,
    -190,
    -190,
    136,
    -190,
    -190};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] = {0,
    37,
    0,
    88,
    88,
    0,
    0,
    27,
    0,
    0,
    0,
    28,
    29,
    30,
    26,
    25,
    0,
    0,
    0,
    0,
    24,
    23,
    17,
    18,
    19,
    20,
    9,
    10,
    11,
    14,
    12,
    13,
    8,
    15,
    16,
    5,
    7,
    6,
    3,
    4,
    21,
    22,
    0,
    36,
    0,
    0,
    0,
    0,
    0,
    88,
    0,
    75,
    72,
    73,
    108,
    74,
    0,
    99,
    97,
    86,
    103,
    101,
    102,
    98,
    87,
    33,
    32,
    0,
    0,
    0,
    0,
    0,
    148,
    1,
    150,
    2,
    77,
    0,
    0,
    31,
    0,
    48,
    88,
    0,
    0,
    0,
    0,
    67,
    69,
    88,
    0,
    96,
    0,
    104,
    0,
    0,
    0,
    0,
    89,
    0,
    0,
    0,
    115,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    107,
    95,
    70,
    71,
    76,
    0,
    0,
    109,
    100,
    105,
    91,
    92,
    93,
    94,
    88,
    110,
    103,
    115,
    34,
    0,
    0,
    0,
    79,
    0,
    115,
    81,
    149,
    0,
    49,
    0,
    0,
    45,
    46,
    38,
    0,
    0,
    40,
    68,
    106,
    90,
    0,
    111,
    142,
    0,
    0,
    63,
    133,
    131,
    0,
    121,
    122,
    123,
    124,
    125,
    126,
    129,
    127,
    0,
    116,
    0,
    0,
    0,
    80,
    57,
    58,
    59,
    60,
    61,
    62,
    56,
    0,
    0,
    0,
    44,
    0,
    0,
    0,
    0,
    0,
    0,
    144,
    0,
    0,
    0,
    134,
    132,
    130,
    128,
    0,
    0,
    0,
    118,
    83,
    82,
    0,
    0,
    55,
    54,
    52,
    49,
    77,
    78,
    39,
    0,
    0,
    0,
    115,
    103,
    112,
    88,
    0,
    135,
    0,
    65,
    0,
    117,
    119,
    120,
    0,
    53,
    50,
    43,
    47,
    0,
    0,
    142,
    143,
    145,
    0,
    146,
    64,
    0,
    56,
    0,
    42,
    35,
    113,
    85,
    0,
    0,
    84,
    66,
    51,
    41,
    0,
    139,
    136,
    137,
    147,
    0,
    141,
    140,
    0,
    114,
    138};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-190,
    -190,
    251,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -190,
    -124,
    -190,
    -190,
    -190,
    -190,
    59,
    86,
    25,
    -190,
    -190,
    47,
    -150,
    -54,
    -46,
    60,
    -190,
    -190,
    -190,
    107,
    -47,
    -190,
    -4,
    -55,
    214,
    -190,
    -190,
    -190,
    -94,
    84,
    16,
    -127,
    -189,
    110,
    -190,
    17,
    -190,
    45,
    -190,
    -190,
    -190,
    -190,
    -190};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] = {0,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    45,
    147,
    31,
    32,
    33,
    34,
    184,
    141,
    211,
    182,
    35,
    158,
    86,
    87,
    58,
    107,
    36,
    37,
    137,
    138,
    38,
    39,
    59,
    60,
    154,
    61,
    62,
    63,
    218,
    130,
    219,
    135,
    171,
    172,
    242,
    259,
    260,
    193,
    224,
    253,
    40,
    41,
    75};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] = {64,
    91,
    83,
    155,
    88,
    129,
    131,
    195,
    156,
    197,
    175,
    263,
    132,
    229,
    230,
    89,
    92,
    42,
    46,
    105,
    47,
    174,
    65,
    92,
    264,
    143,
    108,
    120,
    66,
    67,
    68,
    121,
    207,
    198,
    240,
    92,
    133,
    90,
    82,
    123,
    124,
    125,
    126,
    134,
    43,
    84,
    109,
    208,
    249,
    209,
    139,
    210,
    106,
    226,
    246,
    50,
    118,
    70,
    88,
    254,
    144,
    145,
    118,
    215,
    150,
    44,
    48,
    82,
    199,
    69,
    51,
    159,
    88,
    94,
    95,
    96,
    97,
    244,
    112,
    170,
    94,
    95,
    96,
    97,
    93,
    119,
    94,
    95,
    96,
    97,
    153,
    93,
    238,
    236,
    73,
    160,
    186,
    220,
    82,
    52,
    53,
    161,
    55,
    93,
    85,
    49,
    74,
    50,
    202,
    203,
    208,
    88,
    209,
    71,
    210,
    76,
    257,
    204,
    205,
    115,
    116,
    78,
    51,
    152,
    162,
    163,
    164,
    165,
    166,
    167,
    168,
    169,
    117,
    118,
    96,
    97,
    94,
    95,
    96,
    97,
    202,
    203,
    77,
    103,
    79,
    80,
    228,
    170,
    170,
    81,
    99,
    52,
    53,
    54,
    55,
    101,
    56,
    57,
    100,
    102,
    49,
    176,
    50,
    177,
    178,
    179,
    180,
    181,
    170,
    235,
    104,
    159,
    110,
    111,
    113,
    114,
    122,
    51,
    134,
    127,
    142,
    88,
    170,
    128,
    136,
    140,
    49,
    247,
    50,
    82,
    146,
    148,
    149,
    151,
    157,
    160,
    258,
    173,
    188,
    256,
    185,
    161,
    183,
    51,
    187,
    189,
    52,
    53,
    54,
    55,
    258,
    56,
    57,
    190,
    191,
    192,
    194,
    196,
    239,
    200,
    213,
    216,
    217,
    223,
    162,
    163,
    164,
    165,
    166,
    167,
    168,
    169,
    52,
    53,
    54,
    55,
    214,
    56,
    57,
    1,
    2,
    222,
    225,
    227,
    232,
    231,
    237,
    106,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    241,
    202,
    245,
    248,
    251,
    11,
    12,
    13,
    252,
    265,
    261,
    262,
    72,
    212,
    255,
    233,
    243,
    234,
    98,
    221,
    14,
    15,
    266,
    0,
    201,
    206,
    267,
    250,
    0,
    16,
    0,
    0,
    17};

static const yytype_int16 yycheck[] = {4,
    56,
    49,
    130,
    50,
    99,
    100,
    157,
    132,
    9,
    137,
    5,
    24,
    202,
    203,
    24,
    4,
    13,
    13,
    24,
    15,
    28,
    72,
    4,
    18,
    4,
    4,
    72,
    14,
    15,
    47,
    76,
    24,
    33,
    223,
    4,
    48,
    46,
    17,
    94,
    95,
    96,
    97,
    50,
    40,
    49,
    24,
    39,
    237,
    41,
    104,
    43,
    57,
    25,
    4,
    26,
    28,
    72,
    104,
    25,
    107,
    108,
    28,
    187,
    118,
    61,
    61,
    17,
    68,
    49,
    41,
    9,
    118,
    74,
    75,
    76,
    77,
    227,
    82,
    134,
    74,
    75,
    76,
    77,
    72,
    89,
    74,
    75,
    76,
    77,
    59,
    72,
    219,
    217,
    0,
    33,
    143,
    191,
    17,
    70,
    71,
    39,
    73,
    72,
    75,
    24,
    3,
    26,
    51,
    52,
    39,
    157,
    41,
    72,
    43,
    72,
    59,
    172,
    173,
    70,
    71,
    15,
    41,
    127,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    27,
    28,
    76,
    77,
    74,
    75,
    76,
    77,
    51,
    52,
    72,
    53,
    72,
    72,
    201,
    202,
    203,
    72,
    49,
    70,
    71,
    72,
    73,
    72,
    75,
    76,
    49,
    72,
    24,
    32,
    26,
    34,
    35,
    36,
    37,
    38,
    223,
    216,
    62,
    9,
    72,
    54,
    25,
    25,
    72,
    41,
    50,
    28,
    58,
    227,
    237,
    72,
    72,
    72,
    24,
    234,
    26,
    17,
    72,
    54,
    72,
    25,
    24,
    33,
    251,
    62,
    25,
    246,
    62,
    39,
    28,
    41,
    28,
    72,
    70,
    71,
    72,
    73,
    265,
    75,
    76,
    60,
    28,
    10,
    25,
    28,
    222,
    39,
    25,
    4,
    24,
    11,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    72,
    75,
    76,
    7,
    8,
    6,
    48,
    24,
    41,
    70,
    54,
    57,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    12,
    51,
    25,
    25,
    6,
    29,
    30,
    31,
    42,
    28,
    70,
    60,
    17,
    183,
    245,
    212,
    225,
    213,
    60,
    191,
    44,
    45,
    262,
    -1,
    170,
    174,
    265,
    238,
    -1,
    53,
    -1,
    -1,
    56};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] = {0,
    7,
    8,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    29,
    30,
    31,
    44,
    45,
    53,
    56,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    95,
    96,
    97,
    98,
    103,
    109,
    110,
    113,
    114,
    133,
    134,
    13,
    40,
    61,
    93,
    13,
    15,
    61,
    24,
    26,
    41,
    70,
    71,
    72,
    73,
    75,
    76,
    107,
    115,
    116,
    118,
    119,
    120,
    115,
    72,
    14,
    15,
    47,
    49,
    72,
    72,
    81,
    0,
    3,
    135,
    72,
    72,
    15,
    72,
    72,
    72,
    17,
    113,
    115,
    75,
    105,
    106,
    107,
    24,
    46,
    116,
    4,
    72,
    74,
    75,
    76,
    77,
    117,
    49,
    49,
    72,
    72,
    53,
    62,
    24,
    57,
    108,
    4,
    24,
    72,
    54,
    115,
    25,
    25,
    70,
    71,
    27,
    28,
    115,
    72,
    76,
    72,
    116,
    116,
    116,
    116,
    28,
    72,
    121,
    122,
    121,
    24,
    48,
    50,
    124,
    72,
    111,
    112,
    106,
    72,
    100,
    58,
    4,
    113,
    113,
    72,
    94,
    54,
    72,
    106,
    25,
    115,
    59,
    117,
    124,
    94,
    24,
    104,
    9,
    33,
    39,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    116,
    125,
    126,
    62,
    28,
    124,
    32,
    34,
    35,
    36,
    37,
    38,
    102,
    28,
    99,
    62,
    113,
    28,
    25,
    72,
    60,
    28,
    10,
    130,
    25,
    105,
    28,
    9,
    33,
    68,
    39,
    126,
    51,
    52,
    116,
    116,
    112,
    24,
    39,
    41,
    43,
    101,
    100,
    25,
    72,
    94,
    4,
    24,
    121,
    123,
    121,
    122,
    6,
    11,
    131,
    48,
    25,
    24,
    116,
    125,
    125,
    70,
    41,
    99,
    108,
    113,
    94,
    54,
    124,
    115,
    125,
    12,
    127,
    104,
    105,
    25,
    4,
    113,
    25,
    125,
    130,
    6,
    42,
    132,
    25,
    101,
    113,
    59,
    116,
    128,
    129,
    70,
    60,
    5,
    18,
    28,
    123,
    128};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] = {0,
    79,
    80,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    93,
    94,
    94,
    95,
    96,
    96,
    96,
    96,
    96,
    97,
    97,
    98,
    99,
    99,
    100,
    100,
    101,
    101,
    101,
    101,
    102,
    102,
    102,
    102,
    102,
    102,
    103,
    103,
    104,
    104,
    105,
    105,
    106,
    106,
    106,
    107,
    107,
    107,
    107,
    107,
    108,
    108,
    109,
    110,
    111,
    111,
    112,
    113,
    113,
    114,
    114,
    115,
    115,
    115,
    116,
    116,
    116,
    116,
    116,
    116,
    116,
    116,
    116,
    116,
    116,
    116,
    117,
    117,
    117,
    118,
    119,
    120,
    120,
    121,
    122,
    122,
    123,
    123,
    124,
    124,
    125,
    125,
    125,
    125,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    126,
    127,
    127,
    128,
    128,
    129,
    129,
    129,
    130,
    130,
    131,
    131,
    132,
    132,
    133,
    134,
    135};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] = {0,
    2,
    2,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    3,
    2,
    2,
    4,
    9,
    1,
    0,
    1,
    3,
    5,
    10,
    9,
    8,
    6,
    5,
    5,
    8,
    3,
    0,
    3,
    6,
    3,
    2,
    1,
    1,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    5,
    8,
    3,
    5,
    1,
    3,
    1,
    2,
    2,
    1,
    1,
    1,
    1,
    3,
    0,
    4,
    4,
    5,
    1,
    3,
    3,
    9,
    9,
    2,
    2,
    0,
    2,
    4,
    3,
    3,
    3,
    3,
    3,
    2,
    1,
    1,
    1,
    3,
    1,
    1,
    0,
    1,
    2,
    4,
    3,
    1,
    3,
    1,
    2,
    4,
    3,
    6,
    0,
    2,
    3,
    2,
    3,
    3,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    0,
    3,
    1,
    3,
    1,
    2,
    2,
    0,
    3,
    0,
    2,
    0,
    2,
    2,
    4,
    1};

enum
{
  YYENOMEM = -2
};

#define yyerrok (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYNOMEM goto yyexhaustedlab

#define YYRECOVERING() (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                                                \
  do                                                                                          \
    if (yychar == YYEMPTY) {                                                                  \
      yychar = (Token);                                                                       \
      yylval = (Value);                                                                       \
      YYPOPSTACK(yylen);                                                                      \
      yystate = *yyssp;                                                                       \
      goto yybackup;                                                                          \
    } else {                                                                                  \
      yyerror(&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                                                \
    }                                                                                         \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(Current, Rhs, N)                                              \
  do                                                                                 \
    if (N) {                                                                         \
      (Current).first_line   = YYRHSLOC(Rhs, 1).first_line;                          \
      (Current).first_column = YYRHSLOC(Rhs, 1).first_column;                        \
      (Current).last_line    = YYRHSLOC(Rhs, N).last_line;                           \
      (Current).last_column  = YYRHSLOC(Rhs, N).last_column;                         \
    } else {                                                                         \
      (Current).first_line = (Current).last_line = YYRHSLOC(Rhs, 0).last_line;       \
      (Current).first_column = (Current).last_column = YYRHSLOC(Rhs, 0).last_column; \
    }                                                                                \
  while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])

/* Enable debugging if requested.  */
#if YYDEBUG

#ifndef YYFPRINTF
#include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#define YYFPRINTF fprintf
#endif

#define YYDPRINTF(Args) \
  do {                  \
    if (yydebug)        \
      YYFPRINTF Args;   \
  } while (0)

/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YYLOCATION_PRINT

#if defined YY_LOCATION_PRINT

/* Temporary convenience wrapper in case some people defined the
   undocumented and private YY_LOCATION_PRINT macros.  */
#define YYLOCATION_PRINT(File, Loc) YY_LOCATION_PRINT(File, *(Loc))

#elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int yy_location_print_(FILE *yyo, YYLTYPE const *const yylocp)
{
  int res     = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line) {
    res += YYFPRINTF(yyo, "%d", yylocp->first_line);
    if (0 <= yylocp->first_column)
      res += YYFPRINTF(yyo, ".%d", yylocp->first_column);
  }
  if (0 <= yylocp->last_line) {
    if (yylocp->first_line < yylocp->last_line) {
      res += YYFPRINTF(yyo, "-%d", yylocp->last_line);
      if (0 <= end_col)
        res += YYFPRINTF(yyo, ".%d", end_col);
    } else if (0 <= end_col && yylocp->first_column < end_col)
      res += YYFPRINTF(yyo, "-%d", end_col);
  }
  return res;
}

#define YYLOCATION_PRINT yy_location_print_

/* Temporary convenience wrapper in case some people defined the
   undocumented and private YY_LOCATION_PRINT macros.  */
#define YY_LOCATION_PRINT(File, Loc) YYLOCATION_PRINT(File, &(Loc))

#else

#define YYLOCATION_PRINT(File, Loc) ((void)0)
/* Temporary convenience wrapper in case some people defined the
   undocumented and private YY_LOCATION_PRINT macros.  */
#define YY_LOCATION_PRINT YYLOCATION_PRINT

#endif
#endif /* !defined YYLOCATION_PRINT */

#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                                  \
  do {                                                                                 \
    if (yydebug) {                                                                     \
      YYFPRINTF(stderr, "%s ", Title);                                                 \
      yy_symbol_print(stderr, Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF(stderr, "\n");                                                         \
    }                                                                                  \
  } while (0)

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void yy_symbol_value_print(FILE *yyo, yysymbol_kind_t yykind, YYSTYPE const *const yyvaluep,
    YYLTYPE const *const yylocationp, const char *sql_string, ParsedSqlResult *sql_result, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE(yyoutput);
  YY_USE(yylocationp);
  YY_USE(sql_string);
  YY_USE(sql_result);
  YY_USE(scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void yy_symbol_print(FILE *yyo, yysymbol_kind_t yykind, YYSTYPE const *const yyvaluep,
    YYLTYPE const *const yylocationp, const char *sql_string, ParsedSqlResult *sql_result, void *scanner)
{
  YYFPRINTF(yyo, "%s %s (", yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name(yykind));

  YYLOCATION_PRINT(yyo, yylocationp);
  YYFPRINTF(yyo, ": ");
  yy_symbol_value_print(yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF(yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void yy_stack_print(yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF(stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++) {
    int yybot = *yybottom;
    YYFPRINTF(stderr, " %d", yybot);
  }
  YYFPRINTF(stderr, "\n");
}

#define YY_STACK_PRINT(Bottom, Top)    \
  do {                                 \
    if (yydebug)                       \
      yy_stack_print((Bottom), (Top)); \
  } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void yy_reduce_print(yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char *sql_string,
    ParsedSqlResult *sql_result, void *scanner)
{
  int yylno  = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %d):\n", yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++) {
    YYFPRINTF(stderr, "   $%d = ", yyi + 1);
    yy_symbol_print(stderr,
        YY_ACCESSING_SYMBOL(+yyssp[yyi + 1 - yynrhs]),
        &yyvsp[(yyi + 1) - (yynrhs)],
        &(yylsp[(yyi + 1) - (yynrhs)]),
        sql_string,
        sql_result,
        scanner);
    YYFPRINTF(stderr, "\n");
  }
}

#define YY_REDUCE_PRINT(Rule)                                                      \
  do {                                                                             \
    if (yydebug)                                                                   \
      yy_reduce_print(yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
#define YYDPRINTF(Args) ((void)0)
#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
#define YY_STACK_PRINT(Bottom, Top)
#define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Context of a parse error.  */
typedef struct
{
  yy_state_t     *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE        *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int yypcontext_expected_tokens(const yypcontext_t *yyctx, yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn     = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default(yyn)) {
    /* Start YYX at -YYN if negative to avoid negative indexes in
       YYCHECK.  In other words, skip the first -YYN actions for
       this state because they are default actions.  */
    int yyxbegin = yyn < 0 ? -yyn : 0;
    /* Stay within bounds of both yycheck and yytname.  */
    int yychecklim = YYLAST - yyn + 1;
    int yyxend     = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
    int yyx;
    for (yyx = yyxbegin; yyx < yyxend; ++yyx)
      if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror && !yytable_value_is_error(yytable[yyx + yyn])) {
        if (!yyarg)
          ++yycount;
        else if (yycount == yyargn)
          return 0;
        else
          yyarg[yycount++] = YY_CAST(yysymbol_kind_t, yyx);
      }
  }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}

#ifndef yystrlen
#if defined __GLIBC__ && defined _STRING_H
#define yystrlen(S) (YY_CAST(YYPTRDIFF_T, strlen(S)))
#else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T yystrlen(const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#endif
#endif

#ifndef yystpcpy
#if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#define yystpcpy stpcpy
#else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *yystpcpy(char *yydest, const char *yysrc)
{
  char       *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T yytnamerr(char *yyres, const char *yystr)
{
  if (*yystr == '"') {
    YYPTRDIFF_T yyn = 0;
    char const *yyp = yystr;
    for (;;)
      switch (*++yyp) {
        case '\'':
        case ',': goto do_not_strip_quotes;

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
  do_not_strip_quotes:;
  }

  if (yyres)
    return yystpcpy(yyres, yystr) - yyres;
  else
    return yystrlen(yystr);
}
#endif

static int yy_syntax_error_arguments(const yypcontext_t *yyctx, yysymbol_kind_t yyarg[], int yyargn)
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY) {
    int yyn;
    if (yyarg)
      yyarg[yycount] = yyctx->yytoken;
    ++yycount;
    yyn = yypcontext_expected_tokens(yyctx, yyarg ? yyarg + 1 : yyarg, yyargn - 1);
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
static int yysyntax_error(YYPTRDIFF_T *yymsg_alloc, char **yymsg, const yypcontext_t *yyctx)
{
  enum
  {
    YYARGS_MAX = 5
  };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments(yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount) {
#define YYCASE_(N, S) \
  case N: yyformat = S; break
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
  yysize = yystrlen(yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi) {
      YYPTRDIFF_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyarg[yyi]]);
      if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
        yysize = yysize1;
      else
        return YYENOMEM;
    }
  }

  if (*yymsg_alloc < yysize) {
    *yymsg_alloc = 2 * yysize;
    if (!(yysize <= *yymsg_alloc && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
      *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
    return -1;
  }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int   yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount) {
        yyp += yytnamerr(yyp, yytname[yyarg[yyi++]]);
        yyformat += 2;
      } else {
        ++yyp;
        ++yyformat;
      }
  }
  return 0;
}

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void yydestruct(const char *yymsg, yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp,
    const char *sql_string, ParsedSqlResult *sql_result, void *scanner)
{
  YY_USE(yyvaluep);
  YY_USE(yylocationp);
  YY_USE(sql_string);
  YY_USE(sql_result);
  YY_USE(scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT(yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/*----------.
| yyparse.  |
`----------*/

int yyparse(const char *sql_string, ParsedSqlResult *sql_result, void *scanner)
{
  /* Lookahead token kind.  */
  int yychar;

  /* The semantic value of the lookahead symbol.  */
  /* Default value used for initialization, for pacifying older GCCs
     or non-GCC compilers.  */
  YY_INITIAL_VALUE(static YYSTYPE yyval_default;)
  YYSTYPE yylval YY_INITIAL_VALUE(= yyval_default);

  /* Location data for the lookahead symbol.  */
  static YYLTYPE yyloc_default
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
      = {1, 1, 1, 1}
#endif
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
  yy_state_t  yyssa[YYINITDEPTH];
  yy_state_t *yyss  = yyssa;
  yy_state_t *yyssp = yyss;

  /* The semantic value stack: array, bottom, top.  */
  YYSTYPE  yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs  = yyvsa;
  YYSTYPE *yyvsp = yyvs;

  /* The location stack: array, bottom, top.  */
  YYLTYPE  yylsa[YYINITDEPTH];
  YYLTYPE *yyls  = yylsa;
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
  char        yymsgbuf[128];
  char       *yymsg       = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N) (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF((stderr, "Starting parse\n"));

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
  YYDPRINTF((stderr, "Entering state %d\n", yystate));
  YY_ASSERT(0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST(yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT(yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
  {
    /* Get the current used size of the three stacks, in elements.  */
    YYPTRDIFF_T yysize = yyssp - yyss + 1;

#if defined yyoverflow
    {
      /* Give user a chance to reallocate the stack.  Use copies of
         these so that the &'s don't force the real ones into
         memory.  */
      yy_state_t *yyss1 = yyss;
      YYSTYPE    *yyvs1 = yyvs;
      YYLTYPE    *yyls1 = yyls;

      /* Each stack pointer address is followed by the size of the
         data in use in that stack, in bytes.  This used to be a
         conditional around just the two extra args, but that might
         be undefined if yyoverflow is a macro.  */
      yyoverflow(YY_("memory exhausted"),
          &yyss1,
          yysize * YYSIZEOF(*yyssp),
          &yyvs1,
          yysize * YYSIZEOF(*yyvsp),
          &yyls1,
          yysize * YYSIZEOF(*yylsp),
          &yystacksize);
      yyss = yyss1;
      yyvs = yyvs1;
      yyls = yyls1;
    }
#else /* defined YYSTACK_RELOCATE */
    /* Extend the stack our own way.  */
    if (YYMAXDEPTH <= yystacksize)
      YYNOMEM;
    yystacksize *= 2;
    if (YYMAXDEPTH < yystacksize)
      yystacksize = YYMAXDEPTH;

    {
      yy_state_t    *yyss1 = yyss;
      union yyalloc *yyptr = YY_CAST(union yyalloc *, YYSTACK_ALLOC(YY_CAST(YYSIZE_T, YYSTACK_BYTES(yystacksize))));
      if (!yyptr)
        YYNOMEM;
      YYSTACK_RELOCATE(yyss_alloc, yyss);
      YYSTACK_RELOCATE(yyvs_alloc, yyvs);
      YYSTACK_RELOCATE(yyls_alloc, yyls);
#undef YYSTACK_RELOCATE
      if (yyss1 != yyssa)
        YYSTACK_FREE(yyss1);
    }
#endif

    yyssp = yyss + yysize - 1;
    yyvsp = yyvs + yysize - 1;
    yylsp = yyls + yysize - 1;

    YY_IGNORE_USELESS_CAST_BEGIN
    YYDPRINTF((stderr, "Stack size increased to %ld\n", YY_CAST(long, yystacksize)));
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
  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY) {
    YYDPRINTF((stderr, "Reading a token\n"));
    yychar = yylex(&yylval, &yylloc, scanner);
  }

  if (yychar <= YYEOF) {
    yychar  = YYEOF;
    yytoken = YYSYMBOL_YYEOF;
    YYDPRINTF((stderr, "Now at end of input.\n"));
  } else if (yychar == YYerror) {
    /* The scanner already issued an error message, process directly
       to error recovery.  But do not keep the error token as
       lookahead, it is too special and may lead us to an endless
       loop in error recovery. */
    yychar           = YYUNDEF;
    yytoken          = YYSYMBOL_YYerror;
    yyerror_range[1] = yylloc;
    goto yyerrlab1;
  } else {
    yytoken = YYTRANSLATE(yychar);
    YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
  }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0) {
    if (yytable_value_is_error(yyn))
      goto yyerrlab;
    yyn = -yyn;
    goto yyreduce;
  }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);
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
  yyval = yyvsp[1 - yylen];

  /* Default location. */
  YYLLOC_DEFAULT(yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT(yyn);
  switch (yyn) {
    case 2: /* commands: command_wrapper opt_semicolon  */
#line 266 "yacc_sql.y"
    {
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
#line 1885 "yacc_sql.cpp"
    break;

    case 25: /* exit_stmt: EXIT  */
#line 298 "yacc_sql.y"
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1894 "yacc_sql.cpp"
    break;

    case 26: /* help_stmt: HELP  */
#line 304 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1902 "yacc_sql.cpp"
    break;

    case 27: /* sync_stmt: SYNC  */
#line 309 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1910 "yacc_sql.cpp"
    break;

    case 28: /* begin_stmt: TRX_BEGIN  */
#line 315 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1918 "yacc_sql.cpp"
    break;

    case 29: /* commit_stmt: TRX_COMMIT  */
#line 321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1926 "yacc_sql.cpp"
    break;

    case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 327 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1934 "yacc_sql.cpp"
    break;

    case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 333 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1944 "yacc_sql.cpp"
    break;

    case 32: /* show_tables_stmt: SHOW TABLES  */
#line 340 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1952 "yacc_sql.cpp"
    break;

    case 33: /* desc_table_stmt: DESC ID  */
#line 346 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1962 "yacc_sql.cpp"
    break;

    case 34: /* show_index_stmt: SHOW INDEX FROM relation  */
#line 355 "yacc_sql.y"
    {
      (yyval.sql_node)             = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = (yyval.sql_node)->show_index;
      show_index.relation_name     = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1973 "yacc_sql.cpp"
    break;

    case 35: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE attr_list RBRACE  */
#line 365 "yacc_sql.y"
    {
      (yyval.sql_node)                 = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.unique              = (yyvsp[-7].unique);  // 用 opt_unique 的返回值来确定是否 UNIQUE
      create_index.index_name          = (yyvsp[-5].string);
      create_index.relation_name       = (yyvsp[-3].string);
      create_index.attribute_name.swap(*(yyvsp[-1].index_attr_list));  // $8 是 vector<string> 类型
      delete (yyvsp[-1].index_attr_list);                              // 释放指针
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1989 "yacc_sql.cpp"
    break;

    case 36: /* opt_unique: UNIQUE  */
#line 379 "yacc_sql.y"
    {
      (yyval.unique) = true;
    }
#line 1995 "yacc_sql.cpp"
    break;

    case 37: /* opt_unique: %empty  */
#line 380 "yacc_sql.y"
    {
      (yyval.unique) = false;
    }
#line 2001 "yacc_sql.cpp"
    break;

    case 38: /* attr_list: ID  */
#line 385 "yacc_sql.y"
    {
      (yyval.index_attr_list) = new std::vector<std::string>;    // 创建一个新的 vector
      (yyval.index_attr_list)->emplace_back((yyvsp[0].string));  // 将列名加入 vector
      free((yyvsp[0].string));
    }
#line 2011 "yacc_sql.cpp"
    break;

    case 39: /* attr_list: ID COMMA attr_list  */
#line 391 "yacc_sql.y"
    {
      (yyval.index_attr_list) = (yyvsp[0].index_attr_list);  // 使用现有的 vector
      (yyval.index_attr_list)
          ->emplace((yyval.index_attr_list)->begin(), (yyvsp[-2].string));  // 将新列名加入 vector 开头
      free((yyvsp[-2].string));
    }
#line 2021 "yacc_sql.cpp"
    break;

    case 40: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 400 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name    = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2033 "yacc_sql.cpp"
    break;

    case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt */
#line 410 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-7].string), (yyvsp[-5].attr_info), (yyvsp[-4].attr_infos), (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2041 "yacc_sql.cpp"
    break;

    case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 414 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-6].string), (yyvsp[-4].attr_info), (yyvsp[-3].attr_infos), (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2049 "yacc_sql.cpp"
    break;

    case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 418 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-5].string), (yyvsp[-3].attr_info), (yyvsp[-2].attr_infos), (yyvsp[0].string), nullptr);
    }
#line 2057 "yacc_sql.cpp"
    break;

    case 44: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 422 "yacc_sql.y"
    {
      (yyval.sql_node) =
          create_table_sql_node((yyvsp[-3].string), nullptr, nullptr, (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2065 "yacc_sql.cpp"
    break;

    case 45: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 426 "yacc_sql.y"
    {
      (yyval.sql_node) =
          create_table_sql_node((yyvsp[-2].string), nullptr, nullptr, (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2073 "yacc_sql.cpp"
    break;

    case 46: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 433 "yacc_sql.y"
    {
      (yyval.sql_node)               = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name      = (yyvsp[-2].string);
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-2].string));
    }
#line 2085 "yacc_sql.cpp"
    break;

    case 47: /* create_view_stmt: CREATE VIEW ID LBRACE attr_list RBRACE AS select_stmt  */
#line 441 "yacc_sql.y"
    {
      (yyval.sql_node)               = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name      = (yyvsp[-5].string);
      create_view.attribute_names    = std::move(*(yyvsp[-3].index_attr_list));
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-5].string));
    }
#line 2098 "yacc_sql.cpp"
    break;

    case 48: /* drop_view_stmt: DROP VIEW ID  */
#line 453 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2108 "yacc_sql.cpp"
    break;

    case 49: /* attr_def_list: %empty  */
#line 462 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2116 "yacc_sql.cpp"
    break;

    case 50: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 466 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2130 "yacc_sql.cpp"
    break;

    case 51: /* attr_def: ID type LBRACE NUMBER RBRACE nullable_constraint  */
#line 479 "yacc_sql.y"
    {
      (yyval.attr_info)       = new AttrInfoSqlNode;
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
#line 2152 "yacc_sql.cpp"
    break;

    case 52: /* attr_def: ID type nullable_constraint  */
#line 497 "yacc_sql.y"
    {
      (yyval.attr_info)       = new AttrInfoSqlNode;
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
#line 2182 "yacc_sql.cpp"
    break;

    case 53: /* nullable_constraint: NOT NULL_T  */
#line 526 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // NOT NULL 对应的可空性为 false
    }
#line 2190 "yacc_sql.cpp"
    break;

    case 54: /* nullable_constraint: NULLABLE  */
#line 530 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULLABLE 对应的可空性为 true 2022
    }
#line 2198 "yacc_sql.cpp"
    break;

    case 55: /* nullable_constraint: NULL_T  */
#line 534 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULL 对应的可空性也为 true 2023
    }
#line 2206 "yacc_sql.cpp"
    break;

    case 56: /* nullable_constraint: %empty  */
#line 538 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // 默认情况为 NULL
    }
#line 2214 "yacc_sql.cpp"
    break;

    case 57: /* type: INT_T  */
#line 544 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::INTS);
    }
#line 2220 "yacc_sql.cpp"
    break;

    case 58: /* type: STRING_T  */
#line 545 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::CHARS);
    }
#line 2226 "yacc_sql.cpp"
    break;

    case 59: /* type: FLOAT_T  */
#line 546 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::FLOATS);
    }
#line 2232 "yacc_sql.cpp"
    break;

    case 60: /* type: DATE_T  */
#line 547 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::DATES);
    }
#line 2238 "yacc_sql.cpp"
    break;

    case 61: /* type: TEXT_T  */
#line 548 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::TEXTS);
    }
#line 2244 "yacc_sql.cpp"
    break;

    case 62: /* type: VECTOR_T  */
#line 549 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::VECTORS);
    }
#line 2250 "yacc_sql.cpp"
    break;

    case 63: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 554 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-2].string));
    }
#line 2264 "yacc_sql.cpp"
    break;

    case 64: /* insert_stmt: INSERT INTO ID LBRACE attr_list RBRACE VALUES values_list  */
#line 564 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->insertion.attr_names    = std::move(*(yyvsp[-3].index_attr_list));
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-5].string));
    }
#line 2279 "yacc_sql.cpp"
    break;

    case 65: /* values_list: LBRACE value_list RBRACE  */
#line 578 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2289 "yacc_sql.cpp"
    break;

    case 66: /* values_list: values_list COMMA LBRACE value_list RBRACE  */
#line 584 "yacc_sql.y"
    {
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2298 "yacc_sql.cpp"
    break;

    case 67: /* value_list: value  */
#line 591 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2308 "yacc_sql.cpp"
    break;

    case 68: /* value_list: value_list COMMA value  */
#line 597 "yacc_sql.y"
    {
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2317 "yacc_sql.cpp"
    break;

    case 69: /* value: nonnegative_value  */
#line 604 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2325 "yacc_sql.cpp"
    break;

    case 70: /* value: '-' NUMBER  */
#line 607 "yacc_sql.y"
    {
      (yyval.value) = new Value(-(yyvsp[0].number));
      (yyloc)       = (yylsp[-1]);
    }
#line 2334 "yacc_sql.cpp"
    break;

    case 71: /* value: '-' FLOAT  */
#line 611 "yacc_sql.y"
    {
      (yyval.value) = new Value(-(yyvsp[0].floats));
      (yyloc)       = (yylsp[-1]);
    }
#line 2343 "yacc_sql.cpp"
    break;

    case 72: /* nonnegative_value: NUMBER  */
#line 618 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[0].number));
      (yyloc)       = (yylsp[0]);
    }
#line 2352 "yacc_sql.cpp"
    break;

    case 73: /* nonnegative_value: FLOAT  */
#line 622 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[0].floats));
      (yyloc)       = (yylsp[0]);
    }
#line 2361 "yacc_sql.cpp"
    break;

    case 74: /* nonnegative_value: SSS  */
#line 626 "yacc_sql.y"
    {
      char *tmp     = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2372 "yacc_sql.cpp"
    break;

    case 75: /* nonnegative_value: NULL_T  */
#line 632 "yacc_sql.y"
    {
      (yyval.value) = new Value(NullValue());
    }
#line 2380 "yacc_sql.cpp"
    break;

    case 76: /* nonnegative_value: LSBRACE value_list RSBRACE  */
#line 635 "yacc_sql.y"
    {
      (yyval.value) = new Value(ListValue(), *(yyvsp[-1].value_list));
    }
#line 2388 "yacc_sql.cpp"
    break;

    case 77: /* storage_format: %empty  */
#line 642 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2396 "yacc_sql.cpp"
    break;

    case 78: /* storage_format: STORAGE FORMAT EQ ID  */
#line 646 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2404 "yacc_sql.cpp"
    break;

    case 79: /* delete_stmt: DELETE FROM ID where  */
#line 653 "yacc_sql.y"
    {
      (yyval.sql_node)                         = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.condition = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-1].string));
    }
#line 2417 "yacc_sql.cpp"
    break;

    case 80: /* update_stmt: UPDATE ID SET set_clauses where  */
#line 665 "yacc_sql.y"
    {
      (yyval.sql_node)                       = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.set_clauses.swap(*(yyvsp[-1].set_clauses));
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-3].string));
      delete (yyvsp[-1].set_clauses);
    }
#line 2432 "yacc_sql.cpp"
    break;

    case 81: /* set_clauses: setClause  */
#line 679 "yacc_sql.y"
    {
      (yyval.set_clauses) = new std::vector<SetClauseSqlNode>;
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2441 "yacc_sql.cpp"
    break;

    case 82: /* set_clauses: set_clauses COMMA setClause  */
#line 684 "yacc_sql.y"
    {
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2449 "yacc_sql.cpp"
    break;

    case 83: /* setClause: ID EQ expression  */
#line 691 "yacc_sql.y"
    {
      (yyval.set_clause)             = new SetClauseSqlNode;
      (yyval.set_clause)->field_name = (yyvsp[-2].string);
      (yyval.set_clause)->value      = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2460 "yacc_sql.cpp"
    break;

    case 84: /* select_stmt: SELECT expression_list FROM rel_list where group_by opt_having opt_order_by opt_limit  */
#line 701 "yacc_sql.y"
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
#line 2502 "yacc_sql.cpp"
    break;

    case 85: /* select_stmt: SELECT expression_list FROM relation INNER JOIN join_clauses where group_by  */
#line 739 "yacc_sql.y"
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
        for (auto it = (yyvsp[-2].join_clauses)->relations.rbegin(); it != (yyvsp[-2].join_clauses)->relations.rend();
            ++it) {
          (yyval.sql_node)->selection.relations.emplace_back(std::move(*it));
        }
        (yyval.sql_node)->selection.conditions = std::move((yyvsp[-2].join_clauses)->conditions);
      }

      if ((yyvsp[-1].expression) != nullptr) {
        auto ptr = (yyval.sql_node)->selection.conditions.release();
        (yyval.sql_node)->selection.conditions =
            std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-1].expression));
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2536 "yacc_sql.cpp"
    break;

    case 86: /* calc_stmt: CALC expression_list  */
#line 772 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2546 "yacc_sql.cpp"
    break;

    case 87: /* calc_stmt: SELECT expression_list  */
#line 778 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2556 "yacc_sql.cpp"
    break;

    case 88: /* expression_list: %empty  */
#line 786 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
    }
#line 2564 "yacc_sql.cpp"
    break;

    case 89: /* expression_list: expression alias  */
#line 790 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2577 "yacc_sql.cpp"
    break;

    case 90: /* expression_list: expression alias COMMA expression_list  */
#line 799 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if (nullptr != (yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), std::move((yyvsp[-3].expression)));
      free((yyvsp[-2].string));
    }
#line 2594 "yacc_sql.cpp"
    break;

    case 91: /* expression: expression '+' expression  */
#line 814 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2602 "yacc_sql.cpp"
    break;

    case 92: /* expression: expression '-' expression  */
#line 817 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2610 "yacc_sql.cpp"
    break;

    case 93: /* expression: expression '*' expression  */
#line 820 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2618 "yacc_sql.cpp"
    break;

    case 94: /* expression: expression '/' expression  */
#line 823 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2626 "yacc_sql.cpp"
    break;

    case 95: /* expression: LBRACE expression_list RBRACE  */
#line 826 "yacc_sql.y"
    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().get();
      } else {
        (yyval.expression) = new ListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2639 "yacc_sql.cpp"
    break;

    case 96: /* expression: '-' expression  */
#line 834 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2647 "yacc_sql.cpp"
    break;

    case 97: /* expression: nonnegative_value  */
#line 837 "yacc_sql.y"
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2657 "yacc_sql.cpp"
    break;

    case 98: /* expression: rel_attr  */
#line 842 "yacc_sql.y"
    {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression)   = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2668 "yacc_sql.cpp"
    break;

    case 99: /* expression: '*'  */
#line 848 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr();
    }
#line 2676 "yacc_sql.cpp"
    break;

    case 100: /* expression: ID DOT '*'  */
#line 851 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2684 "yacc_sql.cpp"
    break;

    case 101: /* expression: func_expr  */
#line 854 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // AggrFuncExpr
    }
#line 2692 "yacc_sql.cpp"
    break;

    case 102: /* expression: sub_query_expr  */
#line 857 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // SubQueryExpr
    }
#line 2700 "yacc_sql.cpp"
    break;

    case 103: /* alias: %empty  */
#line 864 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2708 "yacc_sql.cpp"
    break;

    case 104: /* alias: ID  */
#line 867 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2716 "yacc_sql.cpp"
    break;

    case 105: /* alias: AS ID  */
#line 870 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2724 "yacc_sql.cpp"
    break;

    case 106: /* func_expr: ID LBRACE expression_list RBRACE  */
#line 876 "yacc_sql.y"
    {
      (yyval.expression) = new UnboundFunctionExpr((yyvsp[-3].string), std::move(*(yyvsp[-1].expression_list)));
    }
#line 2732 "yacc_sql.cpp"
    break;

    case 107: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 883 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2740 "yacc_sql.cpp"
    break;

    case 108: /* rel_attr: ID  */
#line 889 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2750 "yacc_sql.cpp"
    break;

    case 109: /* rel_attr: ID DOT ID  */
#line 894 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2762 "yacc_sql.cpp"
    break;

    case 110: /* relation: ID  */
#line 904 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2770 "yacc_sql.cpp"
    break;

    case 111: /* rel_list: relation alias  */
#line 910 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<RelationNode>();
      if (nullptr != (yyvsp[0].string)) {
        (yyval.relation_list)->emplace_back((yyvsp[-1].string), (yyvsp[0].string));
        free((yyvsp[0].string));
      } else {
        (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      }
      free((yyvsp[-1].string));
    }
#line 2785 "yacc_sql.cpp"
    break;

    case 112: /* rel_list: relation alias COMMA rel_list  */
#line 920 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationNode>;
      }
      if (nullptr != (yyvsp[-2].string)) {
        (yyval.relation_list)
            ->insert((yyval.relation_list)->begin(), RelationNode((yyvsp[-3].string), (yyvsp[-2].string)));
        free((yyvsp[-2].string));
      } else {
        (yyval.relation_list)->insert((yyval.relation_list)->begin(), RelationNode((yyvsp[-3].string)));
      }
      free((yyvsp[-3].string));
    }
#line 2804 "yacc_sql.cpp"
    break;

    case 113: /* join_clauses: relation ON condition  */
#line 938 "yacc_sql.y"
    {
      (yyval.join_clauses) = new JoinSqlNode;
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-2].string));
      (yyval.join_clauses)->conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2815 "yacc_sql.cpp"
    break;

    case 114: /* join_clauses: relation ON condition INNER JOIN join_clauses  */
#line 945 "yacc_sql.y"
    {
      (yyval.join_clauses) = (yyvsp[0].join_clauses);
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-5].string));
      auto ptr = (yyval.join_clauses)->conditions.release();
      (yyval.join_clauses)->conditions =
          std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-3].expression));
      free((yyvsp[-5].string));
    }
#line 2827 "yacc_sql.cpp"
    break;

    case 115: /* where: %empty  */
#line 956 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2835 "yacc_sql.cpp"
    break;

    case 116: /* where: WHERE condition  */
#line 959 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2843 "yacc_sql.cpp"
    break;

    case 117: /* condition: expression comp_op expression  */
#line 966 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2851 "yacc_sql.cpp"
    break;

    case 118: /* condition: comp_op expression  */
#line 970 "yacc_sql.y"
    {
      Value val;
      val.set_null(true);
      ValueExpr *temp_expr = new ValueExpr(val);
      (yyval.expression)   = new ComparisonExpr((yyvsp[-1].comp), temp_expr, (yyvsp[0].expression));
    }
#line 2862 "yacc_sql.cpp"
    break;

    case 119: /* condition: condition AND condition  */
#line 977 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2870 "yacc_sql.cpp"
    break;

    case 120: /* condition: condition OR condition  */
#line 981 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2878 "yacc_sql.cpp"
    break;

    case 121: /* comp_op: EQ  */
#line 987 "yacc_sql.y"
    {
      (yyval.comp) = EQUAL_TO;
    }
#line 2884 "yacc_sql.cpp"
    break;

    case 122: /* comp_op: LT  */
#line 988 "yacc_sql.y"
    {
      (yyval.comp) = LESS_THAN;
    }
#line 2890 "yacc_sql.cpp"
    break;

    case 123: /* comp_op: GT  */
#line 989 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_THAN;
    }
#line 2896 "yacc_sql.cpp"
    break;

    case 124: /* comp_op: LE  */
#line 990 "yacc_sql.y"
    {
      (yyval.comp) = LESS_EQUAL;
    }
#line 2902 "yacc_sql.cpp"
    break;

    case 125: /* comp_op: GE  */
#line 991 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_EQUAL;
    }
#line 2908 "yacc_sql.cpp"
    break;

    case 126: /* comp_op: NE  */
#line 992 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EQUAL;
    }
#line 2914 "yacc_sql.cpp"
    break;

    case 127: /* comp_op: IS  */
#line 993 "yacc_sql.y"
    {
      (yyval.comp) = IS_OP;
    }
#line 2920 "yacc_sql.cpp"
    break;

    case 128: /* comp_op: IS NOT  */
#line 994 "yacc_sql.y"
    {
      (yyval.comp) = IS_NOT_OP;
    }
#line 2926 "yacc_sql.cpp"
    break;

    case 129: /* comp_op: LIKE  */
#line 995 "yacc_sql.y"
    {
      (yyval.comp) = LIKE_OP;
    }
#line 2932 "yacc_sql.cpp"
    break;

    case 130: /* comp_op: NOT LIKE  */
#line 996 "yacc_sql.y"
    {
      (yyval.comp) = NOT_LIKE_OP;
    }
#line 2938 "yacc_sql.cpp"
    break;

    case 131: /* comp_op: IN  */
#line 997 "yacc_sql.y"
    {
      (yyval.comp) = IN_OP;
    }
#line 2944 "yacc_sql.cpp"
    break;

    case 132: /* comp_op: NOT IN  */
#line 998 "yacc_sql.y"
    {
      (yyval.comp) = NOT_IN_OP;
    }
#line 2950 "yacc_sql.cpp"
    break;

    case 133: /* comp_op: EXISTS  */
#line 999 "yacc_sql.y"
    {
      (yyval.comp) = EXISTS_OP;
    }
#line 2956 "yacc_sql.cpp"
    break;

    case 134: /* comp_op: NOT EXISTS  */
#line 1000 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EXISTS_OP;
    }
#line 2962 "yacc_sql.cpp"
    break;

    case 135: /* opt_order_by: %empty  */
#line 1005 "yacc_sql.y"
    {
      (yyval.orderby_list) = nullptr;
    }
#line 2970 "yacc_sql.cpp"
    break;

    case 136: /* opt_order_by: ORDER BY sort_list  */
#line 1009 "yacc_sql.y"
    {
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
      std::reverse((yyval.orderby_list)->begin(), (yyval.orderby_list)->end());
    }
#line 2979 "yacc_sql.cpp"
    break;

    case 137: /* sort_list: sort_unit  */
#line 1017 "yacc_sql.y"
    {
      (yyval.orderby_list) = new std::vector<OrderBySqlNode>;
      (yyval.orderby_list)->emplace_back(std::move(*(yyvsp[0].orderby_unit)));
    }
#line 2988 "yacc_sql.cpp"
    break;

    case 138: /* sort_list: sort_unit COMMA sort_list  */
#line 1022 "yacc_sql.y"
    {
      (yyvsp[0].orderby_list)->emplace_back(std::move(*(yyvsp[-2].orderby_unit)));
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
    }
#line 2997 "yacc_sql.cpp"
    break;

    case 139: /* sort_unit: expression  */
#line 1030 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 3007 "yacc_sql.cpp"
    break;

    case 140: /* sort_unit: expression DESC  */
#line 1036 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = false;
    }
#line 3017 "yacc_sql.cpp"
    break;

    case 141: /* sort_unit: expression ASC  */
#line 1042 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();  // 默认是升序
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 3027 "yacc_sql.cpp"
    break;

    case 142: /* group_by: %empty  */
#line 1051 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3035 "yacc_sql.cpp"
    break;

    case 143: /* group_by: GROUP BY expression_list  */
#line 1055 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3043 "yacc_sql.cpp"
    break;

    case 144: /* opt_having: %empty  */
#line 1062 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3051 "yacc_sql.cpp"
    break;

    case 145: /* opt_having: HAVING condition  */
#line 1066 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3059 "yacc_sql.cpp"
    break;

    case 146: /* opt_limit: %empty  */
#line 1073 "yacc_sql.y"
    {
      (yyval.limited_info) = nullptr;
    }
#line 3067 "yacc_sql.cpp"
    break;

    case 147: /* opt_limit: LIMIT NUMBER  */
#line 1077 "yacc_sql.y"
    {
      (yyval.limited_info)         = new LimitSqlNode();
      (yyval.limited_info)->number = (yyvsp[0].number);
    }
#line 3076 "yacc_sql.cpp"
    break;

    case 148: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1085 "yacc_sql.y"
    {
      (yyval.sql_node)                   = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3085 "yacc_sql.cpp"
    break;

    case 149: /* set_variable_stmt: SET ID EQ value  */
#line 1093 "yacc_sql.y"
    {
      (yyval.sql_node)                     = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3097 "yacc_sql.cpp"
    break;

#line 3101 "yacc_sql.cpp"

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
  YY_SYMBOL_PRINT("-> $$ =", YY_CAST(yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK(yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi   = yypgoto[yylhs] + *yyssp;
    yystate         = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp ? yytable[yyi] : yydefgoto[yylhs]);
  }

  goto yynewstate;

/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE(yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus) {
    ++yynerrs;
    {
      yypcontext_t yyctx  = {yyssp, yytoken, &yylloc};
      char const  *yymsgp = YY_("syntax error");
      int          yysyntax_error_status;
      yysyntax_error_status = yysyntax_error(&yymsg_alloc, &yymsg, &yyctx);
      if (yysyntax_error_status == 0)
        yymsgp = yymsg;
      else if (yysyntax_error_status == -1) {
        if (yymsg != yymsgbuf)
          YYSTACK_FREE(yymsg);
        yymsg = YY_CAST(char *, YYSTACK_ALLOC(YY_CAST(YYSIZE_T, yymsg_alloc)));
        if (yymsg) {
          yysyntax_error_status = yysyntax_error(&yymsg_alloc, &yymsg, &yyctx);
          yymsgp                = yymsg;
        } else {
          yymsg                 = yymsgbuf;
          yymsg_alloc           = sizeof yymsgbuf;
          yysyntax_error_status = YYENOMEM;
        }
      }
      yyerror(&yylloc, sql_string, sql_result, scanner, yymsgp);
      if (yysyntax_error_status == YYENOMEM)
        YYNOMEM;
    }
  }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3) {
    /* If just tried and failed to reuse lookahead token after an
       error, discard it.  */

    if (yychar <= YYEOF) {
      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        YYABORT;
    } else {
      yydestruct("Error: discarding", yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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
  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;

/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3; /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;) {
    yyn = yypact[yystate];
    if (!yypact_value_is_default(yyn)) {
      yyn += YYSYMBOL_YYerror;
      if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror) {
        yyn = yytable[yyn];
        if (0 < yyn)
          break;
      }
    }

    /* Pop the current state because it cannot handle the error token.  */
    if (yyssp == yyss)
      YYABORT;

    yyerror_range[1] = *yylsp;
    yydestruct("Error: popping", YY_ACCESSING_SYMBOL(yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
    YYPOPSTACK(1);
    yystate = *yyssp;
    YY_STACK_PRINT(yyss, yyssp);
  }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT(*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT("Shifting", YY_ACCESSING_SYMBOL(yyn), yyvsp, yylsp);

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
  yyerror(&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY) {
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = YYTRANSLATE(yychar);
    yydestruct("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
  }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK(yylen);
  YY_STACK_PRINT(yyss, yyssp);
  while (yyssp != yyss) {
    yydestruct("Cleanup: popping", YY_ACCESSING_SYMBOL(+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
    YYPOPSTACK(1);
  }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE(yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE(yymsg);
  return yyresult;
}

#line 1105 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result)
{
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
