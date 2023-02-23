#include <algorithm>
#include <fstream>
#include <valarray>
#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include "MeshLoader.h"
#include "AneuMeshLoader.h"
using namespace std;

namespace std {
    std::ostream& operator<<(std::ostream& out, const std::array<double, 3>& ar) {
        for (const auto& coord : ar)
            out << coord;
        return out;
    }
};

int main() {
    MeshLoader* l = new AneuMeshLoader();
    try {
        l->loadMesh("a", ".aneu");
    }
    catch (std::exception& er) {
        std::cerr << er.what() << std::endl;
        delete l;
        return 0;
    }

    l->printNodes(l->getNodes());
    l->printFiniteElements(l->getFiniteElement());
    l->printFiniteElements(l->getBoundElement());

    std::cout << "ID Finite elements by nodes" << std::endl;
    auto finelem = l->getFiniteElementID(4,1,2);
    for (int elem : finelem) {
        std::cout << elem << " ";
    }
    std::cout << std::endl << "-----------------------------------" << std::endl;

    delete l;

    return 0;
}
