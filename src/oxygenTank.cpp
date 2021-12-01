#include "header/oxygenTank.h"

#include "raylib.h"

tank::tank(int x, int y) {
    this->posX = x;
    this->posY = y;
    this->collected = false;
}

tank::tank() {
    this->posX = 1;
    this->posY = 1;
    this->collected = false;
}

bool tank::getCollected() { return this->collected; }

void tank::showTank() {
    if (!this->getCollected()){
        DrawRectangle(this->posX, this->posY, 30, 50, GRAY);
        DrawText("O2", this->posX + 3, this->posY + 15, 20, BLACK);
    }

}

void tank::setCollected(bool collect) { this->collected = collect; }
void tank::isCollected() { this->collected = true; }
int tank::getX() { return this->posX; }
int tank::getY() { return this->posY; }
