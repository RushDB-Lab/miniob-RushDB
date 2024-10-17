/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/20                                    *
 * @Description : UpdateLogicalOperator source file            *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(
    BaseTable *table, std::vector<FieldMeta> field_metas, std::vector<std::unique_ptr<Expression>> values)
    : table_(table), field_metas_(std::move(field_metas)), values_(std::move(values))
{}
