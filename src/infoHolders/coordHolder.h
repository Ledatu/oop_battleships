#ifndef COORDHOLDER_H
#define COORDHOLDER_H

#include "InfoHolder.h"
#include "coordReader.h"
#include "../exceptions/ReaderException.h"


class CoordHolder : public InfoHolder {

private:
    CoordReader coordReader;
    std::pair<int, int> coords;

public:
    void read () override;

    std::pair<int, int> getCoords ();

};

#endif
