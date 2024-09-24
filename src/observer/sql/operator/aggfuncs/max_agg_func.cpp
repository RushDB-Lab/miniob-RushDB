#include "src/observer/sql/operator/aggfuncs/max_agg_func.h"
#include "sql/parser/value.h"

RC max_agg_func::init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record)
{
  RC rc            = RC::SUCCESS;
  agg_func         = info_of_funcs_;
  table            = table_;
  field_meta       = field_meta_;
  max_record       = current_record;
  table_field_mata = table->table_meta().field(field_meta->name());
  return rc;
}

RC max_agg_func::update(const Record &current_record_)
{
  if (max_record.data() == nullptr) {
    max_record = current_record_;
    return RC::SUCCESS;
  }
  if (compare_with_record(&current_record_, &max_record, table_field_mata) > 0) {
    max_record = current_record_;
  }
  return RC::SUCCESS;
}
Value max_agg_func::get_value()
{
  return_value.set_type(field_meta->attr_type());
  return_value.set_data(max_record.data() + table_field_mata->offset(), table_field_mata->len());
  return return_value;
}
