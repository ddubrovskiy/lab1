#include "AneuMeshLoader.h"
#include <fstream>
#include <algorithm>

void AneuMeshLoader::loadMesh(const std::string& fileName, const std::string& format) {
    std::ifstream file(fileName + format);
    if (!file.is_open()) {
        std::ifstream file2(fileName + format);
        file2.is_open() ? throw WrongFileFormat() : throw FileNotFound();
    }
    int count, dimension;
    file >> count >> dimension;
    Nodes.reserve(count);
    for (int i = 0; i < count; ++i) {
        Node temp;
        file >> temp.coordinate[0] >> temp.coordinate[1] >> temp.coordinate[2];
        temp.ID = i+1;
        temp.bundle = false;
        Nodes.push_back(temp);
    }

    file >> count >> dimension;
    Element.reserve(count);
    for (int i = 0; i < count; ++i) {
        FiniteElement temp;
        int IDNode;
        file >> temp.GeometryAreaID;
        for (int j = 0; j < dimension; ++j) {
            file >> IDNode;
            temp.NodeID.push_back(IDNode);
        }
        temp.FiniteElementID = i;
        Element.push_back(std::move(temp));
    }

    file >> count >> dimension;
    Boundelement.reserve(count);
    for (int i = 0; i < count; ++i) {
        FiniteElement temp;
        int IDNode;
        file >> temp.GeometryAreaID;
        for (int j = 0; j < dimension; ++j) {
            file >> IDNode;
            temp.NodeID.push_back(IDNode);
        }
        temp.FiniteElementID = i;
        Boundelement.push_back(std::move(temp));
    }
}
