/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    windowmanager.cpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

#include <algorithm>
#include "windowmanager.hpp"

using namespace std;

namespace ruukku {
    void WindowManager::pumpEvents(const int maxEvents) {
        if (shouldQuit_ == true) return;

        int eventCount = 0;
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN: {
                    vector< Window* >::iterator it = findWindow(event.key.windowID);
                    if (it != windowList_->end()) {
                        (*it)->onKeyDown(event.key.repeat, event.key.keysym);
                    }
                    break;
                }
                case SDL_KEYUP: {
                    vector< Window* >::iterator it = findWindow(event.key.windowID);
                    if (it != windowList_->end()) {
                        (*it)->onKeyUp(event.key.repeat, event.key.keysym);
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    vector< Window* >::iterator it = findWindow(event.key.windowID);
                    if (it != windowList_->end()) {
                        (*it)->onMouseButtonDown(event.button.state, Int2(event.button.x, event.button.y));
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    vector< Window* >::iterator it = findWindow(event.key.windowID);
                    if (it != windowList_->end()) {
                        (*it)->onMouseButtonUp(event.button.state, Int2(event.button.x, event.button.y));
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    vector< Window* >::iterator it = findWindow(event.key.windowID);
                    if (it != windowList_->end()) {
                        (*it)->onMouseMotion(event.motion.state, Int2(event.motion.x, event.motion.y), Int2(event.motion.xrel, event.motion.yrel));
                    }
                    break;
                }
                case SDL_MOUSEWHEEL: {
                    vector< Window* >::iterator it = findWindow(event.key.windowID);
                    if (it != windowList_->end()) {
                        (*it)->onMouseWheelMotion(Int2(event.wheel.x, event.wheel.y));
                    }
                    break;
                }
                case SDL_WINDOWEVENT: {
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_SHOWN: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onShow();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_HIDDEN: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onHide();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_MOVED: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onMove(Int2(event.window.data1, event.window.data2));
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_RESIZED: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onResize(Int2(event.window.data1, event.window.data2));
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_MINIMIZED: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onMinimize();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_MAXIMIZED: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onMinimize();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_RESTORED: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onRestore();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_ENTER: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onMouseEnter();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_LEAVE: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onMouseLeave();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_GAINED: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onFocusGained();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_LOST: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);
                            if (it != windowList_->end()) {
                                (*it)->onFocusLost();
                            }
                            break;
                        }
                        case SDL_WINDOWEVENT_CLOSE: {
                            vector< Window* >::iterator it = findWindow(event.key.windowID);

                            // Ask the window if it wants to be closed.
                            if (it != windowList_->end()) {
                                if ((*it)->onClose()) {
                                    delete (*it);
                                    windowList_->erase(it);
                                }
                            }
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    break;
                }
                case SDL_QUIT: {
                    for (Window* window : *windowList_) {
                        if (window->onQuit()) shouldQuit_ = true;
                    };

                    // Destroy all windows if even one returned true for the quit event.
                    if (shouldQuit_) {
                        for (Window* window : *windowList_) delete window;
                        windowList_->clear();
                    }

                    break;
                }
                default: {
                    break;
                }
            }

            if (eventCount++ >= maxEvents) break;
        }

        for (Window* window : *windowList_) window->onUpdate();
        if  (windowList_->size() == 0) shouldQuit_ = true;
    }

    std::vector< Window* >::iterator WindowManager::findWindow(uint32_t id) const {
        return find_if(windowList_->begin(), windowList_->end(), [=](Window* window){
            return window->getID() == id;
        });
    }
}

