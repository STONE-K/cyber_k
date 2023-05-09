
#ifndef CYBER_TRANSPORT_SHM_XSI_SEGMENT_H_
#define CYBER_TRANSPORT_SHM_XSI_SEGMENT_H_

#include <stdint.h>
#include <sys/shm.h>
#include <sys/types.h>

namespace cyber_k {
namespace transport {

class XsiSegment {
 public:
  explicit XsiSegment(uint64_t channel_id);
  virtual ~XsiSegment();

  static const char* Type() { return "xsi"; }

 private:
  // void Reset();
  bool Remove();
  // bool OpenOnly();
  bool OpenOrCreate();

  key_t key_;

  bool init_;
  void* managed_shm_;
};

}  // namespace transport
}  // namespace cyber_k

#endif