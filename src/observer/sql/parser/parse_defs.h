/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi
//

#pragma once

#include <string>
// #include <utility>
#include <vector>
#include <memory>

#include "common/value.h"

class Expression;

/**
 * @defgroup SQLParser SQL Parser
 */

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct RelAttrSqlNode
{
  std::string relation_name;   ///< relation name (may be NULL) 表名
  std::string attribute_name;  ///< attribute name              属性名
};

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp
{
  EQUAL_TO,       ///< "="
  LESS_EQUAL,     ///< "<="
  NOT_EQUAL,      ///< "<>"
  LESS_THAN,      ///< "<"
  GREAT_EQUAL,    ///< ">="
  GREAT_THAN,     ///< ">"
  IS_OP,          ///< "is (null)"
  IS_NOT_OP,      ///< "is not (null)"
  LIKE_OP,        ///< "like"
  NOT_LIKE_OP,    ///< "not like"
  IN_OP,          ///< "in (sub query)"
  NOT_IN_OP,      ///< "not in (sub query)"
  EXISTS_OP,      ///< "exists (sub query)"
  NOT_EXISTS_OP,  ///< "not exists (sub query)"
  NO_OP
};

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode
{
  int left_is_attr;              ///< TRUE if left-hand side is an attribute
                                 ///< 1时，操作符左边是属性名，0时，是属性值
  Value          left_value;     ///< left-hand side value if left_is_attr = FALSE
  RelAttrSqlNode left_attr;      ///< left-hand side attribute
  CompOp         comp;           ///< comparison operator
  int            right_is_attr;  ///< TRUE if right-hand side is an attribute
                                 ///< 1时，操作符右边是属性名，0时，是属性值
  RelAttrSqlNode right_attr;     ///< right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value          right_value;    ///< right-hand side value if right_is_attr = FALSE
};

/**
 * @brief 描述一个relation的节点
 */
struct RelationNode
{
  RelationNode(std::string relation_, std::string alias_) : relation(std::move(relation_)), alias(std::move(alias_)) {}
  explicit RelationNode(std::string relation_) : relation(std::move(relation_)) {}
  std::string relation;  ///< 查询的表
  std::string alias;     ///< 该表的别名 (may be NULL)
};

/**
 * @brief 描述一个orderby的节点
 */
struct OrderBySqlNode
{
  std::unique_ptr<Expression> expr;
  bool                        is_asc;  ///< 默认true 为升序
};

struct LimitSqlNode
{
  int number;
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */
struct SelectSqlNode
{
  std::vector<std::unique_ptr<Expression>> expressions;        ///< 查询的表达式
  std::vector<RelationNode>                relations;          ///< 查询的表
  std::unique_ptr<Expression>              conditions;         ///< 查询条件，使用AND串联起来多个条件
  std::vector<std::unique_ptr<Expression>> group_by;           ///< group by clause
  std::vector<OrderBySqlNode>              order_by;           ///< attributes in order clause
  std::unique_ptr<Expression>              having_conditions;  ///< having
  std::unique_ptr<LimitSqlNode>            limit;
};

/**
 * @brief 描述一个join语句
 * @ingroup SQLParser
 * @details 目前只支持 inner join，解析表和条件后直接放到 SelectSqlNode 里。
 */
struct JoinSqlNode
{
  std::vector<std::string>    relations;   ///< 查询的表
  std::unique_ptr<Expression> conditions;  ///< 查询条件，可能有多个
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode
{
  std::vector<std::unique_ptr<Expression>> expressions;  ///< calc clause
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode
{
  std::string                     relation_name;  ///< Relation to insert into
  std::vector<std::string>        attr_names;     ///< attribute names
  std::vector<std::vector<Value>> values_list;    ///< 要插入的值列表
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode
{
  std::string                 relation_name;  ///< Relation to delete from
  std::unique_ptr<Expression> condition;
};

/**
 * @brief 描述一个set语句
 * @ingroup SQLParser
 */
struct SetClauseSqlNode
{
  std::string                 field_name;  ///< 更新的字段
  std::unique_ptr<Expression> value;       ///< 更新的值
};

/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode
{
  std::string                   relation_name;  ///< Relation to update
  std::vector<SetClauseSqlNode> set_clauses;    ///< 更新的set语句，支持多个字段和值
  std::unique_ptr<Expression>   conditions;     ///< 谓词条件
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 */
struct AttrInfoSqlNode
{
  AttrType    type;             ///< Type of attribute
  std::string name;             ///< Attribute name
  size_t      length;           ///< Length of attribute
  bool        nullable;         ///< 字段是否可以为空
  bool        mutable_ = true;  ///< 视图字段是否是可插入修改的
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode
{
  std::string                    relation_name;        ///< Relation name
  std::vector<AttrInfoSqlNode>   attr_infos;           ///< attributes
  std::string                    storage_format;       ///< storage format
  std::unique_ptr<SelectSqlNode> create_table_select;  ///< create table select
};

/**
 * @brief 描述一个create view语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateViewSqlNode
{
  std::string                    relation_name;       ///< Relation name
  std::vector<std::string>       attribute_names;     ///< attribute names
  std::unique_ptr<SelectSqlNode> create_view_select;  ///< create table select
};

/**
 * @brief 描述一个drop view语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct DropViewSqlNode
{
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode
{
  std::string relation_name;  ///< 要删除的表名
};

enum class IndexType
{
  BPlusTreeIndex,
  VectorIVFFlatIndex,  // 目前就支持以上两种
  VectorHNSWIndex
};

struct VectorIndexConfig
{
  std::string distance_fn;                             ///< 距离度量方法
  IndexType   index_type = IndexType::BPlusTreeIndex;  ///< 索引类型，非向量索引情况默认为 b+ 树
  Value       lists;                                   ///< 列表数量
  Value       probes;                                  ///< 探测次数
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode
{
  bool                     unique;               ///< unique index
  std::string              index_name;           ///< Index name
  std::string              relation_name;        ///< Relation name
  std::vector<std::string> attribute_name;       ///< Attribute name
  VectorIndexConfig        vector_index_config;  ///< 向量索引还有一些额外参数
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode
{
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个show index语句
 * @ingroup SQLParser
 */
struct ShowIndexSqlNode
{
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode
{
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode
{
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode
{
  std::string name;
  Value       value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode
{
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode
{
  std::string error_msg;
  int         line;
  int         column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag
{
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SHOW_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_CREATE_VIEW,
  SCF_DROP_VIEW,
  SCF_BEGIN,  ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE,  ///< 设置变量
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode
{
public:
  enum SqlCommandFlag flag;
  ErrorSqlNode        error;
  CalcSqlNode         calc;
  SelectSqlNode       selection;
  InsertSqlNode       insertion;
  DeleteSqlNode       deletion;
  UpdateSqlNode       update;
  CreateTableSqlNode  create_table;
  DropTableSqlNode    drop_table;
  CreateIndexSqlNode  create_index;
  DropIndexSqlNode    drop_index;
  ShowIndexSqlNode    show_index;
  DescTableSqlNode    desc_table;
  CreateViewSqlNode   create_view;
  DropViewSqlNode     drop_view;
  LoadDataSqlNode     load_data;
  ExplainSqlNode      explain;
  SetVariableSqlNode  set_variable;

public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult
{
public:
  void add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);

  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes() { return sql_nodes_; }

private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
