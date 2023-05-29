#pragma once

#include <raylib.h>
#include <initializer_list>

#include "DrawItem.h"
#include "Sprite.h"

class Port
{
private:
    enum class Face : int8_t
    {
        NONE,
        UP,
        RIGHT,
        DOWN,
        LEFT
    } face;

    explicit Port(Face face) :
            face{face}
    {
    }

public:
    static Port up()
    {
        return Port{Face::UP};
    }

    static Port right()
    {
        return Port{Face::RIGHT};
    }

    static Port down()
    {
        return Port{Face::DOWN};
    }

    static Port left()
    {
        return Port{Face::LEFT};
    }

    static Port fromString(const std::string& source)
    {
        if (source == "UP") {
            return up();
        }
        if (source == "RIGHT") {
            return right();
        }
        if (source == "DOWN") {
            return down();
        }
        if (source == "LEFT") {
            return left();
        }
        return Port{Face::NONE};
    }

    bool operator==(const Port& other) const
    {
        return (face == other.face) && !isInvalid();
    }

    bool isInvalid() const
    {
        return face == Face::NONE;
    }
};

class PortSet
{
private:
    bool ports[4] = {false};

    int portToIndex(Port port)
    {
        if (port == Port::up()) {
            return 0;
        } else if (port == Port::right()) {
            return 1;
        } else if (port == Port::down()) {
            return 2;
        } else if (port == Port::left()) {
            return 3;
        }
        return -1;
    }

public:
    static PortSet of(std::initializer_list<Port> ports)
    {
        PortSet set;
        for (const Port p: ports) {
            set.add(p);
        }
        return set;
    }

    void add(Port port)
    {
        int index = portToIndex(port);
        if (index >= 0) {
            ports[index] = true;
        }
    }

    void rotate()
    {
        bool tmp = ports[3];
        ports[3] = ports[2];
        ports[2] = ports[1];
        ports[1] = ports[0];
        ports[0] = tmp;
    }

    bool operator<(const PortSet& other) const
    {
        for (int i = 0; i < 4; ++i) {
            if (ports[i] != other.ports[i]) {
                return ports[i] < other.ports[i];
            }
        }
        return false;
    }
};

class Tile : public DrawItem
{
private:
    PortSet portSet;
    Sprite* sprite;
    Color color;
    int rotation;
public:
    explicit Tile(PortSet portSet, Sprite* sprite, Color color, int rotation);

    static float size();

    void draw() const override;

    void rotate();
};
