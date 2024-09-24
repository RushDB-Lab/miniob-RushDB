#pragma once
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
// #include "src/observer/sql/operator/orderby_operator/order_by_physical_operator.h"
#include "storage/field/field_meta.h"
#include <thread>
#include <mutex>
class Campator
{

public:
  friend class OrderByPhysicalOperator;
  Campator(orderby other) : type(other.type), field_mate(other.field_meta)
  {
    this->spec = new TupleCellSpec(other.attributes.relation_name.c_str(),
        other.attributes.attribute_name.c_str(),
        other.attributes.attribute_name.c_str());
  }

  bool compare(const Tuple *first, const Tuple *second) const
  {
   
    Value                                 first_value, second_value;
    int                                   val = 0;
    // std::cout << first << " " << second << std::endl;
    first->find_cell(*spec, first_value);
    second->find_cell(*spec, second_value);
    val = first_value.compare(second_value);
    if (val != 0) {
      if (type == UP_asc) {
        if (val > 0)
          return false;
        else
          return true;
      } else if (type == DOWN_desc) {
        if (val > 0)
          return true;
        else
          return false;
      }
    }
    if (child_compator != nullptr) {
      return child_compator->compare(first, second);
    }
    return false;
  }

private:
  orderby_type         type           = UNDEFINED_ORDER_TYPE;
  const TupleCellSpec *spec           = nullptr;
  const FieldMeta     *field_mate     = nullptr;
  Campator            *child_compator = nullptr;
};