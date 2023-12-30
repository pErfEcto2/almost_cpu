#include "alu.h"
#include <dlfcn.h>
#include <iostream>

int main() {
  // Load the shared library
  void *libHandle =
      dlopen("/home/mephi/cpp/lab3/shared_objects/libalu.so", RTLD_LAZY);
  if (!libHandle) {
    std::cerr << "Failed to load the shared library: " << dlerror()
              << std::endl;
    return 1;
  }

  // Load the functions from the shared library
  typedef void (*SumFFunc)();
  typedef void (*MulFFunc)();

  SumFFunc sumf = reinterpret_cast<SumFFunc>(dlsym(libHandle, "sumf"));
  MulFFunc mulf = reinterpret_cast<MulFFunc>(dlsym(libHandle, "mulf"));

  if (!sumf || !mulf) {
    std::cerr << "Failed to load symbols from the shared library: " << dlerror()
              << std::endl;
    dlclose(libHandle);
    return 2;
  }

  // Create instances of f_ALU dynamically
  ALU *f_alu = new f_ALU();

  // Call the dynamically loaded functions
  sumf();
  mulf();

  // Clean up and close the shared library
  delete f_alu;
  dlclose(libHandle);

  return 0;
}
