#include "Scene.h"

#include <Box.h>
#include <cstdio>

Scene::Scene(int id)
{
    sceneId = id;
    resetCamera();
}

Scene::~Scene()
{
    for (int i = 0, m = entities.size(); i < m; i++) {
        delete entities[i];
    }
    entities.clear();
}

bool Scene::render(SDL_Renderer* renderer) {
    bool success = true;
    for (int i = 0, m = entities.size(); i < m; i++) {
        entities[i]->render(renderer);
    }

    return success;
}

void Scene::update(double delta) {
    for (int i = 0, m = entities.size(); i < m; i++) {
        entities[i]->update(delta);
    }
}

void Scene::moveCamera(double x, double y) {
    cameraX+=x;
    cameraY+=y;
}

void Scene::resetCamera() {
    cameraX = 0.0;
    cameraY = 0.0;
    zoom = 100.0;
}

void Scene::addEntity(Entity* e) {
    e->scene = this;
    entities.insert(entities.end(), e);
}
