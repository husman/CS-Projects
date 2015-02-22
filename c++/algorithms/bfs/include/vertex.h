#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    Vertex *next;
    Vertex *predecessor;
    char value;
    int distance;
    int index;
    bool visted;
};

#endif