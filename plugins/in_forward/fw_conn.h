/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2015-2016 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef FLB_IN_FW_CONN_H
#define FLB_IN_FW_CONN_H

#define FLB_IN_FW_CHUNK 32768

enum {
    FW_NEW        = 1,  /* it's a new connection                */
    FW_CONNECTED  = 2,  /* MQTT connection per protocol spec OK */
};

struct fw_conn_stream {
    char *tag;
    size_t tag_len;
};

/* Respresents a connection */
struct fw_conn {
    struct mk_event event;           /* Built-in event data for mk_events */
    int fd;                          /* Socket file descriptor            */
    int status;                      /* Connection status                 */

    /* Buffer */
    char *buf;                       /* Buffer data                       */
    int  buf_len;                    /* Data length                       */
    int  buf_size;                   /* Buffer size                       */
    size_t buf_off;                  /* Unpacking offset                  */

    struct flb_input_instance *in;   /* Parent plugin instance            */
    struct flb_in_fw_config *ctx;    /* Plugin configuration context      */

    struct mk_list _head;
};

struct fw_conn *fw_conn_add(int fd, struct flb_in_fw_config *ctx);
int fw_conn_del(struct fw_conn *conn);

#endif
