#include "heavy_magick.hpp"
#include <boost/utility.hpp>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <dlfcn.h>
namespace heavy
{
  HeavyHandle::HeavyHandle(const std::string& soname)
  :
    soname(soname),
    handle(dlopen(soname.c_str(),RTLD_LAZY | RTLD_LOCAL))
  {
    if(!handle)
    {
      std::stringstream ss; 
      ss << "Could not open shared library: " + soname << "\n"
         << "dlerror: \n" << dlerror() << "\n";
      throw std::runtime_error(ss.str());
    }
    
    function = (FunctionT)dlsym(handle, "function");
    const char *error = dlerror();
    if (error != NULL)  {
      std::stringstream ss; 
      ss << "Could not find symbol 'function' in " + soname << "\n"
         << "dlerror: \n" << error << "\n";
      throw std::runtime_error(ss.str());
    }
  }

  void HeavyHandle::operator()(void **blk, int width, int height, int mode, void* miss_handler)
  {
    (*function)(blk,width,height,mode,miss_handler);
  }
  HeavyHandle::~HeavyHandle()
  {
    dlclose(handle);
  }
}

