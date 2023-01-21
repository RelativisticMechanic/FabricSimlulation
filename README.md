<img src="https://github.com/RelativisticMechanic/FabricSimlulation/blob/main/working.gif" alt="Working of the program" width="300"/>

# Fabric Simlulation

This is a C++ program that can simulate a piece of fabric kept on a flat surface. Fabric simlulation finds a lot of application in games where characters or objects have a piece of cloth on them that needs to look real, as well as be able to respond to player input. 

## Basics

A fabric can be modeled as a grid of particles connected by springs. A spring is modelled by Hooke's Law which states:

$$ \frac{d^2 x}{dt^2} = -kx $$

Here $k$ is the spring stiffness, defined for a spring made of particular material while $x$ is the displacement of the spring from the mean position.

This is a one-dimensional version, of course. What we do is apply this law in two dimensions, consider two particles, one at $\vec{p}$ and the other at $\vec{q}$. Suppose that the natural distance between the two particles is $L$. Then the force acting on particle at $\vec{p}$ due to the spring between the two particles will be given by:

$$ \vec{F_{p}} = -k\frac{\vec{p} - \vec{q}}{|\vec{p} - \vec{q}|}(||\vec{p} - \vec{q}| - L|) $$

Now if the particle at $\vec{p}$ is connected to various other particles, we can simply add up the forces, and apply Newton's Second Law $F = m\frac{d^2 x}{dt^2}$ to calculate the acceleration and solve the differential equation to get the position.

I use the Euler Solver, which is not _very_ good, but it works for smaller $k$. For larger $k$, a better solver like Runge Kutta 4 would be required. This was largely a proof of concept project.

## Compiling

The project is tested with Visual Studio 2022. Simply open up the solution and click Run. It should work. You could also compile it with g++, I'll supply a Makefile when I get some time. 

## Running

After you've click run on VS 2022, try pulling on one of the particles using your mouse by clicking on one particle and dragging it. The top and left sides are fixed every other particle can be pulled. 

## Credits

I've used Javidx9's ```olc::PixelGameEngine``` as way to render output. It makes the code portable, as the dependencies are none, and its a header only library and handles system-specific details on its own.

S, Gautam.
