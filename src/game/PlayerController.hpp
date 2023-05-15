#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

class Scene;
class CurlingStone;

class PlayerController {
    public:
        enum class State {
            aiming,
            sliding,
            waiting
        };

    public:
        PlayerController(Scene *);

        void update();

    private:
        void spawnStone();
        void throwStone();

    private:
        State state;
        Scene *scene;
        CurlingStone *curlingStone;
};

#endif
