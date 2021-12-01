# include <bullets.h>

void Bullets::SetActive(Vector2 origin, Vector2 target, float width, float bulletVelocity, bullet_hit_callback *callback) {
    this->origin = origin;
    this->target = target;
    this->width = width;
    this->callback = callback;
    this->active = true;
    this->bulletVelocity = bulletVelocity;
}

void Bullets::Deactivate() { this->active = false; }
void Bullets::SetTarget(Vector2 target) { this->target = target; }
void Bullets::SetWidth(float width) { this->width = width; }

void Bullets::Shoot() {
    if (this->active) {
        // Generate a bullet randomly within the stream spawn region.
        Vector2 bulletPos = this->origin;
        float halfWidth = (int)(0.5 * this->width);
        float bulletPosPertubation = GetRandomValue(-halfWidth, halfWidth);
        Vector2 shootDir = this->GetShootDir();
        Vector2 pDir = (Vector2){-shootDir.y, shootDir.x}; // must be pependicular to the shootDir.
        bulletPos = Vector2Add(bulletPos, Vector2Scale(pDir, bulletPosPertubation));
        // Now take the bullet and add it to the underlying vector array.
        this->bullets.push_back(bulletPos);
    }
}

Vector2 Bullets::GetShootDir() {
    return Vector2Normalize(Vector2Subtract(this->target, this->origin));
}

// NOTE(Noah): I am quite sure that this bullet class is VERY inneficient.
// Only going to see in testing how it performs...and if it is okay.
// TODO(Noah): Need to add a lifetime to bullets.
void Bullets::update(Game *game) {
    if (this->active) {

        float deltaTime = GetFrameTime(); // seconds/frame.

        // Okay so the idea here is to iterate through all the bullets, update them by the velocity, and check if they have hit something else.
        // It could literally be any entity, and if they have hit something, then we want to run a callback. 
        // Also on hit we delete the bullet as well.
        std::vector<Entity *> grounds = game->GetGrounds();
        //std::vector<Entity *> characters = game->GetCharacters();

        std::vector<unsigned int> bulletsToErase;

        // Also in this function we are going to do the rendering of the bullets as well.
        for (unsigned int i = 0; i < this->bullets.size(); i++) {

            Vector2 shootDir = this->GetShootDir();
            float distance = deltaTime * this->bulletVelocity;
            Vector2 lastBulletPos = this->bullets[i];
            this->bullets[i] = Vector2Add(this->bullets[i], Vector2Scale(shootDir, distance));

            // Now we check if this bullet has collided with any entity.
            int bullet_index = -1;
            bullet_hit_info hitInfo;

            for (unsigned int j = 0; j < grounds.size(); j++) {
                /*
                Here's how the collision algorithm is going to work.
                We are going to get the collision of the bullet travel line with the sides of the rectangle.
                The line of the bullet might collide with multiple sides of the platform.
                The point of collision that we want is going to be the point that is closest to the bullet origin.
                */
                Vector2 closestCollisionPoint = lastBulletPos;

                // points on rectangle, maybe we can factor this out.
                Ground *ground = (Ground *)grounds[j];
                Vector2 topLeft = (Vector2){ground->GetPos().x, ground->GetPos().y};
                Vector2 topRight = (Vector2){ground->GetPos().x + ground->getWidth(), ground->GetPos().y};
                Vector2 bottomLeft = (Vector2){ground->GetPos().x, ground->GetPos().y + ground->getHeight()};
                Vector2 bottomRight = (Vector2){ground->GetPos().x + ground->getWidth(), ground->GetPos().y + ground->getHeight()};

                // TODO(Noah): This can likely be factored out.
                // check top of rectangle.
                Vector2 sides[4][2] = {
                    {topLeft, topRight},
                    {bottomLeft, bottomRight},
                    {topLeft, bottomLeft},
                    {topRight, bottomRight}
                };

                Vector2 currentColPos;
                bool result = false;
                for (unsigned int k = 0; k < 4; k++) {
                    Vector2 sideStart = sides[k][0];
                    Vector2 sideEnd = sides[k][1];
                    bool intermediateResult = CheckCollisionLines(sideStart, sideEnd, this->bullets[i], lastBulletPos, &currentColPos);
                    if (intermediateResult) {
                        //std::cout << "We have a collision!!!" << std::endl;
                        result = intermediateResult;
                        if ( Vector2Distance(this->origin,currentColPos) <= Vector2Distance(this->origin,closestCollisionPoint) ) 
                            closestCollisionPoint = currentColPos;
                    }
                }
                
                if (result) {
                    // the bullet has collied with something!
                    hitInfo.entityHit = ground;
                    hitInfo.hitPos = closestCollisionPoint;
                    bullet_index = i;
                    break; 
                    // NOTE/TODO(Noah): no more grounds to check (of course, it might be the case that there is a ground that is very close to another one).
                    // basically, if we wanted to do this properly, we would have to do a proper raycast that considered the depth priority of collision prospects.
                }
            }

            /* for (unsigned int j = 0; j < characters.size() && (bullet_index == -1); j++) {

                // so characters don't really have a defined size....
                // it's literally based on the sprite size.

            }*/

            // check if the bullet has existed for too long.
            if (bullet_index == -1) {
                float distanceTravelled = Vector2Distance( this->bullets[i], this->origin );
                if (distanceTravelled > 600.0f) {
                    bulletsToErase.push_back(i);
                    //this->bullets.erase( this->bullets.begin() + i); // Delete the bullet.
                } else {
                    // if she lives still?
                    // Render the bullet :)
                    DrawPixelV(this->bullets[i], YELLOW);
                    Vector2 startPos = Vector2Add(this->bullets[i], Vector2Scale(shootDir, -5.0f));
                    Vector2 endPos = Vector2Add(this->bullets[i], Vector2Scale(shootDir, 5.0f));
                    DrawLineEx(startPos, endPos, 3.0f, YELLOW); 
                }
            } else if (bullet_index != -1) {
                bulletsToErase.push_back(i);
                //this->bullets.erase( this->bullets.begin() + bullet_index ); // Delete the bullet.
                this->callback(hitInfo); // inform someone that a bullet just hit a thing.
            }

        }

        // delete marked bullets, starting from the back of the array, using the fast method noted by
        // https://stackoverflow.com/questions/3487717/erasing-multiple-objects-from-a-stdvector
        for (int i = bulletsToErase.size() - 1; i >= 0 ; i--) {
            unsigned int toErase = bulletsToErase[i];    
            this->bullets[toErase] = this->bullets.back();
            this->bullets.pop_back();
        }

    }

}
