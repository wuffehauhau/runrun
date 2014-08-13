/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tile.hpp
 * Created: 2014-06-17
 * Authors: Jani Salo
 */

/*
 * Describes a game tile.
 */

#ifndef RUNRUN_TILE_HPP
#define RUNRUN_TILE_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "tilerecord.hpp"

namespace runrun {
    class Tile {
        friend class TileFactory;

        public:
            Tile();

            const TileRecord& getRecord() const;

        private:
            std::size_t index;
            std::vector< TileRecord >* recordList;

            Tile(const TileRecord& record, std::vector< TileRecord >* recordList);

            static std::vector< TileRecord > defaultRecordList;
    };

    inline Tile::Tile() : Tile(TileRecord(), &Tile::defaultRecordList) {}

    inline Tile::Tile(const TileRecord& record, std::vector< TileRecord >* recordList) : recordList(recordList) {
        std::vector< TileRecord >::const_iterator it = std::find(recordList->cbegin(), recordList->cend(), record);

        if (it == recordList->cend()) {
            recordList->push_back(record);
            index = recordList->cend() - recordList->cbegin()- 1;
        }
        else index = it - recordList->cbegin();
    }

    inline const TileRecord& Tile::getRecord() const { return (*recordList)[index]; }
};

#endif /* RUNRUN_TILE_HPP */

