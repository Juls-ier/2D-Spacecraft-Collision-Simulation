# 2D-Spacecraft-Collision-Simulation
A C++/SFML 2D simulation of a moving spacecraft and projectiles, featuring convex hull generation with QuickHull and geometric collision detection.

# Overview

The simulation loads a spacecraft's geometry, position, and velocity from input files. The spacecraft is represented by a set of points, from which a convex hull is calculated using the QuickHull algorithm.

Projectiles are also loaded with their initial positions, velocities, and starting times. The program then simulates their movement and checks whether their trajectories intersect with the moving spacecraft.

The result is visualized in real time using SFML.

# Features

2D visualization using SFML

Loading object geometry from external files

Loading spacecraft position and velocity from input data

Loading projectile trajectories from input data

Convex hull generation using the QuickHull algorithm

2D vector-based object movement

Projectile movement simulation

Geometric intersection calculations

Collision detection between moving objects

Visualization of spacecraft geometry, convex hull, projectiles, and detected collisions

Interactive camera movement and zooming

# Algorithms

Convex Hull – QuickHull

The spacecraft is initially represented by a collection of points. To simplify collision detection, the program calculates a convex hull around these points.
The implementation uses the QuickHull algorithm. 


Collision Detection

Collision detection is based on geometric intersection between line segments representing the motion of the spacecraft and projectiles.

# Spacecraft geometry and state

The spacecraft geometry is loaded as a list of 2D points:

x y

x y

x y

...


The spacecraft state file contains its position and velocity:

position_x position_y

velocity_x velocity_y

Projectile data contains:

time x y ve

locity_x velocity_y

