#ifndef  __PYENGINE_2_0_SHAPE_H__
#define  __PYENGINE_2_0_SHAPE_H__

#include <string>
#include "PrimeEngine/Math/Vector3.h"

class Shape {
public:
    // Enum to represent the shape types
    enum class Type {
        SPHERE,
        BOX,
        PLANE
    };

    // Constructor
    Shape(Type type);

    // Destructor
    ~Shape();

    // Getter for the type
    Type getType() const;



    // Function to get description of the shape
    std::string getDescription() const;

private:
    Type m_type; // Type of the shape
};

// Derived class Sphere
class Sphere : public Shape {
public:
    // Constructor
    Sphere(double radius, Vector3 Center);
    Vector3 m_center;
    double m_radius; 
};

// Derived class Box
class Box : public Shape {
public:
    // Constructor
    Box(Vector3 boxCoords[]);

  


    Vector3 m_boxCoords[];
};

class Plane : public Shape {
public:
    // Constructor
    Plane(Vector3 boxCoords[]);




    Vector3 m_boxCoords[];
};

#endif // SHAPE_H
