#include "shape.h"
#include <cmath>
#include <sstream>

// Constructor
Shape::Shape(Type type) : m_type(type) {}

// Destructor
Shape::~Shape() {}

// Getter for the type
Shape::Type Shape::getType() const {
    return m_type;
}

// Function to get description of the shape
std::string Shape::getDescription() const {
    std::string description;
    switch (m_type) {
    case Type::SPHERE:
        description = "Sphere";
        break;
    case Type::BOX:
        description = "Box";
        break;
    }
    return description;
}

// Constructor for Sphere
Sphere::Sphere(double radius, Vector3 Center) : Shape(Type::SPHERE), m_radius(radius), m_center(Center) {}



// Constructor for Box
Box::Box(Vector3 boxCoords[]) : Shape(Type::BOX)
{
    Vector3 m_boxCoords[8];
    for (int i = 0; i < 8; i++) {
        m_boxCoords[i] = boxCoords[i];
    };
}

Plane::Plane(Vector3 boxCoords[]) : Shape(Type::PLANE)
{
    Vector3 m_boxCoords[8];
    for (int i = 0; i < 8; i++) {
        m_boxCoords[i] = boxCoords[i];
    };
}
