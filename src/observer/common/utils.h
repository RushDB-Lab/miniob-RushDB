/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/30                                    *
 * @Description : utils header file                            *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "rc.h"
#include <vector>
#include <cmath>
#include <string>

bool check_date(int y, int m, int d);

RC parse_date(const char *str, int &result);

RC parse_float_prefix(const char *str, float &result);

RC parse_vector_from_string(const char *str, float *&array, int &length);

std::string get_day_with_suffix(int day);

std::string get_full_month_name(int month);