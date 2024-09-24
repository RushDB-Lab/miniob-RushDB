#include "src/observer/sql/operator/aggfuncs/sum_agg_func.h"
#include "sql/parser/value.h"

RC sum_agg_func::init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record)
{
  RC rc            = RC::SUCCESS;
  agg_func         = info_of_funcs_;
  table            = table_;
  field_meta       = field_meta_;
  table_field_mata = table->table_meta().field(field_meta->name());
  return rc;
}

RC sum_agg_func::update(const Record &current_record_)
{
  Value now;
  now.set_type(table_field_mata->attr_type());
  now.set_data(current_record_.data() + table_field_mata->offset(), table_field_mata->len());
  if (now.attr_type() == null) {
    has_null = true;
    return RC::SUCCESS;
  }
  switch (table_field_mata->attr_type()) {
    case INTS: {
      int_sum += now.get_int();
    } break;
    case FLOATS: {
      float_sum += now.get_float();
    } break;
    default: {
      return RC::FAILURE;
    }
  }
  return RC::SUCCESS;
}
Value sum_agg_func::get_value()
{
  if (int_sum == 0 && float_sum == 0 && has_null)
    return Value("null");
  switch (table_field_mata->attr_type()) {
    case INTS: {
      return Value(int_sum);
    } break;
    case FLOATS: {
      return Value(float_sum);
    } break;
    default: {
      return Value(-999999);
    }
  }
}
