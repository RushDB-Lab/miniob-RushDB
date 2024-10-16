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
  YYSYMBOL_COMMA               = 26,  /* COMMA  */
  YYSYMBOL_TRX_BEGIN           = 27,  /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT          = 28,  /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK        = 29,  /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T               = 30,  /* INT_T  */
  YYSYMBOL_IN                  = 31,  /* IN  */
  YYSYMBOL_STRING_T            = 32,  /* STRING_T  */
  YYSYMBOL_FLOAT_T             = 33,  /* FLOAT_T  */
  YYSYMBOL_DATE_T              = 34,  /* DATE_T  */
  YYSYMBOL_TEXT_T              = 35,  /* TEXT_T  */
  YYSYMBOL_VECTOR_T            = 36,  /* VECTOR_T  */
  YYSYMBOL_NOT                 = 37,  /* NOT  */
  YYSYMBOL_UNIQUE              = 38,  /* UNIQUE  */
  YYSYMBOL_NULL_T              = 39,  /* NULL_T  */
  YYSYMBOL_LIMIT               = 40,  /* LIMIT  */
  YYSYMBOL_NULLABLE            = 41,  /* NULLABLE  */
  YYSYMBOL_HELP                = 42,  /* HELP  */
  YYSYMBOL_EXIT                = 43,  /* EXIT  */
  YYSYMBOL_DOT                 = 44,  /* DOT  */
  YYSYMBOL_INTO                = 45,  /* INTO  */
  YYSYMBOL_VALUES              = 46,  /* VALUES  */
  YYSYMBOL_FROM                = 47,  /* FROM  */
  YYSYMBOL_WHERE               = 48,  /* WHERE  */
  YYSYMBOL_AND                 = 49,  /* AND  */
  YYSYMBOL_OR                  = 50,  /* OR  */
  YYSYMBOL_SET                 = 51,  /* SET  */
  YYSYMBOL_ON                  = 52,  /* ON  */
  YYSYMBOL_LOAD                = 53,  /* LOAD  */
  YYSYMBOL_INFILE              = 54,  /* INFILE  */
  YYSYMBOL_EXPLAIN             = 55,  /* EXPLAIN  */
  YYSYMBOL_STORAGE             = 56,  /* STORAGE  */
  YYSYMBOL_FORMAT              = 57,  /* FORMAT  */
  YYSYMBOL_INNER               = 58,  /* INNER  */
  YYSYMBOL_JOIN                = 59,  /* JOIN  */
  YYSYMBOL_VIEW                = 60,  /* VIEW  */
  YYSYMBOL_EQ                  = 61,  /* EQ  */
  YYSYMBOL_LT                  = 62,  /* LT  */
  YYSYMBOL_GT                  = 63,  /* GT  */
  YYSYMBOL_LE                  = 64,  /* LE  */
  YYSYMBOL_GE                  = 65,  /* GE  */
  YYSYMBOL_NE                  = 66,  /* NE  */
  YYSYMBOL_LIKE                = 67,  /* LIKE  */
  YYSYMBOL_IS                  = 68,  /* IS  */
  YYSYMBOL_NUMBER              = 69,  /* NUMBER  */
  YYSYMBOL_FLOAT               = 70,  /* FLOAT  */
  YYSYMBOL_ID                  = 71,  /* ID  */
  YYSYMBOL_SSS                 = 72,  /* SSS  */
  YYSYMBOL_73_                 = 73,  /* '+'  */
  YYSYMBOL_74_                 = 74,  /* '-'  */
  YYSYMBOL_75_                 = 75,  /* '*'  */
  YYSYMBOL_76_                 = 76,  /* '/'  */
  YYSYMBOL_UMINUS              = 77,  /* UMINUS  */
  YYSYMBOL_YYACCEPT            = 78,  /* $accept  */
  YYSYMBOL_commands            = 79,  /* commands  */
  YYSYMBOL_command_wrapper     = 80,  /* command_wrapper  */
  YYSYMBOL_exit_stmt           = 81,  /* exit_stmt  */
  YYSYMBOL_help_stmt           = 82,  /* help_stmt  */
  YYSYMBOL_sync_stmt           = 83,  /* sync_stmt  */
  YYSYMBOL_begin_stmt          = 84,  /* begin_stmt  */
  YYSYMBOL_commit_stmt         = 85,  /* commit_stmt  */
  YYSYMBOL_rollback_stmt       = 86,  /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt     = 87,  /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt    = 88,  /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt     = 89,  /* desc_table_stmt  */
  YYSYMBOL_show_index_stmt     = 90,  /* show_index_stmt  */
  YYSYMBOL_create_index_stmt   = 91,  /* create_index_stmt  */
  YYSYMBOL_opt_unique          = 92,  /* opt_unique  */
  YYSYMBOL_attr_list           = 93,  /* attr_list  */
  YYSYMBOL_drop_index_stmt     = 94,  /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt   = 95,  /* create_table_stmt  */
  YYSYMBOL_create_view_stmt    = 96,  /* create_view_stmt  */
  YYSYMBOL_drop_view_stmt      = 97,  /* drop_view_stmt  */
  YYSYMBOL_attr_def_list       = 98,  /* attr_def_list  */
  YYSYMBOL_attr_def            = 99,  /* attr_def  */
  YYSYMBOL_nullable_constraint = 100, /* nullable_constraint  */
  YYSYMBOL_type                = 101, /* type  */
  YYSYMBOL_insert_stmt         = 102, /* insert_stmt  */
  YYSYMBOL_values_list         = 103, /* values_list  */
  YYSYMBOL_value_list          = 104, /* value_list  */
  YYSYMBOL_value               = 105, /* value  */
  YYSYMBOL_nonnegative_value   = 106, /* nonnegative_value  */
  YYSYMBOL_storage_format      = 107, /* storage_format  */
  YYSYMBOL_delete_stmt         = 108, /* delete_stmt  */
  YYSYMBOL_update_stmt         = 109, /* update_stmt  */
  YYSYMBOL_set_clauses         = 110, /* set_clauses  */
  YYSYMBOL_setClause           = 111, /* setClause  */
  YYSYMBOL_select_stmt         = 112, /* select_stmt  */
  YYSYMBOL_calc_stmt           = 113, /* calc_stmt  */
  YYSYMBOL_expression_list     = 114, /* expression_list  */
  YYSYMBOL_expression          = 115, /* expression  */
  YYSYMBOL_alias               = 116, /* alias  */
  YYSYMBOL_aggr_func_expr      = 117, /* aggr_func_expr  */
  YYSYMBOL_sub_query_expr      = 118, /* sub_query_expr  */
  YYSYMBOL_rel_attr            = 119, /* rel_attr  */
  YYSYMBOL_relation            = 120, /* relation  */
  YYSYMBOL_rel_list            = 121, /* rel_list  */
  YYSYMBOL_join_clauses        = 122, /* join_clauses  */
  YYSYMBOL_where               = 123, /* where  */
  YYSYMBOL_condition           = 124, /* condition  */
  YYSYMBOL_comp_op             = 125, /* comp_op  */
  YYSYMBOL_opt_order_by        = 126, /* opt_order_by  */
  YYSYMBOL_sort_list           = 127, /* sort_list  */
  YYSYMBOL_sort_unit           = 128, /* sort_unit  */
  YYSYMBOL_group_by            = 129, /* group_by  */
  YYSYMBOL_opt_having          = 130, /* opt_having  */
  YYSYMBOL_opt_limit           = 131, /* opt_limit  */
  YYSYMBOL_explain_stmt        = 132, /* explain_stmt  */
  YYSYMBOL_set_variable_stmt   = 133, /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon       = 134  /* opt_semicolon  */
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
#define YYFINAL 72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 57
/* YYNRULES -- Number of rules.  */
#define YYNRULES 149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 265

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 328

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
    75,
    73,
    2,
    74,
    2,
    76,
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
    77};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] = {0,
    266,
    266,
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
    293,
    294,
    295,
    296,
    300,
    306,
    311,
    317,
    323,
    329,
    335,
    342,
    348,
    356,
    366,
    381,
    382,
    386,
    392,
    401,
    411,
    415,
    419,
    423,
    427,
    434,
    442,
    454,
    464,
    467,
    480,
    498,
    527,
    531,
    535,
    540,
    546,
    547,
    548,
    549,
    550,
    551,
    555,
    565,
    579,
    585,
    592,
    598,
    606,
    609,
    613,
    620,
    624,
    628,
    634,
    641,
    644,
    651,
    663,
    677,
    682,
    689,
    699,
    737,
    770,
    776,
    785,
    788,
    797,
    813,
    816,
    819,
    822,
    825,
    833,
    836,
    841,
    847,
    850,
    853,
    856,
    863,
    866,
    869,
    874,
    881,
    888,
    893,
    903,
    909,
    919,
    936,
    943,
    955,
    958,
    964,
    968,
    975,
    979,
    986,
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
    1004,
    1007,
    1015,
    1020,
    1028,
    1034,
    1040,
    1050,
    1053,
    1061,
    1064,
    1072,
    1075,
    1096,
    1104,
    1115};
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
    "LOAD",
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
    "aggr_func_expr",
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

#define YYPACT_NINF (-145)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {223,
    6,
    9,
    -11,
    -11,
    -56,
    16,
    -145,
    -22,
    -15,
    -21,
    -145,
    -145,
    -145,
    -145,
    -145,
    -1,
    223,
    67,
    85,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    20,
    -145,
    29,
    113,
    81,
    83,
    84,
    129,
    -145,
    -145,
    -145,
    -3,
    -145,
    -11,
    -145,
    -145,
    -145,
    10,
    -145,
    -145,
    -145,
    109,
    -145,
    -145,
    110,
    87,
    88,
    111,
    99,
    -145,
    -145,
    -145,
    -145,
    -13,
    23,
    95,
    -145,
    117,
    -145,
    -11,
    136,
    142,
    -11,
    -20,
    -145,
    101,
    -145,
    -11,
    -11,
    -11,
    -11,
    144,
    102,
    102,
    -7,
    123,
    103,
    66,
    104,
    119,
    12,
    160,
    112,
    128,
    116,
    109,
    -145,
    -145,
    156,
    -145,
    -145,
    -145,
    -27,
    -27,
    -145,
    -145,
    -11,
    -145,
    4,
    123,
    -145,
    112,
    158,
    154,
    -145,
    125,
    -8,
    -145,
    3,
    -145,
    -145,
    115,
    162,
    131,
    160,
    -145,
    -145,
    163,
    165,
    124,
    -145,
    -145,
    -145,
    137,
    176,
    195,
    181,
    66,
    183,
    -145,
    -145,
    11,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    170,
    56,
    63,
    -11,
    -11,
    103,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    55,
    104,
    185,
    140,
    -145,
    112,
    208,
    190,
    102,
    102,
    221,
    222,
    186,
    90,
    -145,
    210,
    -145,
    -145,
    -145,
    -145,
    -11,
    154,
    154,
    33,
    33,
    -145,
    166,
    197,
    -145,
    -145,
    -145,
    162,
    182,
    -145,
    -145,
    160,
    112,
    196,
    123,
    5,
    -145,
    -11,
    154,
    225,
    158,
    -145,
    66,
    66,
    33,
    -145,
    198,
    224,
    -145,
    -145,
    78,
    -145,
    228,
    154,
    195,
    -145,
    63,
    248,
    215,
    183,
    -145,
    108,
    100,
    160,
    -145,
    -145,
    -24,
    -145,
    -11,
    187,
    -145,
    -145,
    -145,
    -145,
    199,
    28,
    -145,
    231,
    -145,
    102,
    -145,
    -145,
    -11,
    -145,
    -145};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] = {0,
    37,
    0,
    87,
    87,
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
    87,
    75,
    72,
    73,
    107,
    74,
    0,
    98,
    96,
    85,
    102,
    100,
    101,
    97,
    86,
    33,
    32,
    0,
    0,
    0,
    0,
    0,
    147,
    1,
    149,
    2,
    76,
    0,
    0,
    31,
    0,
    48,
    87,
    0,
    0,
    87,
    0,
    95,
    0,
    103,
    0,
    0,
    0,
    0,
    88,
    0,
    0,
    0,
    114,
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
    106,
    94,
    0,
    108,
    99,
    104,
    90,
    91,
    92,
    93,
    87,
    109,
    102,
    114,
    34,
    0,
    0,
    0,
    78,
    0,
    114,
    80,
    0,
    148,
    69,
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
    105,
    89,
    0,
    110,
    141,
    0,
    0,
    63,
    132,
    130,
    0,
    120,
    121,
    122,
    123,
    124,
    125,
    128,
    126,
    0,
    115,
    0,
    0,
    0,
    79,
    70,
    71,
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
    143,
    0,
    0,
    67,
    0,
    133,
    131,
    129,
    127,
    0,
    0,
    0,
    117,
    82,
    81,
    0,
    0,
    55,
    54,
    52,
    49,
    76,
    77,
    39,
    0,
    0,
    0,
    114,
    102,
    111,
    87,
    0,
    134,
    0,
    65,
    0,
    0,
    116,
    118,
    119,
    0,
    53,
    50,
    43,
    47,
    0,
    0,
    141,
    142,
    144,
    0,
    145,
    64,
    68,
    0,
    56,
    0,
    42,
    35,
    112,
    84,
    0,
    0,
    83,
    66,
    51,
    41,
    0,
    138,
    135,
    136,
    146,
    0,
    140,
    139,
    0,
    113,
    137};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-145,
    -145,
    242,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -145,
    -113,
    -145,
    -145,
    -145,
    -145,
    53,
    86,
    19,
    -145,
    -145,
    42,
    41,
    -95,
    -97,
    59,
    -145,
    -145,
    -145,
    105,
    -46,
    -145,
    -4,
    -54,
    209,
    -145,
    -145,
    -145,
    -88,
    91,
    13,
    -116,
    -144,
    107,
    -145,
    8,
    -145,
    39,
    -145,
    -145,
    -145,
    -145,
    -145};

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
    140,
    31,
    32,
    33,
    34,
    178,
    134,
    206,
    176,
    35,
    150,
    189,
    190,
    57,
    102,
    36,
    37,
    128,
    129,
    38,
    39,
    58,
    59,
    146,
    60,
    61,
    62,
    213,
    121,
    214,
    126,
    163,
    164,
    238,
    256,
    257,
    187,
    219,
    250,
    40,
    41,
    74};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] = {63,
    86,
    132,
    82,
    131,
    147,
    120,
    122,
    87,
    87,
    148,
    100,
    167,
    49,
    87,
    64,
    136,
    123,
    166,
    42,
    192,
    84,
    46,
    67,
    47,
    197,
    198,
    103,
    50,
    81,
    65,
    66,
    68,
    260,
    254,
    114,
    115,
    116,
    117,
    124,
    125,
    85,
    193,
    101,
    43,
    83,
    261,
    104,
    91,
    92,
    69,
    111,
    132,
    225,
    226,
    112,
    137,
    138,
    51,
    52,
    53,
    54,
    145,
    55,
    56,
    151,
    44,
    72,
    210,
    48,
    70,
    162,
    168,
    169,
    236,
    88,
    88,
    107,
    194,
    202,
    110,
    88,
    243,
    89,
    90,
    91,
    92,
    152,
    73,
    246,
    180,
    75,
    203,
    153,
    204,
    81,
    205,
    215,
    234,
    232,
    76,
    89,
    90,
    91,
    92,
    50,
    89,
    90,
    91,
    92,
    199,
    200,
    197,
    198,
    144,
    221,
    222,
    154,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    132,
    132,
    240,
    77,
    89,
    90,
    91,
    92,
    251,
    222,
    51,
    52,
    203,
    54,
    204,
    130,
    205,
    224,
    162,
    162,
    170,
    81,
    171,
    172,
    173,
    174,
    175,
    78,
    49,
    79,
    80,
    94,
    95,
    96,
    97,
    99,
    108,
    98,
    151,
    162,
    231,
    105,
    109,
    50,
    106,
    118,
    125,
    113,
    119,
    127,
    133,
    135,
    81,
    49,
    162,
    141,
    143,
    149,
    139,
    244,
    152,
    165,
    142,
    177,
    181,
    182,
    153,
    179,
    50,
    255,
    183,
    184,
    253,
    51,
    52,
    53,
    54,
    185,
    55,
    56,
    186,
    188,
    195,
    255,
    191,
    208,
    209,
    211,
    235,
    212,
    154,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    51,
    52,
    53,
    54,
    217,
    55,
    56,
    1,
    2,
    220,
    218,
    223,
    227,
    228,
    237,
    101,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    197,
    233,
    242,
    11,
    12,
    13,
    245,
    248,
    249,
    258,
    262,
    259,
    71,
    229,
    252,
    239,
    207,
    241,
    14,
    15,
    230,
    93,
    196,
    264,
    201,
    263,
    247,
    16,
    0,
    216,
    0,
    17};

static const yytype_int16 yycheck[] = {4,
    55,
    99,
    49,
    99,
    121,
    94,
    95,
    4,
    4,
    123,
    24,
    128,
    24,
    4,
    71,
    4,
    24,
    26,
    13,
    9,
    24,
    13,
    45,
    15,
    49,
    50,
    4,
    39,
    17,
    14,
    15,
    47,
    5,
    58,
    89,
    90,
    91,
    92,
    46,
    48,
    44,
    31,
    56,
    38,
    49,
    18,
    24,
    75,
    76,
    71,
    71,
    149,
    197,
    198,
    75,
    102,
    103,
    69,
    70,
    71,
    72,
    58,
    74,
    75,
    9,
    60,
    0,
    181,
    60,
    71,
    125,
    69,
    70,
    218,
    71,
    71,
    81,
    67,
    24,
    84,
    71,
    4,
    73,
    74,
    75,
    76,
    31,
    3,
    233,
    136,
    71,
    37,
    37,
    39,
    17,
    41,
    185,
    214,
    212,
    71,
    73,
    74,
    75,
    76,
    39,
    73,
    74,
    75,
    76,
    164,
    165,
    49,
    50,
    118,
    25,
    26,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    222,
    223,
    222,
    15,
    73,
    74,
    75,
    76,
    25,
    26,
    69,
    70,
    37,
    72,
    39,
    74,
    41,
    196,
    197,
    198,
    30,
    17,
    32,
    33,
    34,
    35,
    36,
    71,
    24,
    71,
    71,
    47,
    47,
    71,
    71,
    61,
    25,
    51,
    9,
    218,
    211,
    71,
    25,
    39,
    52,
    26,
    48,
    71,
    71,
    71,
    71,
    57,
    17,
    24,
    233,
    52,
    25,
    24,
    71,
    230,
    31,
    61,
    71,
    26,
    26,
    25,
    37,
    61,
    39,
    248,
    71,
    59,
    243,
    69,
    70,
    71,
    72,
    26,
    74,
    75,
    10,
    25,
    37,
    262,
    26,
    25,
    71,
    4,
    217,
    24,
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
    6,
    74,
    75,
    7,
    8,
    46,
    11,
    24,
    69,
    39,
    12,
    56,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    49,
    52,
    25,
    27,
    28,
    29,
    25,
    6,
    40,
    69,
    26,
    59,
    17,
    207,
    242,
    220,
    177,
    223,
    42,
    43,
    208,
    59,
    162,
    262,
    166,
    259,
    234,
    51,
    -1,
    185,
    -1,
    55};

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
    27,
    28,
    29,
    42,
    43,
    51,
    55,
    79,
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
    94,
    95,
    96,
    97,
    102,
    108,
    109,
    112,
    113,
    132,
    133,
    13,
    38,
    60,
    92,
    13,
    15,
    60,
    24,
    39,
    69,
    70,
    71,
    72,
    74,
    75,
    106,
    114,
    115,
    117,
    118,
    119,
    114,
    71,
    14,
    15,
    45,
    47,
    71,
    71,
    80,
    0,
    3,
    134,
    71,
    71,
    15,
    71,
    71,
    71,
    17,
    112,
    114,
    24,
    44,
    115,
    4,
    71,
    73,
    74,
    75,
    76,
    116,
    47,
    47,
    71,
    71,
    51,
    61,
    24,
    56,
    107,
    4,
    24,
    71,
    52,
    114,
    25,
    25,
    114,
    71,
    75,
    71,
    115,
    115,
    115,
    115,
    26,
    71,
    120,
    121,
    120,
    24,
    46,
    48,
    123,
    71,
    110,
    111,
    74,
    105,
    106,
    71,
    99,
    57,
    4,
    112,
    112,
    71,
    93,
    52,
    71,
    25,
    114,
    58,
    116,
    123,
    93,
    24,
    103,
    9,
    31,
    37,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    115,
    124,
    125,
    61,
    26,
    123,
    69,
    70,
    30,
    32,
    33,
    34,
    35,
    36,
    101,
    26,
    98,
    61,
    112,
    26,
    25,
    71,
    59,
    26,
    10,
    129,
    25,
    104,
    105,
    26,
    9,
    31,
    67,
    37,
    125,
    49,
    50,
    115,
    115,
    111,
    24,
    37,
    39,
    41,
    100,
    99,
    25,
    71,
    93,
    4,
    24,
    120,
    122,
    120,
    121,
    6,
    11,
    130,
    46,
    25,
    26,
    24,
    115,
    124,
    124,
    69,
    39,
    98,
    107,
    112,
    93,
    52,
    123,
    114,
    124,
    12,
    126,
    103,
    105,
    104,
    25,
    4,
    112,
    25,
    124,
    129,
    6,
    40,
    131,
    25,
    100,
    112,
    58,
    115,
    127,
    128,
    69,
    59,
    5,
    18,
    26,
    122,
    127};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] = {0,
    78,
    79,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
    80,
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
    92,
    93,
    93,
    94,
    95,
    95,
    95,
    95,
    95,
    96,
    96,
    97,
    98,
    98,
    99,
    99,
    100,
    100,
    100,
    100,
    101,
    101,
    101,
    101,
    101,
    101,
    102,
    102,
    103,
    103,
    104,
    104,
    105,
    105,
    105,
    106,
    106,
    106,
    106,
    107,
    107,
    108,
    109,
    110,
    110,
    111,
    112,
    112,
    113,
    113,
    114,
    114,
    114,
    115,
    115,
    115,
    115,
    115,
    115,
    115,
    115,
    115,
    115,
    115,
    115,
    116,
    116,
    116,
    117,
    118,
    119,
    119,
    120,
    121,
    121,
    122,
    122,
    123,
    123,
    124,
    124,
    124,
    124,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    125,
    126,
    126,
    127,
    127,
    128,
    128,
    128,
    129,
    129,
    130,
    130,
    131,
    131,
    132,
    133,
    134};

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
#line 267 "yacc_sql.y"
    {
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
#line 1879 "yacc_sql.cpp"
    break;

    case 25: /* exit_stmt: EXIT  */
#line 300 "yacc_sql.y"
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1888 "yacc_sql.cpp"
    break;

    case 26: /* help_stmt: HELP  */
#line 306 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1896 "yacc_sql.cpp"
    break;

    case 27: /* sync_stmt: SYNC  */
#line 311 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1904 "yacc_sql.cpp"
    break;

    case 28: /* begin_stmt: TRX_BEGIN  */
#line 317 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1912 "yacc_sql.cpp"
    break;

    case 29: /* commit_stmt: TRX_COMMIT  */
#line 323 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1920 "yacc_sql.cpp"
    break;

    case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 329 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1928 "yacc_sql.cpp"
    break;

    case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 335 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1938 "yacc_sql.cpp"
    break;

    case 32: /* show_tables_stmt: SHOW TABLES  */
#line 342 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1946 "yacc_sql.cpp"
    break;

    case 33: /* desc_table_stmt: DESC ID  */
#line 348 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1956 "yacc_sql.cpp"
    break;

    case 34: /* show_index_stmt: SHOW INDEX FROM relation  */
#line 357 "yacc_sql.y"
    {
      (yyval.sql_node)             = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = (yyval.sql_node)->show_index;
      show_index.relation_name     = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1967 "yacc_sql.cpp"
    break;

    case 35: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE attr_list RBRACE  */
#line 367 "yacc_sql.y"
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
#line 1983 "yacc_sql.cpp"
    break;

    case 36: /* opt_unique: UNIQUE  */
#line 381 "yacc_sql.y"
    {
      (yyval.unique) = true;
    }
#line 1989 "yacc_sql.cpp"
    break;

    case 37: /* opt_unique: %empty  */
#line 382 "yacc_sql.y"
    {
      (yyval.unique) = false;
    }
#line 1995 "yacc_sql.cpp"
    break;

    case 38: /* attr_list: ID  */
#line 387 "yacc_sql.y"
    {
      (yyval.index_attr_list) = new std::vector<std::string>;    // 创建一个新的 vector
      (yyval.index_attr_list)->emplace_back((yyvsp[0].string));  // 将列名加入 vector
      free((yyvsp[0].string));
    }
#line 2005 "yacc_sql.cpp"
    break;

    case 39: /* attr_list: ID COMMA attr_list  */
#line 393 "yacc_sql.y"
    {
      (yyval.index_attr_list) = (yyvsp[0].index_attr_list);  // 使用现有的 vector
      (yyval.index_attr_list)
          ->emplace((yyval.index_attr_list)->begin(), (yyvsp[-2].string));  // 将新列名加入 vector 开头
      free((yyvsp[-2].string));
    }
#line 2015 "yacc_sql.cpp"
    break;

    case 40: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 402 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name    = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2027 "yacc_sql.cpp"
    break;

    case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt */
#line 412 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-7].string), (yyvsp[-5].attr_info), (yyvsp[-4].attr_infos), (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2035 "yacc_sql.cpp"
    break;

    case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 416 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-6].string), (yyvsp[-4].attr_info), (yyvsp[-3].attr_infos), (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2043 "yacc_sql.cpp"
    break;

    case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 420 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-5].string), (yyvsp[-3].attr_info), (yyvsp[-2].attr_infos), (yyvsp[0].string), nullptr);
    }
#line 2051 "yacc_sql.cpp"
    break;

    case 44: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 424 "yacc_sql.y"
    {
      (yyval.sql_node) =
          create_table_sql_node((yyvsp[-3].string), nullptr, nullptr, (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2059 "yacc_sql.cpp"
    break;

    case 45: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 428 "yacc_sql.y"
    {
      (yyval.sql_node) =
          create_table_sql_node((yyvsp[-2].string), nullptr, nullptr, (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2067 "yacc_sql.cpp"
    break;

    case 46: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 435 "yacc_sql.y"
    {
      (yyval.sql_node)               = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name      = (yyvsp[-2].string);
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-2].string));
    }
#line 2079 "yacc_sql.cpp"
    break;

    case 47: /* create_view_stmt: CREATE VIEW ID LBRACE attr_list RBRACE AS select_stmt  */
#line 443 "yacc_sql.y"
    {
      (yyval.sql_node)               = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name      = (yyvsp[-5].string);
      create_view.attribute_names    = std::move(*(yyvsp[-3].index_attr_list));
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-5].string));
    }
#line 2092 "yacc_sql.cpp"
    break;

    case 48: /* drop_view_stmt: DROP VIEW ID  */
#line 455 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2102 "yacc_sql.cpp"
    break;

    case 49: /* attr_def_list: %empty  */
#line 464 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2110 "yacc_sql.cpp"
    break;

    case 50: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 468 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2124 "yacc_sql.cpp"
    break;

    case 51: /* attr_def: ID type LBRACE NUMBER RBRACE nullable_constraint  */
#line 481 "yacc_sql.y"
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
#line 2146 "yacc_sql.cpp"
    break;

    case 52: /* attr_def: ID type nullable_constraint  */
#line 499 "yacc_sql.y"
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
#line 2176 "yacc_sql.cpp"
    break;

    case 53: /* nullable_constraint: NOT NULL_T  */
#line 528 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // NOT NULL 对应的可空性为 false
    }
#line 2184 "yacc_sql.cpp"
    break;

    case 54: /* nullable_constraint: NULLABLE  */
#line 532 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULLABLE 对应的可空性为 true 2022
    }
#line 2192 "yacc_sql.cpp"
    break;

    case 55: /* nullable_constraint: NULL_T  */
#line 536 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULL 对应的可空性也为 true 2023
    }
#line 2200 "yacc_sql.cpp"
    break;

    case 56: /* nullable_constraint: %empty  */
#line 540 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // 默认情况为 NULL
    }
#line 2208 "yacc_sql.cpp"
    break;

    case 57: /* type: INT_T  */
#line 546 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::INTS);
    }
#line 2214 "yacc_sql.cpp"
    break;

    case 58: /* type: STRING_T  */
#line 547 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::CHARS);
    }
#line 2220 "yacc_sql.cpp"
    break;

    case 59: /* type: FLOAT_T  */
#line 548 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::FLOATS);
    }
#line 2226 "yacc_sql.cpp"
    break;

    case 60: /* type: DATE_T  */
#line 549 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::DATES);
    }
#line 2232 "yacc_sql.cpp"
    break;

    case 61: /* type: TEXT_T  */
#line 550 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::TEXTS);
    }
#line 2238 "yacc_sql.cpp"
    break;

    case 62: /* type: VECTOR_T  */
#line 551 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::VECTORS);
    }
#line 2244 "yacc_sql.cpp"
    break;

    case 63: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 556 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-2].string));
    }
#line 2258 "yacc_sql.cpp"
    break;

    case 64: /* insert_stmt: INSERT INTO ID LBRACE attr_list RBRACE VALUES values_list  */
#line 566 "yacc_sql.y"
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
#line 2273 "yacc_sql.cpp"
    break;

    case 65: /* values_list: LBRACE value_list RBRACE  */
#line 580 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2283 "yacc_sql.cpp"
    break;

    case 66: /* values_list: values_list COMMA LBRACE value_list RBRACE  */
#line 586 "yacc_sql.y"
    {
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2292 "yacc_sql.cpp"
    break;

    case 67: /* value_list: value  */
#line 593 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2302 "yacc_sql.cpp"
    break;

    case 68: /* value_list: value_list COMMA value  */
#line 599 "yacc_sql.y"
    {
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2311 "yacc_sql.cpp"
    break;

    case 69: /* value: nonnegative_value  */
#line 606 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2319 "yacc_sql.cpp"
    break;

    case 70: /* value: '-' NUMBER  */
#line 609 "yacc_sql.y"
    {
      (yyval.value) = new Value(-(yyvsp[0].number));
      (yyloc)       = (yylsp[-1]);
    }
#line 2328 "yacc_sql.cpp"
    break;

    case 71: /* value: '-' FLOAT  */
#line 613 "yacc_sql.y"
    {
      (yyval.value) = new Value(-(yyvsp[0].floats));
      (yyloc)       = (yylsp[-1]);
    }
#line 2337 "yacc_sql.cpp"
    break;

    case 72: /* nonnegative_value: NUMBER  */
#line 620 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[0].number));
      (yyloc)       = (yylsp[0]);
    }
#line 2346 "yacc_sql.cpp"
    break;

    case 73: /* nonnegative_value: FLOAT  */
#line 624 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[0].floats));
      (yyloc)       = (yylsp[0]);
    }
#line 2355 "yacc_sql.cpp"
    break;

    case 74: /* nonnegative_value: SSS  */
#line 628 "yacc_sql.y"
    {
      char *tmp     = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2366 "yacc_sql.cpp"
    break;

    case 75: /* nonnegative_value: NULL_T  */
#line 634 "yacc_sql.y"
    {
      (yyval.value) = new Value(NullValue());
    }
#line 2374 "yacc_sql.cpp"
    break;

    case 76: /* storage_format: %empty  */
#line 641 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2382 "yacc_sql.cpp"
    break;

    case 77: /* storage_format: STORAGE FORMAT EQ ID  */
#line 645 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2390 "yacc_sql.cpp"
    break;

    case 78: /* delete_stmt: DELETE FROM ID where  */
#line 652 "yacc_sql.y"
    {
      (yyval.sql_node)                         = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.condition = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-1].string));
    }
#line 2403 "yacc_sql.cpp"
    break;

    case 79: /* update_stmt: UPDATE ID SET set_clauses where  */
#line 664 "yacc_sql.y"
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
#line 2418 "yacc_sql.cpp"
    break;

    case 80: /* set_clauses: setClause  */
#line 678 "yacc_sql.y"
    {
      (yyval.set_clauses) = new std::vector<SetClauseSqlNode>;
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2427 "yacc_sql.cpp"
    break;

    case 81: /* set_clauses: set_clauses COMMA setClause  */
#line 683 "yacc_sql.y"
    {
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2435 "yacc_sql.cpp"
    break;

    case 82: /* setClause: ID EQ expression  */
#line 690 "yacc_sql.y"
    {
      (yyval.set_clause)             = new SetClauseSqlNode;
      (yyval.set_clause)->field_name = (yyvsp[-2].string);
      (yyval.set_clause)->value      = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2446 "yacc_sql.cpp"
    break;

    case 83: /* select_stmt: SELECT expression_list FROM rel_list where group_by opt_having opt_order_by opt_limit  */
#line 700 "yacc_sql.y"
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
#line 2488 "yacc_sql.cpp"
    break;

    case 84: /* select_stmt: SELECT expression_list FROM relation INNER JOIN join_clauses where group_by  */
#line 738 "yacc_sql.y"
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
#line 2522 "yacc_sql.cpp"
    break;

    case 85: /* calc_stmt: CALC expression_list  */
#line 771 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2532 "yacc_sql.cpp"
    break;

    case 86: /* calc_stmt: SELECT expression_list  */
#line 777 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2542 "yacc_sql.cpp"
    break;

    case 87: /* expression_list: %empty  */
#line 785 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
    }
#line 2550 "yacc_sql.cpp"
    break;

    case 88: /* expression_list: expression alias  */
#line 789 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2563 "yacc_sql.cpp"
    break;

    case 89: /* expression_list: expression alias COMMA expression_list  */
#line 798 "yacc_sql.y"
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
#line 2580 "yacc_sql.cpp"
    break;

    case 90: /* expression: expression '+' expression  */
#line 813 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2588 "yacc_sql.cpp"
    break;

    case 91: /* expression: expression '-' expression  */
#line 816 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2596 "yacc_sql.cpp"
    break;

    case 92: /* expression: expression '*' expression  */
#line 819 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2604 "yacc_sql.cpp"
    break;

    case 93: /* expression: expression '/' expression  */
#line 822 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2612 "yacc_sql.cpp"
    break;

    case 94: /* expression: LBRACE expression_list RBRACE  */
#line 825 "yacc_sql.y"
    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().get();
      } else {
        (yyval.expression) = new ListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2625 "yacc_sql.cpp"
    break;

    case 95: /* expression: '-' expression  */
#line 833 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2633 "yacc_sql.cpp"
    break;

    case 96: /* expression: nonnegative_value  */
#line 836 "yacc_sql.y"
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2643 "yacc_sql.cpp"
    break;

    case 97: /* expression: rel_attr  */
#line 841 "yacc_sql.y"
    {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression)   = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2654 "yacc_sql.cpp"
    break;

    case 98: /* expression: '*'  */
#line 847 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr();
    }
#line 2662 "yacc_sql.cpp"
    break;

    case 99: /* expression: ID DOT '*'  */
#line 850 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2670 "yacc_sql.cpp"
    break;

    case 100: /* expression: aggr_func_expr  */
#line 853 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // AggrFuncExpr
    }
#line 2678 "yacc_sql.cpp"
    break;

    case 101: /* expression: sub_query_expr  */
#line 856 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // SubQueryExpr
    }
#line 2686 "yacc_sql.cpp"
    break;

    case 102: /* alias: %empty  */
#line 863 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2694 "yacc_sql.cpp"
    break;

    case 103: /* alias: ID  */
#line 866 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2702 "yacc_sql.cpp"
    break;

    case 104: /* alias: AS ID  */
#line 869 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2710 "yacc_sql.cpp"
    break;

    case 105: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 875 "yacc_sql.y"
    {
      (yyval.expression) = new UnboundFunctionExpr((yyvsp[-3].string), std::move(*(yyvsp[-1].expression_list)));
    }
#line 2718 "yacc_sql.cpp"
    break;

    case 106: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 882 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2726 "yacc_sql.cpp"
    break;

    case 107: /* rel_attr: ID  */
#line 888 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2736 "yacc_sql.cpp"
    break;

    case 108: /* rel_attr: ID DOT ID  */
#line 893 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2748 "yacc_sql.cpp"
    break;

    case 109: /* relation: ID  */
#line 903 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2756 "yacc_sql.cpp"
    break;

    case 110: /* rel_list: relation alias  */
#line 909 "yacc_sql.y"
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
#line 2771 "yacc_sql.cpp"
    break;

    case 111: /* rel_list: relation alias COMMA rel_list  */
#line 919 "yacc_sql.y"
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
#line 2790 "yacc_sql.cpp"
    break;

    case 112: /* join_clauses: relation ON condition  */
#line 937 "yacc_sql.y"
    {
      (yyval.join_clauses) = new JoinSqlNode;
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-2].string));
      (yyval.join_clauses)->conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2801 "yacc_sql.cpp"
    break;

    case 113: /* join_clauses: relation ON condition INNER JOIN join_clauses  */
#line 944 "yacc_sql.y"
    {
      (yyval.join_clauses) = (yyvsp[0].join_clauses);
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-5].string));
      auto ptr = (yyval.join_clauses)->conditions.release();
      (yyval.join_clauses)->conditions =
          std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-3].expression));
      free((yyvsp[-5].string));
    }
#line 2813 "yacc_sql.cpp"
    break;

    case 114: /* where: %empty  */
#line 955 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2821 "yacc_sql.cpp"
    break;

    case 115: /* where: WHERE condition  */
#line 958 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2829 "yacc_sql.cpp"
    break;

    case 116: /* condition: expression comp_op expression  */
#line 965 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2837 "yacc_sql.cpp"
    break;

    case 117: /* condition: comp_op expression  */
#line 969 "yacc_sql.y"
    {
      Value val;
      val.set_null(true);
      ValueExpr *temp_expr = new ValueExpr(val);
      (yyval.expression)   = new ComparisonExpr((yyvsp[-1].comp), temp_expr, (yyvsp[0].expression));
    }
#line 2848 "yacc_sql.cpp"
    break;

    case 118: /* condition: condition AND condition  */
#line 976 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2856 "yacc_sql.cpp"
    break;

    case 119: /* condition: condition OR condition  */
#line 980 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2864 "yacc_sql.cpp"
    break;

    case 120: /* comp_op: EQ  */
#line 986 "yacc_sql.y"
    {
      (yyval.comp) = EQUAL_TO;
    }
#line 2870 "yacc_sql.cpp"
    break;

    case 121: /* comp_op: LT  */
#line 987 "yacc_sql.y"
    {
      (yyval.comp) = LESS_THAN;
    }
#line 2876 "yacc_sql.cpp"
    break;

    case 122: /* comp_op: GT  */
#line 988 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_THAN;
    }
#line 2882 "yacc_sql.cpp"
    break;

    case 123: /* comp_op: LE  */
#line 989 "yacc_sql.y"
    {
      (yyval.comp) = LESS_EQUAL;
    }
#line 2888 "yacc_sql.cpp"
    break;

    case 124: /* comp_op: GE  */
#line 990 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_EQUAL;
    }
#line 2894 "yacc_sql.cpp"
    break;

    case 125: /* comp_op: NE  */
#line 991 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EQUAL;
    }
#line 2900 "yacc_sql.cpp"
    break;

    case 126: /* comp_op: IS  */
#line 992 "yacc_sql.y"
    {
      (yyval.comp) = IS_OP;
    }
#line 2906 "yacc_sql.cpp"
    break;

    case 127: /* comp_op: IS NOT  */
#line 993 "yacc_sql.y"
    {
      (yyval.comp) = IS_NOT_OP;
    }
#line 2912 "yacc_sql.cpp"
    break;

    case 128: /* comp_op: LIKE  */
#line 994 "yacc_sql.y"
    {
      (yyval.comp) = LIKE_OP;
    }
#line 2918 "yacc_sql.cpp"
    break;

    case 129: /* comp_op: NOT LIKE  */
#line 995 "yacc_sql.y"
    {
      (yyval.comp) = NOT_LIKE_OP;
    }
#line 2924 "yacc_sql.cpp"
    break;

    case 130: /* comp_op: IN  */
#line 996 "yacc_sql.y"
    {
      (yyval.comp) = IN_OP;
    }
#line 2930 "yacc_sql.cpp"
    break;

    case 131: /* comp_op: NOT IN  */
#line 997 "yacc_sql.y"
    {
      (yyval.comp) = NOT_IN_OP;
    }
#line 2936 "yacc_sql.cpp"
    break;

    case 132: /* comp_op: EXISTS  */
#line 998 "yacc_sql.y"
    {
      (yyval.comp) = EXISTS_OP;
    }
#line 2942 "yacc_sql.cpp"
    break;

    case 133: /* comp_op: NOT EXISTS  */
#line 999 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EXISTS_OP;
    }
#line 2948 "yacc_sql.cpp"
    break;

    case 134: /* opt_order_by: %empty  */
#line 1004 "yacc_sql.y"
    {
      (yyval.orderby_list) = nullptr;
    }
#line 2956 "yacc_sql.cpp"
    break;

    case 135: /* opt_order_by: ORDER BY sort_list  */
#line 1008 "yacc_sql.y"
    {
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
      std::reverse((yyval.orderby_list)->begin(), (yyval.orderby_list)->end());
    }
#line 2965 "yacc_sql.cpp"
    break;

    case 136: /* sort_list: sort_unit  */
#line 1016 "yacc_sql.y"
    {
      (yyval.orderby_list) = new std::vector<OrderBySqlNode>;
      (yyval.orderby_list)->emplace_back(std::move(*(yyvsp[0].orderby_unit)));
    }
#line 2974 "yacc_sql.cpp"
    break;

    case 137: /* sort_list: sort_unit COMMA sort_list  */
#line 1021 "yacc_sql.y"
    {
      (yyvsp[0].orderby_list)->emplace_back(std::move(*(yyvsp[-2].orderby_unit)));
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
    }
#line 2983 "yacc_sql.cpp"
    break;

    case 138: /* sort_unit: expression  */
#line 1029 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2993 "yacc_sql.cpp"
    break;

    case 139: /* sort_unit: expression DESC  */
#line 1035 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = false;
    }
#line 3003 "yacc_sql.cpp"
    break;

    case 140: /* sort_unit: expression ASC  */
#line 1041 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();  // 默认是升序
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 3013 "yacc_sql.cpp"
    break;

    case 141: /* group_by: %empty  */
#line 1050 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3021 "yacc_sql.cpp"
    break;

    case 142: /* group_by: GROUP BY expression_list  */
#line 1054 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3029 "yacc_sql.cpp"
    break;

    case 143: /* opt_having: %empty  */
#line 1061 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3037 "yacc_sql.cpp"
    break;

    case 144: /* opt_having: HAVING condition  */
#line 1065 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3045 "yacc_sql.cpp"
    break;

    case 145: /* opt_limit: %empty  */
#line 1072 "yacc_sql.y"
    {
      (yyval.limited_info) = nullptr;
    }
#line 3053 "yacc_sql.cpp"
    break;

    case 146: /* opt_limit: LIMIT NUMBER  */
#line 1076 "yacc_sql.y"
    {
      (yyval.limited_info)         = new LimitSqlNode();
      (yyval.limited_info)->number = (yyvsp[0].number);
    }
#line 3062 "yacc_sql.cpp"
    break;

    case 147: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1097 "yacc_sql.y"
    {
      (yyval.sql_node)                   = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3071 "yacc_sql.cpp"
    break;

    case 148: /* set_variable_stmt: SET ID EQ value  */
#line 1105 "yacc_sql.y"
    {
      (yyval.sql_node)                     = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3083 "yacc_sql.cpp"
    break;

#line 3087 "yacc_sql.cpp"

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

#line 1117 "yacc_sql.y"

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
