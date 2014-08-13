/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    view.hpp
 * Created: 2014-06-05
 * Authors: Jani Salo
 */

/*
 * Camera view.
 */

#ifndef RUNRUN_VIEW_HPP
#define RUNRUN_VIEW_HPP

#include "geometry/line.hpp"
#include "geometry/aasquare.hpp"

namespace runrun {
    class View {
        public:
            View() {}
            View(
                const Line& lLine,
                const Line& rLine,
                const Line& bLine,
                const Line& tLine
            ) :
                m_lLine(lLine),
                m_rLine(rLine),
                m_bLine(bLine),
                m_tLine(tLine)
            {}

            const Line& getLLine() const { return m_lLine; }
            const Line& getRLine() const { return m_rLine; }
            const Line& getBLine() const { return m_bLine; }
            const Line& getTLine() const { return m_tLine; }

            bool isAASquareVisible(const AASquare& square) const;

        private:
            Line m_lLine;
            Line m_rLine;
            Line m_bLine;
            Line m_tLine;
    };

    inline bool View::isAASquareVisible(const AASquare& square) const {
        if      (square.isAboveLine(m_lLine)) return false;
        else if (square.isAboveLine(m_rLine)) return false;
        else if (square.isAboveLine(m_bLine)) return false;
        else if (square.isAboveLine(m_tLine)) return false;
        else return true;
    }
};

#endif /* RUNRUN_VIEW_HPP */

