// ClothSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Cloth.h"

olc::vi2d Vec2Vi(vec2 v2)
{
    return olc::vi2d(v2[0], v2[1]);
}

class myApp : public olc::PixelGameEngine
{
private:
    // Create a cloth grid at (50,50) of 20x20 dimensions and spring
    // stiffness 2 and damping constant 3.
    Cloth cloth_grid = Cloth(vec2(50, 50), 20, 20, 25, 2.0, 3.0);
    // Keeps track of the mouse position when it was clicked.
    olc::vi2d old_mouse_pos;
    // Boolean to check if particle is selected
    bool has_clicked_on_particle = false;
    // Coordinates of the selected particle
    int particle_selected_i, particle_selected_j;

public:
    void DrawClothGrid()
    {
        // This function draws the cloth grid and the associated springs.
        for (int j = 0; j < cloth_grid.particles.size(); j++)
        {
            for (int i = 0; i < cloth_grid.particles[j].size(); i++)
            {
                // Draw the particle
                vec2 final_pos = cloth_grid.position + cloth_grid.particles[j][i].position;
                FillCircle(Vec2Vi(final_pos), cloth_grid.particles[j][i].mass, olc::RED);

                // Draw all the springs connected to it.
                // This function iterates through each of the spring and draws
                // a line. It thus redraws many springs and could be better
                // optimized.
                std::vector<std::pair<int, int>> connected_indexes = cloth_grid.springs[j][i];
                for (int k = 0; k < connected_indexes.size(); k++)
                {
                    std::pair<int, int> pt = connected_indexes[k];
                    if (pt.first >= 0 && pt.first < cloth_grid.particles[0].size())
                    {
                        if (pt.second >= 0 && pt.second < cloth_grid.particles.size())
                        {
                            vec2 final_pos_to_spring = cloth_grid.position + cloth_grid.particles[pt.second][pt.first].position;
                            DrawLine(Vec2Vi(final_pos), Vec2Vi(final_pos_to_spring), olc::RED, '3333');
                        }
                    }
                }
            }
        }
    }
    myApp()
    {
        sAppName = "Cloth Simulation";
    }
    bool OnUserCreate() override
    {
        return true;
    }

    void GetParticleFromCursor(olc::vi2d mouse_pos)
    {
        // Iterate through all particles
        // This could be optimized, but I've chosen it to remain
        // like this
        for (int j = 0; j < cloth_grid.particles.size(); j++)
        {
            for (int i = 0; i < cloth_grid.particles[0].size(); i++)
            {
                vec2 particle_screen_pos = cloth_grid.position + cloth_grid.particles[j][i].position;
                olc::vi2d ppsp_olc = olc::vi2d(particle_screen_pos[0], particle_screen_pos[1]);
                // If distance of mouse cursor is less than sqrt(50) pixels, select this particle
                // and return.
                if ((mouse_pos - ppsp_olc).mag2() < 50)
                {
                    this->particle_selected_i = i;
                    this->particle_selected_j = j;
                    return;
                }
            }
        }
        // If no particle found, set selected boolean to false.
        this->has_clicked_on_particle = false;
    }
    bool OnUserUpdate(float elapsed)
    {
        Clear(olc::WHITE);
        // If selected, find the particle at mouse position
        // and 
        if (GetMouse(0).bPressed && this->has_clicked_on_particle == false)
        {
            this->has_clicked_on_particle = true;
            old_mouse_pos = GetMousePos();
            GetParticleFromCursor(old_mouse_pos);
        }

        // If mouse is held, then apply force on the selected particle
        if (GetMouse(0).bHeld && this->has_clicked_on_particle == true)
        {
            olc::vi2d f_dir = GetMousePos() - old_mouse_pos;
            // The force F is applied in the direction to the mouse cursor from the
            // original point that was clicked, multiplied by a factor (5 in this case).
            Force f = vec2(f_dir.x, f_dir.y) * 5;
            this->cloth_grid.particles[particle_selected_j][particle_selected_i].ApplyForce(f, elapsed);
        }

        // If mouse is released set the boolean to false so that we don't keep
        // applying the force
        if (GetMouse(0).bReleased)
        {
            this->has_clicked_on_particle = false;
        }
        this->cloth_grid.UpdateGrid(elapsed);
        DrawClothGrid();
        return true;
    }
};

int main()
{
    myApp app;
    if (app.Construct(800, 800, 1, 1))
        app.Start();
    return 0;
}