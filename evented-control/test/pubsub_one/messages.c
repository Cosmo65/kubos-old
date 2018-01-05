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
 * Functions for publishing/subscribing/parsing the TestSignal signal exposed
 * by the Test Publisher.
 *
 * org.KubOS.TestPublisher.TestSignal
 */

#include "messages.h"
#include <dbus/dbus.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "evented-control/ecp.h"

KECPStatus format_test_signal_message(int16_t num, DBusMessage ** message)
{
    DBusMessageIter iter;

    *message = dbus_message_new_signal(TEST_PUB_PATH, TEST_PUB_INTERFACE,
                                       TEST_PUB_SIGNAL);
    dbus_message_append_args(*message, DBUS_TYPE_INT16, &num,
                             DBUS_TYPE_INVALID);

    return ECP_OK;
}

KECPStatus parse_test_signal_message(int16_t * num, DBusMessage * message)
{
    DBusMessageIter iter;
    DBusError       derror;

    dbus_error_init(&derror);

    if (!dbus_message_get_args(message, &derror, DBUS_TYPE_INT16, num,
                               DBUS_TYPE_INVALID))
    {
        printf("Had issuing parsing args\n%s\n", derror.message);
        return ECP_ERROR;
    }

    return ECP_OK;
}

KECPStatus on_test_signal_parser(const ecp_context *           context,
                                 DBusMessage *                 message,
                                 struct _ecp_message_handler * handler)
{
    int16_t                       num;
    test_signal_message_handler * status_handler
        = (test_signal_message_handler *) handler;

    if (ECP_OK == parse_test_signal_message(&num, message))
    {
        status_handler->cb(num);
    }
}

KECPStatus on_test_signal(ecp_context * context, test_signal_cb cb)
{
    test_signal_message_handler * handler = malloc(sizeof(*handler));
    handler->super.next                   = NULL;
    handler->super.interface              = TEST_PUB_INTERFACE;
    handler->super.member                 = TEST_PUB_SIGNAL;
    handler->super.parser                 = &on_test_signal_parser;
    handler->cb                           = cb;

    ecp_add_message_handler(context, &handler->super);

    return ecp_listen(context, TEST_PUB_INTERFACE);
}
