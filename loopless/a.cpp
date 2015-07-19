// Taken directly from Knuth TAoCP v4 7.2.1.1
//
// Algorithm L (Loopless Gray binary generation).
// This algorithm, like Algorithm G, visits all binary n-tuples
// (a[n-1], ..., a[0]) in the order of the Gary binary code.
// But instead of maintaining a parity bit,
// it uses an array of "focus pointers".
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

class Focus {
 public:
  // Destructor
  virtual ~Focus() {}
  virtual void Visit() = 0;
  virtual void VisitHelper(bool) = 0;
  virtual void Choose() = 0;
  virtual void ChooseHelper() = 0;
  virtual Focus* GetNext() = 0;
  virtual Focus* GetTarget() = 0;
  virtual void Reset() = 0;
 protected:
  // Constructor
  Focus() {}
};

class LastFocus : public Focus {
 public:
  void Visit() { printf("()\n"); }
  void VisitHelper(bool b) { printf("%d)\n", b); }
  void Choose() { exit(0); }
  void ChooseHelper() { exit(0); }
  Focus* GetNext() { return 0; }
  Focus* GetTarget() { return this; }
  void Reset() { }
  
};

class NonlastFocus : public Focus {
 public:
  // Constructor
  NonlastFocus(Focus* next) :
    next(next),
    target(this),
    a(false)
  {
  }
  void Visit() { printf("("); next->VisitHelper(a); }
  void VisitHelper(bool b) { printf("%d, ", b); next->VisitHelper(a); }
  void Choose();
  void ChooseHelper();
  Focus* GetNext() { return next; }
  Focus* GetTarget() { return target; }
  void Reset() { target = this; }

private:
  int number;
  Focus* next;
  Focus* target;
  bool a;

};

void NonlastFocus::Choose() {
  Focus* j = target;
  Reset();
  j->ChooseHelper();
}

void NonlastFocus::ChooseHelper() {
  target = next->GetTarget();
  next->Reset();
  a = 1 - a;
}

int main(int argc, char* argv[]) {
  assert(argc == 2);
  int n = atoi(argv[1]);

  Focus* top = new LastFocus();
  for (int i = n-1; i >= 0; i -= 1) {
    top = new NonlastFocus(top);
  }

  while (true) {
    top->Visit();
    top->Choose();
  }
}

  

  
  
