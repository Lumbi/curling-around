#ifndef COMPONENT_H
#define COMPONENT_H

class Actor;

class Component
{
    public:
        Component();
        virtual ~Component();

        virtual void update() = 0;
        virtual void draw() = 0;

        void setActor(Actor *);
        Actor * const getActor() const;

    private:
        Actor *actor;
};

#endif
