#include "Struct.h"

Node::Node(int nId, const std::array<double, 3>& nCoords, bool nVertex):
        ID(nId), coordinate(nCoords), bundle(nVertex) {}


std::ostream& operator<<(std::ostream& out, const Node& _node) {
    out << _node.ID << " ";
    out << _node.coordinate[0] << " " << _node.coordinate[1] << " " << _node.coordinate[2];
    out << " " << _node.bundle;
    out << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<Node>& _node) {
    for (const auto& node : _node)
        out << node;
    return out;
};

std::ostream& operator<<(std::ostream& out, const std::array<double, 3>& ar) {
    for (const auto& coord : ar)
        out << coord;
    return out;
}

bool Node::operator<(const Node& node) const {
    return ID < node.ID;
};

std::ostream& operator<<(std::ostream& out, const FiniteElement& _finiteel) {
    out << _finiteel.FiniteElementID << " ";
    out << _finiteel.GeometryAreaID << " ";
    for (auto& node : _finiteel.NodeID) {
        out << node << " ";
    }
    out << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<FiniteElement>& _finiteel) {
    for (const auto& node : _finiteel)
        out << node;
    return out;
}

Edge::Edge(int firstNodeId, int secNodeId)
        : edgeNodes({ firstNodeId, secNodeId }) {}

void Edge::updMid(int midN) {
    midNode = midN;
}

Edge& Edge::operator=(const Edge& edge) {
    if (this != &edge) {
        this->edgeNodes = edge.edgeNodes;
        this->midNode = edge.midNode;
    }
    return *this;
}

bool Edge::operator==(const Edge& edge) const {
    return (edgeNodes.first == edge.edgeNodes.first) &&
           (edgeNodes.second == edge.edgeNodes.second);
}

std::istream& operator>>(std::istream& in, Edge& edge) {
    in >> edge.edgeNodes.first
       >> edge.edgeNodes.second;
    return in;
}

std::ostream& operator<<(std::ostream& out, Edge& edge) {
    out << edge.edgeNodes.first << ", "
        << edge.edgeNodes.second << std::endl;
    return out;
}


