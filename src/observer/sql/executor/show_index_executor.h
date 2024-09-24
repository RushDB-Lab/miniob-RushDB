#pragma once

#include "common/rc.h"
#include "event/sql_event.h"

class ShowIndexExecutor
{
public:
  ShowIndexExecutor()          = default;
  virtual ~ShowIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};