#include <cassert>
#include <iostream>

#include "customptr.h"

class Lol {
public:
  void lol() { std::cout << "Lol" << std::endl; }
};

int main() {
  auto lol = make_custom_ptr<Lol>();
  Lol *fp = lol.release();

  assert(lol.get() == nullptr);
  assert(lol == nullptr);

  fp->lol();

  delete fp;
  return 0;
}
