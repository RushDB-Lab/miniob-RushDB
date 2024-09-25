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

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const char *attribute_name, const Value *value)
    : table_(table), attribute_name_(attribute_name), value_(value)
{}
