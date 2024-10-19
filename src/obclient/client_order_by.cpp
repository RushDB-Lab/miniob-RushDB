/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#if 0

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "common/defs.h"
#include "common/lang/string.h"

#ifdef USE_READLINE
#include "readline/history.h"
#include "readline/readline.h"
#endif

const int TABLE_RECORD_NUMBER = 20;

#define MAX_MEM_BUFFER_SIZE 131072
#define PORT_DEFAULT 6789

using namespace std;
using namespace common;

#ifdef USE_READLINE
const string HISTORY_FILE            = string(getenv("HOME")) + "/.miniob.history";
time_t       last_history_write_time = 0;

char *my_readline(const char *prompt)
{
  int size = history_length;
  if (size == 0) {
    read_history(HISTORY_FILE.c_str());

    FILE *fp = fopen(HISTORY_FILE.c_str(), "a");
    if (fp != nullptr) {
      fclose(fp);
    }
  }

  char *line = readline(prompt);
  if (line != nullptr && line[0] != 0) {
    add_history(line);
    if (time(NULL) - last_history_write_time > 5) {
      write_history(HISTORY_FILE.c_str());
    }
  }
  return line;
}
#else   // USE_READLINE
char *my_readline(const char *prompt)
{
  char *buffer = (char *)malloc(MAX_MEM_BUFFER_SIZE);
  if (nullptr == buffer) {
    fprintf(stderr, "failed to alloc line buffer");
    return nullptr;
  }
  fprintf(stdout, "%s", prompt);
  char *s = fgets(buffer, MAX_MEM_BUFFER_SIZE, stdin);
  if (nullptr == s) {
    fprintf(stderr, "failed to read message from console");
    free(buffer);
    return nullptr;
  }
  return buffer;
}
#endif  // USE_READLINE

bool is_exit_command(const char *cmd)
{
  return 0 == strncasecmp("exit", cmd, 4) || 0 == strncasecmp("bye", cmd, 3) || 0 == strncasecmp("\\q", cmd, 2);
}

int init_unix_sock(const char *unix_sock_path)
{
  int sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr, "failed to create unix socket. %s", strerror(errno));
    return -1;
  }

  struct sockaddr_un sockaddr;
  memset(&sockaddr, 0, sizeof(sockaddr));
  sockaddr.sun_family = PF_UNIX;
  snprintf(sockaddr.sun_path, sizeof(sockaddr.sun_path), "%s", unix_sock_path);

  if (connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
    fprintf(stderr, "failed to connect to server. unix socket path '%s'. error %s", sockaddr.sun_path, strerror(errno));
    close(sockfd);
    return -1;
  }
  return sockfd;
}

int init_tcp_sock(const char *server_host, int server_port)
{
  struct hostent    *host;
  struct sockaddr_in serv_addr;

  if ((host = gethostbyname(server_host)) == NULL) {
    fprintf(stderr, "gethostbyname failed. errmsg=%d:%s\n", errno, strerror(errno));
    return -1;
  }

  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "create socket error. errmsg=%d:%s\n", errno, strerror(errno));
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port   = htons(server_port);
  serv_addr.sin_addr   = *((struct in_addr *)host->h_addr);
  bzero(&(serv_addr.sin_zero), 8);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
    fprintf(stderr, "Failed to connect. errmsg=%d:%s\n", errno, strerror(errno));
    close(sockfd);
    return -1;
  }
  return sockfd;
}

const char *startup_tips = R"(
Welcome to the OceanBase database implementation course.

Copyright (c) 2021 OceanBase and/or its affiliates.

Learn more about OceanBase at https://github.com/oceanbase/oceanbase
Learn more about MiniOB at https://github.com/oceanbase/miniob

)";

// Function to send SQL query and receive response
void send_sql(int sockfd, const char *sql)
{
  char send_buf[MAX_MEM_BUFFER_SIZE];
  printf("Sending SQL: %s\n", sql);

  if (write(sockfd, sql, strlen(sql) + 1) == -1) {
    fprintf(stderr, "send error: %d:%s \n", errno, strerror(errno));
    exit(1);
  }

  memset(send_buf, 0, sizeof(send_buf));
  int len = 0;
  while ((len = recv(sockfd, send_buf, MAX_MEM_BUFFER_SIZE, 0)) > 0) {
    bool msg_end = false;
    for (int i = 0; i < len; i++) {
      if (0 == send_buf[i]) {
        msg_end = true;
        break;
      }
      printf("%c", send_buf[i]);
    }
    if (msg_end) {
      break;
    }
    memset(send_buf, 0, MAX_MEM_BUFFER_SIZE);
  }

  if (len < 0) {
    fprintf(stderr, "Connection was broken: %s\n", strerror(errno));
    exit(1);
  } else if (len == 0) {
    printf("Connection closed by server.\n");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  printf("%s", startup_tips);

  const char  *unix_socket_path = nullptr;
  const char  *server_host      = "127.0.0.1";
  int          server_port      = PORT_DEFAULT;
  int          opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "s:h:p:")) > 0) {
    switch (opt) {
      case 's': unix_socket_path = optarg; break;
      case 'p': server_port = atoi(optarg); break;
      case 'h': server_host = optarg; break;
    }
  }

  int sockfd;

  if (unix_socket_path != nullptr) {
    sockfd = init_unix_sock(unix_socket_path);
  } else {
    sockfd = init_tcp_sock(server_host, server_port);
  }
  if (sockfd < 0) {
    return 1;
  }

  // Send CREATE TABLE statements
  send_sql(sockfd, "CREATE TABLE big_order_by_0 (id INT, addr CHAR(100), num INT, price FLOAT, birthday DATE);");
  send_sql(sockfd, "CREATE TABLE big_order_by_1 (id INT, addr CHAR(100), num INT, price FLOAT, birthday DATE);");
  send_sql(sockfd, "CREATE TABLE big_order_by_2 (id INT, addr CHAR(100), num INT, price FLOAT, birthday DATE);");
  send_sql(sockfd, "CREATE TABLE big_order_by_3 (id INT, addr CHAR(100), num INT, price FLOAT, birthday DATE);");

  // Insert data (for simplicity, inserting a small amount of random data)
  for (int i = 1; i <= TABLE_RECORD_NUMBER; i++) {
    char insert_sql[512];
    snprintf(insert_sql,
        sizeof(insert_sql),
        "INSERT INTO big_order_by_0 VALUES (%d, 'addr%d', %d, %.2f, '2022-01-01');",
        i,
        i,
        rand() % 1000,
        (float)(rand() % 10000) / 100);
    send_sql(sockfd, insert_sql);

    snprintf(insert_sql,
        sizeof(insert_sql),
        "INSERT INTO big_order_by_1 VALUES (%d, 'addr%d', %d, %.2f, '2022-01-01');",
        i,
        i,
        rand() % 1000,
        (float)(rand() % 10000) / 100);
    send_sql(sockfd, insert_sql);

    snprintf(insert_sql,
        sizeof(insert_sql),
        "INSERT INTO big_order_by_2 VALUES (%d, 'addr%d', %d, %.2f, '2022-01-01');",
        i,
        i,
        rand() % 1000,
        (float)(rand() % 10000) / 100);
    send_sql(sockfd, insert_sql);

    snprintf(insert_sql,
        sizeof(insert_sql),
        "INSERT INTO big_order_by_3 VALUES (%d, 'addr%d', %d, %.2f, '2022-01-01');",
        i,
        i,
        rand() % 1000,
        (float)(rand() % 10000) / 100);
    send_sql(sockfd, insert_sql);
  }

  // Send the ORDER BY query
  const char *order_by_sql = "SELECT * FROM big_order_by_0, big_order_by_1, big_order_by_2, big_order_by_3 "
                             "ORDER BY big_order_by_0.addr, big_order_by_2.num, big_order_by_0.price, "
                             "big_order_by_3.id, big_order_by_1.id, big_order_by_1.num, big_order_by_0.id, "
                             "big_order_by_0.birthday LIMIT 1;";
  send_sql(sockfd, order_by_sql);

  // Close the socket
  close(sockfd);

  return 0;
}

#endif  // #if 0