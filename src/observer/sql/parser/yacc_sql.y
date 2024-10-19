
%{

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
%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        AS
        ASC
        BY
        CREATE
        DROP
        EXISTS
        GROUP
        HAVING
        ORDER
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        LSBRACE
        RSBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        IN
        TRUE
        FALSE
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        VECTOR_T
        NOT
        UNIQUE
        NULL_T
        LIMIT
        NULLABLE
        HELP
        QUOTE
        EXIT
        DOT
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
        SET
        ON
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        INNER
        JOIN
        VIEW
        WITH
        DISTANCE
        TYPE
        LISTS
        PROBES
        IVFFLAT
        EQ
        LT
        GT
        LE
        GE
        NE
        LIKE
        IS

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
  enum IndexType                             index_type;
  VectorIndexConfig *                        vector_index_config;
  float                                      digits;
  std::vector<float> *                       digits_list;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <digits>              digits
%type <digits_list>         digits_list
%type <value>               value
%type <value>               nonnegative_value
%type <string>              relation
%type <string>              alias
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <nullable_info>       nullable_constraint
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <values_list>         values_list
%type <expression>          condition
%type <string>              storage_format
%type <relation_list>       rel_list
%type <expression>          expression
%type <expression>          where
%type <expression>          func_expr
%type <expression>          sub_query_expr
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <expression>          opt_having
%type <set_clause>          set_clause
%type <set_clauses>         set_clauses
%type <join_clauses>        join_clauses
%type <orderby_unit>        sort_unit
%type <orderby_list>        sort_list
%type <orderby_list>        opt_order_by
%type <limited_info>        opt_limit
%type <index_attr_list>     attr_list
%type <unique>              opt_unique
%type <index_type>          index_type
%type <vector_index_config> vector_index_config
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            create_view_stmt
%type <sql_node>            drop_view_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left OR
%left AND
%left EQ LT GT LE GE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    select_stmt
  | calc_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | show_index_stmt
  | create_view_stmt
  | drop_view_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

show_index_stmt:
      SHOW INDEX FROM relation
    {
      $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
      ShowIndexSqlNode &show_index = $$->show_index;
      show_index.relation_name = $4;
      free($4);
    }
    ;

create_index_stmt:
    CREATE opt_unique INDEX ID ON ID LBRACE attr_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.unique = $2; // 用 opt_unique 的返回值来确定是否 UNIQUE
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.attribute_name.swap(*$8); // $8 是 vector<string> 类型
      delete $8; // 释放指针
      free($4);
      free($6);
    }
    | CREATE VECTOR_T INDEX ID ON ID LBRACE attr_list RBRACE WITH vector_index_config
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.unique = false; // 向量索引不支持
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.attribute_name.swap(*$8); // $8 是 vector<string> 类型
      create_index.vector_index_config = std::move(*$11);
      delete $8; // 释放指针
      free($4);
      free($6);
    }
    ;

opt_unique:
    UNIQUE { $$ = true; }
    | /* 空 */ { $$ = false; }
    ;

index_type:
      IVFFLAT
    {
      $$ = IndexType::VectorIVFFlatIndex;
    }
    ;

vector_index_config:
      LBRACE DISTANCE EQ ID COMMA TYPE EQ index_type RBRACE
    {
      $$ = new VectorIndexConfig;
      $$->distance_fn = $4;
      $$->index_type = $8;
      free($4);
    }
    | LBRACE DISTANCE EQ ID COMMA TYPE EQ index_type COMMA LISTS EQ value COMMA PROBES EQ value RBRACE
    {
      $$ = new VectorIndexConfig;
      $$->distance_fn = $4;
      $$->index_type = $8;
      $$->lists = std::move(*$12);
      $$->probes = std::move(*$16);
      free($4);
    }
    | LBRACE TYPE EQ index_type COMMA DISTANCE EQ ID COMMA LISTS EQ value COMMA PROBES EQ value RBRACE
    {
      $$ = new VectorIndexConfig;
      $$->distance_fn = $8;
      $$->index_type = $4;
      $$->lists = std::move(*$12);
      $$->probes = std::move(*$16);
      free($8);
    }
    ;

attr_list:
    ID
    {
      $$ = new std::vector<std::string>; // 创建一个新的 vector
      $$->emplace_back($1); // 将列名加入 vector
      free($1);
    }
    | ID COMMA attr_list
    {
      $$ = $3; // 使用现有的 vector
      $$->emplace($$->begin(), $1); // 将新列名加入 vector 开头
      free($1);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt
    {
        $$ = create_table_sql_node($3, $5, $6, $8, $10);
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt
    {
        $$ = create_table_sql_node($3, $5, $6, $8, $9);
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
        $$ = create_table_sql_node($3, $5, $6, $8, nullptr);
    }
    | CREATE TABLE ID storage_format AS select_stmt
    {
        $$ = create_table_sql_node($3, nullptr, nullptr, $4, $6);
    }
    | CREATE TABLE ID storage_format select_stmt
    {
      $$ = create_table_sql_node($3, nullptr, nullptr, $4, $5);
    }
    ;

create_view_stmt:
      CREATE VIEW ID AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = $$->create_view;
      create_view.relation_name = $3;
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move($5->selection));
      free($3);
    }
    | CREATE VIEW ID LBRACE attr_list RBRACE AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = $$->create_view;
      create_view.relation_name = $3;
      create_view.attribute_names = std::move(*$5);
      create_view.create_view_select = std::make_unique<SelectSqlNode>(std::move($8->selection));
      free($3);
    }
    ;

drop_view_stmt:
      DROP VIEW ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_VIEW);
      $$->drop_view.relation_name = $3;
      free($3);
    }
    ;

attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE NUMBER RBRACE nullable_constraint
    {
      $$ = new AttrInfoSqlNode;
      $$->name = $1;
      $$->type = (AttrType)$2;
      if ($$->type == AttrType::CHARS) {
        $$->length = $4;
      } else if ($$->type == AttrType::VECTORS) {
        $$->length = sizeof(float) * $4;
      } else {
        ASSERT(false, "$$->type is invalid.");
      }
      $$->nullable = $6;
      if ($$->nullable) {
        $$->length++;
      }
      free($1);
    }
    | ID type nullable_constraint
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if ($$->type == AttrType::INTS) {
        $$->length = sizeof(int);
      } else if ($$->type == AttrType::FLOATS) {
        $$->length = sizeof(float);
      } else if ($$->type == AttrType::DATES) {
        $$->length = sizeof(int);
      } else if ($$->type == AttrType::CHARS) {
        $$->length = sizeof(char);
      } else if ($$->type == AttrType::VECTORS) {
        $$->length = sizeof(float) * 1;
      } else if ($$->type == AttrType::TEXTS) {
        $$->length = 65535;
      } else {
        ASSERT(false, "$$->type is invalid.");
      }
      $$->nullable = $3;  // 处理NULL/NOT NULL标记
      if ($$->nullable) {
        $$->length++;
      }
      free($1);
    }
    ;

nullable_constraint:
    NOT NULL_T
    {
      $$ = false;  // NOT NULL 对应的可空性为 false
    }
    | NULLABLE
    {
      $$ = true;  // NULLABLE 对应的可空性为 true 2022
    }
    | NULL_T
    {
      $$ = true;  // NULL 对应的可空性也为 true 2023
    }
    | /* empty */
    {
      $$ = true;  // 默认情况为 NULL
    }
    ;

type:
      INT_T      { $$ = static_cast<int>(AttrType::INTS);   }
    | STRING_T   { $$ = static_cast<int>(AttrType::CHARS);  }
    | FLOAT_T    { $$ = static_cast<int>(AttrType::FLOATS); }
    | DATE_T     { $$ = static_cast<int>(AttrType::DATES);  }
    | TEXT_T     { $$ = static_cast<int>(AttrType::TEXTS);  }
    | VECTOR_T   { $$ = static_cast<int>(AttrType::VECTORS);  }
    ;

insert_stmt:        /*insert   语句的语法解析树*/
      INSERT INTO ID VALUES values_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($5 != nullptr) {
        $$->insertion.values_list.swap(*$5);
        delete $5;
      }
      free($3);
    }
    | INSERT INTO ID LBRACE attr_list RBRACE VALUES values_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      $$->insertion.attr_names = std::move(*$5);
      if ($8 != nullptr) {
        $$->insertion.values_list.swap(*$8);
        delete $8;
      }
      free($3);
    }
    ;

values_list:
      LBRACE value_list RBRACE
    {
      $$ = new std::vector<std::vector<Value>>;
      $$->emplace_back(*$2);
      delete $2;
    }
    | values_list COMMA LBRACE value_list RBRACE
    {
      $$->emplace_back(*$4);
      delete $4;
    }

digits:
    NUMBER
    {
      $$ = float($1);
    }
    | '-' NUMBER
    {
      $$ = float(-$2);
    }
    | FLOAT
    {
      $$ = $1;
    }
    | '-' FLOAT
    {
      $$ = $2;
    }
    ;

digits_list:
    /* empty */
    {
      $$ = new std::vector<float>();
    }
    | digits
    {
      $$ = new std::vector<float>();
      $$->push_back($1);
    }
    | digits_list COMMA digits
    {
      $$->push_back($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = new std::vector<Value>;
    }
    | value
    {
      $$ = new std::vector<Value>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | value_list COMMA value
    {
      $$->emplace_back(*$3);
      delete $3;
    }
    ;

value:
    nonnegative_value {
      $$ = $1;
    }
    | '-' NUMBER {
      $$ = new Value(-$2);
      @$ = @1;
    }
    | '-' FLOAT {
      $$ = new Value(-$2);
      @$ = @1;
    }
    ;

nonnegative_value:
    NUMBER {
      $$ = new Value($1);
      @$ = @1;
    }
    | FLOAT {
      $$ = new Value($1);
      @$ = @1;
    }
    | SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | TRUE {
      $$ = new Value(true);
    }
    | FALSE {
      $$ = new Value(false);
    }
    | NULL_T {
      $$ = new Value(NullValue());
    }
    | LSBRACE digits_list RSBRACE {
      $$ = new Value(*$2);
    }
    ;

storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.condition = std::unique_ptr<Expression>($4);
      }
      free($3);
    }
    ;

update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET set_clauses where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.set_clauses.swap(*$4);
      if ($5 != nullptr) {
        $$->update.conditions = std::unique_ptr<Expression>($5);
      }
      free($2);
      delete $4;
    }
    ;

set_clauses:
      set_clause
    {
      $$ = new std::vector<SetClauseSqlNode>;
      $$->emplace_back(std::move(*$1));
    }
    | set_clauses COMMA set_clause
    {
      $$->emplace_back(std::move(*$3));
    }
    ;

set_clause:
      ID EQ expression
    {
      $$ = new SetClauseSqlNode;
      $$->field_name = $1;
      $$->value = std::unique_ptr<Expression>($3);
      free($1);
    }
    ;

select_stmt:
    SELECT expression_list FROM rel_list where group_by opt_having opt_order_by opt_limit
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      $$->selection.conditions = nullptr;

      if ($5 != nullptr) {
        $$->selection.conditions = std::unique_ptr<Expression>($5);
      }

      if ($6 != nullptr) {
        $$->selection.group_by.swap(*$6);
        delete $6;
      }

      if ($7 != nullptr) {
        $$->selection.having_conditions = std::unique_ptr<Expression>($7);
      }

      if ($8 != nullptr) {
        $$->selection.order_by.swap(*$8);
        delete $8;
      }

      if ($9 != nullptr) {
        $$->selection.limit = std::make_unique<LimitSqlNode>(*$9);
        delete $9;
      }
    }
    | SELECT expression_list FROM relation INNER JOIN join_clauses where group_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.emplace_back($4);
        free($4);
      }

      if ($7 != nullptr) {
        for (auto it = $7->relations.rbegin(); it != $7->relations.rend(); ++it) {
          $$->selection.relations.emplace_back(std::move(*it));
        }
        $$->selection.conditions = std::move($7->conditions);
      }

      if ($8 != nullptr) {
        auto ptr = $$->selection.conditions.release();
        $$->selection.conditions = std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, $8);
      }

      if ($9 != nullptr) {
        $$->selection.group_by.swap(*$9);
        delete $9;
      }
    }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    | SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    /* empty */ {
      $$ = new std::vector<std::unique_ptr<Expression>>;
    }
    | expression alias
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != $2) {
        $1->set_alias($2);
      }
      $$->emplace_back($1);
      free($2);
    }
    | expression alias COMMA expression_list
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      if (nullptr != $2) {
        $1->set_alias($2);
      }
      $$->emplace($$->begin(),std::move($1));
      free($2);
    }
    ;

expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression_list RBRACE {
      if ($2->size() == 1) {
        $$ = $2->front().get();
      } else {
        $$ = new ListExpr(std::move(*$2));
      }
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | nonnegative_value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    | ID DOT '*' {
      $$ = new StarExpr($1);
    }
    | func_expr {
      $$ = $1;      // AggrFuncExpr
    }
    | sub_query_expr {
      $$ = $1; // SubQueryExpr
    }
    // your code here
    ;

alias:
    /* empty */ {
      $$ = nullptr;
    }
    | ID {
      $$ = $1;
    }
    | AS ID {
      $$ = $2;
    }

func_expr:
    ID LBRACE expression_list RBRACE
    {
        $$ = new UnboundFunctionExpr($1, std::move(*$3));
        $$->set_name(token_name(sql_string, &@$));
    }
    ;

sub_query_expr:
    LBRACE select_stmt RBRACE
    {
      $$ = new SubQueryExpr($2->selection);
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;

rel_list:
    relation alias {
      $$ = new std::vector<RelationNode>();
      if(nullptr!=$2){
        $$->emplace_back($1,$2);
        free($2);
      }else{
        $$->emplace_back($1);
      }
      free($1);
    }
    | relation alias COMMA rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<RelationNode>;
      }
      if(nullptr!=$2){
        $$->insert($$->begin(), RelationNode($1,$2));
        free($2);
      }else{
        $$->insert($$->begin(), RelationNode($1));
      }
      free($1);
    }
    ;

join_clauses:
      relation ON condition
    {
      $$ = new JoinSqlNode;
      $$->relations.emplace_back($1);
      $$->conditions = std::unique_ptr<Expression>($3);
      free($1);
    }
    | relation ON condition INNER JOIN join_clauses
    {
      $$ = $6;
      $$->relations.emplace_back($1);
      auto ptr = $$->conditions.release();
      $$->conditions = std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, ptr, $3);
      free($1);
    }
    ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition {
      $$ = $2;  
    }
    ;

condition:
      expression comp_op expression
    {
      $$ = new ComparisonExpr($2, $1, $3);
    }
    | comp_op expression
    {
      Value val;
      val.set_null(true);
      ValueExpr *temp_expr = new ValueExpr(val);
      $$ = new ComparisonExpr($1,temp_expr, $2);
    }
    | condition AND condition
    {
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::AND, $1, $3);
    }
    | condition OR condition
    {
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::OR, $1, $3);
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS { $$ = IS_OP; }
    | IS NOT { $$ = IS_NOT_OP; }
    | LIKE { $$ = LIKE_OP;}
    | NOT LIKE {$$ = NOT_LIKE_OP;}
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN_OP; }
    | EXISTS { $$ = EXISTS_OP; }
    | NOT EXISTS { $$ = NOT_EXISTS_OP; }
    ;

opt_order_by:
	/* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY sort_list
    {
      $$ = $3;
      std::reverse($$->begin(),$$->end());
    }
    ;

sort_list:
	  sort_unit
	{
      $$ = new std::vector<OrderBySqlNode>;
      $$->emplace_back(std::move(*$1));
	}
    | sort_unit COMMA sort_list
	{
      $3->emplace_back(std::move(*$1));
      $$ = $3;
	}
	;

sort_unit:
	  expression
	{
      $$ = new OrderBySqlNode();
      $$->expr = std::unique_ptr<Expression>($1);
      $$->is_asc = true;
	}
	| expression DESC
	{
      $$ = new OrderBySqlNode();
      $$->expr = std::unique_ptr<Expression>($1);
      $$->is_asc = false;
	}
	| expression ASC
	{
      $$ = new OrderBySqlNode(); // 默认是升序
      $$->expr = std::unique_ptr<Expression>($1);
      $$->is_asc = true;
	}
	;

group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression_list
    {
      $$ = $3;
    }
    ;

opt_having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition
    {
      $$ = $2;
    }
    ;

opt_limit:
    /* empty */
    {
      $$ = nullptr;
    }
    | LIMIT NUMBER
    {
      $$ = new LimitSqlNode();
      $$->number = $2;
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon:
    SEMICOLON
    ;
%%
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
