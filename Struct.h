#ifndef LAB1_STRUCT_H
#define LAB1_STRUCT_H
#include <iostream>
#include <vector>
#include <array>

struct Node {
    int ID;
    static constexpr int dim = 3;
    std::array<double, dim> coordinate;
    bool bundle;

    Node() = default;
    Node(int, const std::array<double, dim>&, bool);

    friend std::ostream& operator<<(std::ostream&, const Node&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Node>&);
    friend std::ostream& operator<<(std::ostream&, const std::array<double,3>&);

    bool operator<(const Node& node) const;
};

struct FiniteElement {
    int FiniteElementID;
    int GeometryAreaID;
    std::vector<int> NodeID;

    friend std::ostream& operator<<(std::ostream&, const FiniteElement&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<FiniteElement>&);

};

struct Edge {
    std::pair<int, int> edgeNodes;
    int midNode = -1;
    Edge() = default;
    Edge(int, int);
    void updMid(int);
    Edge& operator=(const Edge&);
    bool operator==(const Edge&) const;
    friend std::istream& operator>>(std::istream&, Edge&);
    friend std::ostream& operator<<(std::ostream&, Edge&);
};

#endif //LAB1_STRUCT_H
