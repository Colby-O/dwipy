#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include <utility>

namespace ObjectManger {
    class Object {
    public:
        virtual ~Object() {}
    };

    extern std::vector<Object*> objects;
    unsigned int getNewObjectID();
    void deleteObject(unsigned int id);

    template<class T>
    T* getObject(unsigned int id) {
        assert(id < objects.size());
        return (T*)objects[id]; 
    }

    template<class T, class... Args>
    std::pair<T*, unsigned int> insertObject(Args&&... args) {
        T* obj = new T(std::forward<Args>(args)...);
        unsigned int id = ObjectManger::getNewObjectID();
        objects[id] = obj;
        return std::make_pair(obj, id);
    }
}

#endif