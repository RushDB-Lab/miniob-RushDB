#include "sql/operator/aggfuncs/basc_agg_func.h"
#include "storage/record/record.h"
class avg_agg_func : public aggregation
{
public:
  RC    init(Agg_Func &info_of_funcs_, Table *table_, const FieldMeta *field_meta_, Record current_record) override;
  RC    update(const Record &current_record_) override;
  Value get_value() override;

private:
  Table           *table;
  bool             has_null = false;
  const FieldMeta *field_meta;
  int              int_sum    = 0;
  float            float_sum  = 0.0;
  int              all_counts = 0;
};