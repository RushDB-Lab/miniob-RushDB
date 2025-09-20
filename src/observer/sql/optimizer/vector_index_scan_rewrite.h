/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/18                                     *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "sql/optimizer/rewrite_rule.h"

/**
 * @brief 向量索引重写规则
 * @ingroup Rewriter
 * @details 识别 orderby limit 重写为向量索引
 */
class VectorIndexScanRewrite : public RewriteRule
{
public:
  VectorIndexScanRewrite()          = default;
  virtual ~VectorIndexScanRewrite() = default;

  RC rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made) override;
};
