#include <obj.h>
#include <stdio.h>

CLASS(Vehicle) {
  char* brand;
  void(*honk)();
};

void Vehicle_init(Vehicle* veh, char* brand, void(*honk)()) {
  veh->brand = brand;
  veh->honk = honk;
}

enum WheelQuality {
  EXCELLENT,
  GOOD,
  WORN
};

CLASSI(Car, Vehicle) {
  enum WheelQuality wheels[4];
};

void Car_honk() {
  printf("Tuut, tuut!");
}

void Car_init(Car* car, char* brand) {
  Vehicle_init(obj_parent(car), brand, Car_honk);
  for (int i = 0; i < 4; i++) {
    car->wheels[i] = EXCELLENT;
  }
}

CLASSI(ClownCar, Car) {
  int capacity;
};

void ClownCar_honk() {
  printf("Honk, honk!");
}

void ClownCar_init(ClownCar* car, int capacity) {
  Car* parent_car = obj_parent(car);
  Car_init(parent_car, "ClownCar");
  // Overriding property
  ((Vehicle*)obj_parent(parent_car))->honk = ClownCar_honk;
  car->capacity = capacity;
}

void Vehicle_print(obj_t obj) {
  // Get the Vehicle parent of the object
  Vehicle* vehicle = OBJ_PARENT_OF(obj, Vehicle);
  printf("%s: ", vehicle->brand);
  vehicle->honk();
  printf("\n");
}

int main(void) {
  obj_t* vehicles = malloc(5 * sizeof(obj_t));

  char* brands[4] = {
    "Mustang",
    "Volvo",
    "Audi",
    "Prosche"
  };

  for (int i = 0; i < 4; i++) {
    Car* car = OBJ_CREATE(Car);
    Car_init(car, brands[i]);
    vehicles[i] = car;
  }

  vehicles[4] = OBJ_CREATE(ClownCar);
  ClownCar_init(vehicles[4], 26);

  printf("Available vehicles: \n");

  for (int i = 0; i < 5; i++) {
    Vehicle_print(vehicles[i]);
  }
}
