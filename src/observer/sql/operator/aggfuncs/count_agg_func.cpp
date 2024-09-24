#include "src/observer/sql/operator/aggfuncs/count_agg_func.h"
#include "sql/parser/value.h"
#include <cstring>

RC count_agg_func::init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record)
{
  RC rc    = RC::SUCCESS;
  agg_func = info_of_funcs_;
  table    = table_;
  if (agg_func.attributes.attribute_name == "*")
    field_meta = nullptr;
  else {
    //std::cout << agg_func.attributes.attribute_name.c_str() << std::endl;
    field_meta = table->find_fieldmate_by_name(agg_func.attributes.attribute_name.c_str());
  }
  return rc;
}

RC count_agg_func::update(const Record &current_record_)
{
  if (field_meta == nullptr || std::memcmp(current_record_.data() + field_meta->offset(), "null", 4) != 0)
    all_counts++;
  return RC::SUCCESS;
}

Value count_agg_func::get_value() { return Value(all_counts); }
