#pragma once
#include <boost/utility.hpp>
namespace heavy
{
struct HeavyHandle : boost::noncopyable
{
  typedef void (*FunctionT)(void**, int, int, int, void *);
  HeavyHandle(const std::string& soname);
  void operator()(void **blk, int width, int height, int mode, void* miss_handler);
  ~HeavyHandle();
  std::string soname;
  void * handle;
  FunctionT function;
};
}
