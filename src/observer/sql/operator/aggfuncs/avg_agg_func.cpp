#include "src/observer/sql/operator/aggfuncs/avg_agg_func.h"
#include "common/rc.h"
#include "sql/parser/value.h"

RC avg_agg_func::init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record)
{
  RC rc            = RC::SUCCESS;
  agg_func         = info_of_funcs_;
  table            = table_;
  field_meta       = field_meta_;
  table_field_mata = table->table_meta().field(field_meta->name());
  return rc;
}

RC avg_agg_func::update(const Record &current_record_)
{
  if (std::memcmp(current_record_.data() + table_field_mata->offset(), "null", 4) != 0)
    all_counts++;
  else {
    has_null = true;
  }

  Value now;
  now.set_type(table_field_mata->attr_type());
  now.set_data(current_record_.data() + table_field_mata->offset(), table_field_mata->len());
  switch (table_field_mata->attr_type()) {
    case INTS: {
      int_sum += now.get_int();
    } break;
    case FLOATS: {
      float_sum += now.get_float();
    } break;
    case null: {
      float_sum += 0;
      int_sum += 0;
    } break;
    default: {
      return RC::FAILURE;
    }
  }
  return RC::SUCCESS;
}

Value avg_agg_func::get_value()
{
  if (all_counts != 0) {
    switch (table_field_mata->attr_type()) {
      case INTS: {
        return Value((float)int_sum / all_counts);
      } break;
      case FLOATS: {
        return Value((float)float_sum / all_counts);
      } break;
      default: {
        return Value(-999999);
      }
    }
  } else {
    if (!has_null)
      return Value(0);
    else
      return Value("null");
  }
}

/*SELECT avg(num) FROM aggregation_func;
- 52.39
+ 52
-- below are some requests executed before(partial) --
-- init data
CREATE TABLE aggregation_func(id int, num int, price float, addr char(4), birthday date);
-- insert data:168
INSERT INTO aggregation_func VALUES (40, 24, 90.0, '1KD3', '2008-10-25');
INSERT INTO aggregation_func VALUES (90, 39, 20.0, 'TZJC', '2001-09-13');
INSERT INTO aggregation_func VALUES (60, 31, 20.0, 'IPR', '1992-06-08');
INSERT INTO aggregation_func VALUES (70, 83, 30.0, 'C94', '2001-10-24');
INSERT INTO aggregation_func VALUES (40, 20, 40.0, '46', '1992-10-12');*/
