#include "Port.h"

Port Port::fromString(const std::string& source)
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

Port Port::up()
{
    return Port{Face::UP};
}

Port Port::right()
{
    return Port{Face::RIGHT};
}

Port Port::down()
{
    return Port{Face::DOWN};
}

Port Port::left()
{
    return Port{Face::LEFT};
}

Port::Port(Port::Face face) :
        face{face}
{
}

bool Port::operator==(const Port& other) const
{
    return (face == other.face) && !isInvalid();
}

bool Port::isInvalid() const
{
    return face == Face::NONE;
}

PortSet PortSet::of(std::initializer_list<Port> ports)
{
    PortSet set;
    for (const Port p: ports) {
        set.add(p);
    }
    return set;
}

void PortSet::add(Port port)
{
    int index = portToIndex(port);
    if (index >= 0) {
        ports[index] = true;
    }
}

int PortSet::portToIndex(Port port)
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

void PortSet::rotate()
{
    bool tmp = ports[3];
    ports[3] = ports[2];
    ports[2] = ports[1];
    ports[1] = ports[0];
    ports[0] = tmp;
}

bool PortSet::operator<(const PortSet& other) const
{
    for (int i = 0; i < 4; ++i) {
        if (ports[i] != other.ports[i]) {
            return ports[i] < other.ports[i];
        }
    }
    return false;
}
