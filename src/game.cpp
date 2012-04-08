#include <iostream>
#include <cstdio>

#include <SDL.h>

#include "renderer.h"
#include "resourcemanager.h"
#include "game.h"
#include "image.h"
#include "drawable.h"
#include "tileset.h"
#include "tilemap.h"
#include "resource.h"
#include "font.h"

game::game()
{
    updateno = 0;

    r = new renderer(960, 640);
    rm = new resourcemanager(this);
    f = new font(rm->getImage("charmap1.png"), this, 16, 16);

    c.x = 0;
    c.y = 0;

    assets.push_back(new tilemap(this, "tileset.png", resource("tilemap.json").getJson()));
//    tileset foo(this, "tileset.png", resource("tileset.json").getJson());

    std::cout << "Made game" << std::endl;
}

game::~game()
{
    delete(rm);
    delete(r);
    delete(f);
}

void
game::render()
{
    r->clear();

    f->drawString("\\ff0000ff\\red\n\\00ff00ff\\green\n\\0000ffff\\blue", 0, 0);

/*    for (uint32_t i=0; i < assets.size(); i++)
    {
        assets[i]->render();
    }*/



    r->swap();
}

int
game::update()
{
    updateno++;

    if ( updateno % 60 == 0 )
    {
        char caption[128];
        sprintf(caption, "Assets: %lu", assets.size());
        SDL_WM_SetCaption(caption, NULL);
    }
    c.x += 10;

    for (uint32_t i=0; i < assets.size(); i++)
    {
        assets[i]->update();
    }


    return 0;
}
