#ifndef FREDKIN_CELL_HPP
#define FREDKIN_CELL_HPP

class FredkinCell : public AbstractCell {
    private:
        int _age;
    public:
        FredkinCell(bool);
        void update(int);
        FredkinCell& operator= (FredkinCell&);
}

#endif