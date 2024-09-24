
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
         CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        UNIQUE
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        LIKE
        NOT
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        INNER
        JOIN
        MAX
        MIN
        COUNT
        AVG
        SUM
        ORDER
        BY
        ASC
        NULL_T
        IS
        IN
        EQ
        LT
        GT
        LE
        GE
        NE
       

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  InnerListNode*                    inner_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::string> *        relation_list;
  std::vector<std::string> *        brace_string;
  std::vector<std::string> *        more_brace_string;
  std::vector<updateNode> *         UpdateNode;
  std::vector<OrderBy> *            OrderByNode;
  std::vector<OrderBy> *            more_OrderByNode;
  bool                              nullable;
  char *                            string;
  int                               number;
  float                             floats;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <nullable>            nullable
%type <rel_attr>            rel_attr
%type <OrderByNode>         OrderByNode
%type <more_OrderByNode>    more_OrderByNode
%type <brace_string>        brace_string
%type <brace_string>        more_brace_string
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <UpdateNode>          UpdateNode
%type <condition_list>      condition_list
%type <inner_list>          inner_list
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
%type <rel_attr_list>       attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

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
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | show_index_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
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
show_index_stmt:       /*SHOW INDEX 语句的语法解析树*/
    SHOW INDEX FROM ID{
      $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
      $$->show_index.relation_name=$4;
      free($4);
    };

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      if($8!=nullptr){
      create_index.attribute_names.swap(*$8);}
      create_index.attribute_names.push_back($7);
      create_index.relation_name = $5;
      free($3);
      free($5);
      free($7);
    }
    |CREATE UNIQUE INDEX ID ON ID LBRACE ID rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      if($9!=nullptr){
      create_index.attribute_names.swap(*$9);}
      create_index.attribute_names.push_back($8);
      create_index.relation_name = $6;
      create_index.unique_index=true;
      free($4);
      free($6);
      free($8);
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
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
nullable:
/* empty */
  {
    $$ = true;
  }
  |NULL_T
  {
    $$ = true;
  }
  |NOT NULL_T
  {
    $$=false;
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
    ID type LBRACE number RBRACE  nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->can_be_null=$6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->can_be_null=$3;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE value_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($9 != nullptr) {
        $$->insertion.values.swap(*$9);
      }
      if($7!=nullptr){
      $$->insertion.values.insert(($$->insertion.values).end(),$7->begin(),$7->end());}
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    |COMMA LBRACE value value_list RBRACE value_list
    {
      if ($6 != nullptr) {
        $$ = $6;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->insert($$->end(),$4->begin(),$4->end());
      $$->emplace_back(*$3);
      delete $3;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |NULL_T{
      $$ = new Value("null");
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value UpdateNode where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      if($7!=nullptr){
        $$->update.update_nodes.swap(*$7);
        delete $7;
      }
      updateNode temp;
      temp.attribute_name=$4;
      temp.value=*$6;
      $$->update.update_nodes.emplace_back(temp);

      if ($8 != nullptr) {
        $$->update.conditions.swap(*$8);
        delete $8;
      }
      free($2);
      free($4);
    }
    ;

UpdateNode:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID EQ value UpdateNode { 
      if($5!=nullptr){
        $$=$5;
      }else{
        $$=new std::vector<updateNode>;
      }
      updateNode temp;
      temp.attribute_name=$2;
      temp.value=*$4;
      $$->emplace_back(temp);
      free($2);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr  FROM ID rel_list inner_list where OrderByNode
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      //处理表名
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      free($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if($6 != nullptr ){
        $$->selection.inner=*$6;
        delete $6;
      }

      if ($7 != nullptr) {
        $$->selection.conditions.swap(*$7);
        delete $7;
      }
      if($8!=nullptr){
        $$->selection.order_bys.swap(*$8);
        std::reverse($$->selection.order_bys.begin(), $$->selection.order_bys.end());
        delete $8;
      }
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
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
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;
OrderByNode:
  //NULL
  {
    $$=nullptr;
  }
  |ORDER BY rel_attr ASC  more_OrderByNode
  {
    if($5!=nullptr){
      $$=$5;
    }else{
      $$=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*$3;
    node.type=UP_asc;
    $$->emplace_back(node);
  }
  |ORDER BY rel_attr DESC  more_OrderByNode
  {
    if($5!=nullptr){
      $$=$5;
    }else{
      $$=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*$3;
    node.type=DOWN_desc;
    $$->emplace_back(node);
  }|ORDER BY rel_attr   more_OrderByNode
  {
    if($4!=nullptr){
      $$=$4;
    }else{
      $$=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*$3;
    node.type=UP_asc;
    $$->emplace_back(node);
  }
  
more_OrderByNode:
//NULL
  {
    $$=nullptr;
  }
  |COMMA rel_attr ASC  more_OrderByNode
  {
    if($4!=nullptr){
      $$=$4;
    }else{
      $$=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*$2;
    node.type=UP_asc;
    $$->emplace_back(node);
  }
  |COMMA rel_attr DESC  more_OrderByNode
  {
    if($4!=nullptr){
      $$=$4;
    }else{
      $$=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*$2;
    node.type=DOWN_desc;
    $$->emplace_back(node);
  }|COMMA rel_attr   more_OrderByNode
  {
    if($3!=nullptr){
      $$=$3;
    }else{
      $$=new std::vector<OrderBy>;
    }
    OrderBy node;
    node.attributes=*$2;
    node.type=UP_asc;
    $$->emplace_back(node);
  }
  ;

select_attr:
    {
      $$=nullptr;
    }
    |'*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      $$->emplace_back(attr);
    }
    | rel_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    |'*' COMMA rel_attr attr_list{
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      if ($4 != nullptr) {
        $$ = $4;
      }
      $$->emplace_back(*$3);
      $$->emplace_back(attr); 
      delete $3;
    }
    ;

brace_string:
  /* empty */
  {
    $$ = nullptr;
  }
  |LBRACE RBRACE
  {
    $$ =nullptr;
  }
  |LBRACE ID more_brace_string RBRACE
  {
    if($3!=nullptr)
    {
      $$=$3;
    }else{
    $$ =new std::vector<std::string>;
    }
    $$->push_back($2);
    free($2);
  }
  |LBRACE ID DOT ID more_brace_string RBRACE
  {
    if($5!=nullptr)
    {
      $$=$5;
    }else{
    $$ =new std::vector<std::string>;
    }
    $$->push_back($4);
    free($4);
    free($2);
  }
  |LBRACE '*' more_brace_string RBRACE
  {
    if($3!=nullptr)
    {
      $$=$3;
    }else{
    $$ =new std::vector<std::string>;
    }
    $$->push_back("*");
  }
  ;

more_brace_string:
  /* empty */
  {
    $$ = nullptr;
  }
  |COMMA ID brace_string
  {
    if($3!=nullptr)
    {
      $$=$3;
    }else{
    $$ =new std::vector<std::string>;
    }
    $$->push_back($2);
    free($2);
  }
  |COMMA ID DOT ID brace_string
  {
    if($5!=nullptr)
    {
      $$=$5;
    }else{
    $$ =new std::vector<std::string>;
    }
    $$->push_back($4);
    free($4);
    free($2);
  }
  |COMMA '*' brace_string
  {
    if($3!=nullptr)
    {
      $$=$3;
    }else{
    $$ =new std::vector<std::string>;
    }
    $$->push_back("*");
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
  |MAX brace_string 
  {
   $$ = new RelAttrSqlNode;
   if($2!=nullptr&&$2->size()==1)
    $$->attribute_name=*($2->begin());
    else
    $$->attribute_name="";
   $$->type=AGG_MAX;
   delete $2;
  }
  |MIN brace_string 
  {
    $$ = new RelAttrSqlNode;
   if($2!=nullptr&&$2->size()==1)
    $$->attribute_name=*($2->begin());
    else
    $$->attribute_name="";
   $$->type=AGG_MIN;
   delete $2;
  }
  |COUNT brace_string 
  {
    $$ = new RelAttrSqlNode;
   if($2!=nullptr&&$2->size()==1)
    $$->attribute_name=*($2->begin());
    else
    $$->attribute_name="";
   $$->type=AGG_COUNT;
   delete $2;
  }
  |AVG brace_string 
  {
    $$ = new RelAttrSqlNode;
   if($2!=nullptr&&$2->size()==1)
    $$->attribute_name=*($2->begin());
    else
    $$->attribute_name="";
   $$->type=AGG_AVG;
   delete $2;
  }
  |SUM brace_string 
  {
    $$ = new RelAttrSqlNode;
   if($2!=nullptr&&$2->size()==1)
    $$->attribute_name=*($2->begin());
    else
    $$->attribute_name="";
   $$->type=AGG_SUM;
   delete $2;
  }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }

      $$->push_back($2);
      free($2);
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
inner_list:
 /* empty */
{
$$=nullptr;
}
|
INNER JOIN ID ON condition_list inner_list
{
  if($6!=nullptr){
    $$=$6;
  }
  else{
    $$=new InnerListNode;
  }
  ($$->table_name).push_back($3);
  free ($3);

  //处理on后面的条件

  if ($5 != nullptr) {
    ($$->conditions).insert($$->conditions.end(),$5->begin(),$5->end());
    delete $5;
  } 
};
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    |rel_attr LIKE SSS
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->att_name=$1->attribute_name;
      $$->right_is_attr = 0;
      $$->like=$3;
      $$->is_like=true;
      delete $3;
      delete $1;
    }
    |rel_attr NOT LIKE SSS
    {
      $$ = new ConditionSqlNode;
      $$->att_name=$1->attribute_name;
      $$->left_is_attr = 1;
      $$->right_is_attr = 0;
      $$->not_like=$4;
      $$->is_not_like=true;
      delete $4;
      delete $1;
    }
    |rel_attr IN LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in;

      delete $1;
    }
    |rel_attr NOT IN LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($5->selection);
      $$->comp = not_in;

      delete $1;
    }
    |rel_attr EQ LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in_EQUAL_TO;

      delete $1;
    }
    |LBRACE select_stmt RBRACE EQ rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$5;
      $$->right_is_attr = 0;
      $$->sub_select=&($2->selection);
      $$->comp = in_EQUAL_TO;
      delete $5;
    }
    |rel_attr LT LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in_LESS_THAN;

      delete $1;
    }
    |LBRACE select_stmt RBRACE LT rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$5;
      $$->right_is_attr = 0;
      $$->sub_select=&($2->selection);
      $$->comp = in_GREAT_THAN;
      delete $5;
    }
    |rel_attr GT LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in_GREAT_THAN;

      delete $1;
    }
    |LBRACE select_stmt RBRACE GT rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$5;
      $$->right_is_attr = 0;
      $$->sub_select=&($2->selection);
      $$->comp = in_LESS_THAN;
      delete $5;
    }
    |rel_attr LE  LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in_LESS_EQUAL;

      delete $1;
    }
    |LBRACE select_stmt RBRACE LE rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$5;
      $$->right_is_attr = 0;
      $$->sub_select=&($2->selection);
      $$->comp = in_GREAT_EQUAL;
      delete $5;
    }
    |rel_attr GE  LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in_GREAT_EQUAL;

      delete $1;
    }
    |LBRACE select_stmt RBRACE GE rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$5;
      $$->right_is_attr = 0;
      $$->sub_select=&($2->selection);
      $$->comp = in_LESS_EQUAL;
      delete $5;
    }
    |rel_attr NE  LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->sub_select=&($4->selection);
      $$->comp = in_NOT_EQUAL;

      delete $1;
    }
    |LBRACE select_stmt RBRACE NE rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$5;
      $$->right_is_attr = 0;
      $$->sub_select=&($2->selection);
      $$->comp = in_NOT_EQUAL;
      delete $5;
    }
    ;

comp_op:
      EQ    { $$ = EQUAL_TO; }
    | LT    { $$ = LESS_THAN; }
    | GT    { $$ = GREAT_THAN; }
    | LE    { $$ = LESS_EQUAL; }
    | GE    { $$ = GREAT_EQUAL; }
    | NE    { $$ = NOT_EQUAL; }
    | IS    { $$ = is;}
    | IS NOT{ $$ = is_not;}
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
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

opt_semicolon: /*empty*/
    | SEMICOLON
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
