#define __STDC_FORMAT_MACROS

#include <alloca.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <map>
#include <string>
#include <vector>

#include "libcvmfs_cache.h"

#include "../cvmfs/cvmfs/logging.h"

#include "ndncatchunks.hpp"
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;  // NOLINT



struct Listing {
  Listing() : pos(0) { }
  cvmcache_object_type type;
  uint64_t pos;
};


map<uint64_t, Listing> listings;

struct cvmcache_context *ctx;

char* secondCachePath = "/var/lib/cvmfs/";
char* primaryCachePath = "/var/lib/cvmfs/shared/";

static std::string ndn_file_name(struct cvmcache_hash *id)
{
        std::stringstream ss;
        char* fileName = cvmcache_hash_print(id);
        char tmp_path[strlen(fileName)+2];
        memcpy(tmp_path, fileName, 2);
        tmp_path[2] = '/';
        memcpy(tmp_path+3, fileName + 2, strlen(fileName)-2);
        tmp_path[sizeof(tmp_path)-1]='\0';
        ss << tmp_path;

        // char tmp_path[sizeof(id.digest) + 2];
        //memcpy(tmp_path, id.digest, 2);
        //  tmp_path[2] = '/';
        //  memcpy(tmp_path+3, id.digest+2, sizeof(id.digest)-2);
        //  tmp_path[sizeof(tmp_path)-1] = '\0';
        //  ss << g_hdfs_base << "/" << tmp_path;
        return ss.str();
}

static int ndn_chrefcnt(struct cvmcache_hash *id, int32_t change_by) {



 printf("ndn chrefcnt ... \n");
        std::string fname = ndn_file_name(id);
        printf("The file name is : %s \n",fname.c_str());
        std::string fPathName= secondCachePath + fname;

std::string fPathNameUpper = primaryCachePath + fname;
int fd_upper = open(fPathNameUpper.c_str(),O_RDONLY);
if(fd_upper >= 0)
{
close(fd_upper);
return CVMCACHE_STATUS_OK;


}
close(fd_upper);

        int fd = open(fPathName.c_str(), O_RDONLY);
        if(fd < 0)
        {close(fd);
                ndn::chunks::ndnChunks nchunks;
                printf("lower miss .. \n");

                nchunks.startChunk(fname,secondCachePath);
printf("after sending interenst \n");
        //      close(fd);
        }

        if(fd) close(fd);
        int fd2 = open(fPathName.c_str(), O_RDONLY);
        if(fd2 < 0)
        {
                printf("still can't be opend \n");
                close(fd2);
                return CVMCACHE_STATUS_NOENTRY;
        }
        struct stat64 info;
        fstat64(fd2, &info);
        int64_t size = info.st_size;
        if(size < 0)

        
        {
                printf("size less than zero! \n");
                close(fd2);
                return CVMCACHE_STATUS_NOENTRY;

        }
        else{
                printf("size is %" PRId64 "\n", size);

                //      return CVMCACHE_STATUS_NOENTRY;
        }
return CVMCACHE_STATUS_OK;

}


static int ndn_obj_info(
  struct cvmcache_hash *id,
  struct cvmcache_object_info *info)
{
 printf("ndn obj info ... \n");

        std::string fname = ndn_file_name(id);
        std::string fPathName= secondCachePath + fname;
        int fd = open(fPathName.c_str(), O_RDONLY);
        struct stat64 infoFile;
        fstat64(fd, &infoFile);
        uint64_t size = infoFile.st_size;
        info->size = size;
         printf("size is %" PRId64 "\n", info->size);
        close(fd);
        return CVMCACHE_STATUS_OK;


}


static int ndn_pread(struct cvmcache_hash *id,
                    uint64_t offset,
                    uint32_t *size,
                    unsigned char *buffer)
{
printf("ndn pread \n");

        std::string fname = ndn_file_name(id);
        std::string fPathName= secondCachePath + fname;
        int fd = open(fPathName.c_str(), O_RDONLY);

        if(fd < 0)
        {
                printf("can't open from pread \n");
                close(fd);
                return CVMCACHE_STATUS_NOENTRY;
        }
        int32_t  nbytes = pread(fd, buffer, *size, offset);

        if(-1 == nbytes)
        {
        close(fd);
        return CVMCACHE_STATUS_IOERR;
        }
        *size = nbytes;
        return CVMCACHE_STATUS_OK;

}


static int ndn_start_txn(
  struct cvmcache_hash *id,
  uint64_t txn_id,
  struct cvmcache_object_info *info)
{
  return CVMCACHE_STATUS_OK;
}


static int ndn_write_txn(
  uint64_t txn_id,
  unsigned char *buffer,
  uint32_t size)
{
  return CVMCACHE_STATUS_OK;
}


static int ndn_commit_txn(uint64_t txn_id) {
  return CVMCACHE_STATUS_OK;
}

static int ndn_abort_txn(uint64_t txn_id) {
  return CVMCACHE_STATUS_OK;
}

static int ndn_info(struct cvmcache_info *info) {
  return CVMCACHE_STATUS_OK;
}

static int ndn_shrink(uint64_t shrink_to, uint64_t *used) {
      return CVMCACHE_STATUS_OK;
}

static int ndn_listing_begin(
  uint64_t lst_id,
  enum cvmcache_object_type type)
{
  return CVMCACHE_STATUS_OK;
}

static int ndn_listing_next(
  int64_t listing_id,
  struct cvmcache_object_info *item)
{
  return CVMCACHE_STATUS_OK;
}

static int ndn_listing_end(int64_t listing_id) {
  return CVMCACHE_STATUS_OK;
}

static void Usage(const char *progname) {
  printf("%s <config file>\n", progname);
}


int main(int argc, char **argv) {

/*
std::string fname = "testme";
 ndn::chunks::ndnChunks nchunks;
                printf("lower miss .. \n");
std::string secondCachePath2 = "ed/";
                nchunks.startChunk(fname,secondCachePath2);
*/

  if (argc < 2) {
    Usage(argv[0]);
    return 1;
  }
 freopen ("/dev/tty", "a", stdout);

  cvmcache_init_global();

  cvmcache_option_map *options = cvmcache_options_init();
  if (cvmcache_options_parse(options, argv[1]) != 0) {
    printf("cannot parse options file %s\n", argv[1]);
    return 1;
  }
  char *locator = cvmcache_options_get(options, "CVMFS_CACHE_PLUGIN_LOCATOR");
  if (locator == NULL) {
    printf("CVMFS_CACHE_PLUGIN_LOCATOR missing\n");
    cvmcache_options_fini(options);
    return 1;
  }

  cvmcache_spawn_watchdog(NULL);

  struct cvmcache_callbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.cvmcache_chrefcnt = ndn_chrefcnt;
  callbacks.cvmcache_obj_info  = ndn_obj_info;
  callbacks.cvmcache_pread = ndn_pread;
  callbacks.cvmcache_start_txn = ndn_start_txn;
  callbacks.cvmcache_write_txn = ndn_write_txn;
  callbacks.cvmcache_commit_txn = ndn_commit_txn;
  callbacks.cvmcache_abort_txn = ndn_abort_txn;
  callbacks.cvmcache_info = ndn_info;
  callbacks.cvmcache_shrink = ndn_shrink;
  callbacks.cvmcache_listing_begin = ndn_listing_begin;
  callbacks.cvmcache_listing_next = ndn_listing_next;
  callbacks.cvmcache_listing_end = ndn_listing_end;
  callbacks.capabilities = CVMCACHE_CAP_ALL_V1;

  ctx = cvmcache_init(&callbacks);
  int retval = cvmcache_listen(ctx, locator);
  if (!retval) {
    fprintf(stderr, "failed to listen on %s\n", locator);
    return 1;
  }
  printf("Listening for cvmfs clients on %s\n", locator);
  printf("NOTE: this process needs to run as user cvmfs\n\n");

  // Starts the I/O processing thread
  cvmcache_process_requests(ctx, 0);

  if (!cvmcache_is_supervised()) {
    printf("Press <R ENTER> to ask clients to release nested catalogs\n");
    printf("Press <Ctrl+D> to quit\n");
    while (true) {
      char buf;
      int retval = read(fileno(stdin), &buf, 1);
      if (retval != 1)
        break;
      if (buf == 'R') {
        printf("  ... asking clients to release nested catalogs\n");
        cvmcache_ask_detach(ctx);
      }
    }
    cvmcache_terminate(ctx);
  }

  cvmcache_wait_for(ctx);
  printf("  ... good bye\n");

  cvmcache_options_free(locator);
  cvmcache_options_fini(options);
  cvmcache_terminate_watchdog();
  cvmcache_cleanup_global();
  return 0;
}
