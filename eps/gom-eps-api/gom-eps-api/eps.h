/*
 * Copyright (C) 2017 Kubos Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdint.h>

typedef enum {
    EPS_NO_ERR = 0,
} eps_err;

typedef struct {
    uint16_t line_1;
} eps_power_state;

typedef struct {
    float voltage;
} eps_battery_state;

eps_err eps_enable_power_line(uint16_t line);

eps_err eps_disable_power_line(uint16_t line);

eps_err eps_get_power_status(eps_power_state * state);

eps_err eps_get_battery_state(eps_battery_state * state);