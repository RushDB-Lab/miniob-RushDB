/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/29                                    *
 * @Description : ShowIndexExecutor header file                *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 描述表的执行器
 * @ingroup Executor
 */
class ShowIndexExecutor
{
public:
  ShowIndexExecutor()          = default;
  virtual ~ShowIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};
