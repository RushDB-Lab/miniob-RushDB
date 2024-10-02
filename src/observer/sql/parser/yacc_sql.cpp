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

UnboundAggregateExpr *create_aggregate_expression(
    const char *aggregate_name, Expression *child, const char *sql_string, YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

#line 125 "yacc_sql.cpp"

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
  YYSYMBOL_ORDER               = 11,  /* ORDER  */
  YYSYMBOL_TABLE               = 12,  /* TABLE  */
  YYSYMBOL_TABLES              = 13,  /* TABLES  */
  YYSYMBOL_INDEX               = 14,  /* INDEX  */
  YYSYMBOL_CALC                = 15,  /* CALC  */
  YYSYMBOL_SELECT              = 16,  /* SELECT  */
  YYSYMBOL_DESC                = 17,  /* DESC  */
  YYSYMBOL_SHOW                = 18,  /* SHOW  */
  YYSYMBOL_SYNC                = 19,  /* SYNC  */
  YYSYMBOL_INSERT              = 20,  /* INSERT  */
  YYSYMBOL_DELETE              = 21,  /* DELETE  */
  YYSYMBOL_UPDATE              = 22,  /* UPDATE  */
  YYSYMBOL_LBRACE              = 23,  /* LBRACE  */
  YYSYMBOL_RBRACE              = 24,  /* RBRACE  */
  YYSYMBOL_COMMA               = 25,  /* COMMA  */
  YYSYMBOL_TRX_BEGIN           = 26,  /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT          = 27,  /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK        = 28,  /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T               = 29,  /* INT_T  */
  YYSYMBOL_IN                  = 30,  /* IN  */
  YYSYMBOL_STRING_T            = 31,  /* STRING_T  */
  YYSYMBOL_FLOAT_T             = 32,  /* FLOAT_T  */
  YYSYMBOL_DATE_T              = 33,  /* DATE_T  */
  YYSYMBOL_NOT                 = 34,  /* NOT  */
  YYSYMBOL_NULL_T              = 35,  /* NULL_T  */
  YYSYMBOL_NULLABLE            = 36,  /* NULLABLE  */
  YYSYMBOL_HELP                = 37,  /* HELP  */
  YYSYMBOL_EXIT                = 38,  /* EXIT  */
  YYSYMBOL_DOT                 = 39,  /* DOT  */
  YYSYMBOL_INTO                = 40,  /* INTO  */
  YYSYMBOL_VALUES              = 41,  /* VALUES  */
  YYSYMBOL_FROM                = 42,  /* FROM  */
  YYSYMBOL_WHERE               = 43,  /* WHERE  */
  YYSYMBOL_AND                 = 44,  /* AND  */
  YYSYMBOL_OR                  = 45,  /* OR  */
  YYSYMBOL_SET                 = 46,  /* SET  */
  YYSYMBOL_ON                  = 47,  /* ON  */
  YYSYMBOL_LOAD                = 48,  /* LOAD  */
  YYSYMBOL_DATA                = 49,  /* DATA  */
  YYSYMBOL_INFILE              = 50,  /* INFILE  */
  YYSYMBOL_EXPLAIN             = 51,  /* EXPLAIN  */
  YYSYMBOL_STORAGE             = 52,  /* STORAGE  */
  YYSYMBOL_FORMAT              = 53,  /* FORMAT  */
  YYSYMBOL_INNER               = 54,  /* INNER  */
  YYSYMBOL_JOIN                = 55,  /* JOIN  */
  YYSYMBOL_EQ                  = 56,  /* EQ  */
  YYSYMBOL_LT                  = 57,  /* LT  */
  YYSYMBOL_GT                  = 58,  /* GT  */
  YYSYMBOL_LE                  = 59,  /* LE  */
  YYSYMBOL_GE                  = 60,  /* GE  */
  YYSYMBOL_NE                  = 61,  /* NE  */
  YYSYMBOL_LIKE                = 62,  /* LIKE  */
  YYSYMBOL_IS                  = 63,  /* IS  */
  YYSYMBOL_NUMBER              = 64,  /* NUMBER  */
  YYSYMBOL_FLOAT               = 65,  /* FLOAT  */
  YYSYMBOL_ID                  = 66,  /* ID  */
  YYSYMBOL_SSS                 = 67,  /* SSS  */
  YYSYMBOL_68_                 = 68,  /* '+'  */
  YYSYMBOL_69_                 = 69,  /* '-'  */
  YYSYMBOL_70_                 = 70,  /* '*'  */
  YYSYMBOL_71_                 = 71,  /* '/'  */
  YYSYMBOL_UMINUS              = 72,  /* UMINUS  */
  YYSYMBOL_YYACCEPT            = 73,  /* $accept  */
  YYSYMBOL_commands            = 74,  /* commands  */
  YYSYMBOL_command_wrapper     = 75,  /* command_wrapper  */
  YYSYMBOL_exit_stmt           = 76,  /* exit_stmt  */
  YYSYMBOL_help_stmt           = 77,  /* help_stmt  */
  YYSYMBOL_sync_stmt           = 78,  /* sync_stmt  */
  YYSYMBOL_begin_stmt          = 79,  /* begin_stmt  */
  YYSYMBOL_commit_stmt         = 80,  /* commit_stmt  */
  YYSYMBOL_rollback_stmt       = 81,  /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt     = 82,  /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt    = 83,  /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt     = 84,  /* desc_table_stmt  */
  YYSYMBOL_show_index_stmt     = 85,  /* show_index_stmt  */
  YYSYMBOL_create_index_stmt   = 86,  /* create_index_stmt  */
  YYSYMBOL_attr_list           = 87,  /* attr_list  */
  YYSYMBOL_drop_index_stmt     = 88,  /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt   = 89,  /* create_table_stmt  */
  YYSYMBOL_attr_def_list       = 90,  /* attr_def_list  */
  YYSYMBOL_attr_def            = 91,  /* attr_def  */
  YYSYMBOL_nullable_constraint = 92,  /* nullable_constraint  */
  YYSYMBOL_number              = 93,  /* number  */
  YYSYMBOL_type                = 94,  /* type  */
  YYSYMBOL_insert_stmt         = 95,  /* insert_stmt  */
  YYSYMBOL_values_list         = 96,  /* values_list  */
  YYSYMBOL_value_list          = 97,  /* value_list  */
  YYSYMBOL_value               = 98,  /* value  */
  YYSYMBOL_storage_format      = 99,  /* storage_format  */
  YYSYMBOL_delete_stmt         = 100, /* delete_stmt  */
  YYSYMBOL_update_stmt         = 101, /* update_stmt  */
  YYSYMBOL_setClauses          = 102, /* setClauses  */
  YYSYMBOL_setClause           = 103, /* setClause  */
  YYSYMBOL_select_stmt         = 104, /* select_stmt  */
  YYSYMBOL_calc_stmt           = 105, /* calc_stmt  */
  YYSYMBOL_expression_list     = 106, /* expression_list  */
  YYSYMBOL_expression          = 107, /* expression  */
  YYSYMBOL_alias               = 108, /* alias  */
  YYSYMBOL_aggr_func_expr      = 109, /* aggr_func_expr  */
  YYSYMBOL_sub_query_expr      = 110, /* sub_query_expr  */
  YYSYMBOL_rel_attr            = 111, /* rel_attr  */
  YYSYMBOL_relation            = 112, /* relation  */
  YYSYMBOL_rel_list            = 113, /* rel_list  */
  YYSYMBOL_joinClauses         = 114, /* joinClauses  */
  YYSYMBOL_where               = 115, /* where  */
  YYSYMBOL_condition           = 116, /* condition  */
  YYSYMBOL_comp_op             = 117, /* comp_op  */
  YYSYMBOL_opt_order_by        = 118, /* opt_order_by  */
  YYSYMBOL_sort_list           = 119, /* sort_list  */
  YYSYMBOL_sort_unit           = 120, /* sort_unit  */
  YYSYMBOL_group_by            = 121, /* group_by  */
  YYSYMBOL_load_data_stmt      = 122, /* load_data_stmt  */
  YYSYMBOL_explain_stmt        = 123, /* explain_stmt  */
  YYSYMBOL_set_variable_stmt   = 124, /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon       = 125  /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL 70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 53
/* YYNRULES -- Number of rules.  */
#define YYNRULES 125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 225

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 323

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
    70,
    68,
    2,
    69,
    2,
    71,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
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
    72};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] = {0,
    222,
    222,
    230,
    231,
    232,
    233,
    234,
    235,
    236,
    237,
    238,
    239,
    240,
    241,
    242,
    243,
    244,
    245,
    246,
    247,
    248,
    249,
    250,
    254,
    260,
    265,
    271,
    277,
    283,
    289,
    296,
    302,
    310,
    320,
    334,
    340,
    349,
    359,
    383,
    386,
    399,
    411,
    436,
    440,
    445,
    451,
    454,
    455,
    456,
    457,
    461,
    474,
    480,
    487,
    493,
    501,
    505,
    509,
    515,
    522,
    525,
    532,
    544,
    558,
    564,
    572,
    582,
    611,
    644,
    653,
    662,
    678,
    681,
    684,
    687,
    690,
    699,
    702,
    707,
    713,
    716,
    719,
    726,
    729,
    732,
    737,
    745,
    752,
    759,
    764,
    774,
    780,
    790,
    807,
    814,
    826,
    829,
    835,
    839,
    843,
    850,
    851,
    852,
    853,
    854,
    855,
    856,
    857,
    858,
    859,
    860,
    861,
    866,
    869,
    877,
    882,
    890,
    896,
    902,
    912,
    917,
    930,
    938,
    948,
    949};
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
    "NOT",
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
    "attr_list",
    "drop_index_stmt",
    "create_table_stmt",
    "attr_def_list",
    "attr_def",
    "nullable_constraint",
    "number",
    "type",
    "insert_stmt",
    "values_list",
    "value_list",
    "value",
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
    "load_data_stmt",
    "explain_stmt",
    "set_variable_stmt",
    "opt_semicolon",
    YY_NULLPTR};

static const char *yysymbol_name(yysymbol_kind_t yysymbol) { return yytname[yysymbol]; }
#endif

#define YYPACT_NINF (-160)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {137,
    70,
    71,
    64,
    64,
    -54,
    17,
    -160,
    16,
    -5,
    12,
    -160,
    -160,
    -160,
    -160,
    -160,
    25,
    46,
    137,
    98,
    43,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    36,
    37,
    38,
    39,
    -12,
    -160,
    -160,
    -160,
    6,
    -160,
    64,
    -160,
    -160,
    -160,
    -2,
    -160,
    -160,
    -160,
    65,
    -160,
    -160,
    66,
    44,
    48,
    63,
    59,
    67,
    -160,
    -160,
    -160,
    -160,
    93,
    73,
    -160,
    78,
    94,
    95,
    57,
    69,
    -160,
    74,
    -160,
    64,
    64,
    64,
    64,
    107,
    75,
    75,
    96,
    99,
    77,
    -26,
    79,
    81,
    82,
    84,
    -160,
    -160,
    -160,
    112,
    -160,
    -160,
    -20,
    -20,
    -160,
    -160,
    64,
    -160,
    11,
    99,
    -160,
    115,
    64,
    -160,
    83,
    -15,
    -160,
    -160,
    120,
    -7,
    142,
    138,
    -160,
    -160,
    -160,
    114,
    146,
    -160,
    -26,
    147,
    136,
    45,
    -26,
    77,
    -160,
    150,
    -160,
    -160,
    -160,
    -160,
    13,
    81,
    149,
    110,
    75,
    75,
    166,
    72,
    -160,
    155,
    -160,
    -14,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    145,
    64,
    64,
    64,
    -160,
    -160,
    116,
    117,
    151,
    -160,
    -160,
    142,
    128,
    159,
    163,
    143,
    99,
    9,
    -160,
    183,
    -160,
    -160,
    -26,
    -26,
    -160,
    -160,
    -160,
    -9,
    -160,
    156,
    -160,
    -160,
    167,
    -160,
    -160,
    148,
    -160,
    110,
    -160,
    64,
    -160,
    64,
    -160,
    76,
    52,
    152,
    -160,
    -27,
    -160,
    2,
    -160,
    177,
    -160,
    -160,
    144,
    154,
    -160,
    -160,
    64,
    -160,
    75,
    -160,
    -160};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] = {0,
    0,
    0,
    0,
    0,
    0,
    0,
    26,
    0,
    0,
    0,
    27,
    28,
    29,
    25,
    24,
    0,
    0,
    0,
    0,
    124,
    23,
    22,
    15,
    16,
    17,
    18,
    9,
    10,
    11,
    14,
    12,
    13,
    8,
    5,
    7,
    6,
    4,
    3,
    19,
    20,
    21,
    0,
    0,
    0,
    0,
    0,
    59,
    56,
    57,
    89,
    58,
    0,
    80,
    78,
    69,
    83,
    81,
    82,
    79,
    0,
    32,
    31,
    0,
    0,
    0,
    0,
    0,
    0,
    122,
    1,
    125,
    2,
    0,
    0,
    30,
    0,
    0,
    0,
    0,
    0,
    77,
    0,
    84,
    0,
    0,
    0,
    0,
    70,
    0,
    0,
    0,
    96,
    0,
    0,
    0,
    0,
    0,
    0,
    88,
    76,
    87,
    0,
    90,
    85,
    72,
    73,
    74,
    75,
    0,
    91,
    83,
    96,
    33,
    0,
    0,
    62,
    0,
    96,
    64,
    123,
    0,
    0,
    39,
    0,
    37,
    86,
    71,
    0,
    92,
    120,
    0,
    51,
    0,
    97,
    0,
    0,
    63,
    0,
    47,
    48,
    49,
    50,
    45,
    0,
    0,
    0,
    0,
    0,
    113,
    0,
    54,
    0,
    111,
    0,
    101,
    102,
    103,
    104,
    105,
    106,
    109,
    107,
    0,
    0,
    0,
    66,
    65,
    0,
    0,
    0,
    44,
    42,
    39,
    60,
    35,
    0,
    0,
    96,
    83,
    93,
    0,
    67,
    52,
    0,
    0,
    112,
    110,
    108,
    98,
    99,
    100,
    121,
    46,
    0,
    43,
    40,
    0,
    38,
    0,
    34,
    0,
    120,
    0,
    55,
    0,
    45,
    0,
    36,
    94,
    68,
    117,
    114,
    115,
    53,
    41,
    0,
    0,
    119,
    118,
    0,
    61,
    0,
    116,
    95};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-160,
    -160,
    185,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    -160,
    14,
    -160,
    -160,
    41,
    68,
    5,
    -160,
    -160,
    -160,
    -160,
    30,
    -91,
    -160,
    -160,
    -160,
    -160,
    80,
    171,
    -160,
    -3,
    -52,
    162,
    -160,
    -160,
    -160,
    -69,
    85,
    -1,
    -104,
    -159,
    -160,
    -160,
    0,
    -160,
    20,
    -160,
    -160,
    -160,
    -160};

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
    176,
    32,
    33,
    145,
    123,
    172,
    194,
    143,
    34,
    132,
    150,
    54,
    198,
    35,
    36,
    118,
    119,
    37,
    38,
    55,
    56,
    129,
    57,
    58,
    59,
    177,
    112,
    178,
    116,
    134,
    163,
    182,
    212,
    213,
    149,
    39,
    40,
    41,
    72};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] = {81,
    60,
    82,
    120,
    4,
    190,
    191,
    218,
    130,
    47,
    136,
    46,
    61,
    82,
    137,
    82,
    186,
    164,
    165,
    219,
    111,
    113,
    139,
    47,
    140,
    141,
    142,
    217,
    115,
    79,
    62,
    63,
    105,
    106,
    107,
    108,
    169,
    65,
    48,
    49,
    151,
    51,
    209,
    78,
    166,
    80,
    71,
    170,
    187,
    171,
    86,
    87,
    48,
    49,
    50,
    51,
    64,
    52,
    53,
    84,
    85,
    86,
    87,
    133,
    83,
    128,
    84,
    85,
    86,
    87,
    84,
    85,
    86,
    87,
    202,
    83,
    102,
    83,
    66,
    179,
    46,
    101,
    42,
    44,
    43,
    45,
    170,
    46,
    171,
    164,
    165,
    67,
    47,
    204,
    151,
    68,
    183,
    184,
    70,
    47,
    214,
    184,
    73,
    74,
    75,
    76,
    127,
    89,
    90,
    93,
    91,
    189,
    133,
    133,
    92,
    94,
    96,
    95,
    99,
    100,
    97,
    48,
    49,
    50,
    51,
    98,
    52,
    53,
    48,
    49,
    50,
    51,
    109,
    52,
    53,
    103,
    126,
    114,
    131,
    135,
    104,
    110,
    115,
    117,
    1,
    2,
    121,
    122,
    124,
    133,
    125,
    211,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    138,
    146,
    168,
    11,
    12,
    13,
    153,
    144,
    211,
    147,
    154,
    148,
    152,
    174,
    14,
    15,
    175,
    181,
    185,
    188,
    197,
    193,
    192,
    16,
    199,
    17,
    195,
    200,
    18,
    203,
    201,
    206,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    162,
    164,
    207,
    220,
    69,
    84,
    85,
    86,
    87,
    216,
    222,
    221,
    215,
    173,
    208,
    196,
    205,
    167,
    77,
    88,
    0,
    223,
    224,
    210,
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
    180};

static const yytype_int16 yycheck[] = {52,
    4,
    4,
    94,
    16,
    164,
    165,
    5,
    112,
    35,
    25,
    23,
    66,
    4,
    118,
    4,
    30,
    44,
    45,
    17,
    89,
    90,
    29,
    35,
    31,
    32,
    33,
    54,
    43,
    23,
    13,
    14,
    84,
    85,
    86,
    87,
    23,
    42,
    64,
    65,
    131,
    67,
    201,
    46,
    135,
    39,
    3,
    34,
    62,
    36,
    70,
    71,
    64,
    65,
    66,
    67,
    40,
    69,
    70,
    68,
    69,
    70,
    71,
    115,
    66,
    54,
    68,
    69,
    70,
    71,
    68,
    69,
    70,
    71,
    178,
    66,
    79,
    66,
    66,
    148,
    23,
    24,
    12,
    12,
    14,
    14,
    34,
    23,
    36,
    44,
    45,
    66,
    35,
    184,
    185,
    49,
    24,
    25,
    0,
    35,
    24,
    25,
    66,
    66,
    66,
    66,
    109,
    42,
    42,
    46,
    66,
    163,
    164,
    165,
    66,
    56,
    23,
    50,
    24,
    24,
    47,
    64,
    65,
    66,
    67,
    47,
    69,
    70,
    64,
    65,
    66,
    67,
    25,
    69,
    70,
    66,
    24,
    41,
    23,
    56,
    66,
    66,
    43,
    66,
    7,
    8,
    67,
    66,
    66,
    201,
    66,
    203,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    40,
    23,
    12,
    26,
    27,
    28,
    30,
    25,
    220,
    55,
    34,
    25,
    25,
    24,
    37,
    38,
    66,
    11,
    23,
    34,
    52,
    64,
    66,
    46,
    25,
    48,
    35,
    24,
    51,
    6,
    47,
    24,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    44,
    53,
    25,
    18,
    68,
    69,
    70,
    71,
    56,
    55,
    66,
    206,
    144,
    199,
    173,
    185,
    136,
    46,
    56,
    -1,
    220,
    222,
    202,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    148};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] = {0,
    7,
    8,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    26,
    27,
    28,
    37,
    38,
    46,
    48,
    51,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    88,
    89,
    95,
    100,
    101,
    104,
    105,
    122,
    123,
    124,
    12,
    14,
    12,
    14,
    23,
    35,
    64,
    65,
    66,
    67,
    69,
    70,
    98,
    106,
    107,
    109,
    110,
    111,
    106,
    66,
    13,
    14,
    40,
    42,
    66,
    66,
    49,
    75,
    0,
    3,
    125,
    66,
    66,
    66,
    66,
    104,
    106,
    23,
    39,
    107,
    4,
    66,
    68,
    69,
    70,
    71,
    108,
    42,
    42,
    66,
    66,
    46,
    56,
    50,
    23,
    47,
    47,
    24,
    24,
    24,
    106,
    66,
    66,
    107,
    107,
    107,
    107,
    25,
    66,
    112,
    113,
    112,
    41,
    43,
    115,
    66,
    102,
    103,
    98,
    67,
    66,
    91,
    66,
    66,
    24,
    106,
    54,
    108,
    115,
    23,
    96,
    107,
    116,
    56,
    25,
    115,
    40,
    29,
    31,
    32,
    33,
    94,
    25,
    90,
    23,
    55,
    25,
    121,
    97,
    98,
    25,
    30,
    34,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    117,
    44,
    45,
    98,
    103,
    12,
    23,
    34,
    36,
    92,
    91,
    24,
    66,
    87,
    112,
    114,
    112,
    113,
    11,
    118,
    24,
    25,
    23,
    30,
    62,
    34,
    107,
    116,
    116,
    66,
    64,
    93,
    35,
    90,
    52,
    99,
    25,
    24,
    47,
    115,
    6,
    98,
    97,
    24,
    53,
    87,
    116,
    121,
    107,
    119,
    120,
    24,
    92,
    56,
    54,
    5,
    17,
    25,
    66,
    55,
    119,
    114};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] = {0,
    73,
    74,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    75,
    76,
    77,
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
    87,
    88,
    89,
    90,
    90,
    91,
    91,
    92,
    92,
    92,
    93,
    94,
    94,
    94,
    94,
    95,
    96,
    96,
    97,
    97,
    98,
    98,
    98,
    98,
    99,
    99,
    100,
    101,
    102,
    102,
    103,
    104,
    104,
    105,
    106,
    106,
    107,
    107,
    107,
    107,
    107,
    107,
    107,
    107,
    107,
    107,
    107,
    108,
    108,
    108,
    109,
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
    116,
    116,
    116,
    117,
    117,
    117,
    117,
    117,
    117,
    117,
    117,
    117,
    117,
    117,
    117,
    118,
    118,
    119,
    119,
    120,
    120,
    120,
    121,
    122,
    123,
    124,
    125,
    125};

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
    3,
    2,
    2,
    4,
    8,
    1,
    3,
    5,
    8,
    0,
    3,
    6,
    3,
    2,
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
    7,
    9,
    2,
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
    1,
    1,
    0,
    1,
    2,
    4,
    3,
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
    0,
    3,
    1,
    3,
    1,
    2,
    2,
    0,
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
#line 223 "yacc_sql.y"
    {
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
#line 1811 "yacc_sql.cpp"
    break;

    case 24: /* exit_stmt: EXIT  */
#line 254 "yacc_sql.y"
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1820 "yacc_sql.cpp"
    break;

    case 25: /* help_stmt: HELP  */
#line 260 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1828 "yacc_sql.cpp"
    break;

    case 26: /* sync_stmt: SYNC  */
#line 265 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1836 "yacc_sql.cpp"
    break;

    case 27: /* begin_stmt: TRX_BEGIN  */
#line 271 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1844 "yacc_sql.cpp"
    break;

    case 28: /* commit_stmt: TRX_COMMIT  */
#line 277 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1852 "yacc_sql.cpp"
    break;

    case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 283 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1860 "yacc_sql.cpp"
    break;

    case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 289 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1870 "yacc_sql.cpp"
    break;

    case 31: /* show_tables_stmt: SHOW TABLES  */
#line 296 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1878 "yacc_sql.cpp"
    break;

    case 32: /* desc_table_stmt: DESC ID  */
#line 302 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1888 "yacc_sql.cpp"
    break;

    case 33: /* show_index_stmt: SHOW INDEX FROM relation  */
#line 311 "yacc_sql.y"
    {
      (yyval.sql_node)             = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = (yyval.sql_node)->show_index;
      show_index.relation_name     = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1899 "yacc_sql.cpp"
    break;

    case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE attr_list RBRACE  */
#line 321 "yacc_sql.y"
    {
      (yyval.sql_node)                 = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name          = (yyvsp[-5].string);
      create_index.relation_name       = (yyvsp[-3].string);
      create_index.attribute_name.swap(*(yyvsp[-1].index_attr_list));  // $7 是 vector<string> 类型
      delete (yyvsp[-1].index_attr_list);                              // 释放指针
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

    case 35: /* attr_list: ID  */
#line 335 "yacc_sql.y"
    {
      (yyval.index_attr_list) = new std::vector<std::string>;    // 创建一个新的 vector
      (yyval.index_attr_list)->emplace_back((yyvsp[0].string));  // 将列名加入 vector
      free((yyvsp[0].string));
    }
#line 1924 "yacc_sql.cpp"
    break;

    case 36: /* attr_list: ID COMMA attr_list  */
#line 341 "yacc_sql.y"
    {
      (yyval.index_attr_list) = (yyvsp[0].index_attr_list);  // 使用现有的 vector
      (yyval.index_attr_list)
          ->emplace((yyval.index_attr_list)->begin(), (yyvsp[-2].string));  // 将新列名加入 vector 开头
      free((yyvsp[-2].string));
    }
#line 1934 "yacc_sql.cpp"
    break;

    case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 350 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name    = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1946 "yacc_sql.cpp"
    break;

    case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 360 "yacc_sql.y"
    {
      (yyval.sql_node)                 = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name       = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 1971 "yacc_sql.cpp"
    break;

    case 39: /* attr_def_list: %empty  */
#line 383 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1979 "yacc_sql.cpp"
    break;

    case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 387 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1993 "yacc_sql.cpp"
    break;

    case 41: /* attr_def: ID type LBRACE number RBRACE nullable_constraint  */
#line 400 "yacc_sql.y"
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
#line 2009 "yacc_sql.cpp"
    break;

    case 42: /* attr_def: ID type nullable_constraint  */
#line 412 "yacc_sql.y"
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
      } else {
        ASSERT(false, "$$->type is invalid.");
      }
      (yyval.attr_info)->nullable = (yyvsp[0].nullable_info);  // 处理NULL/NOT NULL标记
      if ((yyval.attr_info)->nullable) {
        (yyval.attr_info)->length++;
      }
      free((yyvsp[-2].string));
    }
#line 2035 "yacc_sql.cpp"
    break;

    case 43: /* nullable_constraint: NOT NULL_T  */
#line 437 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // NOT NULL 对应的可空性为 false
    }
#line 2043 "yacc_sql.cpp"
    break;

    case 44: /* nullable_constraint: NULLABLE  */
#line 441 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULLABLE 对应的可空性为 true
    }
#line 2051 "yacc_sql.cpp"
    break;

    case 45: /* nullable_constraint: %empty  */
#line 445 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // 默认情况为 NOT NULL
    }
#line 2059 "yacc_sql.cpp"
    break;

    case 46: /* number: NUMBER  */
#line 451 "yacc_sql.y"
    {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2065 "yacc_sql.cpp"
    break;

    case 47: /* type: INT_T  */
#line 454 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::INTS);
    }
#line 2071 "yacc_sql.cpp"
    break;

    case 48: /* type: STRING_T  */
#line 455 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::CHARS);
    }
#line 2077 "yacc_sql.cpp"
    break;

    case 49: /* type: FLOAT_T  */
#line 456 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::FLOATS);
    }
#line 2083 "yacc_sql.cpp"
    break;

    case 50: /* type: DATE_T  */
#line 457 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::DATES);
    }
#line 2089 "yacc_sql.cpp"
    break;

    case 51: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 462 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-2].string));
    }
#line 2103 "yacc_sql.cpp"
    break;

    case 52: /* values_list: LBRACE value_list RBRACE  */
#line 475 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2113 "yacc_sql.cpp"
    break;

    case 53: /* values_list: values_list COMMA LBRACE value_list RBRACE  */
#line 481 "yacc_sql.y"
    {
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2122 "yacc_sql.cpp"
    break;

    case 54: /* value_list: value  */
#line 488 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2132 "yacc_sql.cpp"
    break;

    case 55: /* value_list: value_list COMMA value  */
#line 494 "yacc_sql.y"
    {
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2141 "yacc_sql.cpp"
    break;

    case 56: /* value: NUMBER  */
#line 501 "yacc_sql.y"
    {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc)       = (yylsp[0]);
    }
#line 2150 "yacc_sql.cpp"
    break;

    case 57: /* value: FLOAT  */
#line 505 "yacc_sql.y"
    {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc)       = (yylsp[0]);
    }
#line 2159 "yacc_sql.cpp"
    break;

    case 58: /* value: SSS  */
#line 509 "yacc_sql.y"
    {
      char *tmp     = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2170 "yacc_sql.cpp"
    break;

    case 59: /* value: NULL_T  */
#line 515 "yacc_sql.y"
    {
      (yyval.value) = new Value(NullValue());
    }
#line 2178 "yacc_sql.cpp"
    break;

    case 60: /* storage_format: %empty  */
#line 522 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2186 "yacc_sql.cpp"
    break;

    case 61: /* storage_format: STORAGE FORMAT EQ ID  */
#line 526 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2194 "yacc_sql.cpp"
    break;

    case 62: /* delete_stmt: DELETE FROM ID where  */
#line 533 "yacc_sql.y"
    {
      (yyval.sql_node)                         = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.condition = std::unique_ptr<Expression>((yyvsp[0].expression));
      }
      free((yyvsp[-1].string));
    }
#line 2207 "yacc_sql.cpp"
    break;

    case 63: /* update_stmt: UPDATE ID SET setClauses where  */
#line 545 "yacc_sql.y"
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
#line 2222 "yacc_sql.cpp"
    break;

    case 64: /* setClauses: setClause  */
#line 559 "yacc_sql.y"
    {
      (yyval.set_clauses) = new std::vector<SetClauseSqlNode>;
      (yyval.set_clauses)->emplace_back(*(yyvsp[0].set_clause));
      delete (yyvsp[0].set_clause);
    }
#line 2232 "yacc_sql.cpp"
    break;

    case 65: /* setClauses: setClauses COMMA setClause  */
#line 565 "yacc_sql.y"
    {
      (yyval.set_clauses)->emplace_back(*(yyvsp[0].set_clause));
      delete (yyvsp[0].set_clause);
    }
#line 2241 "yacc_sql.cpp"
    break;

    case 66: /* setClause: ID EQ value  */
#line 573 "yacc_sql.y"
    {
      (yyval.set_clause)             = new SetClauseSqlNode;
      (yyval.set_clause)->field_name = (yyvsp[-2].string);
      (yyval.set_clause)->value      = std::move(*(yyvsp[0].value));
      free((yyvsp[-2].string));
    }
#line 2252 "yacc_sql.cpp"
    break;

    case 67: /* select_stmt: SELECT expression_list FROM rel_list where group_by opt_order_by  */
#line 583 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }

      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }

      (yyval.sql_node)->selection.conditions = nullptr;

      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = std::unique_ptr<Expression>((yyvsp[-2].expression));
      }

      if ((yyvsp[-1].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }

      if ((yyvsp[0].orderby_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].orderby_list));
        delete (yyvsp[0].orderby_list);
      }
    }
#line 2285 "yacc_sql.cpp"
    break;

    case 68: /* select_stmt: SELECT expression_list FROM relation INNER JOIN joinClauses where group_by  */
#line 612 "yacc_sql.y"
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
#line 2319 "yacc_sql.cpp"
    break;

    case 69: /* calc_stmt: CALC expression_list  */
#line 645 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2329 "yacc_sql.cpp"
    break;

    case 70: /* expression_list: expression alias  */
#line 654 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_name((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2342 "yacc_sql.cpp"
    break;

    case 71: /* expression_list: expression alias COMMA expression_list  */
#line 663 "yacc_sql.y"
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
#line 2359 "yacc_sql.cpp"
    break;

    case 72: /* expression: expression '+' expression  */
#line 678 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2367 "yacc_sql.cpp"
    break;

    case 73: /* expression: expression '-' expression  */
#line 681 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2375 "yacc_sql.cpp"
    break;

    case 74: /* expression: expression '*' expression  */
#line 684 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2383 "yacc_sql.cpp"
    break;

    case 75: /* expression: expression '/' expression  */
#line 687 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2391 "yacc_sql.cpp"
    break;

    case 76: /* expression: LBRACE expression_list RBRACE  */
#line 690 "yacc_sql.y"
    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().get();
      } else {
        (yyval.expression) = new ListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2405 "yacc_sql.cpp"
    break;

    case 77: /* expression: '-' expression  */
#line 699 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2413 "yacc_sql.cpp"
    break;

    case 78: /* expression: value  */
#line 702 "yacc_sql.y"
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2423 "yacc_sql.cpp"
    break;

    case 79: /* expression: rel_attr  */
#line 707 "yacc_sql.y"
    {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression)   = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2434 "yacc_sql.cpp"
    break;

    case 80: /* expression: '*'  */
#line 713 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr();
    }
#line 2442 "yacc_sql.cpp"
    break;

    case 81: /* expression: aggr_func_expr  */
#line 716 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // AggrFuncExpr
    }
#line 2450 "yacc_sql.cpp"
    break;

    case 82: /* expression: sub_query_expr  */
#line 719 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // SubQueryExpr
    }
#line 2458 "yacc_sql.cpp"
    break;

    case 83: /* alias: %empty  */
#line 726 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2466 "yacc_sql.cpp"
    break;

    case 84: /* alias: ID  */
#line 729 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2474 "yacc_sql.cpp"
    break;

    case 85: /* alias: AS ID  */
#line 732 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2482 "yacc_sql.cpp"
    break;

    case 86: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 738 "yacc_sql.y"
    {
      if ((*(yyvsp[-1].expression_list)).size() != 1) {
        (yyval.expression) = new UnboundAggregateExpr("max", new StarExpr());
      } else {
        (yyval.expression) = new UnboundAggregateExpr((yyvsp[-3].string), std::move((*(yyvsp[-1].expression_list))[0]));
      }
    }
#line 2494 "yacc_sql.cpp"
    break;

    case 87: /* aggr_func_expr: ID LBRACE RBRACE  */
#line 746 "yacc_sql.y"
    {
      (yyval.expression) = new UnboundAggregateExpr("max", new StarExpr());
    }
#line 2502 "yacc_sql.cpp"
    break;

    case 88: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 753 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2510 "yacc_sql.cpp"
    break;

    case 89: /* rel_attr: ID  */
#line 759 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2520 "yacc_sql.cpp"
    break;

    case 90: /* rel_attr: ID DOT ID  */
#line 764 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2532 "yacc_sql.cpp"
    break;

    case 91: /* relation: ID  */
#line 774 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2540 "yacc_sql.cpp"
    break;

    case 92: /* rel_list: relation alias  */
#line 780 "yacc_sql.y"
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
#line 2555 "yacc_sql.cpp"
    break;

    case 93: /* rel_list: relation alias COMMA rel_list  */
#line 790 "yacc_sql.y"
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
#line 2574 "yacc_sql.cpp"
    break;

    case 94: /* joinClauses: relation ON condition  */
#line 808 "yacc_sql.y"
    {
      (yyval.join_clauses) = new JoinSqlNode;
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-2].string));
      (yyval.join_clauses)->conditions = std::unique_ptr<Expression>((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2585 "yacc_sql.cpp"
    break;

    case 95: /* joinClauses: relation ON condition INNER JOIN joinClauses  */
#line 815 "yacc_sql.y"
    {
      (yyval.join_clauses) = (yyvsp[0].join_clauses);
      (yyval.join_clauses)->relations.emplace_back((yyvsp[-5].string));
      auto ptr = (yyval.join_clauses)->conditions.release();
      (yyval.join_clauses)->conditions =
          std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, (yyvsp[-3].expression));
      free((yyvsp[-5].string));
    }
#line 2597 "yacc_sql.cpp"
    break;

    case 96: /* where: %empty  */
#line 826 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2605 "yacc_sql.cpp"
    break;

    case 97: /* where: WHERE condition  */
#line 829 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2613 "yacc_sql.cpp"
    break;

    case 98: /* condition: expression comp_op expression  */
#line 836 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2621 "yacc_sql.cpp"
    break;

    case 99: /* condition: condition AND condition  */
#line 840 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2629 "yacc_sql.cpp"
    break;

    case 100: /* condition: condition OR condition  */
#line 844 "yacc_sql.y"
    {
      (yyval.expression) =
          new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2637 "yacc_sql.cpp"
    break;

    case 101: /* comp_op: EQ  */
#line 850 "yacc_sql.y"
    {
      (yyval.comp) = EQUAL_TO;
    }
#line 2643 "yacc_sql.cpp"
    break;

    case 102: /* comp_op: LT  */
#line 851 "yacc_sql.y"
    {
      (yyval.comp) = LESS_THAN;
    }
#line 2649 "yacc_sql.cpp"
    break;

    case 103: /* comp_op: GT  */
#line 852 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_THAN;
    }
#line 2655 "yacc_sql.cpp"
    break;

    case 104: /* comp_op: LE  */
#line 853 "yacc_sql.y"
    {
      (yyval.comp) = LESS_EQUAL;
    }
#line 2661 "yacc_sql.cpp"
    break;

    case 105: /* comp_op: GE  */
#line 854 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_EQUAL;
    }
#line 2667 "yacc_sql.cpp"
    break;

    case 106: /* comp_op: NE  */
#line 855 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EQUAL;
    }
#line 2673 "yacc_sql.cpp"
    break;

    case 107: /* comp_op: IS  */
#line 856 "yacc_sql.y"
    {
      (yyval.comp) = OP_IS;
    }
#line 2679 "yacc_sql.cpp"
    break;

    case 108: /* comp_op: IS NOT  */
#line 857 "yacc_sql.y"
    {
      (yyval.comp) = OP_IS_NOT;
    }
#line 2685 "yacc_sql.cpp"
    break;

    case 109: /* comp_op: LIKE  */
#line 858 "yacc_sql.y"
    {
      (yyval.comp) = LIKE_OP;
    }
#line 2691 "yacc_sql.cpp"
    break;

    case 110: /* comp_op: NOT LIKE  */
#line 859 "yacc_sql.y"
    {
      (yyval.comp) = NOT_LIKE_OP;
    }
#line 2697 "yacc_sql.cpp"
    break;

    case 111: /* comp_op: IN  */
#line 860 "yacc_sql.y"
    {
      (yyval.comp) = IN_OP;
    }
#line 2703 "yacc_sql.cpp"
    break;

    case 112: /* comp_op: NOT IN  */
#line 861 "yacc_sql.y"
    {
      (yyval.comp) = NOT_IN_OP;
    }
#line 2709 "yacc_sql.cpp"
    break;

    case 113: /* opt_order_by: %empty  */
#line 866 "yacc_sql.y"
    {
      (yyval.orderby_list) = nullptr;
    }
#line 2717 "yacc_sql.cpp"
    break;

    case 114: /* opt_order_by: ORDER BY sort_list  */
#line 870 "yacc_sql.y"
    {
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
      std::reverse((yyval.orderby_list)->begin(), (yyval.orderby_list)->end());
    }
#line 2726 "yacc_sql.cpp"
    break;

    case 115: /* sort_list: sort_unit  */
#line 878 "yacc_sql.y"
    {
      (yyval.orderby_list) = new std::vector<OrderBySqlNode>;
      (yyval.orderby_list)->emplace_back(std::move(*(yyvsp[0].orderby_unit)));
    }
#line 2735 "yacc_sql.cpp"
    break;

    case 116: /* sort_list: sort_unit COMMA sort_list  */
#line 883 "yacc_sql.y"
    {
      (yyvsp[0].orderby_list)->emplace_back(std::move(*(yyvsp[-2].orderby_unit)));
      (yyval.orderby_list) = (yyvsp[0].orderby_list);
    }
#line 2744 "yacc_sql.cpp"
    break;

    case 117: /* sort_unit: expression  */
#line 891 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2754 "yacc_sql.cpp"
    break;

    case 118: /* sort_unit: expression DESC  */
#line 897 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = false;
    }
#line 2764 "yacc_sql.cpp"
    break;

    case 119: /* sort_unit: expression ASC  */
#line 903 "yacc_sql.y"
    {
      (yyval.orderby_unit)         = new OrderBySqlNode();  // 默认是升序
      (yyval.orderby_unit)->expr   = std::unique_ptr<Expression>((yyvsp[-1].expression));
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2774 "yacc_sql.cpp"
    break;

    case 120: /* group_by: %empty  */
#line 912 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2782 "yacc_sql.cpp"
    break;

    case 121: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 918 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node)                          = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name     = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2796 "yacc_sql.cpp"
    break;

    case 122: /* explain_stmt: EXPLAIN command_wrapper  */
#line 931 "yacc_sql.y"
    {
      (yyval.sql_node)                   = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2805 "yacc_sql.cpp"
    break;

    case 123: /* set_variable_stmt: SET ID EQ value  */
#line 939 "yacc_sql.y"
    {
      (yyval.sql_node)                     = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2817 "yacc_sql.cpp"
    break;

#line 2821 "yacc_sql.cpp"

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

#line 951 "yacc_sql.y"

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
