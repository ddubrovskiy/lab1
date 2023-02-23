#ifndef LAB1_MESHLOADER_H
#define LAB1_MESHLOADER_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <array>
#include "Struct.h"

class MeshLoader {
private:
    Node getMiddleNode(const Edge&);
    std::array<double,3> getMiddleEdge(const Edge&);
    std::array<double,3> getCoordinate(int);
protected:
    std::vector<Node> Nodes;
    std::vector<FiniteElement> Element;
    std::vector<FiniteElement> Boundelement;
public:

    virtual void loadMesh(const std::string&, const std::string&) = 0;
    virtual ~MeshLoader() = default;

    const std::vector<Node>& getNodes();
    const std::vector<FiniteElement>& getFiniteElement();
    const std::vector<FiniteElement>& getBoundElement();

    std::vector<int> getFiniteElementID(int, int, int);
    std::vector<int> getFiniteElementEdge(int, int);
    std::vector<int> getNodesIDByBorderID(int);
    std::vector<Node> getNodesByBorderID(int);

    std::vector<int> getFiniteElementIdSurface(int);
    std::vector<int> getFiniteElementIDVol(int);

    static void printNodes(const std::vector<Node>&);

    static void printFiniteElements(const std::vector<FiniteElement>&);

    void insertNodeMid();

    std::vector<std::set<int>> createNeighborsVector();
};

#endif //LAB1_MESHLOADER_H
