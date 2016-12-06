#include "Block.h"
#include "Drone.h"
#include "Simulator.h"
#include "Map.h"
#include "SdlRenderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>

using namespace std;

Simulator::Simulator() {
    SimObject::setDefaultSimulator(this);
    Render = make_unique<SdlRenderer>();
    Drn = make_unique<Drone>(Vector2D(75, 75), 50);

}

Simulator::~Simulator() {
}

int Simulator::run() {
    SDL_Event Event;

    if (!Render->init()) {
        return 1;
    }

    if (!loadMap(string(SDL_GetBasePath()) + "map.txt")) {
        return 1;
    }

    while (true) {
        while (SDL_PollEvent(&Event) == 1) {
            switch (Event.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    switch(Event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            Render->Offset.X += int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_LEFT:
                            Render->Offset.X -= int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_UP:
                            Render->Offset.Y -= int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_DOWN:
                            Render->Offset.Y += int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_ESCAPE:
                            return 0;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        Render->WinWidth = Event.window.data1;
                        Render->WinHeight = Event.window.data2;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    Render->Zoom += Event.wheel.y * 0.2;
                    if (Render->Zoom < 0.2)
                        Render->Zoom = 0.2;
                    if (Render->Zoom > 10)
                        Render->Zoom = 10;
                    break;
            }
        }

        Render->clear();

        drawObjects();
        updateObjects();

        Render->update();
    }
}

void Simulator::drawObjects() {
    drawBlockGrid();

    for (auto B : Blocks) {
        B.draw();
    }

    Drn->draw();

    drawInfoBox();
}

void Simulator::updateObjects() {
    Drn->update();
}

bool Simulator::loadMap(string Path) {
    ifstream File(Path, ifstream::in);

    int x = Block::Size / 2;
    int y = Block::Size / 2;
    char c;
    while ((c = File.get()) != EOF) {
        switch (c) {
            case WALL_CHAR:
                Blocks.push_back(Block({x, y}, BlockType::Wall));
                x += Block::Size;
                break;
            case WINDOW_CHAR:
                Blocks.push_back(Block({x, y}, BlockType::Window));
                x += Block::Size;
                break;
            case AIR_CHAR:
                x += Block::Size;
                break;
            case '\n':
                y += Block::Size;
                x = Block::Size / 2;
                break;
            default:
                cout << "Wrong character in file: '" << c << "'";
                return false;
        }
    }

    return true;
}

void Simulator::drawBlockGrid() {
    int Height = Render->WinHeight;
    int Width = Render->WinWidth;

    int BlockSize = int(Block::Size * Render->Zoom);

    int HLines = Height / BlockSize;
    int VLines = Width / BlockSize;
    //int FirstBoldY = Render->Offset.Y % (Block::Size * 4) ? 0 : 1;

    Render->setColor({0, 0, 0});


    for (int i = 1; i <= HLines; ++i) {
        int LineY = i * BlockSize;
        if (i % 4)
            Render->drawLine({0, LineY}, {Width, LineY});
        else {
            Render->drawLine({0, LineY - 1}, {Width, LineY - 1});
            Render->drawLine({0, LineY}, {Width, LineY});
            Render->drawLine({0, LineY + 1}, {Width, LineY + 1});
        }
    }


    //int FirstBoldX = Render->Offset.X % (Block::Size * 4) ? 0 : 1;
    for (int i = 1; i <= VLines; ++i) {
        int LineX = i * BlockSize;
        if (i % 4)
            Render->drawLine({LineX, 0}, {LineX, Height});
        else {
            Render->drawLine({LineX - 1, 0}, {LineX - 1, Height});
            Render->drawLine({LineX, 0}, {LineX, Height});
            Render->drawLine({LineX + 1, 0}, {LineX + 1, Height});
        }
    }

}

void Simulator::drawInfoBox() {
    int Height = int(Render->WinHeight * 0.6);
    int Width = Height / 2;

    Vector2D Pos = {int(Render->WinWidth - Width), int(Render->WinHeight - Height)};
    int MarginX = 25, MarginY = 25;
    int OffsetX = Pos.X + MarginX, OffsetY = Pos.Y + MarginY;

    // Design constants
    const int Indent = OffsetX + 20;
    const int ObjSpace = 40;
    const int PropSpace = 40;

    // Draw backgound
    Color BGColor = {35, 35, 35};
    Render->setColor(BGColor);
    Render->drawRect(Pos, int(Width), int(Height));

    // Text color
    Render->setColor({255, 255, 255}, 100);

    // Mouse info
    int MouseOffset = OffsetY;
    Render->drawText(string("Mouse: "), {OffsetX, MouseOffset}, BGColor);

    // Mouse pos
    int MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);
    Render->drawText(string("Pos : (") + to_string(Render->iRelX(MouseX)) + " cm, " + to_string(Render->iRelY(MouseY)) + " cm)", {Indent, MouseOffset + PropSpace}, BGColor);

    // Drone info
    int DroneOffset = MouseOffset + PropSpace + ObjSpace;
    Render->drawText(string("Drone:"), {OffsetX, DroneOffset}, BGColor);
    Render->drawText(string("Pos: (") + to_string(Drn->Pos.X) + " cm, " + to_string(Drn->Pos.Y) + " cm)", {Indent, DroneOffset + PropSpace}, BGColor);
    Render->drawText(string("Angle: ") + to_string(rad_to_deg(Drn->Angle)), {Indent, DroneOffset + PropSpace * 2}, BGColor);

    // Laser info
    int LaserOffset = DroneOffset + PropSpace * 2 + ObjSpace;
    Render->drawText(string("Laser:"), {OffsetX, LaserOffset}, BGColor);
    Render->drawText(string("Front: ") + to_string(Drn->Laser.front_value) + " cm", {Indent, LaserOffset + PropSpace * 1}, BGColor);
    Render->drawText(string("Left: ")  + to_string(Drn->Laser.left_value ) + " cm", {Indent, LaserOffset + PropSpace * 2}, BGColor);
    Render->drawText(string("Right: ") + to_string(Drn->Laser.right_value) + " cm", {Indent, LaserOffset + PropSpace * 3}, BGColor);

    // Sonar info
    int SonarOffset = LaserOffset + PropSpace * 3 + ObjSpace;
    Render->drawText(string("Sonar:"), {OffsetX, SonarOffset}, BGColor);
    Render->drawText(string("Front: ") + to_string(Drn->Sonar.sonar.value) + " cm", {Indent, SonarOffset + PropSpace * 1}, BGColor);


    // Block to cm meter
    int MeterHeight = Render->WinHeight * 0.1;
    int MeterTopY = Render->WinHeight - MeterHeight - MarginY;
    int MeterBotY =  Render->WinHeight - MarginY;
    Render->drawLine({OffsetX + 10, MeterTopY}, {OffsetX + 30, MeterTopY});
    Render->drawLine({OffsetX + 19, MeterTopY}, {OffsetX + 19, MeterBotY});
    Render->drawLine({OffsetX + 20, MeterTopY}, {OffsetX + 20, MeterBotY});
    Render->drawLine({OffsetX + 21, MeterTopY}, {OffsetX + 21, MeterBotY});
    Render->drawLine({OffsetX + 10, MeterBotY}, {OffsetX + 30, MeterBotY});
    Render->drawText(to_string(Render->iRel(MeterHeight)) + string("cm"), {OffsetX + 30, MeterTopY + MeterHeight / 2 - 15}, BGColor);
}

