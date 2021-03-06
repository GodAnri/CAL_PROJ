#include "spot.h"

void Spot::setQuantity(float q) {
    quantity = q;
}

enum type Spot::getType() {
    return type;
}

float Spot::getQuantity() {
    return quantity;
}

int Spot::getVertex() {
    return vertex;
}

bool Spot::fits(float q) {
    return quantity + q <= max_quantity;
}
