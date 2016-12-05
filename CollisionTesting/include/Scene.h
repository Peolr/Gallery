#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <vector>
#include <Entity.h>
class Entity;

class Scene
{
    public:
        Scene(int id);
        virtual ~Scene();

        int sceneId;

        double cameraX;
        double cameraY;

        double zoom;

        void resetCamera();

        bool render(SDL_Renderer* renderer);
        std::vector<Entity*> entities;

        void addEntity(Entity* e);

        void moveCamera(double x, double y);

        void update(double delta);


    protected:

    private:
};

#endif // SCENE_H
