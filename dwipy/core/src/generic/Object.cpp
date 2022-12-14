#include "dwipy/core/include/generic/Object.h"

using namespace ObjectManger;

std::vector<Object*> ObjectManger::objects;

unsigned int ObjectManger::getNewObjectID() {
    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i] == nullptr) {
            return i;
        }
    }

    objects.push_back(nullptr);
    return objects.size() - 1;
}

void ObjectManger::deleteObject(unsigned int id) {
    delete objects[id];
    objects[id] = nullptr;
}