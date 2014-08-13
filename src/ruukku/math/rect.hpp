/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    rect.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template container for an axis aligned rectangle.
 */

#ifndef RUUKKU_RECT_HPP
#define RUUKKU_RECT_HPP

namespace ruukku {
    template < typename T >
    class Rect {
        public:
            T posX,  posY;
            T sizeX, sizeY;

        public:
            Rect() {}
            Rect(
                const T posX,  const T posY,
                const T sizeX, const T sizeY
            ) : posX(posX), posY(posY), sizeX(sizeX), sizeY(sizeY) {}

        public:
            bool hasArea() const { return sizeX != static_cast< T >(0) && sizeY != static_cast< T >(0); }

            bool operator ==(const Rect& r) const { return (posX == r.posX) && (posY == r.posY) && (sizeX == r.sizeX) && (sizeY == r.sizeY); }
            bool operator !=(const Rect& r) const { return (posX != r.posX) || (posY != r.posY) || (sizeX != r.sizeX) || (sizeY != r.sizeY); }

        public:
            // Returns the rectangle aligned to positive dimensions.
            Rect getRealign() const;

        public:
            // Clips target rectangle so that it's wholly inside this.
            Rect clip(const Rect& target) const;
    };

    template < typename T >
    Rect< T > Rect< T >::getRealign() const {
        Rect r(*this);

        if (sizeX <static_cast< T >(0)) r.posX = posX + sizeX + static_cast< T >(1), r.sizeX = -sizeX;
        if (sizeY <static_cast< T >(0)) r.posY = posY + sizeY + static_cast< T >(1), r.sizeY = -sizeY;

        return r;

    }

    template < typename T >
    Rect< T > Rect< T >::clip(const Rect& target) const {
        if        (!hasArea()) return Rect(static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0));
        if (!target.hasArea()) return Rect(static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0));

        const Rect clippee = target.getRealign();

        T srcX0 = clippee.posX;
        T srcY0 = clippee.posY;
        T srcX1 = clippee.posX + clippee.sizeX - static_cast< T >(1);
        T srcY1 = clippee.posY + clippee.sizeY - static_cast< T >(1);

        const Rect clipper = this->getRealign();

        const T dstX0 = clipper.posX;
        const T dstY0 = clipper.posY;
        const T dstX1 = clipper.posX + clipper.sizeX - static_cast< T >(1);
        const T dstY1 = clipper.posY + clipper.sizeY - static_cast< T >(1);

        // Test whether the rectangle to be clipped is fully outside clipper.
        if ((srcX1 < dstX0) || (srcX0 > dstX1) || (srcY1 < dstY0) || (srcY0 > dstY1)) return Rect(static_cast< T >(0), static_cast< T >(0), static_cast< T >(0), static_cast< T >(0));

        // Clip coordinates.
        if (srcX0 < dstX0) srcX0 = dstX0;
        if (srcY0 < dstY0) srcY0 = dstY0;
        if (srcX1 > dstX1) srcX1 = dstX1;
        if (srcY1 > dstY1) srcY1 = dstY1;

        return Rect(srcX0, srcY0, srcX1 - srcX0 + static_cast< T >(1), srcY1 - srcY0 + static_cast< T >(1));
    }

    typedef Rect< int > IntRect;
};

#endif /* RUUKKU_RECT_HPP */

