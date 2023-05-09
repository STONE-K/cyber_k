#include "xsi_segment.h"

#include <iostream>

namespace cyber_k {
namespace transport {

XsiSegment::XsiSegment(uint64_t channel_id) {
  key_ = static_cast<key_t>(channel_id);
  OpenOrCreate();
}

XsiSegment::~XsiSegment() { Remove(); }

bool XsiSegment::OpenOrCreate() {
  if (init_) {
    return true;
  }

  // create shm
  int retry = 3;
  int shmid = 0;
  while (retry--) {
    shmid = shmget(key_, 1024, 0644 | IPC_CREAT | IPC_EXCL);
    if (shmid != -1) {
      break;
    }

    if (EINVAL == errno) {
      std::cout << "need larger space, recreate." << std::endl;
      // Reset();
      Remove();
    } else if (EEXIST == errno) {
      std::cout << "shm already exist, open only." << std::endl;
      // return OpenOnly();
      return true;
    } else {
      break;
    }
  }

  if (shmid == -1) {
    std::cout << "create shm failed, error code: " << std::endl;
    return false;
  }

  return true;
}

bool XsiSegment::Remove() {
  int shmid = shmget(key_, 0, 0644);
  if (shmid == -1 || shmctl(shmid, IPC_RMID, 0) == -1) {
    std::cout << "remove shm failed, error code: " << std::endl;
    return false;
  }
  std::cout << "remove success." << std::endl;
  return true;
}

}  // namespace transport
}  // namespace cyber_k