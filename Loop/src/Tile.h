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
    bool portUp{false};
    bool portRight{false};
    bool portDown{false};
    bool portLeft{false};
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
        if (port == Port::up()) {
            portUp = true;
        } else if (port == Port::right()) {
            portRight = true;
        } else if (port == Port::down()) {
            portDown = true;
        } else if (port == Port::left()) {
            portLeft = true;
        }
    }

    bool operator<(const PortSet& other) const
    {
        if (portUp != other.portUp) {
            return portUp < other.portUp;
        }
        if (portRight != other.portRight) {
            return portRight < other.portRight;
        }
        if (portDown != other.portDown) {
            return portDown < other.portDown;
        }
        if (portLeft != other.portLeft) {
            return portLeft < other.portLeft;
        }
        return false;
    }
};

class Tile : public DrawItem
{
private:
    Sprite* sprite;
    Color color;

    bool availablePorts[4] = {false};

public:
    explicit Tile(Sprite* sprite, Color color);

    static float size();

    void draw() const override;
};
