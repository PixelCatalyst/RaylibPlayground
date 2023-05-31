#pragma once

#include <string>
#include <initializer_list>

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

    explicit Port(Face face);

public:
    static Port up();

    static Port right();

    static Port down();

    static Port left();

    static Port fromString(const std::string& source);

    bool operator==(const Port& other) const;

    bool isInvalid() const;
};

class PortSet
{
private:
    bool ports[4] = {false};

    int portToIndex(Port port);

public:
    static PortSet of(std::initializer_list<Port> ports);

    void add(Port port);

    void rotate();

    bool operator<(const PortSet& other) const;
};
