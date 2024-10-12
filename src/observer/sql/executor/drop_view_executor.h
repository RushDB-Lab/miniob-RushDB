/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                     *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 删除视图的执行器
 * @ingroup Executor
 */
class DropViewExecutor
{
public:
  DropViewExecutor()          = default;
  virtual ~DropViewExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};
