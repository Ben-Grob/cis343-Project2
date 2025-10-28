#include <iostream>

class Shape {
public:
    int area() {
        // Implementation for area
    }
    
private:
    // Private members
};

class Rectangle : public Shape { // Rectangle is a derived class of Shape
public:
    int length, width;

private:
    int area() {
        return(length * width); 
    }
};

class Circle : public Shape { // Circle is a derived class of Shape
public:
    int radius;

private:
    int area() {
        return((radius * 3.14) * (radius * 3.14)); 
    }
};

Shape* shape_ptr;
Shape obj_shape;
Rectangle obj_rectangle;

// Pointing to derived class
shape_ptr = &obj_rectangle;
