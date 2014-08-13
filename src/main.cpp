/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    main.cpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

#include <fstream>
#include <iostream>

#include "main/mainwindow.hpp"
#include "ruukku/system/windowmanager.hpp"

// DEBUG
// #define RUNRUN_OUTPUT_TO_FILE

using namespace std;
using namespace ruukku;
using namespace runrun;

int main(int argc, char *argv[]) {
    vector< Window* > windowList;

#ifdef RUNRUN_OUTPUT_TO_FILE
    ofstream output("output.log");
    streambuf* oldOut = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    ofstream error("error.log");
    streambuf* oldErr = cerr.rdbuf();
    cerr.rdbuf(error.rdbuf());
#endif

    try {
        MainWindow* mainWindow = new MainWindow();
        windowList.push_back(mainWindow);

        WindowManager manager(&windowList);
        while (!manager.shouldQuit()) { manager.pumpEvents(); }
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }

    for (Window* window : windowList) {
        delete window;
    };

#ifdef RUNRUN_OUTPUT_TO_FILE
    cerr.rdbuf(oldErr);
    cout.rdbuf(oldOut);

    output.close();
    error.close();
#endif

    return 0;
}

