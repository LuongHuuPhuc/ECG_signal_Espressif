#include "modulus.h"

int modulus(int a, int b){
  int r = a % b;
  return r < 0 ? r + b : r; //Neu ket qua la so am thi cong them b de ket qua thanh duong
}
