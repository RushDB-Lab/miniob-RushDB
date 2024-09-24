#include "src/observer/sql/operator/aggfuncs/basc_agg_func.h"
#include "storage/record/record.h"

int aggregation::compare_with_record(const Record *first, const Record *second, const FieldMeta *field_meta)
{
  Value left, right;
  left.set_type(field_meta->type());
  right.set_type(field_meta->type());
  left.set_data(first->data() + field_meta->offset(), field_meta->len());
  right.set_data(second->data() + field_meta->offset(), field_meta->len());
  return left.compare(right);
}