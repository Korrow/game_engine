#ifndef SURFACE_HPP
#define SURFACE_HPP
#include <memory>
#include <string>
#include <assert.h>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "exceptions.hpp"

namespace sdlwrap{
    class Render;

    class Rectangle{
        public:
            Rectangle(int x, int y, int w, int h);
            void get(int *x, int *y, int *w, int *h);
            const SDL_Rect *get_raw() const;

            void set_x(int x){
                prect->x = x;
            }

            void set_y(int y){
                prect->y = y;
            }

            void set_w(int w){
                prect->w = w;
            }

            void set_h(int h){
                prect->h = h;
            }

            ~Rectangle(){
                delete prect;
            }

        private:
            SDL_Rect *prect;
    };

    class Surface{
    public:
        Surface(const std::string filepath);

        std::shared_ptr<SDL_Surface>get_surface(){
            return psurface;
        }
    private:
        std::shared_ptr<SDL_Surface> psurface;
    };

    class Texture{
    public:
        Texture(Render *prenderer, Surface *psurface);

        SDL_Texture *get_texture(){
            return ptexture;
        }
    private:
        Render *prenderer;
        SDL_Texture *ptexture;

    };
}

#endif /* SURFACE_HPP */
