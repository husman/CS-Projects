#include <gtest/gtest.h>

#include "../include/graph.h"

bool vertexIsIn(Vertex *vertex, Vertex *vertices) {
    Vertex *vertices_list = vertices;
    if (vertex == NULL || vertices_list == NULL) {
        return false;
    }
    while(vertices_list != NULL) {
        if(vertices_list->value == vertex->value)
            return true;

        vertices_list = vertices_list->next;
    }

    return false;
}

TEST(Graph, can_add_vertices) {
    Graph graph;
    Vertex v1, v2, v3, v4;
    int _v1, _v2, _v3, _v4;
    v1.value = 'a';
    v2.value = 'b';
    v3.value = 'c';
    v4.value = 'd';

    graph.addVertex(&v1);
    graph.addVertex(&v2);
    graph.addVertex(&v3);
    graph.addVertex(&v4);

    graph.connectVertices(&v1, &v2);
    graph.connectVertices(&v1, &v3);
    graph.connectVertices(&v2, &v4);

    Vertex *path_from_v1_to_v4 = graph.getPathFromTo(&v1, &v4);

    ASSERT_TRUE(vertexIsIn(&v1, path_from_v1_to_v4));
    ASSERT_TRUE(vertexIsIn(&v2, path_from_v1_to_v4));
    ASSERT_TRUE(vertexIsIn(&v4, path_from_v1_to_v4));

    ASSERT_EQ(v1.value, path_from_v1_to_v4->value);
    ASSERT_EQ(0, path_from_v1_to_v4->distance);

    path_from_v1_to_v4 = path_from_v1_to_v4->next;
    ASSERT_EQ(v2.value, path_from_v1_to_v4->value);
    ASSERT_EQ(1, path_from_v1_to_v4->distance);

    path_from_v1_to_v4 = path_from_v1_to_v4->next;
    ASSERT_EQ(v4.value, path_from_v1_to_v4->value);
    ASSERT_EQ(2, path_from_v1_to_v4->distance);

}