#include <iostream>
#include <vector>
#include "player.cpp"
#include "entity.cpp"
#include "ground.cpp"
#include "enemy.cpp"
#include "game.h"
#include "resource.h"
#include "star.cpp"
#include "oxygenTank.cpp"
#include <iostream>
#include "coin.cpp"

#define PLAYER_SPAWN (Vector2){0.0f, 400.0f}
#define PLAYER_CHARACTER_INDEX 0

// Define the things that happen when the game is initialized.
Game::Game() {
    std::cout << "Game has been initialized\n\n";

    // Create game entities.
    // Create player
    this->characters.push_back(new Player(PLAYER_SPAWN, 0));
    // Create enemies
    Enemy *enemy1 = new Enemy((Vector2){1500.0f, 300.0f}, 0);
    enemy1->SetMovable(true, 1, 0, 200, 100);
    Enemy *enemy2 = new Enemy((Vector2){4700.0f, 250.0f}, 0);
    enemy2->SetMovable(true, 1, 0, 200, 100);
    Enemy *enemy3 = new Enemy((Vector2){5000.0f, 450.0f}, 0);
    enemy3->SetMovable(true, -1, 0, 200, 100);

    this->characters.push_back((Entity *)enemy1);
    this->characters.push_back((Entity *)enemy2);
    this->characters.push_back((Entity *)enemy3);
    // Create platforms
    // Spawn platform
    this->grounds.push_back(new Ground((Vector2){-20.0f, 400.0f}, 0, 200, 50));
    // Add a moveable platform for player to jump onto!
    Ground *plat1 = new Ground((Vector2){400.0f, 250.0f}, 0, 200, 50);
    Ground *plat2 = new Ground((Vector2){250.0f, 500.0f}, 0, 200, 50);
    Ground *plat3 = new Ground((Vector2){550.0f, 500.0f}, 0, 200, 50);
    Ground *plat4 = new Ground((Vector2){800.0f, 400.0f}, 0, 200, 50);

    Ground *plat5 = new Ground((Vector2){1200.0f, 500.0f}, 0, 1000, 50);
    Ground *plat6 = new Ground((Vector2){1400.0f, 350.0f}, 0, 200, 50);
    Ground *plat7 = new Ground((Vector2){1800.0f, 350.0f}, 0, 200, 50);
    Ground *plat8 = new Ground((Vector2){1650.0f, 150.0f}, 0, 100, 50);

    Ground *plat9 = new Ground((Vector2){2350.0f, 500.0f}, 0, 300, 50);
    plat9->SetMovable(true, 1, 0, 150, 100);
    Ground *plat10 = new Ground((Vector2){2950.0f, 500.0f}, 0, 300, 50);
    plat10->SetMovable(true, 0, -1, 100, 150);
    Ground *plat11 = new Ground((Vector2){3100.0f, 200.0f}, 0, 300, 50);
    plat11->SetMovable(true, 1, 0, 100, 150);

    Ground *plat12 = new Ground((Vector2){3800.0f, 200.0f}, 0, 200, 50);
    Ground *plat13 = new Ground((Vector2){4050.0f, 300.0f}, 0, 200, 50);
    Ground *plat14 = new Ground((Vector2){4300.0f, 400.0f}, 0, 200, 50);
    Ground *plat15 = new Ground((Vector2){4700.0f, 300.0f}, 0, 300, 50);
    Ground *plat16 = new Ground((Vector2){4700.0f, 500.0f}, 0, 300, 50);
    Ground *plat17 = new Ground((Vector2){5100.0f, 400.0f}, 0, 300, 50);

    Ground *plat18 = new Ground((Vector2){5500.0f, 300.0f}, 0, 200, 50);
	Ground *plat19 = new Ground((Vector2){5900.0f, 500.0f}, 0, 200, 50);
	Ground *plat20 = new Ground((Vector2){6300.0f, 400.0f}, 0, 200, 50);



    this->grounds.push_back((Entity *)plat1);
    this->grounds.push_back((Entity *)plat2);
    this->grounds.push_back((Entity *)plat3);
    this->grounds.push_back((Entity *)plat4);
    this->grounds.push_back((Entity *)plat5);

    this->grounds.push_back((Entity *)plat6);
    this->grounds.push_back((Entity *)plat7);
    this->grounds.push_back((Entity *)plat8);

    this->grounds.push_back((Entity *)plat9);
    this->grounds.push_back((Entity *)plat10);
    this->grounds.push_back((Entity *)plat11);

    this->grounds.push_back((Entity *)plat12);
    this->grounds.push_back((Entity *)plat13);
    this->grounds.push_back((Entity *)plat14);
    this->grounds.push_back((Entity *)plat15);
    this->grounds.push_back((Entity *)plat16);
    this->grounds.push_back((Entity *)plat17);

    this->grounds.push_back((Entity *)plat18);
	this->grounds.push_back((Entity *)plat19);
	this->grounds.push_back((Entity *)plat20);

    this->coins.push_back(coin(80, 250));
    this->coins.push_back(coin(1695, -20));
    this->coins.push_back(coin(1495, 175));
    this->coins.push_back(coin(1895, 175));
    this->coins.push_back(coin(3500, 100));
    this->coins.push_back(coin(4850, 150));
    this->coins.push_back(coin(4850, 400));
    this->coins.push_back(coin(5600, 150));
    this->coins.push_back(coin(6400, 250));

    this->tanks.push_back(tank(495, 30));
    this->tanks.push_back(tank(3875, 30));

    this->onTitle = true;
    this->controlFlag = true; // control flag to swap between WASD and arrow keys
    this->settingsFlag = false; // settings flag to display settings

    this->camera = { 0 };
    this->camera.target = this->characters[0]->GetPos();
    camera.offset = (Vector2){ SCREENWIDTH/2.0f, SCREENHEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    this->timeCount = 0;
    this->oxygenRemaining = this->maxO2;
    //this->tanks.push_back(tank(400, 70));
    //this->tanks.push_back()
    this->score = 0;

    this->moonTexture = LoadTexture("../arts/moon.png");
}

std::vector<Entity *> Game::GetGrounds() {
    return this->grounds;
}

std::vector<Entity *> Game::GetCharacters() {
    return this->characters;
}

float Game::GetLastFrameTime() {
    return GetFrameTime();
}

// Define what will happen each frame of the game.
void Game::GameUpdateAndRender() {

    // oxygen timer
    if ((GetTime() - timeCount) > 1){
        timeCount = GetTime();
        oxygenRemaining--;
    }

	for (int i = 0; i < 200; i++) {
		this->stars[i].x -= 12 * (stars[i].z / 1);

		if (this->stars[i].x <= 0) {  // Check if the star has gone off screen
			this->stars[i].x += 2000;
			this->stars[i].y = GetRandomValue(0, 1000);
		}
	}

    BeginDrawing(); 
    ClearBackground(BLACK);

    for (int i = 0; i < 200; i++) {
		float x = this -> stars[i].x;
		float y = this -> stars[i].y;

		DrawRectangle(x, y, 8*stars[i].z, 8*stars[i].z, RAYWHITE);
	}

    if (onTitle){ // still on title screen
        showTitle();
        if (IsKeyPressed(KEY_ENTER)){ // if enter is pressed, start game
            onTitle = false;
            UnloadTexture(this->titleSprite); // unload sprite
        }
    }

    else { // no longer on title screen

        // Calling raylib function GetFrameTime to return the time in seconds for the last frame drawn.
        float deltaTime = GetFrameTime();


        if (IsKeyPressed(KEY_P)) { // if user hits escape
            this->setSettingsFlag(); // switch settings flag
        }

        if (gameOver){
            showGameOver();
            if (IsKeyPressed(KEY_ENTER)) {
                switchGameOver();
                score = 0;
            }
        }
        else {

            if (settingsFlag){
                showSettings();
            }

            else {

                this->updateCameraSmoothFollowInsideMap(deltaTime);
                BeginMode2D(this->camera);


                // Go through loop of all entities and call update.
                for (unsigned int i = 0; i < this->grounds.size(); i++) {
                    Entity *entity = this->grounds[i];
                    entity->update(this);
                }
                for (unsigned int i = 0; i < this->characters.size(); i++) {
                    Entity *entity = this->characters[i];
                    entity->update(this);
                }

                Vector2 coords = characters[0]->GetPos();
                for (unsigned int i = 0; i < this->tanks.size(); i++) {
                    tanks[i].showTank();
                    if ((coords.x >= (tanks[i].getX()) - 94) && (coords.x <= (tanks[i].getX()) + 25) && (coords.y >= (tanks[i].getY()) - 50) && (coords.y <= (tanks[i].getY()) + 124)){
                        if (!tanks[i].getCollected()) {this->tankRefill(); }
                        // if player touches a tank, set tank to collected
                        tanks[i].isCollected();
                    }
                }

                DrawText(FormatText("Oxygen Remaining: %i", this->getO2()), camera.target.x + 103, camera.target.y - 295, 30, RAYWHITE);

                if (this->oxygenRemaining < 1){
                    this->switchGameOver();
                }

                for (unsigned int i = 0; i < this->coins.size(); i++) { // loop through coins and show
                    coins[i].showCoin();
                    if ((coords.x >= (coins[i].getX() - 79)) && (coords.x <= (coins[i].getX() + 15)) && (coords.y >= (coins[i].getY() - 15)) && (coords.y <= (coins[i].getY() + 79))){
                        if (!coins[i].getCollected()) {score = score + 10; }
                        // if player touches coin, set coin to collected
                        coins[i].isCollected();

                    }

                }

                std::cout << "x: " << coords.x << " y: " << coords.y << std::endl;
                //if (coords.x < )
                DrawText(FormatText("Score: %i", score), camera.target.x - 410, camera.target.y - 295, 30, RAYWHITE);
                EndMode2D();
            }
        }
    }

    EndDrawing();
}

// NOTE(Noah): Camera speed must be exactly player speed to avoid buggy behaviour.
// Overall this type of camera moement feels nice!!!!
void Game::updateCameraSmoothFollowInsideMap(float delta){
    float minSpeed = 600.0f;
    float minEffectLength = 5.0f;
    float fractionSpeed = 0.8f;

    Vector2 playerPos = this->characters[0]->GetPos();
    //this->camera.offset = (Vector2){ SCREENWIDTH/2.0f - OFFSETCORRECTVALUE, SCREENHEIGHT/2.0f };
    Vector2 diff = Vector2Subtract(playerPos, this->camera.target);

    float fringeLenX = 400.0f;
    float fringeLenY = 400.0f;
    bool playerOnFringeX = abs(this->camera.target.x - playerPos.x) > SCREENWIDTH/2.0f - fringeLenX;
    bool playerOnFringeY = abs(this->camera.target.y - playerPos.y) > SCREENHEIGHT/2.0f - fringeLenY;

    // adjust the diff accordingly, to only move in specific dir.
    if (playerOnFringeX && !playerOnFringeY) {
        diff.y = 0; 
    } else if (playerOnFringeY && !playerOnFringeX) {
        diff.x = 0;
    } else if (!playerOnFringeY && !playerOnFringeX) {
        diff.x = 0; diff.y = 0;
    }

    float length = Vector2Length(diff);

    if (length > minEffectLength) {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        this->camera.target = Vector2Add(this->camera.target, Vector2Scale(diff, speed*delta/length));
    }
}

// Define the things that will happen when the game is closed.
Game::~Game() {

    // Clean up entities.
    for (unsigned int i = 0; i < this->characters.size(); i++) {
        Entity *entity = this->characters[i];
        delete entity;
    }

    for (unsigned int i = 0; i < this->grounds.size(); i++) {
        Entity *entity = this->grounds[i];
        delete entity;
    }

    // unload the moon texture.
    UnloadTexture(this->moonTexture);

    std::cout << "Game has been closed\n";
}

void Game::showGameOver() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RED);
    DrawText("Game Over", GetScreenWidth()*0.225, GetScreenHeight()*0.3, 100, RAYWHITE);
    DrawText(FormatText("Final Score: %i", score), GetScreenWidth()*0.225, GetScreenHeight()*0.5, 40, RAYWHITE);
    DrawText("Press Enter to Respawn", GetScreenWidth()*0.225, GetScreenHeight()*0.6, 40, RAYWHITE);
}

void Game::switchGameOver() { 
    
    if (this->gameOver == false) {
        // we are going from not gameover to a gameover state.
        // thus, we reset the position of the player!
        this->characters[PLAYER_CHARACTER_INDEX]->SetPos(PLAYER_SPAWN);
        oxygenRemaining = maxO2;
        for (int i = 0; i < tanks.size(); i++) { // put all coins back
            tanks[i].setCollected(false);
        }
        for (int i = 0; i < coins.size(); i++) { // put all coins back
            coins[i].setCollected(false);
        }
    }
    this->gameOver = !this->gameOver;

}

bool Game::getGameOver() { return this->gameOver; }
void Game::showTitle() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawText("Space Evaders", GetScreenWidth()*0.1, GetScreenHeight()*0.3, 95, RAYWHITE);
    DrawText("Press Enter to Start", GetScreenWidth()*0.2, GetScreenHeight()*0.8, 50, RAYWHITE);
}
void Game::showSettings() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawText("Controls", GetScreenWidth()*0.325, GetScreenHeight()*0.1, 75, RAYWHITE);
    DrawText("Press Enter to Switch Movement", GetScreenWidth()*0.1, GetScreenHeight()*0.4, 40, RAYWHITE);

    if (IsKeyPressed(KEY_ENTER)){ setControlFlag(); }

    if (getControlFlag()) {
        DrawText("Movement: WASD", GetScreenWidth()*0.1, GetScreenHeight()*0.5, 40, RAYWHITE);
    }

    else {
        DrawText("Movement: Arrow Keys", GetScreenWidth()*0.1, GetScreenHeight()*0.5, 40, RAYWHITE);
    }

    DrawText("Jump: Space or W/Up Arrow", GetScreenWidth()*0.1, GetScreenHeight()*0.6, 40, RAYWHITE);
    DrawText("Gravity Flip: F", GetScreenWidth()*0.1, GetScreenHeight()*0.7, 40, RAYWHITE);
    DrawText("Black Hole: G", GetScreenWidth()*0.1, GetScreenHeight()*0.8, 40, RAYWHITE);
}

void Game::setSettingsFlag() {
    this->settingsFlag = !this->settingsFlag; // switch flag
}

void Game::setControlFlag() {
    this->controlFlag = !this->controlFlag; // switch control flag
}

bool Game::getControlFlag() { return this->controlFlag; }

int Game::getO2() { return oxygenRemaining; }
void Game::tankRefill() {
    if (this->oxygenRemaining + 50 <= maxO2){
        this->oxygenRemaining = this->oxygenRemaining + 50;
    }
    else { this->oxygenRemaining = maxO2; }
}