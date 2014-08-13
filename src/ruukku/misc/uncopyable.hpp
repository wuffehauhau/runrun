/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    uncopyable.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A base class for disabling copy operations.
 */

#ifndef RUUKKU_UNCOPYABLE_HPP
#define RUUKKU_UNCOPYABLE_HPP

namespace ruukku {
    class Uncopyable {
        public:
                     Uncopyable() {}
            virtual ~Uncopyable() {}

        private:
            Uncopyable(const Uncopyable& uncopyable);
            Uncopyable& operator =(const Uncopyable& uncopyable);
    };
};

#endif /* RUUKKU_UNCOPYABLE_HPP */

