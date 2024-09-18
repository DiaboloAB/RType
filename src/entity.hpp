#ifndef ENTITY_HPP
    #define ENTITY_HPP

    #include <iostream>

class Entity {
public:
    explicit Entity(std::size_t id) : id(id) {}

    operator std::size_t() {
        return id;
    }

private:
    std::size_t id;
};

#endif // ENTITY_HPP
