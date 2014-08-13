/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    cubo.hpp
 * Created: 2013-01-26
 * Authors: Jani Salo
 */

/*
 * A template container for an axis aligned cuboid.
 */

#ifndef RUUKKU_CUBO_HPP
#define RUUKKU_CUBO_HPP

namespace ruukku {
    template < typename T >
    class Cubo {
        public:
            T posX,  posY,  posZ;
            T sizeX, sizeY, sizeZ;

        public:
            Cubo() {}
            Cubo(
                const T posX,  const T posY,  const T posZ,
                const T sizeX, const T sizeY, const T sizeZ
            ) : posX(posX), posY(posY), posZ(posZ), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {}

        public:
            bool hasVolume() const { return sizeX != static_cast< T >(0) && sizeY != static_cast< T >(0) && sizeZ != static_cast< T >(0); }

            bool operator ==(const Cubo& c) const { return (posX == c.posX) && (posY == c.posY) && (posZ == c.posZ) && (sizeX == c.sizeX) && (sizeY == c.sizeY) && (sizeZ == c.sizeZ); }
            bool operator !=(const Cubo& c) const { return (posX != c.posX) || (posY != c.posY) || (posZ != c.posZ) || (sizeX != c.sizeX) || (sizeY != c.sizeY) || (sizeZ != c.sizeZ); }

        public:
            // Returns the cuboid aligned to positive dimensions.
            Cubo getRealign() const;

        public:
            // Clips target cuboid so that it's wholly inside this.
            Cubo clip(const Cubo& target) const;
    };

    template < typename T >
    Cubo< T > Cubo< T >::getRealign() const {
        Cubo c(*this);

        if (sizeX <static_cast< T >(0)) c.posX = posX + sizeX + static_cast< T >(1), c.sizeX = -sizeX;
        if (sizeY <static_cast< T >(0)) c.posY = posY + sizeY + static_cast< T >(1), c.sizeY = -sizeY;
        if (sizeZ <static_cast< T >(0)) c.posZ = posZ + sizeZ + static_cast< T >(1), c.sizeZ = -sizeZ;

        return c;
    }

    template < typename T >
    Cubo< T > Cubo< T >::clip(const Cubo& target) const {
        if        (!hasVolume()) return Cubo(static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0));
        if (!target.hasVolume()) return Cubo(static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0));

        const Cubo clippee = target.getRealign();

        T srcX0 = clippee.posX;
        T srcY0 = clippee.posY;
        T srcZ0 = clippee.posZ;
        T srcX1 = clippee.posX + clippee.sizeX - static_cast< T >(1);
        T srcY1 = clippee.posY + clippee.sizeY - static_cast< T >(1);
        T srcZ1 = clippee.posZ + clippee.sizeZ - static_cast< T >(1);

        const Cubo clipper = this->getRealign();

        const T dstX0 = clipper.posX;
        const T dstY0 = clipper.posY;
        const T dstZ0 = clipper.posZ;
        const T dstX1 = clipper.posX + clipper.sizeX - static_cast< T >(1);
        const T dstY1 = clipper.posY + clipper.sizeY - static_cast< T >(1);
        const T dstZ1 = clipper.posZ + clipper.sizeZ - static_cast< T >(1);

        // Test whether the cuboid to be clipped is fully outside clipper.
        if ((srcX1 < dstX0) || (srcX0 > dstX1) || (srcY1 < dstY0) || (srcY0 > dstY1) || (srcZ1 < dstZ0) || (srcZ0 > dstZ1)) {
            return Cubo(static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0));
        }

        // Clip coordinates.
        if (srcX0 < dstX0) srcX0 = dstX0;
        if (srcY0 < dstY0) srcY0 = dstY0;
        if (srcZ0 < dstZ0) srcZ0 = dstZ0;
        if (srcX1 > dstX1) srcX1 = dstX1;
        if (srcY1 > dstY1) srcY1 = dstY1;
        if (srcZ1 > dstZ1) srcZ1 = dstZ1;

        return Cubo(srcX0, srcY0, srcZ0, srcX1 - srcX0 + static_cast< T >(1), srcY1 - srcY0 + static_cast< T >(1), srcZ1 - srcZ0 + static_cast< T >(1));
    }

    typedef Cubo< int > IntCubo;
};

#endif /* RUUKKU_CUBO_HPP */

