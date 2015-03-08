#include <iostream>
#include <SDL2/SDL_image.h>
#include "core/render/surfaceManager.hpp"

namespace render{

    SDL_Surface *surfaceManager::do_requestSurface(const std::string &path){
        auto it = surfacemap.find(path);
        SDL_Surface *psurface = nullptr;
        if (it == surfacemap.end() ){
            std::cout << "Haven't loaded this one yet";
            psurface = IMG_Load(path.c_str());
            if (psurface == nullptr ){
                printf ("Unable to load image %s Error %s\n",
                        path.c_str(), IMG_GetError() );
            }else{
                //TODO: Add the SDL_ConvertSurface function here
                surfacemap.emplace(path,psurface);
            }
        }else{
            psurface = (it)->second;
        }
        return psurface;
    }
};
