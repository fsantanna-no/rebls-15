#include "platform.h"
#include "microhttpd.h"
#include <assert.h>

#define ERRORPAGE "<html><body><h1>An error has occurred.</h1></body></html>"
#define BUSYPAGE "<html><body><h1>This server is busy, please try again later.</h1></body></html>"
#define FRONTPAGE "<html><body>What is your name?<br><form action=\"/namepost\" method=\"post\"><input name=\"name\" type=\"text\"><input type=\"submit\" value=\"Send\"></form></body></html>"
#define POSTPAGE "<html><body><h1>Hello Post</h1></body></html>"
#define POSTBUFFERSIZE 512

typedef struct MHD_Response MHD_Response;
typedef struct MHD_Connection MHD_Connection;
static ssize_t crc(void* cls, uint64_t pos, char* buf, size_t max);
#include "_ceu_app.h"
#include "_ceu_app.c"
static char CEU_DATA[sizeof(CEU_Main)];
static tceu_app app;

// Callback used by MHD in order to obtain content.
// The callback has to copy at most max bytes of content into buf.
// The total number of bytes that has been placed into buf should be returned. 
static ssize_t crc(void* cls, uint64_t pos, char* buf, size_t max)
{
  ssize_t out;
  tceu__void___u64__char___size_t__ssize_t_ msg = {
    cls,
    pos,
    buf,
    max,
    &out
  };
  ceu_sys_go(&app, CEU_IN_CRC, &msg);
  return out;
}


static int ahc (
                void* cls,
                struct MHD_Connection* connection,
                const char* url,
                const char* method,
                const char* version,
                const char* upload_data,
                size_t* upload_data_size,
                void** ptr
                )
{
  assert(cls == (void*)1234);
  assert(ptr);
  int out;
  tceu__MHD_Connection___char___char___char___char___size_t___void____int_ msg = {
    connection,
    url,
    method,
    version,
    upload_data,
    upload_data_size,
    ptr,
    &out
  };
  ceu_sys_go(&app, CEU_IN_AHC, &msg);


  // I'd like to do this from Ceu-side, but I couldn't figure out how
  if (ptr == 0) {
    struct MHD_Response* resp = MHD_create_response_from_buffer(
      sizeof(BUSYPAGE),
      BUSYPAGE,
      MHD_RESPMEM_PERSISTENT
    );
    assert(resp);
    out = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
  }

  return out;
}

int main (int argc, const char* argv[]) {
    if (argc != 3) {
      printf ("%s PORT SECONDS-TO-RUN\n", argv[0]);
      return 1;
    }
    app.data = (tceu_org*)&CEU_DATA;
    app.init = &ceu_app_init;
    app.init(&app);
    struct MHD_Daemon* d = MHD_start_daemon (
                                             MHD_USE_DEBUG,
                                             atoi(argv[1]),
                                             NULL,
                                             NULL,
                                             &ahc,
                                             (void*)1234,
                                             MHD_OPTION_END
                                             );
    if (d == NULL) {
      return 1;
    }
    time_t end = time(NULL) + atoi(argv[2]);
    while (1) {
      printf("tick\n");
      {
        // This is a cheap way of providing some sort of wallclock time to Ceu
        // TODO: this better
        int dt_us = 1000 * 1000;
        ceu_sys_go(&app, CEU_IN__WCLOCK, &dt_us);
      }

      time_t t = time(NULL);
      if (t >= end) {
        break;
      }
      struct timeval tv;
      if (end - t < 1) {
        tv.tv_sec = end - t;
      } else {
        tv.tv_sec = 1;
      }
      tv.tv_usec = 0;
      MHD_socket max = 0;
      fd_set rs;
      FD_ZERO(&rs);
      fd_set ws;
      FD_ZERO(&ws);
      fd_set es;
      FD_ZERO(&es);
      assert(MHD_get_fdset(d, &rs, &ws, &es, &max) == MHD_YES);
      /*

      // Johnicholas asks: is this necessary?

      MHD_UNSIGNED_LONG_LONG mhd_timeout;
      if (MHD_get_timeout(d, &mhd_timeout) == MHD_YES) {
        if (((MHD_UNSIGNED_LONG_LONG)tv.tv_sec) < mhd_timeout / 1000LL) {
          tv.tv_sec = mhd_timeout / 1000LL;
          tv.tv_usec = (mhd_timeout - (tv.tv_sec * 1000LL)) * 1000LL;
        }
      }
      */
      select(max + 1, &rs, &ws, &es, &tv);
      MHD_run(d);
    }
    MHD_stop_daemon(d);
    return 0;
}
