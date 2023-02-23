#ifndef LAB1_ANEUMESHLOADER_H
#define LAB1_ANEUMESHLOADER_H
#include "MeshLoader.h"
#include "Struct.h"
#include "Exception.h"
#include <iostream>
#include <vector>

class AneuMeshLoader: public MeshLoader {
private:
public:
    void loadMesh(const std::string&, const std::string&) override;
};

#endif //LAB1_ANEUMESHLOADER_H
