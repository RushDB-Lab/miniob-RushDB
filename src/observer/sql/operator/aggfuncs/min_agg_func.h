#include "sql/operator/aggfuncs/basc_agg_func.h"
#include "storage/record/record.h"
class min_agg_func : public aggregation
{
public:
  min_agg_func() = default;
  RC init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record) override;
  RC update(const Record &current_record_) override;
  Value get_value() override;

private:
  Table     *table;
  const FieldMeta *field_meta;
  Record     min_record;
};