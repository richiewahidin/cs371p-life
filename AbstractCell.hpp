#ifndef ABSTRACT_CELL_HPP
#define ABSTRACT_CELL_HPP

class AbstractCell() {
    protected:
        bool _alive; // 0 dead 1 alive
    public:

        bool isAlive() const;
        void update(int);
}

#endif