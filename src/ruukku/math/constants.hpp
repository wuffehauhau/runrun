/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    constants.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A collection of mathematical constants.
 */

#ifndef RUUKKU_CONSTANTS_HPP
#define RUUKKU_CONSTANTS_HPP

namespace ruukku {
    template < typename T >
    class Constants {
        public:
            static double Pi()        { return static_cast< T >   (3.1415926535897932); }
            static double InvPi()     { return static_cast< T >   (0.3183098861837907); }

            static double Pi2()       { return static_cast< T >   (6.2831853071795865); }
            static double InvPi2()    { return static_cast< T >   (0.1591549430918953); }

            static double E()         { return static_cast< T >   (2.7182818284590452); }
            static double InvE()      { return static_cast< T >   (0.3678794411714423); }

            static double Deg360()    { return static_cast< T > (360.0000000000000000); }
            static double InvDeg360() { return static_cast< T >   (0.0027777777777778); }
    };
};

#endif /* RUUKKU_CONSTANTS_HPP */

