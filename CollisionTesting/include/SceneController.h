#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <vector>
#include <Scene.h>

class SceneController
{
    public:
        SceneController();
        virtual ~SceneController();

        int currentSceneId;
        std::vector<Scene*> scenes;

        Scene* getCurrentScene();

        void setCurrentSceneId(int id);

        Scene* newScene();

        int getCurrentSceneId();

        bool renderCurrentScene(SDL_Renderer* renderer);



    protected:

    private:
};

#endif // SCENECONTROLLER_H
