#include <assert.h>
#include <obj.h>

CLASS(Adder) {
  int a;
  int b;
};

void Adder_init(Adder* self, int a, int b) {
  self->a = a;
  self->b = b;
}

int Adder_add(Adder* self) {
  return self->a + self->b;
}

int main(void) {
  Adder* adder = OBJ_CREATE(Adder);
  Adder_init(adder, 4, 5);
  assert(Adder_add(adder) == 9);
}
