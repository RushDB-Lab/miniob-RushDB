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
  YYSYMBOL_BY                  = 5,   /* BY  */
  YYSYMBOL_CREATE              = 6,   /* CREATE  */
  YYSYMBOL_DROP                = 7,   /* DROP  */
  YYSYMBOL_GROUP               = 8,   /* GROUP  */
  YYSYMBOL_TABLE               = 9,   /* TABLE  */
  YYSYMBOL_TABLES              = 10,  /* TABLES  */
  YYSYMBOL_INDEX               = 11,  /* INDEX  */
  YYSYMBOL_CALC                = 12,  /* CALC  */
  YYSYMBOL_SELECT              = 13,  /* SELECT  */
  YYSYMBOL_DESC                = 14,  /* DESC  */
  YYSYMBOL_SHOW                = 15,  /* SHOW  */
  YYSYMBOL_SYNC                = 16,  /* SYNC  */
  YYSYMBOL_INSERT              = 17,  /* INSERT  */
  YYSYMBOL_DELETE              = 18,  /* DELETE  */
  YYSYMBOL_UPDATE              = 19,  /* UPDATE  */
  YYSYMBOL_LBRACE              = 20,  /* LBRACE  */
  YYSYMBOL_RBRACE              = 21,  /* RBRACE  */
  YYSYMBOL_COMMA               = 22,  /* COMMA  */
  YYSYMBOL_TRX_BEGIN           = 23,  /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT          = 24,  /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK        = 25,  /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T               = 26,  /* INT_T  */
  YYSYMBOL_STRING_T            = 27,  /* STRING_T  */
  YYSYMBOL_FLOAT_T             = 28,  /* FLOAT_T  */
  YYSYMBOL_DATE_T              = 29,  /* DATE_T  */
  YYSYMBOL_NOT                 = 30,  /* NOT  */
  YYSYMBOL_NULL_T              = 31,  /* NULL_T  */
  YYSYMBOL_NULLABLE            = 32,  /* NULLABLE  */
  YYSYMBOL_HELP                = 33,  /* HELP  */
  YYSYMBOL_EXIT                = 34,  /* EXIT  */
  YYSYMBOL_DOT                 = 35,  /* DOT  */
  YYSYMBOL_INTO                = 36,  /* INTO  */
  YYSYMBOL_VALUES              = 37,  /* VALUES  */
  YYSYMBOL_FROM                = 38,  /* FROM  */
  YYSYMBOL_WHERE               = 39,  /* WHERE  */
  YYSYMBOL_AND                 = 40,  /* AND  */
  YYSYMBOL_SET                 = 41,  /* SET  */
  YYSYMBOL_ON                  = 42,  /* ON  */
  YYSYMBOL_LOAD                = 43,  /* LOAD  */
  YYSYMBOL_DATA                = 44,  /* DATA  */
  YYSYMBOL_INFILE              = 45,  /* INFILE  */
  YYSYMBOL_EXPLAIN             = 46,  /* EXPLAIN  */
  YYSYMBOL_STORAGE             = 47,  /* STORAGE  */
  YYSYMBOL_FORMAT              = 48,  /* FORMAT  */
  YYSYMBOL_INNER               = 49,  /* INNER  */
  YYSYMBOL_JOIN                = 50,  /* JOIN  */
  YYSYMBOL_EQ                  = 51,  /* EQ  */
  YYSYMBOL_LT                  = 52,  /* LT  */
  YYSYMBOL_GT                  = 53,  /* GT  */
  YYSYMBOL_LE                  = 54,  /* LE  */
  YYSYMBOL_GE                  = 55,  /* GE  */
  YYSYMBOL_NE                  = 56,  /* NE  */
  YYSYMBOL_LIKE                = 57,  /* LIKE  */
  YYSYMBOL_IS                  = 58,  /* IS  */
  YYSYMBOL_NUMBER              = 59,  /* NUMBER  */
  YYSYMBOL_FLOAT               = 60,  /* FLOAT  */
  YYSYMBOL_ID                  = 61,  /* ID  */
  YYSYMBOL_SSS                 = 62,  /* SSS  */
  YYSYMBOL_63_                 = 63,  /* '+'  */
  YYSYMBOL_64_                 = 64,  /* '-'  */
  YYSYMBOL_65_                 = 65,  /* '*'  */
  YYSYMBOL_66_                 = 66,  /* '/'  */
  YYSYMBOL_UMINUS              = 67,  /* UMINUS  */
  YYSYMBOL_YYACCEPT            = 68,  /* $accept  */
  YYSYMBOL_commands            = 69,  /* commands  */
  YYSYMBOL_command_wrapper     = 70,  /* command_wrapper  */
  YYSYMBOL_exit_stmt           = 71,  /* exit_stmt  */
  YYSYMBOL_help_stmt           = 72,  /* help_stmt  */
  YYSYMBOL_sync_stmt           = 73,  /* sync_stmt  */
  YYSYMBOL_begin_stmt          = 74,  /* begin_stmt  */
  YYSYMBOL_commit_stmt         = 75,  /* commit_stmt  */
  YYSYMBOL_rollback_stmt       = 76,  /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt     = 77,  /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt    = 78,  /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt     = 79,  /* desc_table_stmt  */
  YYSYMBOL_show_index_stmt     = 80,  /* show_index_stmt  */
  YYSYMBOL_create_index_stmt   = 81,  /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt     = 82,  /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt   = 83,  /* create_table_stmt  */
  YYSYMBOL_attr_def_list       = 84,  /* attr_def_list  */
  YYSYMBOL_attr_def            = 85,  /* attr_def  */
  YYSYMBOL_nullable_constraint = 86,  /* nullable_constraint  */
  YYSYMBOL_number              = 87,  /* number  */
  YYSYMBOL_type                = 88,  /* type  */
  YYSYMBOL_insert_stmt         = 89,  /* insert_stmt  */
  YYSYMBOL_values_list         = 90,  /* values_list  */
  YYSYMBOL_value_list          = 91,  /* value_list  */
  YYSYMBOL_value               = 92,  /* value  */
  YYSYMBOL_storage_format      = 93,  /* storage_format  */
  YYSYMBOL_delete_stmt         = 94,  /* delete_stmt  */
  YYSYMBOL_update_stmt         = 95,  /* update_stmt  */
  YYSYMBOL_setClauses          = 96,  /* setClauses  */
  YYSYMBOL_setClause           = 97,  /* setClause  */
  YYSYMBOL_select_stmt         = 98,  /* select_stmt  */
  YYSYMBOL_calc_stmt           = 99,  /* calc_stmt  */
  YYSYMBOL_expression_list     = 100, /* expression_list  */
  YYSYMBOL_expression          = 101, /* expression  */
  YYSYMBOL_alias               = 102, /* alias  */
  YYSYMBOL_aggr_func_expr      = 103, /* aggr_func_expr  */
  YYSYMBOL_rel_attr            = 104, /* rel_attr  */
  YYSYMBOL_relation            = 105, /* relation  */
  YYSYMBOL_rel_list            = 106, /* rel_list  */
  YYSYMBOL_joinClause          = 107, /* joinClause  */
  YYSYMBOL_joinClauses         = 108, /* joinClauses  */
  YYSYMBOL_where               = 109, /* where  */
  YYSYMBOL_condition_list      = 110, /* condition_list  */
  YYSYMBOL_condition           = 111, /* condition  */
  YYSYMBOL_comp_op             = 112, /* comp_op  */
  YYSYMBOL_group_by            = 113, /* group_by  */
  YYSYMBOL_load_data_stmt      = 114, /* load_data_stmt  */
  YYSYMBOL_explain_stmt        = 115, /* explain_stmt  */
  YYSYMBOL_set_variable_stmt   = 116, /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon       = 117  /* opt_semicolon  */
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
#define YYFINAL 69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 199

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 50
/* YYNRULES -- Number of rules.  */
#define YYNRULES 117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 213

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 318

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
    65,
    63,
    2,
    64,
    2,
    66,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
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
    67};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] = {0,
    212,
    212,
    220,
    221,
    222,
    223,
    224,
    225,
    226,
    227,
    228,
    229,
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
    244,
    250,
    255,
    261,
    267,
    273,
    279,
    286,
    292,
    300,
    310,
    324,
    334,
    358,
    361,
    374,
    386,
    411,
    415,
    420,
    426,
    429,
    430,
    431,
    432,
    436,
    449,
    455,
    462,
    468,
    476,
    480,
    484,
    490,
    497,
    500,
    507,
    520,
    535,
    541,
    549,
    559,
    582,
    618,
    627,
    636,
    651,
    654,
    657,
    660,
    663,
    667,
    670,
    675,
    681,
    684,
    691,
    694,
    697,
    702,
    710,
    716,
    721,
    731,
    737,
    747,
    765,
    776,
    782,
    792,
    795,
    801,
    804,
    809,
    816,
    828,
    840,
    852,
    867,
    868,
    869,
    870,
    871,
    872,
    873,
    874,
    875,
    876,
    882,
    887,
    900,
    908,
    918,
    919};
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
    "BY",
    "CREATE",
    "DROP",
    "GROUP",
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
    "rel_attr",
    "relation",
    "rel_list",
    "joinClause",
    "joinClauses",
    "where",
    "condition_list",
    "condition",
    "comp_op",
    "group_by",
    "load_data_stmt",
    "explain_stmt",
    "set_variable_stmt",
    "opt_semicolon",
    YY_NULLPTR};

static const char *yysymbol_name(yysymbol_kind_t yysymbol) { return yytname[yysymbol]; }
#endif

#define YYPACT_NINF (-149)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {98,
    6,
    13,
    37,
    37,
    -51,
    8,
    -149,
    -13,
    -8,
    -26,
    -149,
    -149,
    -149,
    -149,
    -149,
    -19,
    7,
    98,
    59,
    66,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    14,
    19,
    26,
    34,
    37,
    -149,
    -149,
    -149,
    -7,
    -149,
    37,
    -149,
    -149,
    -149,
    -1,
    -149,
    -149,
    62,
    -149,
    -149,
    80,
    58,
    64,
    79,
    75,
    82,
    -149,
    -149,
    -149,
    -149,
    108,
    88,
    -149,
    91,
    20,
    17,
    68,
    -149,
    73,
    -149,
    37,
    37,
    37,
    37,
    118,
    81,
    81,
    106,
    114,
    93,
    -4,
    95,
    97,
    99,
    100,
    -149,
    -149,
    134,
    -149,
    -149,
    -40,
    -40,
    -149,
    -149,
    37,
    -149,
    0,
    114,
    -149,
    136,
    76,
    -149,
    111,
    -10,
    -149,
    -149,
    123,
    65,
    141,
    144,
    -149,
    -149,
    -149,
    115,
    145,
    -149,
    -4,
    146,
    131,
    94,
    94,
    -149,
    129,
    -4,
    93,
    -149,
    161,
    -149,
    -149,
    -149,
    -149,
    1,
    97,
    150,
    112,
    81,
    81,
    -149,
    18,
    -149,
    152,
    117,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    147,
    76,
    76,
    76,
    -149,
    -149,
    119,
    116,
    148,
    -149,
    -149,
    141,
    135,
    155,
    139,
    137,
    114,
    5,
    -149,
    -149,
    -4,
    -4,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    157,
    -149,
    -149,
    140,
    -149,
    -149,
    76,
    133,
    -149,
    -149,
    87,
    2,
    138,
    -149,
    81,
    -149,
    -149,
    -149,
    124,
    -149,
    -149};

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
    116,
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
    57,
    54,
    55,
    85,
    56,
    0,
    78,
    76,
    67,
    80,
    79,
    77,
    0,
    32,
    31,
    0,
    0,
    0,
    0,
    0,
    0,
    114,
    1,
    117,
    2,
    0,
    0,
    30,
    0,
    0,
    0,
    0,
    75,
    0,
    81,
    0,
    0,
    0,
    0,
    68,
    0,
    0,
    0,
    93,
    0,
    0,
    0,
    0,
    0,
    0,
    74,
    84,
    0,
    86,
    82,
    70,
    71,
    72,
    73,
    0,
    87,
    80,
    93,
    33,
    0,
    95,
    60,
    0,
    93,
    62,
    115,
    0,
    0,
    37,
    0,
    35,
    83,
    69,
    0,
    88,
    112,
    0,
    49,
    85,
    0,
    0,
    94,
    96,
    0,
    0,
    61,
    0,
    45,
    46,
    47,
    48,
    43,
    0,
    0,
    0,
    0,
    0,
    65,
    0,
    52,
    0,
    0,
    102,
    103,
    104,
    105,
    106,
    107,
    110,
    108,
    0,
    0,
    95,
    64,
    63,
    0,
    0,
    0,
    42,
    40,
    37,
    58,
    0,
    0,
    91,
    93,
    80,
    89,
    50,
    0,
    0,
    111,
    109,
    99,
    101,
    98,
    100,
    97,
    113,
    44,
    0,
    41,
    38,
    0,
    36,
    34,
    95,
    0,
    112,
    53,
    0,
    43,
    0,
    90,
    0,
    66,
    51,
    39,
    0,
    92,
    59};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-149,
    -149,
    166,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    -149,
    15,
    46,
    -12,
    -149,
    -149,
    -149,
    -149,
    10,
    -92,
    -149,
    -149,
    -149,
    -149,
    57,
    -149,
    -149,
    -3,
    -38,
    142,
    -149,
    -110,
    -81,
    47,
    -149,
    -9,
    -104,
    -148,
    -149,
    67,
    -6,
    -149,
    -149,
    -149,
    -149};

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
    32,
    33,
    145,
    120,
    171,
    192,
    143,
    34,
    129,
    150,
    54,
    196,
    35,
    36,
    115,
    116,
    37,
    38,
    55,
    56,
    126,
    57,
    58,
    175,
    109,
    176,
    177,
    113,
    133,
    134,
    162,
    149,
    39,
    40,
    41,
    71};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] = {117,
    59,
    132,
    80,
    80,
    127,
    108,
    110,
    76,
    80,
    60,
    137,
    136,
    77,
    79,
    42,
    189,
    43,
    61,
    62,
    131,
    168,
    44,
    63,
    45,
    84,
    85,
    47,
    78,
    112,
    64,
    169,
    169,
    170,
    170,
    65,
    151,
    46,
    98,
    180,
    181,
    97,
    66,
    165,
    102,
    103,
    104,
    105,
    47,
    125,
    205,
    67,
    186,
    188,
    132,
    48,
    49,
    46,
    51,
    69,
    81,
    81,
    82,
    83,
    84,
    85,
    81,
    178,
    47,
    70,
    185,
    187,
    131,
    200,
    99,
    72,
    48,
    49,
    50,
    51,
    73,
    52,
    53,
    82,
    83,
    84,
    85,
    74,
    132,
    201,
    151,
    139,
    140,
    141,
    142,
    75,
    48,
    49,
    50,
    51,
    87,
    52,
    53,
    124,
    1,
    2,
    131,
    47,
    208,
    181,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    88,
    89,
    91,
    11,
    12,
    13,
    153,
    90,
    92,
    93,
    94,
    100,
    95,
    14,
    15,
    96,
    101,
    48,
    49,
    130,
    51,
    16,
    106,
    17,
    107,
    111,
    18,
    154,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    112,
    114,
    123,
    128,
    118,
    119,
    138,
    121,
    122,
    135,
    144,
    146,
    147,
    78,
    148,
    152,
    164,
    167,
    173,
    182,
    174,
    183,
    191,
    197,
    184,
    203,
    193,
    190,
    198,
    195,
    206,
    68,
    212,
    199,
    194,
    204,
    210,
    172,
    209,
    202,
    166,
    207,
    179,
    0,
    211,
    86,
    163};

static const yytype_int16 yycheck[] = {92,
    4,
    112,
    4,
    4,
    109,
    87,
    88,
    46,
    4,
    61,
    115,
    22,
    20,
    52,
    9,
    164,
    11,
    10,
    11,
    112,
    20,
    9,
    36,
    11,
    65,
    66,
    31,
    35,
    39,
    38,
    30,
    30,
    32,
    32,
    61,
    128,
    20,
    21,
    21,
    22,
    21,
    61,
    135,
    82,
    83,
    84,
    85,
    31,
    49,
    198,
    44,
    162,
    163,
    164,
    59,
    60,
    20,
    62,
    0,
    61,
    61,
    63,
    64,
    65,
    66,
    61,
    148,
    31,
    3,
    162,
    163,
    164,
    177,
    77,
    61,
    59,
    60,
    61,
    62,
    61,
    64,
    65,
    63,
    64,
    65,
    66,
    61,
    198,
    181,
    182,
    26,
    27,
    28,
    29,
    61,
    59,
    60,
    61,
    62,
    38,
    64,
    65,
    106,
    6,
    7,
    198,
    31,
    21,
    22,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    38,
    61,
    41,
    23,
    24,
    25,
    30,
    61,
    51,
    45,
    20,
    61,
    42,
    33,
    34,
    42,
    61,
    59,
    60,
    61,
    62,
    41,
    22,
    43,
    61,
    37,
    46,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    39,
    61,
    21,
    20,
    62,
    61,
    36,
    61,
    61,
    51,
    22,
    20,
    50,
    35,
    22,
    22,
    40,
    9,
    21,
    20,
    61,
    57,
    59,
    21,
    30,
    21,
    31,
    61,
    42,
    47,
    50,
    18,
    61,
    49,
    172,
    48,
    51,
    144,
    203,
    182,
    136,
    200,
    148,
    -1,
    206,
    56,
    132};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] = {0,
    6,
    7,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    23,
    24,
    25,
    33,
    34,
    41,
    43,
    46,
    69,
    70,
    71,
    72,
    73,
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
    89,
    94,
    95,
    98,
    99,
    114,
    115,
    116,
    9,
    11,
    9,
    11,
    20,
    31,
    59,
    60,
    61,
    62,
    64,
    65,
    92,
    100,
    101,
    103,
    104,
    100,
    61,
    10,
    11,
    36,
    38,
    61,
    61,
    44,
    70,
    0,
    3,
    117,
    61,
    61,
    61,
    61,
    101,
    20,
    35,
    101,
    4,
    61,
    63,
    64,
    65,
    66,
    102,
    38,
    38,
    61,
    61,
    41,
    51,
    45,
    20,
    42,
    42,
    21,
    21,
    100,
    61,
    61,
    101,
    101,
    101,
    101,
    22,
    61,
    105,
    106,
    105,
    37,
    39,
    109,
    61,
    96,
    97,
    92,
    62,
    61,
    85,
    61,
    61,
    21,
    100,
    49,
    102,
    109,
    20,
    90,
    61,
    92,
    104,
    110,
    111,
    51,
    22,
    109,
    36,
    26,
    27,
    28,
    29,
    88,
    22,
    84,
    20,
    50,
    22,
    113,
    91,
    92,
    22,
    30,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    112,
    112,
    40,
    92,
    97,
    9,
    20,
    30,
    32,
    86,
    85,
    21,
    61,
    105,
    107,
    108,
    105,
    106,
    21,
    22,
    20,
    57,
    30,
    92,
    104,
    92,
    104,
    110,
    61,
    59,
    87,
    31,
    84,
    47,
    93,
    21,
    42,
    49,
    109,
    92,
    91,
    21,
    48,
    110,
    50,
    113,
    21,
    86,
    51,
    108,
    61};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] = {0,
    68,
    69,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    70,
    71,
    72,
    73,
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
    84,
    85,
    85,
    86,
    86,
    86,
    87,
    88,
    88,
    88,
    88,
    89,
    90,
    90,
    91,
    91,
    92,
    92,
    92,
    92,
    93,
    93,
    94,
    95,
    96,
    96,
    97,
    98,
    98,
    99,
    100,
    100,
    101,
    101,
    101,
    101,
    101,
    101,
    101,
    101,
    101,
    101,
    102,
    102,
    102,
    103,
    103,
    104,
    104,
    105,
    106,
    106,
    107,
    108,
    108,
    109,
    109,
    110,
    110,
    110,
    111,
    111,
    111,
    111,
    112,
    112,
    112,
    112,
    112,
    112,
    112,
    112,
    112,
    112,
    113,
    114,
    115,
    116,
    117,
    117};

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
    6,
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
    1,
    4,
    0,
    2,
    0,
    1,
    3,
    3,
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
#line 213 "yacc_sql.y"
    {
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
#line 1785 "yacc_sql.cpp"
    break;

    case 24: /* exit_stmt: EXIT  */
#line 244 "yacc_sql.y"
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1794 "yacc_sql.cpp"
    break;

    case 25: /* help_stmt: HELP  */
#line 250 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1802 "yacc_sql.cpp"
    break;

    case 26: /* sync_stmt: SYNC  */
#line 255 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1810 "yacc_sql.cpp"
    break;

    case 27: /* begin_stmt: TRX_BEGIN  */
#line 261 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1818 "yacc_sql.cpp"
    break;

    case 28: /* commit_stmt: TRX_COMMIT  */
#line 267 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1826 "yacc_sql.cpp"
    break;

    case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 273 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1834 "yacc_sql.cpp"
    break;

    case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 279 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1844 "yacc_sql.cpp"
    break;

    case 31: /* show_tables_stmt: SHOW TABLES  */
#line 286 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1852 "yacc_sql.cpp"
    break;

    case 32: /* desc_table_stmt: DESC ID  */
#line 292 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1862 "yacc_sql.cpp"
    break;

    case 33: /* show_index_stmt: SHOW INDEX FROM relation  */
#line 301 "yacc_sql.y"
    {
      (yyval.sql_node)             = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = (yyval.sql_node)->show_index;
      show_index.relation_name     = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1873 "yacc_sql.cpp"
    break;

    case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID RBRACE  */
#line 311 "yacc_sql.y"
    {
      (yyval.sql_node)                 = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name          = (yyvsp[-5].string);
      create_index.relation_name       = (yyvsp[-3].string);
      create_index.attribute_name      = (yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 1888 "yacc_sql.cpp"
    break;

    case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 325 "yacc_sql.y"
    {
      (yyval.sql_node)                           = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name    = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1900 "yacc_sql.cpp"
    break;

    case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 335 "yacc_sql.y"
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
#line 1925 "yacc_sql.cpp"
    break;

    case 37: /* attr_def_list: %empty  */
#line 358 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1933 "yacc_sql.cpp"
    break;

    case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 362 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1947 "yacc_sql.cpp"
    break;

    case 39: /* attr_def: ID type LBRACE number RBRACE nullable_constraint  */
#line 375 "yacc_sql.y"
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
#line 1963 "yacc_sql.cpp"
    break;

    case 40: /* attr_def: ID type nullable_constraint  */
#line 387 "yacc_sql.y"
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
#line 1989 "yacc_sql.cpp"
    break;

    case 41: /* nullable_constraint: NOT NULL_T  */
#line 412 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // NOT NULL 对应的可空性为 false
    }
#line 1997 "yacc_sql.cpp"
    break;

    case 42: /* nullable_constraint: NULLABLE  */
#line 416 "yacc_sql.y"
    {
      (yyval.nullable_info) = true;  // NULLABLE 对应的可空性为 true
    }
#line 2005 "yacc_sql.cpp"
    break;

    case 43: /* nullable_constraint: %empty  */
#line 420 "yacc_sql.y"
    {
      (yyval.nullable_info) = false;  // 默认情况为 NOT NULL
    }
#line 2013 "yacc_sql.cpp"
    break;

    case 44: /* number: NUMBER  */
#line 426 "yacc_sql.y"
    {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2019 "yacc_sql.cpp"
    break;

    case 45: /* type: INT_T  */
#line 429 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::INTS);
    }
#line 2025 "yacc_sql.cpp"
    break;

    case 46: /* type: STRING_T  */
#line 430 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::CHARS);
    }
#line 2031 "yacc_sql.cpp"
    break;

    case 47: /* type: FLOAT_T  */
#line 431 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::FLOATS);
    }
#line 2037 "yacc_sql.cpp"
    break;

    case 48: /* type: DATE_T  */
#line 432 "yacc_sql.y"
    {
      (yyval.number) = static_cast<int>(AttrType::DATES);
    }
#line 2043 "yacc_sql.cpp"
    break;

    case 49: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 437 "yacc_sql.y"
    {
      (yyval.sql_node)                          = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values_list.swap(*(yyvsp[0].values_list));
        delete (yyvsp[0].values_list);
      }
      free((yyvsp[-2].string));
    }
#line 2057 "yacc_sql.cpp"
    break;

    case 50: /* values_list: LBRACE value_list RBRACE  */
#line 450 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2067 "yacc_sql.cpp"
    break;

    case 51: /* values_list: values_list COMMA LBRACE value_list RBRACE  */
#line 456 "yacc_sql.y"
    {
      (yyval.values_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2076 "yacc_sql.cpp"
    break;

    case 52: /* value_list: value  */
#line 463 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2086 "yacc_sql.cpp"
    break;

    case 53: /* value_list: value_list COMMA value  */
#line 469 "yacc_sql.y"
    {
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2095 "yacc_sql.cpp"
    break;

    case 54: /* value: NUMBER  */
#line 476 "yacc_sql.y"
    {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc)       = (yylsp[0]);
    }
#line 2104 "yacc_sql.cpp"
    break;

    case 55: /* value: FLOAT  */
#line 480 "yacc_sql.y"
    {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc)       = (yylsp[0]);
    }
#line 2113 "yacc_sql.cpp"
    break;

    case 56: /* value: SSS  */
#line 484 "yacc_sql.y"
    {
      char *tmp     = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string)) - 2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2124 "yacc_sql.cpp"
    break;

    case 57: /* value: NULL_T  */
#line 490 "yacc_sql.y"
    {
      (yyval.value) = new Value(NullValue());
    }
#line 2132 "yacc_sql.cpp"
    break;

    case 58: /* storage_format: %empty  */
#line 497 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2140 "yacc_sql.cpp"
    break;

    case 59: /* storage_format: STORAGE FORMAT EQ ID  */
#line 501 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2148 "yacc_sql.cpp"
    break;

    case 60: /* delete_stmt: DELETE FROM ID where  */
#line 508 "yacc_sql.y"
    {
      (yyval.sql_node)                         = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2162 "yacc_sql.cpp"
    break;

    case 61: /* update_stmt: UPDATE ID SET setClauses where  */
#line 521 "yacc_sql.y"
    {
      (yyval.sql_node)                       = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.set_clauses.swap(*(yyvsp[-1].set_clauses));
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
      delete (yyvsp[-1].set_clauses);
    }
#line 2178 "yacc_sql.cpp"
    break;

    case 62: /* setClauses: setClause  */
#line 536 "yacc_sql.y"
    {
      (yyval.set_clauses) = new std::vector<SetClauseSqlNode>;
      (yyval.set_clauses)->emplace_back(*(yyvsp[0].set_clause));
      delete (yyvsp[0].set_clause);
    }
#line 2188 "yacc_sql.cpp"
    break;

    case 63: /* setClauses: setClauses COMMA setClause  */
#line 542 "yacc_sql.y"
    {
      (yyval.set_clauses)->emplace_back(*(yyvsp[0].set_clause));
      delete (yyvsp[0].set_clause);
    }
#line 2197 "yacc_sql.cpp"
    break;

    case 64: /* setClause: ID EQ value  */
#line 550 "yacc_sql.y"
    {
      (yyval.set_clause)             = new SetClauseSqlNode;
      (yyval.set_clause)->field_name = (yyvsp[-2].string);
      (yyval.set_clause)->value      = std::move(*(yyvsp[0].value));
      free((yyvsp[-2].string));
    }
#line 2208 "yacc_sql.cpp"
    break;

    case 65: /* select_stmt: SELECT expression_list FROM rel_list where group_by  */
#line 560 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-4].expression_list));
        delete (yyvsp[-4].expression_list);
      }

      if ((yyvsp[-2].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-2].relation_list));
        delete (yyvsp[-2].relation_list);
      }

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2235 "yacc_sql.cpp"
    break;

    case 66: /* select_stmt: SELECT expression_list FROM relation INNER JOIN joinClauses where group_by  */
#line 583 "yacc_sql.y"
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

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[-2].join_clauses) != nullptr) {
        for (auto it = (yyvsp[-2].join_clauses)->rbegin(); it != (yyvsp[-2].join_clauses)->rend(); ++it) {
          (yyval.sql_node)->selection.relations.emplace_back(it->relation);
          for (auto &condition : it->conditions) {
            (yyval.sql_node)->selection.conditions.emplace_back(condition);
          }
        }
        delete (yyvsp[-2].join_clauses);
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2272 "yacc_sql.cpp"
    break;

    case 67: /* calc_stmt: CALC expression_list  */
#line 619 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2282 "yacc_sql.cpp"
    break;

    case 68: /* expression_list: expression alias  */
#line 628 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_name((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2295 "yacc_sql.cpp"
    break;

    case 69: /* expression_list: expression alias COMMA expression_list  */
#line 637 "yacc_sql.y"
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
#line 2312 "yacc_sql.cpp"
    break;

    case 70: /* expression: expression '+' expression  */
#line 651 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2320 "yacc_sql.cpp"
    break;

    case 71: /* expression: expression '-' expression  */
#line 654 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2328 "yacc_sql.cpp"
    break;

    case 72: /* expression: expression '*' expression  */
#line 657 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2336 "yacc_sql.cpp"
    break;

    case 73: /* expression: expression '/' expression  */
#line 660 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2344 "yacc_sql.cpp"
    break;

    case 74: /* expression: LBRACE expression RBRACE  */
#line 663 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2353 "yacc_sql.cpp"
    break;

    case 75: /* expression: '-' expression  */
#line 667 "yacc_sql.y"
    {
      (yyval.expression) = create_arithmetic_expression(
          ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2361 "yacc_sql.cpp"
    break;

    case 76: /* expression: value  */
#line 670 "yacc_sql.y"
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2371 "yacc_sql.cpp"
    break;

    case 77: /* expression: rel_attr  */
#line 675 "yacc_sql.y"
    {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression)   = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2382 "yacc_sql.cpp"
    break;

    case 78: /* expression: '*'  */
#line 681 "yacc_sql.y"
    {
      (yyval.expression) = new StarExpr();
    }
#line 2390 "yacc_sql.cpp"
    break;

    case 79: /* expression: aggr_func_expr  */
#line 684 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);  // AggrFuncExpr
    }
#line 2398 "yacc_sql.cpp"
    break;

    case 80: /* alias: %empty  */
#line 691 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2406 "yacc_sql.cpp"
    break;

    case 81: /* alias: ID  */
#line 694 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2414 "yacc_sql.cpp"
    break;

    case 82: /* alias: AS ID  */
#line 697 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2422 "yacc_sql.cpp"
    break;

    case 83: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 703 "yacc_sql.y"
    {
      if ((*(yyvsp[-1].expression_list)).size() != 1) {
        (yyval.expression) = new UnboundAggregateExpr("max", new StarExpr());
      } else {
        (yyval.expression) = new UnboundAggregateExpr((yyvsp[-3].string), std::move((*(yyvsp[-1].expression_list))[0]));
      }
    }
#line 2434 "yacc_sql.cpp"
    break;

    case 84: /* aggr_func_expr: ID LBRACE RBRACE  */
#line 711 "yacc_sql.y"
    {
      (yyval.expression) = new UnboundAggregateExpr("max", new StarExpr());
    }
#line 2442 "yacc_sql.cpp"
    break;

    case 85: /* rel_attr: ID  */
#line 716 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2452 "yacc_sql.cpp"
    break;

    case 86: /* rel_attr: ID DOT ID  */
#line 721 "yacc_sql.y"
    {
      (yyval.rel_attr)                 = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2464 "yacc_sql.cpp"
    break;

    case 87: /* relation: ID  */
#line 731 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2472 "yacc_sql.cpp"
    break;

    case 88: /* rel_list: relation alias  */
#line 737 "yacc_sql.y"
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
#line 2487 "yacc_sql.cpp"
    break;

    case 89: /* rel_list: relation alias COMMA rel_list  */
#line 747 "yacc_sql.y"
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
#line 2507 "yacc_sql.cpp"
    break;

    case 90: /* joinClause: relation ON condition_list  */
#line 766 "yacc_sql.y"
    {
      (yyval.join_clause)           = new JoinSqlNode;
      (yyval.join_clause)->relation = (yyvsp[-2].string);
      (yyval.join_clause)->conditions.swap(*(yyvsp[0].condition_list));
      free((yyvsp[-2].string));
      delete (yyvsp[0].condition_list);
    }
#line 2519 "yacc_sql.cpp"
    break;

    case 91: /* joinClauses: joinClause  */
#line 777 "yacc_sql.y"
    {
      (yyval.join_clauses) = new std::vector<JoinSqlNode>;
      (yyval.join_clauses)->emplace_back(*(yyvsp[0].join_clause));
      delete (yyvsp[0].join_clause);
    }
#line 2529 "yacc_sql.cpp"
    break;

    case 92: /* joinClauses: joinClause INNER JOIN joinClauses  */
#line 783 "yacc_sql.y"
    {
      (yyval.join_clauses) = (yyvsp[0].join_clauses);
      (yyval.join_clauses)->emplace_back(*(yyvsp[-3].join_clause));
      delete (yyvsp[-3].join_clause);
    }
#line 2539 "yacc_sql.cpp"
    break;

    case 93: /* where: %empty  */
#line 792 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2547 "yacc_sql.cpp"
    break;

    case 94: /* where: WHERE condition_list  */
#line 795 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2555 "yacc_sql.cpp"
    break;

    case 95: /* condition_list: %empty  */
#line 801 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2563 "yacc_sql.cpp"
    break;

    case 96: /* condition_list: condition  */
#line 804 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2573 "yacc_sql.cpp"
    break;

    case 97: /* condition_list: condition AND condition_list  */
#line 809 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2583 "yacc_sql.cpp"
    break;

    case 98: /* condition: rel_attr comp_op value  */
#line 817 "yacc_sql.y"
    {
      (yyval.condition)                = new ConditionSqlNode;
      (yyval.condition)->left_is_attr  = 1;
      (yyval.condition)->left_attr     = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value   = *(yyvsp[0].value);
      (yyval.condition)->comp          = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2599 "yacc_sql.cpp"
    break;

    case 99: /* condition: value comp_op value  */
#line 829 "yacc_sql.y"
    {
      (yyval.condition)                = new ConditionSqlNode;
      (yyval.condition)->left_is_attr  = 0;
      (yyval.condition)->left_value    = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value   = *(yyvsp[0].value);
      (yyval.condition)->comp          = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2615 "yacc_sql.cpp"
    break;

    case 100: /* condition: rel_attr comp_op rel_attr  */
#line 841 "yacc_sql.y"
    {
      (yyval.condition)                = new ConditionSqlNode;
      (yyval.condition)->left_is_attr  = 1;
      (yyval.condition)->left_attr     = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr    = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp          = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2631 "yacc_sql.cpp"
    break;

    case 101: /* condition: value comp_op rel_attr  */
#line 853 "yacc_sql.y"
    {
      (yyval.condition)                = new ConditionSqlNode;
      (yyval.condition)->left_is_attr  = 0;
      (yyval.condition)->left_value    = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr    = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp          = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2647 "yacc_sql.cpp"
    break;

    case 102: /* comp_op: EQ  */
#line 867 "yacc_sql.y"
    {
      (yyval.comp) = EQUAL_TO;
    }
#line 2653 "yacc_sql.cpp"
    break;

    case 103: /* comp_op: LT  */
#line 868 "yacc_sql.y"
    {
      (yyval.comp) = LESS_THAN;
    }
#line 2659 "yacc_sql.cpp"
    break;

    case 104: /* comp_op: GT  */
#line 869 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_THAN;
    }
#line 2665 "yacc_sql.cpp"
    break;

    case 105: /* comp_op: LE  */
#line 870 "yacc_sql.y"
    {
      (yyval.comp) = LESS_EQUAL;
    }
#line 2671 "yacc_sql.cpp"
    break;

    case 106: /* comp_op: GE  */
#line 871 "yacc_sql.y"
    {
      (yyval.comp) = GREAT_EQUAL;
    }
#line 2677 "yacc_sql.cpp"
    break;

    case 107: /* comp_op: NE  */
#line 872 "yacc_sql.y"
    {
      (yyval.comp) = NOT_EQUAL;
    }
#line 2683 "yacc_sql.cpp"
    break;

    case 108: /* comp_op: IS  */
#line 873 "yacc_sql.y"
    {
      (yyval.comp) = OP_IS;
    }
#line 2689 "yacc_sql.cpp"
    break;

    case 109: /* comp_op: IS NOT  */
#line 874 "yacc_sql.y"
    {
      (yyval.comp) = OP_IS_NOT;
    }
#line 2695 "yacc_sql.cpp"
    break;

    case 110: /* comp_op: LIKE  */
#line 875 "yacc_sql.y"
    {
      (yyval.comp) = LIKE_OP;
    }
#line 2701 "yacc_sql.cpp"
    break;

    case 111: /* comp_op: NOT LIKE  */
#line 876 "yacc_sql.y"
    {
      (yyval.comp) = NOT_LIKE_OP;
    }
#line 2707 "yacc_sql.cpp"
    break;

    case 112: /* group_by: %empty  */
#line 882 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2715 "yacc_sql.cpp"
    break;

    case 113: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 888 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node)                          = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name     = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2729 "yacc_sql.cpp"
    break;

    case 114: /* explain_stmt: EXPLAIN command_wrapper  */
#line 901 "yacc_sql.y"
    {
      (yyval.sql_node)                   = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2738 "yacc_sql.cpp"
    break;

    case 115: /* set_variable_stmt: SET ID EQ value  */
#line 909 "yacc_sql.y"
    {
      (yyval.sql_node)                     = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2750 "yacc_sql.cpp"
    break;

#line 2754 "yacc_sql.cpp"

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

#line 921 "yacc_sql.y"

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
