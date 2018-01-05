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

/**
 * @defgroup ECPMessages Generic Message API
 * @addtogroup ECPMessages
 * @{
 */

#pragma once

#include "evented-control/power-manager-messages.h"

/**
 * Checks to see if the message matches the specified interface and member.
 * @param[in] message Message received from event bus
 * @param[in] interface Interface name to check message against
 * @param[in] member Method/Signal name to check message against
 * @return KECPStatus ECP_OK if successful, otherwise error message
 */
KECPStatus check_message(DBusMessage * message, const char * interface,
                         const char * member);

/* @} */
