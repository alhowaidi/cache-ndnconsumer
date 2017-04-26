CVMFS_REPOSITORIES=cms.cern.ch
CVMFS_HTTP_PROXY=DIRECT

#CVMFS_SECOND_CACHE_BASE=/var/lib/cvmfs/secondary

CVMFS_CACHE_BASE=/var/lib/cvmfs
CVMFS_SHARED_CACHE=no
CVMFS_CACHE_PRIMARY=tiered
CVMFS_CACHE_tiered_TYPE=tiered
CVMFS_CACHE_tiered_UPPER=posix
CVMFS_CACHE_posix_TYPE=posix
CVMFS_CACHE_posix_DIR=/var/lib/cvmfs/shared
#CVMFS_CACHE_posix_SHARED=true
CVMFS_CACHE_posix_QUOTA_LIMIT=-1
CVMFS_CACHE_tiered_LOWER=hdfs
CVMFS_CACHE_hdfs_TYPE=external

CVMFS_SECOND_CACHE_BASE=/var/lib/cvmfs/secondary

#CVMFS_CACHE_hdfs_CMDLINE=/home/ubuntu/cache-ndnconsumer/pck,/foo,unix=/var/run/cvmfs/cvmfs_cache_hdfs.socket
#CVMFS_CACHE_hdfs_CMDLINE=/home/ubuntu/cache-ndnconsumer/pck,/etc/cvmfs/default.local,unix=/var/run/cvmfs/cvmfs_cache_hdfs.socket

CVMFS_CACHE_hdfs_CMDLINE=/home/ubuntu/cache-ndnconsumer/pck,/etc/cvmfs/default.local,unix=/var/run/cvmfs/cvmfs_cache_hdfs.socket
#CVMFS_CACHE_hdfs_CMDLINE=/home/ubuntu/cache-ndnconsumer/pck
CVMFS_CACHE_hdfs_LOCATOR=unix=/var/run/cvmfs/cvmfs_cache_hdfs.socket

CVMFS_CACHE_PLUGIN_LOCATOR=unix=/var/run/cvmfs/cvmfs_cache_hdfs.socket
CVMFS_CACHE_EXTERNAL_LOCATOR=unix=/var/run/cvmfs/cvmfs_cache_hdfs.socket

