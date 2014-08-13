/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    datafile.cpp
 * Created: 2014-06-01
 * Authors: Jani Salo
 */

#include <fstream>
#include <stdexcept>

#include "datafile.hpp"

using namespace std;

namespace runrun {
    DataFile::DataFile(const string& filename) {
        ifstream ifs;
        ifs.open(filename, ios::in);

        if (!ifs.is_open()) {
            throw runtime_error(string("Couldn't open data file: ") + string(filename));
        }

        while (ifs.good()) {
            string input;
            getline(ifs, input);

            string formatted;
            for (const char c : input) {
                if      (isspace(c))           continue;
                else if (c == ',' || c == ';') formatted.append(1, ' ');
                else                           formatted.append(1, c);
            }

            if (formatted.size() != 0) {
                formattedLineList.push_back(formatted);
            }
        }
    }
};

