
Prime Engine is an engine developed by Prof. Artem Kovalovs.

I had taken a course on Game Engine Development under Professor Kovalovs in Spring ‘24.

Prime Engine is written entirely by Professor Kovalovs. 

The assignment for the course involved implementing features into this engine. This repo contains a snippet of some functionalities that I have added to the engine.

# [Physics Simulation](https://drive.google.com/file/d/1Wx7KFteXaGDwi_OMLQXlXrRZdmibOwi7/view?usp=sharing)
Demo Link: https://drive.google.com/file/d/1Wx7KFteXaGDwi_OMLQXlXrRZdmibOwi7/view?usp=sharing
## Implementation Details
* This is a small physics demo in which, a soldier collides and slides off a car, and then proceeds to walk off the plane and fall into the nothingness.
# Implementation Details

### Class Structure

1. **Shape**:
    - Defines the shape of the object.
    - Types:
        - **Box**: Used for scene nodes except SoldierNPC, stores AABB coordinates.
        - **Sphere**: Used for SoldierNPC, stores center point and radius.
        - **Plane**: Used for Cobble Plane, stores AABB coordinates.

2. **PhysicsComponent**:
    - Holds:
        - Pointer to its scene node.
        - Shape type.
        - Radius and center point (if Sphere).
        - AABB coordinates (if Plane or Box).
    - Functions:
        - `checkCollisions()`: Checks if the player is colliding with a bounding box.
        - `checkFloor()`: Checks if the player is on the ground.

3. **PhysicsManager**:
    - A singleton class that:
        - Stores a vector of all the physics components present in the scene.
        - Manages a list of pointers to every physics component in the scene.

### Initialization and Population

* **Adding Physics Components**:
    - **SoldierNPC**: Attach a physics component to its scene node in `SoldierNPC.cpp`.
    - **Other Meshes**: Add physics components to all other meshes where they are made into scene nodes in `GameObjectManager.cpp`.

### Physics Implementation

* **Movement and Collision Handling**:
    - Update the physics component's position with the soldier's movement in `MovementStateMachine.cpp`.
    - Before moving, check for collisions using `checkCollisions()`. If a collision is detected, adjust the NPC's movement direction accordingly.
    - Check if the soldier is still on the cobble plane using `checkFloor()`. If not, adjust the soldier's movement to simulate falling.




