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
  YYSYMBOL_NOT                 = 36,  /* NOT  */
  YYSYMBOL_UNIQUE              = 37,  /* UNIQUE  */
  YYSYMBOL_NULL_T              = 38,  /* NULL_T  */
  YYSYMBOL_NULLABLE            = 39,  /* NULLABLE  */
  YYSYMBOL_HELP                = 40,  /* HELP  */
  YYSYMBOL_EXIT                = 41,  /* EXIT  */
  YYSYMBOL_DOT                 = 42,  /* DOT  */
  YYSYMBOL_INTO                = 43,  /* INTO  */
  YYSYMBOL_VALUES              = 44,  /* VALUES  */
  YYSYMBOL_FROM                = 45,  /* FROM  */
  YYSYMBOL_WHERE               = 46,  /* WHERE  */
  YYSYMBOL_AND                 = 47,  /* AND  */
  YYSYMBOL_OR                  = 48,  /* OR  */
  YYSYMBOL_SET                 = 49,  /* SET  */
  YYSYMBOL_ON                  = 50,  /* ON  */
  YYSYMBOL_LOAD                = 51,  /* LOAD  */
  YYSYMBOL_DATA                = 52,  /* DATA  */
  YYSYMBOL_INFILE              = 53,  /* INFILE  */
  YYSYMBOL_EXPLAIN             = 54,  /* EXPLAIN  */
  YYSYMBOL_STORAGE             = 55,  /* STORAGE  */
  YYSYMBOL_FORMAT              = 56,  /* FORMAT  */
  YYSYMBOL_INNER               = 57,  /* INNER  */
  YYSYMBOL_JOIN                = 58,  /* JOIN  */
  YYSYMBOL_VIEW                = 59,  /* VIEW  */
  YYSYMBOL_EQ                  = 60,  /* EQ  */
  YYSYMBOL_LT                  = 61,  /* LT  */
  YYSYMBOL_GT                  = 62,  /* GT  */
  YYSYMBOL_LE                  = 63,  /* LE  */
  YYSYMBOL_GE                  = 64,  /* GE  */
  YYSYMBOL_NE                  = 65,  /* NE  */
  YYSYMBOL_LIKE                = 66,  /* LIKE  */
  YYSYMBOL_IS                  = 67,  /* IS  */
  YYSYMBOL_NUMBER              = 68,  /* NUMBER  */
  YYSYMBOL_FLOAT               = 69,  /* FLOAT  */
  YYSYMBOL_ID                  = 70,  /* ID  */
  YYSYMBOL_SSS                 = 71,  /* SSS  */
  YYSYMBOL_72_                 = 72,  /* '+'  */
  YYSYMBOL_73_                 = 73,  /* '-'  */
  YYSYMBOL_74_                 = 74,  /* '*'  */
  YYSYMBOL_75_                 = 75,  /* '/'  */
  YYSYMBOL_UMINUS              = 76,  /* UMINUS  */
  YYSYMBOL_YYACCEPT            = 77,  /* $accept  */
  YYSYMBOL_commands            = 78,  /* commands  */
  YYSYMBOL_command_wrapper     = 79,  /* command_wrapper  */
  YYSYMBOL_exit_stmt           = 80,  /* exit_stmt  */
  YYSYMBOL_help_stmt           = 81,  /* help_stmt  */
  YYSYMBOL_sync_stmt           = 82,  /* sync_stmt  */
  YYSYMBOL_begin_stmt          = 83,  /* begin_stmt  */
  YYSYMBOL_commit_stmt         = 84,  /* commit_stmt  */
  YYSYMBOL_rollback_stmt       = 85,  /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt     = 86,  /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt    = 87,  /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt     = 88,  /* desc_table_stmt  */
  YYSYMBOL_show_index_stmt     = 89,  /* show_index_stmt  */
  YYSYMBOL_create_index_stmt   = 90,  /* create_index_stmt  */
  YYSYMBOL_opt_unique          = 91,  /* opt_unique  */
  YYSYMBOL_attr_list           = 92,  /* attr_list  */
  YYSYMBOL_drop_index_stmt     = 93,  /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt   = 94,  /* create_table_stmt  */
  YYSYMBOL_create_view_stmt    = 95,  /* create_view_stmt  */
  YYSYMBOL_drop_view_stmt      = 96,  /* drop_view_stmt  */
  YYSYMBOL_attr_def_list       = 97,  /* attr_def_list  */
  YYSYMBOL_attr_def            = 98,  /* attr_def  */
  YYSYMBOL_nullable_constraint = 99,  /* nullable_constraint  */
  YYSYMBOL_type                = 100, /* type  */
  YYSYMBOL_insert_stmt         = 101, /* insert_stmt  */
  YYSYMBOL_values_list         = 102, /* values_list  */
  YYSYMBOL_value_list          = 103, /* value_list  */
  YYSYMBOL_value               = 104, /* value  */
  YYSYMBOL_nonnegative_value   = 105, /* nonnegative_value  */
  YYSYMBOL_storage_format      = 106, /* storage_format  */
  YYSYMBOL_delete_stmt         = 107, /* delete_stmt  */
  YYSYMBOL_update_stmt         = 108, /* update_stmt  */
  YYSYMBOL_setClauses          = 109, /* setClauses  */
  YYSYMBOL_setClause           = 110, /* setClause  */
  YYSYMBOL_select_stmt         = 111, /* select_stmt  */
  YYSYMBOL_calc_stmt           = 112, /* calc_stmt  */
  YYSYMBOL_expression_list     = 113, /* expression_list  */
  YYSYMBOL_expression          = 114, /* expression  */
  YYSYMBOL_alias               = 115, /* alias  */
  YYSYMBOL_aggr_func_expr      = 116, /* aggr_func_expr  */
  YYSYMBOL_sub_query_expr      = 117, /* sub_query_expr  */
  YYSYMBOL_rel_attr            = 118, /* rel_attr  */
  YYSYMBOL_relation            = 119, /* relation  */
  YYSYMBOL_rel_list            = 120, /* rel_list  */
  YYSYMBOL_joinClauses         = 121, /* joinClauses  */
  YYSYMBOL_where               = 122, /* where  */
  YYSYMBOL_condition           = 123, /* condition  */
  YYSYMBOL_comp_op             = 124, /* comp_op  */
  YYSYMBOL_opt_order_by        = 125, /* opt_order_by  */
  YYSYMBOL_sort_list           = 126, /* sort_list  */
  YYSYMBOL_sort_unit           = 127, /* sort_unit  */
  YYSYMBOL_group_by            = 128, /* group_by  */
  YYSYMBOL_opt_having          = 129, /* opt_having  */
  YYSYMBOL_load_data_stmt      = 130, /* load_data_stmt  */
  YYSYMBOL_explain_stmt        = 131, /* explain_stmt  */
  YYSYMBOL_set_variable_stmt   = 132, /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon       = 133  /* opt_semicolon  */
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
#define YYFINAL 75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 276

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 57
/* YYNRULES -- Number of rules.  */
#define YYNRULES 147
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 259

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 327

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
    74,
    72,
    2,
    73,
    2,
    75,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
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
    76};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] = {0,
    262,
    262,
    270,
    271,
    272,
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
    296,
    302,
    307,
    313,
    319,
    325,
    331,
    338,
    344,
    352,
    362,
    377,
    378,
    382,
    388,
    397,
    407,
    411,
    415,
    419,
    423,
    430,
    441,
    451,
    454,
    467,
    479,
    506,
    510,
    514,
    519,
    525,
    526,
    527,
    528,
    529,
    533,
    546,
    552,
    559,
    565,
    573,
    576,
    580,
    587,
    591,
    595,
    601,
    608,
    611,
    618,
    630,
    644,
    649,
    656,
    666,
    699,
    732,
    738,
    747,
    750,
    759,
    775,
    778,
    781,
    784,
    787,
    795,
    798,
    803,
    809,
    812,
    815,
    818,
    825,
    828,
    831,
    836,
    843,
    850,
    855,
    865,
    871,
    881,
    898,
    905,
    917,
    920,
    926,
    930,
    937,
    941,
    948,
    949,
    950,
    951,
    952,
    953,
    954,
    955,
    956,
    957,
    958,
    959,
    960,
    961,
    966,
    969,
    977,
    982,
    990,
    996,
    1002,
    1012,
    1015,
    1023,
    1026,
    1033,
    1046,
    1054,
    1064,
    1065};
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
    "NOT",
    "UNIQUE",
    "NULL_T",
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
    "DATA",
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
    "setClauses",
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
    "joinClauses",
    "where",
    "condition",
    "comp_op",
    "opt_order_by",
    "sort_list",
    "sort_unit",
    "group_by",
    "opt_having",
    "load_data_stmt",
    "explain_stmt",
    "set_variable_stmt",
    "opt_semicolon",
    YY_NULLPTR};

static const char *yysymbol_name(yysymbol_kind_t yysymbol) { return yytname[yysymbol]; }
#endif

#define YYPACT_NINF (-175)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {222,
    47,
    28,
    27,
    27,
    -52,
    38,
    -175,
    -20,
    -19,
    -41,
    -175,
    -175,
    -175,
    -175,
    -175,
    -35,
    2,
    222,
    56,
    85,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    23,
    -175,
    37,
    44,
    40,
    45,
    79,
    -7,
    -175,
    -175,
    -175,
    6,
    -175,
    27,
    -175,
    -175,
    -175,
    0,
    -175,
    -175,
    -175,
    54,
    -175,
    -175,
    78,
    89,
    90,
    113,
    101,
    111,
    -175,
    -175,
    -175,
    -175,
    -13,
    161,
    96,
    -175,
    117,
    -175,
    27,
    143,
    144,
    27,
    -25,
    -175,
    100,
    -175,
    27,
    27,
    27,
    27,
    145,
    102,
    102,
    130,
    129,
    106,
    53,
    108,
    114,
    124,
    15,
    164,
    132,
    116,
    54,
    -175,
    -175,
    158,
    -175,
    -175,
    -175,
    30,
    30,
    -175,
    -175,
    27,
    -175,
    11,
    129,
    -175,
    163,
    154,
    -175,
    133,
    -2,
    -175,
    17,
    -175,
    -175,
    148,
    95,
    168,
    135,
    164,
    -175,
    -175,
    126,
    -175,
    -175,
    -175,
    139,
    172,
    189,
    53,
    175,
    -175,
    -175,
    3,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    166,
    80,
    66,
    27,
    27,
    106,
    -175,
    -175,
    -175,
    190,
    -175,
    -175,
    -175,
    -175,
    -175,
    -11,
    114,
    179,
    136,
    -175,
    181,
    102,
    102,
    201,
    197,
    110,
    -175,
    186,
    -175,
    -175,
    -175,
    -175,
    27,
    154,
    154,
    59,
    59,
    -175,
    141,
    165,
    174,
    -175,
    -175,
    -175,
    168,
    171,
    -175,
    162,
    184,
    129,
    12,
    -175,
    27,
    154,
    219,
    -175,
    53,
    53,
    59,
    -175,
    188,
    -175,
    211,
    -175,
    -175,
    29,
    187,
    212,
    154,
    189,
    -175,
    66,
    240,
    -175,
    -175,
    131,
    112,
    164,
    -175,
    162,
    -175,
    55,
    -175,
    27,
    -175,
    -175,
    -175,
    -175,
    194,
    4,
    -175,
    221,
    102,
    -175,
    -175,
    27,
    -175,
    -175};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] = {0,
    38,
    0,
    85,
    85,
    0,
    0,
    28,
    0,
    0,
    0,
    29,
    30,
    31,
    27,
    26,
    0,
    0,
    0,
    0,
    146,
    25,
    24,
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
    4,
    3,
    21,
    22,
    23,
    0,
    37,
    0,
    0,
    0,
    0,
    0,
    85,
    73,
    70,
    71,
    105,
    72,
    0,
    96,
    94,
    83,
    100,
    98,
    99,
    95,
    84,
    34,
    33,
    0,
    0,
    0,
    0,
    0,
    0,
    144,
    1,
    147,
    2,
    74,
    0,
    0,
    32,
    0,
    48,
    85,
    0,
    0,
    85,
    0,
    93,
    0,
    101,
    0,
    0,
    0,
    0,
    86,
    0,
    0,
    0,
    112,
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
    104,
    92,
    0,
    106,
    97,
    102,
    88,
    89,
    90,
    91,
    85,
    107,
    100,
    112,
    35,
    0,
    0,
    76,
    0,
    112,
    78,
    0,
    145,
    67,
    0,
    0,
    49,
    0,
    0,
    46,
    47,
    0,
    41,
    103,
    87,
    0,
    108,
    139,
    0,
    62,
    130,
    128,
    0,
    118,
    119,
    120,
    121,
    122,
    123,
    126,
    124,
    0,
    113,
    0,
    0,
    0,
    77,
    68,
    69,
    0,
    57,
    58,
    59,
    60,
    61,
    56,
    0,
    0,
    0,
    45,
    0,
    0,
    0,
    0,
    141,
    0,
    65,
    0,
    131,
    129,
    127,
    125,
    0,
    0,
    0,
    115,
    80,
    79,
    0,
    0,
    0,
    55,
    54,
    52,
    49,
    74,
    75,
    0,
    0,
    112,
    100,
    109,
    85,
    0,
    132,
    63,
    0,
    0,
    114,
    116,
    117,
    143,
    0,
    53,
    50,
    44,
    39,
    0,
    0,
    139,
    140,
    142,
    0,
    81,
    66,
    0,
    56,
    0,
    43,
    0,
    36,
    110,
    82,
    0,
    64,
    51,
    42,
    40,
    0,
    136,
    133,
    134,
    0,
    138,
    137,
    0,
    111,
    135};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-175,
    -175,
    230,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    -175,
    13,
    -175,
    -175,
    -175,
    -175,
    49,
    81,
    18,
    -175,
    -175,
    -175,
    39,
    -97,
    -99,
    50,
    -175,
    -175,
    -175,
    93,
    -49,
    -175,
    -4,
    -56,
    199,
    -175,
    -175,
    -175,
    -91,
    82,
    8,
    -116,
    -174,
    104,
    -175,
    14,
    -175,
    34,
    -175,
    -175,
    -175,
    -175,
    -175};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] = {0,
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
    47,
    228,
    32,
    33,
    34,
    35,
    178,
    137,
    204,
    176,
    36,
    150,
    186,
    187,
    59,
    106,
    37,
    38,
    130,
    131,
    39,
    40,
    60,
    61,
    147,
    62,
    63,
    64,
    209,
    124,
    210,
    128,
    163,
    164,
    234,
    251,
    252,
    185,
    215,
    41,
    42,
    43,
    77};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] = {65,
    89,
    85,
    134,
    90,
    133,
    123,
    125,
    148,
    254,
    84,
    104,
    189,
    200,
    167,
    90,
    90,
    51,
    66,
    139,
    220,
    221,
    255,
    69,
    166,
    201,
    70,
    202,
    203,
    71,
    87,
    52,
    84,
    238,
    190,
    72,
    117,
    118,
    119,
    120,
    232,
    48,
    105,
    49,
    127,
    114,
    84,
    86,
    88,
    115,
    134,
    51,
    67,
    68,
    73,
    242,
    75,
    140,
    141,
    80,
    44,
    53,
    54,
    55,
    56,
    52,
    57,
    58,
    146,
    191,
    91,
    162,
    92,
    93,
    94,
    95,
    92,
    93,
    94,
    95,
    110,
    91,
    91,
    113,
    45,
    168,
    169,
    50,
    76,
    151,
    180,
    52,
    211,
    78,
    230,
    53,
    54,
    55,
    56,
    97,
    57,
    58,
    194,
    195,
    94,
    95,
    46,
    79,
    196,
    197,
    81,
    152,
    249,
    194,
    195,
    82,
    153,
    145,
    134,
    134,
    235,
    53,
    54,
    98,
    56,
    171,
    132,
    172,
    173,
    174,
    175,
    92,
    93,
    94,
    95,
    216,
    217,
    219,
    162,
    162,
    154,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    201,
    83,
    202,
    203,
    92,
    93,
    94,
    95,
    245,
    217,
    162,
    99,
    100,
    102,
    101,
    151,
    103,
    107,
    108,
    109,
    111,
    112,
    116,
    121,
    122,
    162,
    126,
    127,
    129,
    239,
    51,
    135,
    138,
    84,
    142,
    144,
    136,
    152,
    143,
    149,
    250,
    247,
    153,
    170,
    52,
    165,
    177,
    179,
    181,
    182,
    183,
    184,
    250,
    188,
    192,
    199,
    206,
    208,
    207,
    213,
    214,
    231,
    218,
    222,
    224,
    240,
    154,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    53,
    54,
    55,
    56,
    105,
    57,
    58,
    1,
    2,
    233,
    227,
    223,
    229,
    194,
    237,
    241,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    244,
    256,
    74,
    11,
    12,
    13,
    253,
    248,
    225,
    246,
    226,
    236,
    205,
    198,
    96,
    257,
    14,
    15,
    243,
    212,
    193,
    0,
    0,
    0,
    258,
    16,
    0,
    17,
    0,
    0,
    18};

static const yytype_int16 yycheck[] = {4,
    57,
    51,
    102,
    4,
    102,
    97,
    98,
    124,
    5,
    17,
    24,
    9,
    24,
    130,
    4,
    4,
    24,
    70,
    4,
    194,
    195,
    18,
    43,
    26,
    36,
    45,
    38,
    39,
    70,
    24,
    38,
    17,
    4,
    31,
    70,
    92,
    93,
    94,
    95,
    214,
    13,
    55,
    15,
    46,
    70,
    17,
    51,
    42,
    74,
    149,
    24,
    14,
    15,
    52,
    229,
    0,
    106,
    107,
    15,
    13,
    68,
    69,
    70,
    71,
    38,
    73,
    74,
    57,
    66,
    70,
    127,
    72,
    73,
    74,
    75,
    72,
    73,
    74,
    75,
    84,
    70,
    70,
    87,
    37,
    68,
    69,
    59,
    3,
    9,
    139,
    38,
    183,
    70,
    210,
    68,
    69,
    70,
    71,
    45,
    73,
    74,
    47,
    48,
    74,
    75,
    59,
    70,
    164,
    165,
    70,
    31,
    57,
    47,
    48,
    70,
    36,
    121,
    217,
    218,
    217,
    68,
    69,
    45,
    71,
    30,
    73,
    32,
    33,
    34,
    35,
    72,
    73,
    74,
    75,
    25,
    26,
    193,
    194,
    195,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    36,
    70,
    38,
    39,
    72,
    73,
    74,
    75,
    25,
    26,
    214,
    70,
    70,
    60,
    49,
    9,
    53,
    4,
    70,
    50,
    25,
    25,
    70,
    26,
    70,
    229,
    44,
    46,
    70,
    226,
    24,
    71,
    56,
    17,
    50,
    25,
    70,
    31,
    70,
    24,
    244,
    238,
    36,
    43,
    38,
    60,
    26,
    60,
    70,
    58,
    26,
    10,
    256,
    26,
    36,
    13,
    25,
    24,
    70,
    6,
    11,
    213,
    24,
    70,
    38,
    26,
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
    55,
    73,
    74,
    7,
    8,
    12,
    70,
    68,
    50,
    47,
    25,
    25,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    6,
    26,
    18,
    27,
    28,
    29,
    58,
    240,
    205,
    237,
    206,
    218,
    177,
    166,
    61,
    253,
    40,
    41,
    230,
    183,
    162,
    -1,
    -1,
    -1,
    256,
    49,
    -1,
    51,
    -1,
    -1,
    54};

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
    40,
    41,
    49,
    51,
    54,
    78,
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
    93,
    94,
    95,
    96,
    101,
    107,
    108,
    111,
    112,
    130,
    131,
    132,
    13,
    37,
    59,
    91,
    13,
    15,
    59,
    24,
    38,
    68,
    69,
    70,
    71,
    73,
    74,
    105,
    113,
    114,
    116,
    117,
    118,
    113,
    70,
    14,
    15,
    43,
    45,
    70,
    70,
    52,
    79,
    0,
    3,
    133,
    70,
    70,
    15,
    70,
    70,
    70,
    17,
    111,
    113,
    24,
    42,
    114,
    4,
    70,
    72,
    73,
    74,
    75,
    115,
    45,
    45,
    70,
    70,
    49,
    60,
    53,
    24,
    55,
    106,
    4,
    70,
    50,
    113,
    25,
    25,
    113,
    70,
    74,
    70,
    114,
    114,
    114,
    114,
    26,
    70,
    119,
    120,
    119,
    44,
    46,
    122,
    70,
    109,
    110,
    73,
    104,
    105,
    71,
    70,
    98,
    56,
    4,
    111,
    111,
    50,
    70,
    25,
    113,
    57,
    115,
    122,
    24,
    102,
    9,
    31,
    36,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    114,
    123,
    124,
    60,
    26,
    122,
    68,
    69,
    43,
    30,
    32,
    33,
    34,
    35,
    100,
    26,
    97,
    60,
    111,
    70,
    58,
    26,
    10,
    128,
    103,
    104,
    26,
    9,
    31,
    66,
    36,
    124,
    47,
    48,
    114,
    114,
    110,
    13,
    24,
    36,
    38,
    39,
    99,
    98,
    25,
    70,
    24,
    119,
    121,
    119,
    120,
    6,
    11,
    129,
    25,
    26,
    24,
    114,
    123,
    123,
    70,
    68,
    38,
    97,
    106,
    70,
    92,
    50,
    122,
    113,
    123,
    12,
    125,
    104,
    103,
    25,
    4,
    111,
    26,
    25,
    123,
    128,
    6,
    25,
    99,
    111,
    92,
    57,
    114,
    126,
    127,
    58,
    5,
    18,
    26,
    121,
    126};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] = {0,
    77,
    78,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
    79,
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
    91,
    92,
    92,
    93,
    94,
    94,
    94,
    94,
    94,
    95,
    96,
    97,
    97,
    98,
    98,
    99,
    99,
    99,
    99,
    100,
    100,
    100,
    100,
    100,
    101,
    102,
    102,
    103,
    103,
    104,
    104,
    104,
    105,
    105,
    105,
    105,
    106,
    106,
    107,
    108,
    109,
    109,
    110,
    111,
    111,
    112,
    112,
    113,
    113,
    113,
    114,
    114,
    114,
    114,
    114,
    114,
    114,
    114,
    114,
    114,
    114,
    114,
    115,
    115,
    115,
    116,
    117,
    118,
    118,
    119,
    120,
    120,
    121,
    121,
    122,
    122,
    123,
    123,
    123,
    123,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    124,
    125,
    125,
    126,
    126,
    127,
    127,
    127,
    128,
    128,
    129,
    129,
    130,
    131,
    132,
    133,
    133};

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
    5,
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
    8,
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
    7,
    2,
    4,
    0,
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
#line 263 "yacc_sql.y"
    {
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
#line 1874 "yacc_sql.cpp"
    break;

    case 26: /* exit_stmt: EXIT  */
#line 296 "yacc_sql.y"
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1883 "yacc_sql.cpp"
    break;

    case 27: /* help_stmt: HELP  */
#line 302 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1891 "yacc_sql.cpp"
    break;

    case 28: /* sync_stmt: SYNC  */
#line 307 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1899 "yacc_sql.cpp"
    break;

    case 29: /* begin_stmt: TRX_BEGIN  */
#line 313 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1907 "yacc_sql.cpp"
    break;

    case 30: /* commit_stmt: TRX_COMMIT  */
#line 319 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1915 "yacc_sql.cpp"
    break;

    case 31: /* rollback_stmt: TRX_ROLLBACK  */
#line 325 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1923 "yacc_sql.cpp"
    break;

    case 32: /* drop_table_stmt: DROP TABLE ID  */
#line 331 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1933 "yacc_sql.cpp"
    break;

    case 33: /* show_tables_stmt: SHOW TABLES  */
#line 338 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1941 "yacc_sql.cpp"
    break;

    case 34: /* desc_table_stmt: DESC ID  */
#line 344 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1951 "yacc_sql.cpp"
    break;

    case 35: /* show_index_stmt: SHOW INDEX FROM relation  */
#line 353 "yacc_sql.y"
    {
      (yyval.sql_node)             = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = (yyval.sql_node)->show_index;
      show_index.relation_name     = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1962 "yacc_sql.cpp"
    break;

    case 36: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE attr_list RBRACE  */
#line 363 "yacc_sql.y"
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
#line 1978 "yacc_sql.cpp"
    break;

    case 37: /* opt_unique: UNIQUE  */
#line 377 "yacc_sql.y"
    {
      (yyval.unique) = true;
    }
#line 1984 "yacc_sql.cpp"
    break;

    case 38: /* opt_unique: %empty  */
#line 378 "yacc_sql.y"
    {
      (yyval.unique) = false;
    }
#line 1990 "yacc_sql.cpp"
    break;

    case 39: /* attr_list: ID  */
#line 383 "yacc_sql.y"
    {
      (yyval.index_attr_list) = new std::vector<std::string>;    // 创建一个新的 vector
      (yyval.index_attr_list)->emplace_back((yyvsp[0].string));  // 将列名加入 vector
      free((yyvsp[0].string));
    }
#line 2000 "yacc_sql.cpp"
    break;

    case 40: /* attr_list: ID COMMA attr_list  */
#line 389 "yacc_sql.y"
    {
      (yyval.index_attr_list) = (yyvsp[0].index_attr_list);  // 使用现有的 vector
      (yyval.index_attr_list)
          ->emplace((yyval.index_attr_list)->begin(), (yyvsp[-2].string));  // 将新列名加入 vector 开头
      free((yyvsp[-2].string));
    }
#line 2010 "yacc_sql.cpp"
    break;

    case 41: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 398 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name    = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2022 "yacc_sql.cpp"
    break;

    case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt */
#line 408 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-7].string), (yyvsp[-5].attr_info), (yyvsp[-4].attr_infos), (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2030 "yacc_sql.cpp"
    break;

    case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 412 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-6].string), (yyvsp[-4].attr_info), (yyvsp[-3].attr_infos), (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2038 "yacc_sql.cpp"
    break;

    case 44: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 416 "yacc_sql.y"
    {
      (yyval.sql_node) = create_table_sql_node(
          (yyvsp[-5].string), (yyvsp[-3].attr_info), (yyvsp[-2].attr_infos), (yyvsp[0].string), nullptr);
    }
#line 2046 "yacc_sql.cpp"
    break;

    case 45: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 420 "yacc_sql.y"
    {
      (yyval.sql_node) =
          create_table_sql_node((yyvsp[-3].string), nullptr, nullptr, (yyvsp[-2].string), (yyvsp[0].sql_node));
    }
#line 2054 "yacc_sql.cpp"
    break;

    case 46: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 424 "yacc_sql.y"
    {
      (yyval.sql_node) =
          create_table_sql_node((yyvsp[-2].string), nullptr, nullptr, (yyvsp[-1].string), (yyvsp[0].sql_node));
    }
#line 2062 "yacc_sql.cpp"
    break;

    case 47: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 431 "yacc_sql.y"
    {
      (yyval.sql_node)               = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name      = (yyvsp[-2].string);
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move((yyvsp[0].sql_node)->selection));
      free((yyvsp[-2].string));
    }
#line 2074 "yacc_sql.cpp"
    break;

    case 48: /* drop_view_stmt: DROP VIEW ID  */
#line 442 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2084 "yacc_sql.cpp"
    break;

    case 49: /* attr_def_list: %empty  */
#line 451 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2092 "yacc_sql.cpp"
    break;

    case 50: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 455 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2106 "yacc_sql.cpp"
    break;

    case 51: /* attr_def: ID type LBRACE NUMBER RBRACE nullable_constraint  */
#line 468 "yacc_sql.y"
    {
      (yyval.attr_info)           = new AttrInfoSqlNode;
      (yyval.attr_info)->type     = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name     = (yyvsp[-5].string);
      (yyval.attr_info)->length   = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].nullable_info);
      if ((yyval.attr_info)->nullable) {
        (yyval.attr_info)->length++;
      }
      free((yyvsp[-5].string));
    }
#line 2122 "yacc_sql.cpp"
    break;

    case 52: /* attr_def: ID type nullable_constraint  */
#line 480 "yacc_sql.y"
    {
      (yyval.attr_info)       = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if ((yyval.attr_info)->type == AttrType::INTS) {
        (yyval.attr_info)->length = 4;
      } else if ((yyval.attr_info)->type == AttrType::FLOATS) {
        (yyval.attr_info)->length = 4;
      } else if ((yyval.attr_info)->type == AttrType::DATES) {
        (yyval.attr_info)->length = 4;
      } else if ((yyval.attr_info)->type == AttrType::CHARS) {
        (yyval.attr_info)->length = 4;
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
#line 2150 "yacc_sql.cpp"
    break;

    case 53: /* nullable_constraint: NOT NULL_T  */
#line 507 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // NOT NULL 对应的可空性为 false
    }
#line 2158 "yacc_sql.cpp"
    break;

    case 54: /* nullable_constraint: NULLABLE  */
#line 511 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULLABLE 对应的可空性为 true 2022
    }
#line 2166 "yacc_sql.cpp"
    break;

    case 55: /* nullable_constraint: NULL_T  */
#line 515 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULL 对应的可空性也为 true 2023
    }
#line 2174 "yacc_sql.cpp"
    break;

    case 56: /* nullable_constraint: %empty  */
#line 519 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // 默认情况为 NULL
    }
#line 2182 "yacc_sql.cpp"
    break;

    case 57: /* type: INT_T  */
#line 525 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::INTS);
    }
#line 2188 "yacc_sql.cpp"
    break;

    case 58: /* type: STRING_T  */
#line 526 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::CHARS);
    }
#line 2194 "yacc_sql.cpp"
    break;

    case 59: /* type: FLOAT_T  */
#line 527 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::FLOATS);
    }
#line 2200 "yacc_sql.cpp"
    break;

    case 60: /* type: DATE_T  */
#line 528 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::DATES);
    }
#line 2206 "yacc_sql.cpp"
    break;

    case 61: /* type: TEXT_T  */
#line 529 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::TEXTS);
    }
#line 2212 "yacc_sql.cpp"
    break;

    case 62: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 534 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-2].string));
    }
#line 2226 "yacc_sql.cpp"
    break;

    case 63: /* values_list: LBRACE value_list RBRACE  */
#line 547 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2236 "yacc_sql.cpp"
    break;

    case 64: /* values_list: values_list COMMA LBRACE value_list RBRACE  */
#line 553 "yacc_sql.y"
    {
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2245 "yacc_sql.cpp"
    break;

    case 65: /* value_list: value  */
#line 560 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2255 "yacc_sql.cpp"
    break;

    case 66: /* value_list: value_list COMMA value  */
#line 566 "yacc_sql.y"
    {
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2264 "yacc_sql.cpp"
    break;

    case 67: /* value: nonnegative_value  */
#line 573 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2272 "yacc_sql.cpp"
    break;

    case 68: /* value: '-' NUMBER  */
#line 576 "yacc_sql.y"
    {
      (yyval.value) = new Value(-(yyvsp[0].number));
      (yyloc)       = (yylsp[-1]);
    }
#line 2281 "yacc_sql.cpp"
    break;

    case 69: /* value: '-' FLOAT  */
#line 580 "yacc_sql.y"
    {
      (yyval.value) = new Value(-(yyvsp[0].floats));
      (yyloc)       = (yylsp[-1]);
    }
#line 2290 "yacc_sql.cpp"
    break;

    case 70: /* nonnegative_value: NUMBER  */
#line 587 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[0].number));
      (yyloc)       = (yylsp[0]);
    }
#line 2299 "yacc_sql.cpp"
    break;

    case 71: /* nonnegative_value: FLOAT  */
#line 591 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[0].floats));
      (yyloc)       = (yylsp[0]);
    }
#line 2308 "yacc_sql.cpp"
    break;

    case 72: /* nonnegative_value: SSS  */
#line 595 "yacc_sql.y"
    {
      char *tmp     = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2319 "yacc_sql.cpp"
    break;

    case 73: /* nonnegative_value: NULL_T  */
#line 601 "yacc_sql.y"
    {
      (yyval.value) = new Value(NullValue());
    }
#line 2327 "yacc_sql.cpp"
    break;

    case 74: /* storage_format: %empty  */
#line 608 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2335 "yacc_sql.cpp"
    break;

    case 75: /* storage_format: STORAGE FORMAT EQ ID  */
#line 612 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2343 "yacc_sql.cpp"
    break;

    case 76: /* delete_stmt: DELETE FROM ID where  */
#line 619 "yacc_sql.y"
    {
      (yyval.sql_node)                         = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.condition = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-1].string));
    }
#line 2356 "yacc_sql.cpp"
    break;

    case 77: /* update_stmt: UPDATE ID SET setClauses where  */
#line 631 "yacc_sql.y"
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
#line 2371 "yacc_sql.cpp"
    break;

    case 78: /* setClauses: setClause  */
#line 645 "yacc_sql.y"
    {
      (yyval.set_clauses) = new std::vector<SetClauseSqlNode>;
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2380 "yacc_sql.cpp"
    break;

    case 79: /* setClauses: setClauses COMMA setClause  */
#line 650 "yacc_sql.y"
    {
      (yyval.set_clauses)->emplace_back(std::move(*(yyvsp[0].set_clause)));
    }
#line 2388 "yacc_sql.cpp"
    break;

    case 80: /* setClause: ID EQ expression  */
#line 657 "yacc_sql.y"
    {
      (yyval.set_clause)             = new SetClauseSqlNode;
      (yyval.set_clause)->field_name = (yyvsp[-2].string);
      (yyval.set_clause)->value      = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2399 "yacc_sql.cpp"
    break;

    case 81: /* select_stmt: SELECT expression_list FROM rel_list where group_by opt_having opt_order_by  */
#line 667 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].relation_list));
        delete (yyvsp[-4].relation_list);
      }

      (yyval.sql_node)->selection.conditions = nullptr;

      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = std::unique_ptr<Expression>((yyvsp[-3].expression));
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.having_conditions = std::unique_ptr<Expression>((yyvsp[-1].expression));
      }

      if ((yyvsp[0].orderby_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].orderby_list));
        delete (yyvsp[0].orderby_list);
      }
    }
#line 2436 "yacc_sql.cpp"
    break;

    case 82: /* select_stmt: SELECT expression_list FROM relation INNER JOIN joinClauses where group_by  */
#line 700 "yacc_sql.y"
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
#line 2470 "yacc_sql.cpp"
    break;

    case 83: /* calc_stmt: CALC expression_list  */
#line 733 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2480 "yacc_sql.cpp"
    break;

    case 84: /* calc_stmt: SELECT expression_list  */
#line 739 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2490 "yacc_sql.cpp"
    break;

    case 85: /* expression_list: %empty  */
#line 747 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
    }
#line 2498 "yacc_sql.cpp"
    break;

    case 86: /* expression_list: expression alias  */
#line 751 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_name((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2511 "yacc_sql.cpp"
    break;

    case 87: /* expression_list: expression alias COMMA expression_list  */
#line 760 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if (nullptr != (yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_name((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), std::move((yyvsp[-3].expression)));
      free((yyvsp[-2].string));
    }
#line 2528 "yacc_sql.cpp"
    break;

    case 88: /* expression: expression '+' expression  */
#line 775 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2536 "yacc_sql.cpp"
    break;

    case 89: /* expression: expression '-' expression  */
#line 778 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2544 "yacc_sql.cpp"
    break;

    case 90: /* expression: expression '*' expression  */
#line 781 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2552 "yacc_sql.cpp"
    break;

    case 91: /* expression: expression '/' expression  */
#line 784 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2560 "yacc_sql.cpp"
    break;

    case 92: /* expression: LBRACE expression_list RBRACE  */
#line 787 "yacc_sql.y"
    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().get();
      } else {
        (yyval.expression) = new ListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2573 "yacc_sql.cpp"
    break;

    case 93: /* expression: '-' expression  */
#line 795 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2581 "yacc_sql.cpp"
    break;

    case 94: /* expression: nonnegative_value  */
#line 798 "yacc_sql.y"
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2591 "yacc_sql.cpp"
    break;

    case 95: /* expression: rel_attr  */
#line 803 "yacc_sql.y"
    {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression)   = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2602 "yacc_sql.cpp"
    break;

    case 96: /* expression: '*'  */
#line 809 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr();
    }
#line 2610 "yacc_sql.cpp"
    break;

    case 97: /* expression: ID DOT '*'  */
#line 812 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2618 "yacc_sql.cpp"
    break;

    case 98: /* expression: aggr_func_expr  */
#line 815 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // AggrFuncExpr
    }
#line 2626 "yacc_sql.cpp"
    break;

    case 99: /* expression: sub_query_expr  */
#line 818 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // SubQueryExpr
    }
#line 2634 "yacc_sql.cpp"
    break;

    case 100: /* alias: %empty  */
#line 825 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2642 "yacc_sql.cpp"
    break;

    case 101: /* alias: ID  */
#line 828 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2650 "yacc_sql.cpp"
    break;

    case 102: /* alias: AS ID  */
#line 831 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2658 "yacc_sql.cpp"
    break;

    case 103: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 837 "yacc_sql.y"
    {
      (yyval.expression) = new UnboundFunctionExpr((yyvsp[-3].string), std::move(*(yyvsp[-1].expression_list)));
    }
#line 2666 "yacc_sql.cpp"
    break;

    case 104: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 844 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2674 "yacc_sql.cpp"
    break;

    case 105: /* rel_attr: ID  */
#line 850 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2684 "yacc_sql.cpp"
    break;

    case 106: /* rel_attr: ID DOT ID  */
#line 855 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2696 "yacc_sql.cpp"
    break;

    case 107: /* relation: ID  */
#line 865 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2704 "yacc_sql.cpp"
    break;

    case 108: /* rel_list: relation alias  */
#line 871 "yacc_sql.y"
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
#line 2719 "yacc_sql.cpp"
    break;

    case 109: /* rel_list: relation alias COMMA rel_list  */
#line 881 "yacc_sql.y"
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
#line 2738 "yacc_sql.cpp"
    break;

    case 110: /* joinClauses: relation ON condition  */
#line 899 "yacc_sql.y"
    {
      (yyval.join_clauses) = new JoinSqlNode;
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-2].string));
      (yyval.join_clauses)->conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2749 "yacc_sql.cpp"
    break;

    case 111: /* joinClauses: relation ON condition INNER JOIN joinClauses  */
#line 906 "yacc_sql.y"
    {
      (yyval.join_clauses) = (yyvsp[0].join_clauses);
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-5].string));
      auto ptr = (yyval.join_clauses)->conditions.release();
      (yyval.join_clauses)->conditions =
          std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-3].expression));
      free((yyvsp[-5].string));
    }
#line 2761 "yacc_sql.cpp"
    break;

    case 112: /* where: %empty  */
#line 917 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2769 "yacc_sql.cpp"
    break;

    case 113: /* where: WHERE condition  */
#line 920 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2777 "yacc_sql.cpp"
    break;

    case 114: /* condition: expression comp_op expression  */
#line 927 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2785 "yacc_sql.cpp"
    break;

    case 115: /* condition: comp_op expression  */
#line 931 "yacc_sql.y"
    {
      Value val;
      val.set_null(true);
      ValueExpr *temp_expr = new ValueExpr(val);
      (yyval.expression)   = new ComparisonExpr((yyvsp[-1].comp), temp_expr, (yyvsp[0].expression));
    }
#line 2796 "yacc_sql.cpp"
    break;

    case 116: /* condition: condition AND condition  */
#line 938 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2804 "yacc_sql.cpp"
    break;

    case 117: /* condition: condition OR condition  */
#line 942 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2812 "yacc_sql.cpp"
    break;

    case 118: /* comp_op: EQ  */
#line 948 "yacc_sql.y"
    {
      (yyval.comp) = EQUAL_TO;
    }
#line 2818 "yacc_sql.cpp"
    break;

    case 119: /* comp_op: LT  */
#line 949 "yacc_sql.y"
    {
      (yyval.comp) = LESS_THAN;
    }
#line 2824 "yacc_sql.cpp"
    break;

    case 120: /* comp_op: GT  */
#line 950 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_THAN;
    }
#line 2830 "yacc_sql.cpp"
    break;

    case 121: /* comp_op: LE  */
#line 951 "yacc_sql.y"
    {
      (yyval.comp) = LESS_EQUAL;
    }
#line 2836 "yacc_sql.cpp"
    break;

    case 122: /* comp_op: GE  */
#line 952 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_EQUAL;
    }
#line 2842 "yacc_sql.cpp"
    break;

    case 123: /* comp_op: NE  */
#line 953 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EQUAL;
    }
#line 2848 "yacc_sql.cpp"
    break;

    case 124: /* comp_op: IS  */
#line 954 "yacc_sql.y"
    {
      (yyval.comp) = IS_OP;
    }
#line 2854 "yacc_sql.cpp"
    break;

    case 125: /* comp_op: IS NOT  */
#line 955 "yacc_sql.y"
    {
      (yyval.comp) = IS_NOT_OP;
    }
#line 2860 "yacc_sql.cpp"
    break;

    case 126: /* comp_op: LIKE  */
#line 956 "yacc_sql.y"
    {
      (yyval.comp) = LIKE_OP;
    }
#line 2866 "yacc_sql.cpp"
    break;

    case 127: /* comp_op: NOT LIKE  */
#line 957 "yacc_sql.y"
    {
      (yyval.comp) = NOT_LIKE_OP;
    }
#line 2872 "yacc_sql.cpp"
    break;

    case 128: /* comp_op: IN  */
#line 958 "yacc_sql.y"
    {
      (yyval.comp) = IN_OP;
    }
#line 2878 "yacc_sql.cpp"
    break;

    case 129: /* comp_op: NOT IN  */
#line 959 "yacc_sql.y"
    {
      (yyval.comp) = NOT_IN_OP;
    }
#line 2884 "yacc_sql.cpp"
    break;

    case 130: /* comp_op: EXISTS  */
#line 960 "yacc_sql.y"
    {
      (yyval.comp) = EXISTS_OP;
    }
#line 2890 "yacc_sql.cpp"
    break;

    case 131: /* comp_op: NOT EXISTS  */
#line 961 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EXISTS_OP;
    }
#line 2896 "yacc_sql.cpp"
    break;

    case 132: /* opt_order_by: %empty  */
#line 966 "yacc_sql.y"
    {
      (yyval.orderby_list) = nullptr;
    }
#line 2904 "yacc_sql.cpp"
    break;

    case 133: /* opt_order_by: ORDER BY sort_list  */
#line 970 "yacc_sql.y"
    {
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
      std::reverse((yyval.orderby_list)->begin(), (yyval.orderby_list)->end());
    }
#line 2913 "yacc_sql.cpp"
    break;

    case 134: /* sort_list: sort_unit  */
#line 978 "yacc_sql.y"
    {
      (yyval.orderby_list) = new std::vector<OrderBySqlNode>;
      (yyval.orderby_list)->emplace_back(std::move(*(yyvsp[0].orderby_unit)));
    }
#line 2922 "yacc_sql.cpp"
    break;

    case 135: /* sort_list: sort_unit COMMA sort_list  */
#line 983 "yacc_sql.y"
    {
      (yyvsp[0].orderby_list)->emplace_back(std::move(*(yyvsp[-2].orderby_unit)));
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
    }
#line 2931 "yacc_sql.cpp"
    break;

    case 136: /* sort_unit: expression  */
#line 991 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2941 "yacc_sql.cpp"
    break;

    case 137: /* sort_unit: expression DESC  */
#line 997 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = false;
    }
#line 2951 "yacc_sql.cpp"
    break;

    case 138: /* sort_unit: expression ASC  */
#line 1003 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();  // 默认是升序
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2961 "yacc_sql.cpp"
    break;

    case 139: /* group_by: %empty  */
#line 1012 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2969 "yacc_sql.cpp"
    break;

    case 140: /* group_by: GROUP BY expression_list  */
#line 1016 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2977 "yacc_sql.cpp"
    break;

    case 141: /* opt_having: %empty  */
#line 1023 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2985 "yacc_sql.cpp"
    break;

    case 142: /* opt_having: HAVING condition  */
#line 1027 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2993 "yacc_sql.cpp"
    break;

    case 143: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1034 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node)                          = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name     = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3007 "yacc_sql.cpp"
    break;

    case 144: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1047 "yacc_sql.y"
    {
      (yyval.sql_node)                   = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3016 "yacc_sql.cpp"
    break;

    case 145: /* set_variable_stmt: SET ID EQ value  */
#line 1055 "yacc_sql.y"
    {
      (yyval.sql_node)                     = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3028 "yacc_sql.cpp"
    break;

#line 3032 "yacc_sql.cpp"

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

#line 1067 "yacc_sql.y"

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
