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


#line 115 "yacc_sql.cpp"

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
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_UNIQUE = 14,                    /* UNIQUE  */
  YYSYMBOL_INSERT = 15,                    /* INSERT  */
  YYSYMBOL_DELETE = 16,                    /* DELETE  */
  YYSYMBOL_UPDATE = 17,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 21,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 22,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 23,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 24,                     /* INT_T  */
  YYSYMBOL_STRING_T = 25,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 27,                    /* DATE_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_LIKE = 35,                      /* LIKE  */
  YYSYMBOL_NOT = 36,                       /* NOT  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_ON = 39,                        /* ON  */
  YYSYMBOL_LOAD = 40,                      /* LOAD  */
  YYSYMBOL_DATA = 41,                      /* DATA  */
  YYSYMBOL_INFILE = 42,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 43,                   /* EXPLAIN  */
  YYSYMBOL_INNER = 44,                     /* INNER  */
  YYSYMBOL_JOIN = 45,                      /* JOIN  */
  YYSYMBOL_MAX = 46,                       /* MAX  */
  YYSYMBOL_MIN = 47,                       /* MIN  */
  YYSYMBOL_COUNT = 48,                     /* COUNT  */
  YYSYMBOL_AVG = 49,                       /* AVG  */
  YYSYMBOL_SUM = 50,                       /* SUM  */
  YYSYMBOL_ORDER = 51,                     /* ORDER  */
  YYSYMBOL_BY = 52,                        /* BY  */
  YYSYMBOL_ASC = 53,                       /* ASC  */
  YYSYMBOL_NULL_T = 54,                    /* NULL_T  */
  YYSYMBOL_IS = 55,                        /* IS  */
  YYSYMBOL_IN = 56,                        /* IN  */
  YYSYMBOL_EQ = 57,                        /* EQ  */
  YYSYMBOL_LT = 58,                        /* LT  */
  YYSYMBOL_GT = 59,                        /* GT  */
  YYSYMBOL_LE = 60,                        /* LE  */
  YYSYMBOL_GE = 61,                        /* GE  */
  YYSYMBOL_NE = 62,                        /* NE  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_SSS = 66,                       /* SSS  */
  YYSYMBOL_67_ = 67,                       /* '+'  */
  YYSYMBOL_68_ = 68,                       /* '-'  */
  YYSYMBOL_69_ = 69,                       /* '*'  */
  YYSYMBOL_70_ = 70,                       /* '/'  */
  YYSYMBOL_UMINUS = 71,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command_wrapper = 74,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 75,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 76,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 77,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 78,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 79,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 80,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 81,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 82,          /* show_tables_stmt  */
  YYSYMBOL_show_index_stmt = 83,           /* show_index_stmt  */
  YYSYMBOL_desc_table_stmt = 84,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 85,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 86,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 87,         /* create_table_stmt  */
  YYSYMBOL_nullable = 88,                  /* nullable  */
  YYSYMBOL_attr_def_list = 89,             /* attr_def_list  */
  YYSYMBOL_attr_def = 90,                  /* attr_def  */
  YYSYMBOL_number = 91,                    /* number  */
  YYSYMBOL_type = 92,                      /* type  */
  YYSYMBOL_insert_stmt = 93,               /* insert_stmt  */
  YYSYMBOL_value_list = 94,                /* value_list  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete_stmt = 96,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 97,               /* update_stmt  */
  YYSYMBOL_UpdateNode = 98,                /* UpdateNode  */
  YYSYMBOL_select_stmt = 99,               /* select_stmt  */
  YYSYMBOL_calc_stmt = 100,                /* calc_stmt  */
  YYSYMBOL_expression_list = 101,          /* expression_list  */
  YYSYMBOL_expression = 102,               /* expression  */
  YYSYMBOL_OrderByNode = 103,              /* OrderByNode  */
  YYSYMBOL_more_OrderByNode = 104,         /* more_OrderByNode  */
  YYSYMBOL_select_attr = 105,              /* select_attr  */
  YYSYMBOL_brace_string = 106,             /* brace_string  */
  YYSYMBOL_more_brace_string = 107,        /* more_brace_string  */
  YYSYMBOL_rel_attr = 108,                 /* rel_attr  */
  YYSYMBOL_attr_list = 109,                /* attr_list  */
  YYSYMBOL_rel_list = 110,                 /* rel_list  */
  YYSYMBOL_where = 111,                    /* where  */
  YYSYMBOL_inner_list = 112,               /* inner_list  */
  YYSYMBOL_condition_list = 113,           /* condition_list  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_comp_op = 115,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 116,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 117,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 118,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 119             /* opt_semicolon  */
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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   307

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  306

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
       2,     2,    69,    67,     2,    68,     2,    70,     2,     2,
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
      65,    66,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   206,   206,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   238,   244,   249,   255,   261,   267,
     273,   280,   285,   292,   300,   313,   330,   340,   359,   362,
     366,   373,   376,   389,   398,   409,   412,   413,   414,   415,
     418,   436,   439,   448,   461,   465,   469,   474,   480,   492,
     516,   519,   533,   566,   576,   581,   592,   595,   598,   601,
     604,   608,   611,   619,   622,   634,   645,   660,   663,   675,
     686,   701,   704,   711,   720,   736,   739,   743,   754,   766,
     780,   783,   794,   806,   819,   824,   831,   841,   851,   861,
     871,   885,   888,   902,   905,   918,   921,   927,   931,   951,
     954,   959,   966,   978,   990,  1002,  1014,  1025,  1036,  1047,
    1058,  1069,  1079,  1090,  1100,  1111,  1121,  1132,  1142,  1153,
    1163,  1174,  1187,  1188,  1189,  1190,  1191,  1192,  1193,  1194,
    1198,  1211,  1219,  1229,  1230
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "UNIQUE", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "LIKE", "NOT", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "INNER", "JOIN", "MAX", "MIN", "COUNT", "AVG", "SUM", "ORDER",
  "BY", "ASC", "NULL_T", "IS", "IN", "EQ", "LT", "GT", "LE", "GE", "NE",
  "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "show_index_stmt",
  "desc_table_stmt", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "nullable", "attr_def_list", "attr_def", "number",
  "type", "insert_stmt", "value_list", "value", "delete_stmt",
  "update_stmt", "UpdateNode", "select_stmt", "calc_stmt",
  "expression_list", "expression", "OrderByNode", "more_OrderByNode",
  "select_attr", "brace_string", "more_brace_string", "rel_attr",
  "attr_list", "rel_list", "where", "inner_list", "condition_list",
  "condition", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-232)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     153,   135,   113,     2,   -20,   -48,    97,  -232,   -12,    10,
     -27,  -232,  -232,  -232,  -232,  -232,    -2,    12,   153,    72,
      73,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,    22,    28,    74,    48,    55,     2,  -232,  -232,
    -232,  -232,     2,  -232,  -232,    11,   126,   126,   126,   126,
     126,   129,   141,   134,   151,  -232,  -232,   139,   119,   120,
     148,   130,   146,  -232,  -232,  -232,  -232,   171,   155,   125,
    -232,   156,    -8,  -232,     2,     2,     2,     2,     2,     4,
    -232,  -232,  -232,  -232,  -232,   127,    62,   145,    62,  -232,
     161,   179,   186,   162,   -22,   163,   165,   166,   182,   167,
    -232,  -232,    70,    70,  -232,  -232,  -232,    17,   208,  -232,
     151,   213,   151,  -232,   216,    68,  -232,   178,  -232,   205,
      99,   217,   226,   180,  -232,   -17,   181,   228,   229,  -232,
     184,   206,  -232,   -22,   241,   157,   142,  -232,   215,   -22,
     247,  -232,  -232,  -232,  -232,    -3,   165,   235,   190,   238,
      53,   126,   208,  -232,  -232,   213,   212,   186,   239,   242,
     222,  -232,  -232,  -232,  -232,  -232,  -232,   159,   196,   -21,
     245,   246,   248,   249,   250,   251,   252,   159,    68,   253,
     200,   209,   220,  -232,  -232,   217,  -232,   213,   210,   211,
    -232,  -232,   258,  -232,   214,   227,    84,   261,    94,  -232,
    -232,  -232,  -232,   218,   263,   241,   241,   241,   241,   241,
     241,   241,  -232,  -232,  -232,   221,   186,  -232,  -232,   264,
    -232,  -232,   266,   213,   126,  -232,   232,   230,  -232,   -22,
     239,   239,    62,    62,    62,    62,    62,    62,  -232,   241,
     268,   270,   271,   272,   273,   274,   275,   240,  -232,   -18,
    -232,   276,  -232,    68,    62,   239,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,   277,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,   -22,  -232,  -232,   206,     1,   279,  -232,   253,
    -232,   280,    62,   280,  -232,   239,  -232,  -232,     5,  -232,
    -232,   280,   280,  -232,  -232,  -232
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    81,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     143,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    57,    54,
      55,    56,     0,    72,    63,    64,    85,    85,    85,    85,
      85,    94,    82,     0,   101,    33,    31,     0,     0,     0,
       0,     0,     0,   141,     1,   144,     2,     0,     0,     0,
      30,     0,     0,    71,     0,     0,     0,     0,     0,     0,
      96,    97,    98,    99,   100,     0,     0,     0,     0,    83,
       0,     0,   105,     0,     0,     0,     0,     0,     0,     0,
      70,    65,    66,    67,    68,    69,    86,    90,    90,    95,
     101,   103,   101,    32,     0,   109,    58,     0,   142,     0,
       0,    41,     0,     0,    36,     0,     0,     0,     0,    84,
       0,   107,   102,     0,     0,     0,     0,   106,   110,     0,
       0,    46,    47,    48,    49,    38,     0,     0,     0,     0,
      85,    85,    90,    87,    89,   103,     0,   105,    51,     0,
     138,   132,   133,   134,   135,   136,   137,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   109,    60,
       0,     0,     0,    39,    44,    41,    37,   103,     0,     0,
      91,    93,     0,   104,     0,    73,     0,     0,     0,   139,
     113,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   114,   111,     0,   105,   140,    45,     0,
      40,    42,     0,   103,    85,    88,     0,     0,    62,     0,
      51,    51,     0,     0,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    38,
      34,     0,    92,   109,     0,    51,    52,    50,   121,   123,
     125,   127,   129,   131,     0,   118,   120,   122,   124,   126,
     128,   130,     0,    43,    35,   107,    77,     0,   119,    60,
     108,    77,     0,    77,    76,    51,    61,    75,    77,    74,
      53,    77,    77,    80,    79,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -232,  -232,   281,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,    42,   107,   147,  -232,
    -232,  -232,  -231,  -103,  -232,  -232,    15,  -120,  -232,   223,
       3,  -232,  -156,  -232,   -54,  -105,    -4,     8,  -158,  -159,
      20,  -186,  -232,   160,  -232,  -232,  -232,  -232
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   194,   157,   131,   229,
     155,    34,   207,    53,    35,    36,   226,    37,    38,    54,
      55,   238,   294,    63,    90,   137,   146,    99,   141,   126,
     167,   147,   148,   177,    39,    40,    41,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   128,   224,    91,    92,    93,    94,   203,   205,   266,
     267,   110,   291,   138,   213,   191,   301,    65,   192,    68,
      47,   292,   145,   116,   169,   292,    56,    57,    58,    59,
      60,    84,    48,   192,   287,   214,   193,   135,    70,   232,
     168,    49,    50,    69,    51,    61,   189,   136,   160,    62,
      82,   193,   161,    72,   293,    83,    48,   202,   302,    85,
      86,    87,    88,    71,   300,    49,    50,   258,    51,   117,
      52,    89,    74,   118,   210,   261,    75,   285,    85,    86,
      87,    88,    79,   199,   222,   145,   144,    77,   112,   113,
     114,   115,   120,    78,   122,   250,   251,   252,   253,   254,
     255,   256,   239,   240,    66,    67,   200,   201,    56,    57,
      58,    59,    60,    80,    56,    57,    58,    59,    60,    45,
      81,    46,    48,   151,   152,   153,   154,    61,   139,   274,
     142,    49,    50,    61,    51,   297,   265,   299,    48,    87,
      88,    42,   303,    43,    89,   304,   305,    49,    50,    44,
      51,   242,   243,   244,   245,   246,   247,     1,     2,    95,
     145,    96,     3,     4,     5,     6,     7,    97,     8,     9,
      10,    98,   100,   211,    11,    12,    13,   178,   179,   289,
     262,    14,    15,   223,   101,   102,   103,   104,   105,   106,
     108,    16,   119,    17,   107,   109,    18,   170,   180,   181,
     182,   183,   184,   185,   186,    56,    57,    58,    59,    60,
     121,   124,   170,    48,   171,   172,   173,   174,   175,   176,
     125,   133,    49,    50,    61,    51,   123,   127,   135,   129,
     130,   132,   134,   140,   143,   149,   150,   156,   268,   269,
     270,   271,   272,   273,   158,   159,   162,   163,   164,   165,
     166,     4,   188,   190,   196,   197,   198,   204,   209,   206,
     286,   208,   212,   215,   216,   227,   217,   218,   219,   220,
     221,   263,   228,   225,   230,   233,   234,   235,   237,   236,
     241,   249,   264,   259,   248,   260,   257,   275,   298,   276,
     277,   278,   279,   280,   281,   284,   288,   282,   295,    73,
     292,   283,   231,   195,   296,   290,   187,   111
};

static const yytype_int16 yycheck[] =
{
       4,   104,   188,    57,    58,    59,    60,   165,   167,   240,
     241,    19,    11,   118,    35,    18,    11,    65,    36,    31,
      18,    20,   125,    19,   144,    20,    46,    47,    48,    49,
      50,    20,    54,    36,   265,    56,    54,    20,    65,   197,
     143,    63,    64,    33,    66,    65,   149,    30,    65,    69,
      47,    54,    69,    41,    53,    52,    54,   162,    53,    67,
      68,    69,    70,    65,   295,    63,    64,   226,    66,    65,
      68,    18,     0,    69,   177,   233,     3,   263,    67,    68,
      69,    70,     8,    30,   187,   188,    18,    65,    85,    86,
      87,    88,    96,    65,    98,   215,   216,   217,   218,   219,
     220,   221,    18,   206,     7,     8,   160,   161,    46,    47,
      48,    49,    50,    65,    46,    47,    48,    49,    50,     6,
      65,     8,    54,    24,    25,    26,    27,    65,   120,   249,
     122,    63,    64,    65,    66,   291,   239,   293,    54,    69,
      70,     6,   298,     8,    18,   301,   302,    63,    64,    14,
      66,    57,    58,    59,    60,    61,    62,     4,     5,    30,
     263,    20,     9,    10,    11,    12,    13,    33,    15,    16,
      17,    20,    33,   177,    21,    22,    23,    35,    36,   282,
     234,    28,    29,   187,    65,    65,    38,    57,    42,    18,
      65,    38,    65,    40,    39,    39,    43,    55,    56,    57,
      58,    59,    60,    61,    62,    46,    47,    48,    49,    50,
      65,    32,    55,    54,    57,    58,    59,    60,    61,    62,
      34,    39,    63,    64,    65,    66,    65,    65,    20,    66,
      65,    65,    65,    20,    18,    57,    31,    20,   242,   243,
     244,   245,   246,   247,    18,    65,    65,    19,    19,    65,
      44,    10,    37,     6,    19,    65,    18,    45,    36,    20,
     264,    19,    66,    18,    18,    65,    18,    18,    18,    18,
      18,    39,    63,    20,    54,    65,    65,    19,    51,    65,
      19,    18,    52,    19,    66,    19,    65,    19,   292,    19,
      19,    19,    19,    19,    19,    19,    19,    57,    19,    18,
      20,   259,   195,   156,   289,   285,   146,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    15,    16,
      17,    21,    22,    23,    28,    29,    38,    40,    43,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    93,    96,    97,    99,   100,   116,
     117,   118,     6,     8,    14,     6,     8,    18,    54,    63,
      64,    66,    68,    95,   101,   102,    46,    47,    48,    49,
      50,    65,    69,   105,   108,    65,     7,     8,    31,    33,
      65,    65,    41,    74,     0,     3,   119,    65,    65,     8,
      65,    65,   102,   102,    20,    67,    68,    69,    70,    18,
     106,   106,   106,   106,   106,    30,    20,    33,    20,   109,
      33,    65,    65,    38,    57,    42,    18,    39,    65,    39,
      19,   101,   102,   102,   102,   102,    19,    65,    69,    65,
     108,    65,   108,    65,    32,    34,   111,    65,    95,    66,
      65,    90,    65,    39,    65,    20,    30,   107,   107,   109,
      20,   110,   109,    18,    18,    95,   108,   113,   114,    57,
      31,    24,    25,    26,    27,    92,    20,    89,    18,    65,
      65,    69,    65,    19,    19,    65,    44,   112,    95,    99,
      55,    57,    58,    59,    60,    61,    62,   115,    35,    36,
      56,    57,    58,    59,    60,    61,    62,   115,    37,    95,
       6,    18,    36,    54,    88,    90,    19,    65,    18,    30,
     106,   106,   107,   110,    45,   111,    20,    94,    19,    36,
      95,   108,    66,    35,    56,    18,    18,    18,    18,    18,
      18,    18,    95,   108,   113,    20,    98,    65,    63,    91,
      54,    89,   110,    65,    65,    19,    65,    51,   103,    18,
      95,    19,    57,    58,    59,    60,    61,    62,    66,    18,
      99,    99,    99,    99,    99,    99,    99,    65,   111,    19,
      19,   110,   106,    39,    52,    95,    94,    94,   108,   108,
     108,   108,   108,   108,    99,    19,    19,    19,    19,    19,
      19,    19,    57,    88,    19,   113,   108,    94,    19,    95,
     112,    11,    20,    53,   104,    19,    98,   104,   108,   104,
      94,    11,    53,   104,   104,   104
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    85,    86,    87,    88,    88,
      88,    89,    89,    90,    90,    91,    92,    92,    92,    92,
      93,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      98,    98,    99,   100,   101,   101,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   103,   103,   104,   104,   104,
     104,   105,   105,   105,   105,   106,   106,   106,   106,   106,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   112,   112,   113,
     113,   113,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   117,   118,   119,   119
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     9,    10,     5,     7,     0,     1,
       2,     0,     3,     6,     3,     1,     1,     1,     1,     1,
       9,     0,     3,     6,     1,     1,     1,     1,     4,     8,
       0,     5,     8,     2,     1,     3,     3,     3,     3,     3,
       3,     2,     1,     0,     5,     5,     4,     0,     4,     4,
       3,     0,     1,     2,     4,     0,     2,     4,     6,     4,
       0,     3,     5,     3,     1,     3,     2,     2,     2,     2,
       2,     0,     3,     0,     3,     0,     2,     0,     6,     0,
       1,     3,     3,     3,     3,     3,     3,     4,     5,     6,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     1,     1,     1,     1,     1,     1,     1,     2,
       7,     2,     4,     0,     1
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
#line 207 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1837 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 238 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1846 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 244 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1854 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 249 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 255 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1870 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 261 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1878 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 267 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1886 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 273 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 280 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 32: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 285 "yacc_sql.y"
                      {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name=(yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 292 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1924 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID rel_list RBRACE  */
#line 301 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      if((yyvsp[-1].relation_list)!=nullptr){
      create_index.attribute_names.swap(*(yyvsp[-1].relation_list));}
      create_index.attribute_names.push_back((yyvsp[-2].string));
      create_index.relation_name = (yyvsp[-4].string);
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID rel_list RBRACE  */
#line 314 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      if((yyvsp[-1].relation_list)!=nullptr){
      create_index.attribute_names.swap(*(yyvsp[-1].relation_list));}
      create_index.attribute_names.push_back((yyvsp[-2].string));
      create_index.relation_name = (yyvsp[-4].string);
      create_index.unique_index=true;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1959 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 331 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 341 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1991 "yacc_sql.cpp"
    break;

  case 38: /* nullable: %empty  */
#line 359 "yacc_sql.y"
  {
    (yyval.nullable) = true;
  }
#line 1999 "yacc_sql.cpp"
    break;

  case 39: /* nullable: NULL_T  */
#line 363 "yacc_sql.y"
  {
    (yyval.nullable) = true;
  }
#line 2007 "yacc_sql.cpp"
    break;

  case 40: /* nullable: NOT NULL_T  */
#line 367 "yacc_sql.y"
  {
    (yyval.nullable)=false;
  }
#line 2015 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 373 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2023 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 377 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2037 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 390 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->can_be_null=(yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2050 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type nullable  */
#line 399 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->can_be_null=(yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2063 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 409 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2069 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 412 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2075 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 413 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2081 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 414 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2087 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 415 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2093 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE value_list  */
#line 419 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-6].string);
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].value_list));
      }
      if((yyvsp[-2].value_list)!=nullptr){
      (yyval.sql_node)->insertion.values.insert(((yyval.sql_node)->insertion.values).end(),(yyvsp[-2].value_list)->begin(),(yyvsp[-2].value_list)->end());}
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-3].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-3].value);
      free((yyvsp[-6].string));
    }
#line 2111 "yacc_sql.cpp"
    break;

  case 51: /* value_list: %empty  */
#line 436 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2119 "yacc_sql.cpp"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 439 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA LBRACE value value_list RBRACE value_list  */
#line 449 "yacc_sql.y"
    {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->insert((yyval.value_list)->end(),(yyvsp[-2].value_list)->begin(),(yyvsp[-2].value_list)->end());
      (yyval.value_list)->emplace_back(*(yyvsp[-3].value));
      delete (yyvsp[-3].value);
    }
#line 2148 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 461 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 465 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2166 "yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 469 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2176 "yacc_sql.cpp"
    break;

  case 57: /* value: NULL_T  */
#line 474 "yacc_sql.y"
           {
      (yyval.value) = new Value("null");
    }
#line 2184 "yacc_sql.cpp"
    break;

  case 58: /* delete_stmt: DELETE FROM ID where  */
#line 481 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2198 "yacc_sql.cpp"
    break;

  case 59: /* update_stmt: UPDATE ID SET ID EQ value UpdateNode where  */
#line 493 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-6].string);
      if((yyvsp[-1].UpdateNode)!=nullptr){
        (yyval.sql_node)->update.update_nodes.swap(*(yyvsp[-1].UpdateNode));
        delete (yyvsp[-1].UpdateNode);
      }
      updateNode temp;
      temp.attribute_name=(yyvsp[-4].string);
      temp.value=*(yyvsp[-2].value);
      (yyval.sql_node)->update.update_nodes.emplace_back(temp);

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 60: /* UpdateNode: %empty  */
#line 516 "yacc_sql.y"
    {
      (yyval.UpdateNode) = nullptr;
    }
#line 2230 "yacc_sql.cpp"
    break;

  case 61: /* UpdateNode: COMMA ID EQ value UpdateNode  */
#line 519 "yacc_sql.y"
                                   { 
      if((yyvsp[0].UpdateNode)!=nullptr){
        (yyval.UpdateNode)=(yyvsp[0].UpdateNode);
      }else{
        (yyval.UpdateNode)=new std::vector<updateNode>;
      }
      updateNode temp;
      temp.attribute_name=(yyvsp[-3].string);
      temp.value=*(yyvsp[-1].value);
      (yyval.UpdateNode)->emplace_back(temp);
      free((yyvsp[-3].string));
    }
#line 2247 "yacc_sql.cpp"
    break;

  case 62: /* select_stmt: SELECT select_attr FROM ID rel_list inner_list where OrderByNode  */
#line 534 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-6].rel_attr_list));
        delete (yyvsp[-6].rel_attr_list);
      }
      //处理表名
      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-4].string));
      free((yyvsp[-4].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if((yyvsp[-2].inner_list) != nullptr ){
        (yyval.sql_node)->selection.inner=*(yyvsp[-2].inner_list);
        delete (yyvsp[-2].inner_list);
      }

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      if((yyvsp[0].OrderByNode)!=nullptr){
        (yyval.sql_node)->selection.order_bys.swap(*(yyvsp[0].OrderByNode));
        std::reverse((yyval.sql_node)->selection.order_bys.begin(), (yyval.sql_node)->selection.order_bys.end());
        delete (yyvsp[0].OrderByNode);
      }
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 63: /* calc_stmt: CALC expression_list  */
#line 567 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2293 "yacc_sql.cpp"
    break;

  case 64: /* expression_list: expression  */
#line 577 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2302 "yacc_sql.cpp"
    break;

  case 65: /* expression_list: expression COMMA expression_list  */
#line 582 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2315 "yacc_sql.cpp"
    break;

  case 66: /* expression: expression '+' expression  */
#line 592 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 67: /* expression: expression '-' expression  */
#line 595 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2331 "yacc_sql.cpp"
    break;

  case 68: /* expression: expression '*' expression  */
#line 598 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 69: /* expression: expression '/' expression  */
#line 601 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2347 "yacc_sql.cpp"
    break;

  case 70: /* expression: LBRACE expression RBRACE  */
#line 604 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2356 "yacc_sql.cpp"
    break;

  case 71: /* expression: '-' expression  */
#line 608 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2364 "yacc_sql.cpp"
    break;

  case 72: /* expression: value  */
#line 611 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2374 "yacc_sql.cpp"
    break;

  case 73: /* OrderByNode: %empty  */
#line 619 "yacc_sql.y"
  {
    (yyval.OrderByNode)=nullptr;
  }
#line 2382 "yacc_sql.cpp"
    break;

  case 74: /* OrderByNode: ORDER BY rel_attr ASC more_OrderByNode  */
#line 623 "yacc_sql.y"
  {
    if((yyvsp[0].more_OrderByNode)!=nullptr){
      (yyval.OrderByNode)=(yyvsp[0].more_OrderByNode);
    }else{
      (yyval.OrderByNode)=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*(yyvsp[-2].rel_attr);
    node.type=UP_asc;
    (yyval.OrderByNode)->emplace_back(node);
  }
#line 2398 "yacc_sql.cpp"
    break;

  case 75: /* OrderByNode: ORDER BY rel_attr DESC more_OrderByNode  */
#line 635 "yacc_sql.y"
  {
    if((yyvsp[0].more_OrderByNode)!=nullptr){
      (yyval.OrderByNode)=(yyvsp[0].more_OrderByNode);
    }else{
      (yyval.OrderByNode)=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*(yyvsp[-2].rel_attr);
    node.type=DOWN_desc;
    (yyval.OrderByNode)->emplace_back(node);
  }
#line 2414 "yacc_sql.cpp"
    break;

  case 76: /* OrderByNode: ORDER BY rel_attr more_OrderByNode  */
#line 646 "yacc_sql.y"
  {
    if((yyvsp[0].more_OrderByNode)!=nullptr){
      (yyval.OrderByNode)=(yyvsp[0].more_OrderByNode);
    }else{
      (yyval.OrderByNode)=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*(yyvsp[-1].rel_attr);
    node.type=UP_asc;
    (yyval.OrderByNode)->emplace_back(node);
  }
#line 2430 "yacc_sql.cpp"
    break;

  case 77: /* more_OrderByNode: %empty  */
#line 660 "yacc_sql.y"
  {
    (yyval.more_OrderByNode)=nullptr;
  }
#line 2438 "yacc_sql.cpp"
    break;

  case 78: /* more_OrderByNode: COMMA rel_attr ASC more_OrderByNode  */
#line 664 "yacc_sql.y"
  {
    if((yyvsp[0].more_OrderByNode)!=nullptr){
      (yyval.more_OrderByNode)=(yyvsp[0].more_OrderByNode);
    }else{
      (yyval.more_OrderByNode)=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*(yyvsp[-2].rel_attr);
    node.type=UP_asc;
    (yyval.more_OrderByNode)->emplace_back(node);
  }
#line 2454 "yacc_sql.cpp"
    break;

  case 79: /* more_OrderByNode: COMMA rel_attr DESC more_OrderByNode  */
#line 676 "yacc_sql.y"
  {
    if((yyvsp[0].more_OrderByNode)!=nullptr){
      (yyval.more_OrderByNode)=(yyvsp[0].more_OrderByNode);
    }else{
      (yyval.more_OrderByNode)=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*(yyvsp[-2].rel_attr);
    node.type=DOWN_desc;
    (yyval.more_OrderByNode)->emplace_back(node);
  }
#line 2470 "yacc_sql.cpp"
    break;

  case 80: /* more_OrderByNode: COMMA rel_attr more_OrderByNode  */
#line 687 "yacc_sql.y"
  {
    if((yyvsp[0].more_OrderByNode)!=nullptr){
      (yyval.more_OrderByNode)=(yyvsp[0].more_OrderByNode);
    }else{
      (yyval.more_OrderByNode)=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*(yyvsp[-1].rel_attr);
    node.type=UP_asc;
    (yyval.more_OrderByNode)->emplace_back(node);
  }
#line 2486 "yacc_sql.cpp"
    break;

  case 81: /* select_attr: %empty  */
#line 701 "yacc_sql.y"
    {
      (yyval.rel_attr_list)=nullptr;
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 82: /* select_attr: '*'  */
#line 704 "yacc_sql.y"
         {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 83: /* select_attr: rel_attr attr_list  */
#line 711 "yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 84: /* select_attr: '*' COMMA rel_attr attr_list  */
#line 720 "yacc_sql.y"
                                 {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      (yyval.rel_attr_list)->emplace_back(attr); 
      delete (yyvsp[-1].rel_attr);
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 85: /* brace_string: %empty  */
#line 736 "yacc_sql.y"
  {
    (yyval.brace_string) = nullptr;
  }
#line 2545 "yacc_sql.cpp"
    break;

  case 86: /* brace_string: LBRACE RBRACE  */
#line 740 "yacc_sql.y"
  {
    (yyval.brace_string) =nullptr;
  }
#line 2553 "yacc_sql.cpp"
    break;

  case 87: /* brace_string: LBRACE ID more_brace_string RBRACE  */
#line 744 "yacc_sql.y"
  {
    if((yyvsp[-1].brace_string)!=nullptr)
    {
      (yyval.brace_string)=(yyvsp[-1].brace_string);
    }else{
    (yyval.brace_string) =new std::vector<std::string>;
    }
    (yyval.brace_string)->push_back((yyvsp[-2].string));
    free((yyvsp[-2].string));
  }
#line 2568 "yacc_sql.cpp"
    break;

  case 88: /* brace_string: LBRACE ID DOT ID more_brace_string RBRACE  */
#line 755 "yacc_sql.y"
  {
    if((yyvsp[-1].brace_string)!=nullptr)
    {
      (yyval.brace_string)=(yyvsp[-1].brace_string);
    }else{
    (yyval.brace_string) =new std::vector<std::string>;
    }
    (yyval.brace_string)->push_back((yyvsp[-2].string));
    free((yyvsp[-2].string));
    free((yyvsp[-4].string));
  }
#line 2584 "yacc_sql.cpp"
    break;

  case 89: /* brace_string: LBRACE '*' more_brace_string RBRACE  */
#line 767 "yacc_sql.y"
  {
    if((yyvsp[-1].brace_string)!=nullptr)
    {
      (yyval.brace_string)=(yyvsp[-1].brace_string);
    }else{
    (yyval.brace_string) =new std::vector<std::string>;
    }
    (yyval.brace_string)->push_back("*");
  }
#line 2598 "yacc_sql.cpp"
    break;

  case 90: /* more_brace_string: %empty  */
#line 780 "yacc_sql.y"
  {
    (yyval.brace_string) = nullptr;
  }
#line 2606 "yacc_sql.cpp"
    break;

  case 91: /* more_brace_string: COMMA ID brace_string  */
#line 784 "yacc_sql.y"
  {
    if((yyvsp[0].brace_string)!=nullptr)
    {
      (yyval.brace_string)=(yyvsp[0].brace_string);
    }else{
    (yyval.brace_string) =new std::vector<std::string>;
    }
    (yyval.brace_string)->push_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 2621 "yacc_sql.cpp"
    break;

  case 92: /* more_brace_string: COMMA ID DOT ID brace_string  */
#line 795 "yacc_sql.y"
  {
    if((yyvsp[0].brace_string)!=nullptr)
    {
      (yyval.brace_string)=(yyvsp[0].brace_string);
    }else{
    (yyval.brace_string) =new std::vector<std::string>;
    }
    (yyval.brace_string)->push_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
    free((yyvsp[-3].string));
  }
#line 2637 "yacc_sql.cpp"
    break;

  case 93: /* more_brace_string: COMMA '*' brace_string  */
#line 807 "yacc_sql.y"
  {
    if((yyvsp[0].brace_string)!=nullptr)
    {
      (yyval.brace_string)=(yyvsp[0].brace_string);
    }else{
    (yyval.brace_string) =new std::vector<std::string>;
    }
    (yyval.brace_string)->push_back("*");
  }
#line 2651 "yacc_sql.cpp"
    break;

  case 94: /* rel_attr: ID  */
#line 819 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 95: /* rel_attr: ID DOT ID  */
#line 824 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 96: /* rel_attr: MAX brace_string  */
#line 832 "yacc_sql.y"
  {
   (yyval.rel_attr) = new RelAttrSqlNode;
   if((yyvsp[0].brace_string)!=nullptr&&(yyvsp[0].brace_string)->size()==1)
    (yyval.rel_attr)->attribute_name=*((yyvsp[0].brace_string)->begin());
    else
    (yyval.rel_attr)->attribute_name="";
   (yyval.rel_attr)->type=AGG_MAX;
   delete (yyvsp[0].brace_string);
  }
#line 2687 "yacc_sql.cpp"
    break;

  case 97: /* rel_attr: MIN brace_string  */
#line 842 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
   if((yyvsp[0].brace_string)!=nullptr&&(yyvsp[0].brace_string)->size()==1)
    (yyval.rel_attr)->attribute_name=*((yyvsp[0].brace_string)->begin());
    else
    (yyval.rel_attr)->attribute_name="";
   (yyval.rel_attr)->type=AGG_MIN;
   delete (yyvsp[0].brace_string);
  }
#line 2701 "yacc_sql.cpp"
    break;

  case 98: /* rel_attr: COUNT brace_string  */
#line 852 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
   if((yyvsp[0].brace_string)!=nullptr&&(yyvsp[0].brace_string)->size()==1)
    (yyval.rel_attr)->attribute_name=*((yyvsp[0].brace_string)->begin());
    else
    (yyval.rel_attr)->attribute_name="";
   (yyval.rel_attr)->type=AGG_COUNT;
   delete (yyvsp[0].brace_string);
  }
#line 2715 "yacc_sql.cpp"
    break;

  case 99: /* rel_attr: AVG brace_string  */
#line 862 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
   if((yyvsp[0].brace_string)!=nullptr&&(yyvsp[0].brace_string)->size()==1)
    (yyval.rel_attr)->attribute_name=*((yyvsp[0].brace_string)->begin());
    else
    (yyval.rel_attr)->attribute_name="";
   (yyval.rel_attr)->type=AGG_AVG;
   delete (yyvsp[0].brace_string);
  }
#line 2729 "yacc_sql.cpp"
    break;

  case 100: /* rel_attr: SUM brace_string  */
#line 872 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
   if((yyvsp[0].brace_string)!=nullptr&&(yyvsp[0].brace_string)->size()==1)
    (yyval.rel_attr)->attribute_name=*((yyvsp[0].brace_string)->begin());
    else
    (yyval.rel_attr)->attribute_name="";
   (yyval.rel_attr)->type=AGG_SUM;
   delete (yyvsp[0].brace_string);
  }
#line 2743 "yacc_sql.cpp"
    break;

  case 101: /* attr_list: %empty  */
#line 885 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 102: /* attr_list: COMMA rel_attr attr_list  */
#line 888 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 103: /* rel_list: %empty  */
#line 902 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 104: /* rel_list: COMMA ID rel_list  */
#line 905 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2789 "yacc_sql.cpp"
    break;

  case 105: /* where: %empty  */
#line 918 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2797 "yacc_sql.cpp"
    break;

  case 106: /* where: WHERE condition_list  */
#line 921 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2805 "yacc_sql.cpp"
    break;

  case 107: /* inner_list: %empty  */
#line 927 "yacc_sql.y"
{
(yyval.inner_list)=nullptr;
}
#line 2813 "yacc_sql.cpp"
    break;

  case 108: /* inner_list: INNER JOIN ID ON condition_list inner_list  */
#line 932 "yacc_sql.y"
{
  if((yyvsp[0].inner_list)!=nullptr){
    (yyval.inner_list)=(yyvsp[0].inner_list);
  }
  else{
    (yyval.inner_list)=new InnerListNode;
  }
  ((yyval.inner_list)->table_name).push_back((yyvsp[-3].string));
  free ((yyvsp[-3].string));

  //处理on后面的条件

  if ((yyvsp[-1].condition_list) != nullptr) {
    ((yyval.inner_list)->conditions).insert((yyval.inner_list)->conditions.end(),(yyvsp[-1].condition_list)->begin(),(yyvsp[-1].condition_list)->end());
    delete (yyvsp[-1].condition_list);
  } 
}
#line 2835 "yacc_sql.cpp"
    break;

  case 109: /* condition_list: %empty  */
#line 951 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2843 "yacc_sql.cpp"
    break;

  case 110: /* condition_list: condition  */
#line 954 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: condition AND condition_list  */
#line 959 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 112: /* condition: rel_attr comp_op value  */
#line 967 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 113: /* condition: value comp_op value  */
#line 979 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 114: /* condition: rel_attr comp_op rel_attr  */
#line 991 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2911 "yacc_sql.cpp"
    break;

  case 115: /* condition: value comp_op rel_attr  */
#line 1003 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2927 "yacc_sql.cpp"
    break;

  case 116: /* condition: rel_attr LIKE SSS  */
#line 1015 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->att_name=(yyvsp[-2].rel_attr)->attribute_name;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->like=(yyvsp[0].string);
      (yyval.condition)->is_like=true;
      delete (yyvsp[0].string);
      delete (yyvsp[-2].rel_attr);
    }
#line 2942 "yacc_sql.cpp"
    break;

  case 117: /* condition: rel_attr NOT LIKE SSS  */
#line 1026 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->att_name=(yyvsp[-3].rel_attr)->attribute_name;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->not_like=(yyvsp[0].string);
      (yyval.condition)->is_not_like=true;
      delete (yyvsp[0].string);
      delete (yyvsp[-3].rel_attr);
    }
#line 2957 "yacc_sql.cpp"
    break;

  case 118: /* condition: rel_attr IN LBRACE select_stmt RBRACE  */
#line 1037 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in;

      delete (yyvsp[-4].rel_attr);
    }
#line 2972 "yacc_sql.cpp"
    break;

  case 119: /* condition: rel_attr NOT IN LBRACE select_stmt RBRACE  */
#line 1048 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = not_in;

      delete (yyvsp[-5].rel_attr);
    }
#line 2987 "yacc_sql.cpp"
    break;

  case 120: /* condition: rel_attr EQ LBRACE select_stmt RBRACE  */
#line 1059 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in_EQUAL_TO;

      delete (yyvsp[-4].rel_attr);
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 121: /* condition: LBRACE select_stmt RBRACE EQ rel_attr  */
#line 1070 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = in_EQUAL_TO;
      delete (yyvsp[0].rel_attr);
    }
#line 3016 "yacc_sql.cpp"
    break;

  case 122: /* condition: rel_attr LT LBRACE select_stmt RBRACE  */
#line 1080 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in_LESS_THAN;

      delete (yyvsp[-4].rel_attr);
    }
#line 3031 "yacc_sql.cpp"
    break;

  case 123: /* condition: LBRACE select_stmt RBRACE LT rel_attr  */
#line 1091 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = in_GREAT_THAN;
      delete (yyvsp[0].rel_attr);
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 124: /* condition: rel_attr GT LBRACE select_stmt RBRACE  */
#line 1101 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in_GREAT_THAN;

      delete (yyvsp[-4].rel_attr);
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 125: /* condition: LBRACE select_stmt RBRACE GT rel_attr  */
#line 1112 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = in_LESS_THAN;
      delete (yyvsp[0].rel_attr);
    }
#line 3074 "yacc_sql.cpp"
    break;

  case 126: /* condition: rel_attr LE LBRACE select_stmt RBRACE  */
#line 1122 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in_LESS_EQUAL;

      delete (yyvsp[-4].rel_attr);
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 127: /* condition: LBRACE select_stmt RBRACE LE rel_attr  */
#line 1133 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = in_GREAT_EQUAL;
      delete (yyvsp[0].rel_attr);
    }
#line 3103 "yacc_sql.cpp"
    break;

  case 128: /* condition: rel_attr GE LBRACE select_stmt RBRACE  */
#line 1143 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in_GREAT_EQUAL;

      delete (yyvsp[-4].rel_attr);
    }
#line 3118 "yacc_sql.cpp"
    break;

  case 129: /* condition: LBRACE select_stmt RBRACE GE rel_attr  */
#line 1154 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = in_LESS_EQUAL;
      delete (yyvsp[0].rel_attr);
    }
#line 3132 "yacc_sql.cpp"
    break;

  case 130: /* condition: rel_attr NE LBRACE select_stmt RBRACE  */
#line 1164 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = in_NOT_EQUAL;

      delete (yyvsp[-4].rel_attr);
    }
#line 3147 "yacc_sql.cpp"
    break;

  case 131: /* condition: LBRACE select_stmt RBRACE NE rel_attr  */
#line 1175 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->sub_select=&((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = in_NOT_EQUAL;
      delete (yyvsp[0].rel_attr);
    }
#line 3161 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: EQ  */
#line 1187 "yacc_sql.y"
            { (yyval.comp) = EQUAL_TO; }
#line 3167 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: LT  */
#line 1188 "yacc_sql.y"
            { (yyval.comp) = LESS_THAN; }
#line 3173 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: GT  */
#line 1189 "yacc_sql.y"
            { (yyval.comp) = GREAT_THAN; }
#line 3179 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: LE  */
#line 1190 "yacc_sql.y"
            { (yyval.comp) = LESS_EQUAL; }
#line 3185 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: GE  */
#line 1191 "yacc_sql.y"
            { (yyval.comp) = GREAT_EQUAL; }
#line 3191 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: NE  */
#line 1192 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 3197 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: IS  */
#line 1193 "yacc_sql.y"
            { (yyval.comp) = is;}
#line 3203 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: IS NOT  */
#line 1194 "yacc_sql.y"
            { (yyval.comp) = is_not;}
#line 3209 "yacc_sql.cpp"
    break;

  case 140: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1199 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3223 "yacc_sql.cpp"
    break;

  case 141: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1212 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3232 "yacc_sql.cpp"
    break;

  case 142: /* set_variable_stmt: SET ID EQ value  */
#line 1220 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3244 "yacc_sql.cpp"
    break;


#line 3248 "yacc_sql.cpp"

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

#line 1232 "yacc_sql.y"

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
