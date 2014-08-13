/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    datafile.hpp
 * Created: 2014-06-01
 * Authors: Jani Salo
 */

/*
 * A simple formatter for CSV data files.
 */

#ifndef RUNRUN_DATAFILE_HPP
#define RUNRUN_DATAFILE_HPP

#include <string>
#include <vector>

namespace runrun {
    class DataFile {
        public:
            typedef std::vector< std::string >::const_iterator ConstListIt;
            typedef std::vector< std::string >::iterator       ListIt;

            DataFile(const std::string& filename);

            const std::vector< std::string >& getFormattedData() const;
                  std::vector< std::string >& getFormattedData();

        private:
            std::vector< std::string > formattedLineList;
    };

    inline const std::vector< std::string >& DataFile::getFormattedData() const { return formattedLineList; }
    inline       std::vector< std::string >& DataFile::getFormattedData()       { return formattedLineList; }
};

#endif /* RUNRUN_DATAFILE_HPP */

