#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include "MeshLoader.h"
#include "Hash.h"
#include <fstream>


//!!! Задание на защиту (не удалять)
//!!! Реализовать на основе std::ranges 
//!!! 1. Создать контейнер всех КЭ (тетраэдров)
//!!! 2. За один pipeline вывести в файл координаты узлов тетраэдра,
//!!!    лежащего напротив грани с наибольшей площадью. Вывести требуется 10 первых таких точек.




const std::vector<Node>& MeshLoader::getNodes() {
    return Nodes;
}

const std::vector<FiniteElement>& MeshLoader::getFiniteElement() {
    return Element;
}

const std::vector<FiniteElement>& MeshLoader::getBoundElement() {
    return Boundelement;
}


std::vector<int> MeshLoader::getFiniteElementID(int _id1, int _id2, int _id3) {
    std::vector<int> res;

    auto po = [&_id1, &_id2, &_id3, &res](const FiniteElement& elem) {

        if ((std::any_of(elem.NodeID.begin(), elem.NodeID.end(),
                         [_id1](const int id) {return id==_id1;})) &&
            (std::any_of(elem.NodeID.begin(), elem.NodeID.end(),
                         [_id2](const int id) {return id == _id2; })) &&
            (std::any_of(elem.NodeID.begin(), elem.NodeID.end(),
                         [_id3](const int id) {return id == _id3; }))) {
            res.push_back(elem.FiniteElementID);
        }
    };

    std::for_each(Element.begin(), Element.end(),po);
    return res;
}

std::vector<int> MeshLoader::getFiniteElementEdge(int _id1, int _id2) {
    std::vector<int> res;
    auto po = [&_id1, &_id2, &res](const FiniteElement& elem) {

        if ((std::any_of(elem.NodeID.begin(), elem.NodeID.end(),
                         [_id1](const int id) {return id == _id1; })) &&
            (std::any_of(elem.NodeID.begin(), elem.NodeID.end(),
                         [_id2](const int id) {return id == _id2; }))) {
            res.push_back(elem.FiniteElementID);
        }
    };

    std::for_each(Element.begin(), Element.end(),po);
    return res;
}

std::vector<int> MeshLoader::getNodesIDByBorderID(int _id) {
    std::set<int> res;
    auto cur = Boundelement.begin();


    while (cur != Boundelement.end()) {
        cur = std::find_if(cur, Boundelement.end(), [_id](const FiniteElement& elem) {
                               return elem.GeometryAreaID == _id;
                           }
        );
        if (cur != Boundelement.end()) {
            for (const auto &nod : cur->NodeID) {
                Node nodeId = Nodes[nod-1];
                res.insert(nodeId.ID);
            }
            ++cur;
        }
    }
    return std::vector<int>(res.begin(), res.end());
}


//!!! Метод должен возвращать контейнер из ID 

std::vector<Node> MeshLoader::getNodesByBorderID(int _id) {
    std::set<Node> res;
    auto cur = Boundelement.begin();


    while (cur != Boundelement.end()) {
        cur = std::find_if(cur, Boundelement.end(), [_id](const FiniteElement& elem) {
                               return elem.GeometryAreaID == _id;
                           }
        );
        if (cur != Boundelement.end()) {
            for (const auto& nod : cur->NodeID) {
                Node nodeId = Nodes[nod - 1];
                res.insert(nodeId);
            }
            ++cur;
        }
    }
    return std::vector<Node>(res.begin(), res.end());
}

std::vector<int> MeshLoader::getFiniteElementIdSurface(int _id) {
    std::vector<int> res;
    auto po = [&_id, &res](const FiniteElement& elem) {
        if (elem.GeometryAreaID == _id) {
            res.push_back(elem.FiniteElementID);
        }
    };

    std::for_each(Element.begin(), Element.end(), po);
    return res;
}

std::vector<int> MeshLoader::getFiniteElementIDVol(int _id) {
    std::vector<int> res;
    auto po = [&_id, &res](const FiniteElement& elem) {
        if (elem.GeometryAreaID == _id) {
            res.push_back(elem.FiniteElementID);
        }
    };

    std::for_each(Boundelement.begin(), Boundelement.end(), po);
    return res;
}

void MeshLoader::printNodes(const std::vector<Node>& nodes) {
    std::cout << nodes;
}

void MeshLoader::printFiniteElements(const std::vector<FiniteElement>& elem) {
    std::cout << elem;
}

void MeshLoader::insertNodeMid() {
    std::unordered_set<Edge, hash> edge;
    for (auto& elem : Element) {
        std::vector<int> ElemNideID = elem.NodeID;
        for (int first = 0; first < 4; ++first) {
            for (auto sec = first + 1; sec < 4; ++sec) {
                Edge curEdge(ElemNideID[first], ElemNideID[sec]);
                if (edge.insert(curEdge).second) {
                    Node newNode = getMiddleNode(curEdge);
                    curEdge.updMid(newNode.ID);
                    Nodes.push_back(newNode);
                    elem.NodeID.push_back(newNode.ID);
                }
                else {
                    elem.NodeID.push_back(curEdge.midNode);
                }
            }
        }
    }
    for (auto& belem : Boundelement) {
        std::vector<int> bfeNodesId = belem.NodeID;
        for (auto first = 0; first < 3; ++first) {
            for (auto sec = first + 1; sec < 3; ++sec) {
                auto curEdgeIter = edge.find({ bfeNodesId[first], bfeNodesId[sec]});
                if (curEdgeIter == edge.end()) {
                    curEdgeIter = edge.find({ bfeNodesId[sec], bfeNodesId[first]});
                }
                belem.NodeID.push_back(curEdgeIter->midNode);
            }
        }
    }
}


std::array<double,3> MeshLoader::getMiddleEdge(const Edge& edge) {
    double MiddleX = ((Nodes.at(edge.edgeNodes.first - 1).coordinate.at(0)) +
                      (Nodes.at(edge.edgeNodes.second - 1).coordinate.at(0))) / 2;
    double MiddleY = ((Nodes.at(edge.edgeNodes.first - 1).coordinate.at(1)) +
                      (Nodes.at(edge.edgeNodes.second - 1).coordinate.at(1))) / 2;
    double MiddleZ = ((Nodes.at(edge.edgeNodes.first - 1).coordinate.at(2)) +
                      (Nodes.at(edge.edgeNodes.second - 1).coordinate.at(2))) / 2;
    return { MiddleX, MiddleY, MiddleZ };
}

Node MeshLoader::getMiddleNode(const Edge& edge) {
    Node newNode(Nodes.size() + 1, getMiddleEdge(edge), false);
    return newNode;
}

std::array<double,3> MeshLoader::getCoordinate(int id) {
    return Nodes.at(id).coordinate;
}

std::vector<std::set<int>> MeshLoader::createNeighborsVector() {
    std::vector<std::set<int>> neighbors(Nodes.size() + 1);
    for (const auto& elem : Boundelement) {
        for (auto nodeId : elem.NodeID)
            for (auto anthNodeId : elem.NodeID)
                if (nodeId != anthNodeId)
                    neighbors[nodeId].insert(anthNodeId);
    }

    return neighbors;
}
