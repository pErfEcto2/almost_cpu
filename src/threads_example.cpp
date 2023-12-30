#include <ctime>
#include <exception>
#include <iostream>
#include <thread>
#include <vector>

class A {
public:
  bool stop;
  A() { stop = false; }
};

bool any_not_stop(std::vector<A> &as) {
  bool res = false;
  for (auto &a : as)
    res = res || !a.stop;
  return res;
}

int main() {
  srand(time(0));

  int n = 5;

  std::vector<std::thread> threads;
  std::vector<A> as;

  for (int i{0}; i < n; i++) {
    as.push_back(A());
    threads.push_back(std::thread( // replace lambda with function to run
        [&as](int i) {
          while (!as[i].stop) {
            if (rand() % 10 == 0)
              return;
            as[i].stop = rand() % 20 == 0;
          }
        },
        i));
  }

  for (auto &t : threads) {
    t.join();
  }

  while (any_not_stop(as)) {
    for (auto &a : as) {
      std::cout << a.stop << " ";
    }
    std::cout << std::endl;

    for (int i{0}; i < n; i++) {
      if (!as[i].stop) {
        threads[i] = std::thread( // replace lambda with function to run
            [&as](int i) {
              while (!as[i].stop) {
                if (rand() % 10 == 0)
                  return;
                as[i].stop = rand() % 20 == 0;
              }
            },
            i);
      }
    }

    for (int i{0}; i < n; i++) {
      try {
        threads[i].join();
      } catch (std::exception &e) {
      }
    }
  }

  for (auto &a : as) {
    std::cout << a.stop << " ";
  }
  std::cout << std::endl;

  return 0;
}
