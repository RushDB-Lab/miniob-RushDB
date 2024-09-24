#pragma once
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
#include "src/observer/common/rc.h"
#include "src/observer/sql/parser/parse_defs.h"
#include "src/observer/storage/table/table.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
class aggregation
{
public:
  friend class AggFuncPhysicalOperator;
  aggregation()  = default;
  ~aggregation() = default;
  virtual RC    init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record) = 0;
  virtual RC    update(const Record &current_record_)                                                              = 0;
  int           compare_with_record(const Record *first, const Record *second, const FieldMeta *field_meta);
  virtual Value get_value() = 0;

protected:
  const FieldMeta *table_field_mata;
  Agg_Func         agg_func;
  Value            return_value;
};