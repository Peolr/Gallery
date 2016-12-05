#include "SceneController.h"
#include <cstdio>

SceneController::SceneController()
{
    currentSceneId = 0;
}

SceneController::~SceneController()
{
    for (int i = 0, m = scenes.size(); i < m; i++) {
        delete scenes[i];
    }
    scenes.clear();
}


Scene* SceneController::newScene() {
    Scene* s = new Scene(scenes.size());//no + 1 or - 1 because size is always + 1
    scenes.insert(scenes.end(), s);
    return s;
}

Scene* SceneController::getCurrentScene() {
    return scenes[getCurrentSceneId()];
}

int SceneController::getCurrentSceneId() {
    return currentSceneId;
}

bool SceneController::renderCurrentScene(SDL_Renderer* renderer) {
    return getCurrentScene()->render(renderer);
}
