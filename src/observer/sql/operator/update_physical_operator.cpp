
#include "sql/operator/update_physical_operator.h"
#include "sql/parser/value.h"
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <cstdint>

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(
    Table *table, std::vector<std::string> names, std::vector<Value> &&values)
    : table_(table), att_names(names), values_(values)
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    for (int index = att_names.size() - 1; index >= 0; index--) {

      if (table_->find_attry_by_name(att_names[index]) == DATES &&
          Value::is_date(values_[index].get_string().c_str())) {
        int flag = values_[index].char_to_int32();
        if (!flag) {
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
      const char *new_data = values_[index].data();
      Record     &record   = row_tuple->record();
      rc                   = trx_->update_record(table_, record, new_data, att_names[index]);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to delete record: %s", strrc(rc));
        return rc;
      }
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}