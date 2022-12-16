#ifndef VECTOR3_H_
#define VECTOR3_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cmath>
#include <type_traits>

namespace linalg {
    template<class T> 
    struct Vector3 {
        T x, y, z;

        Vector3() : x(0), y(0), z(0) {}
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        Vector3(PyObject* obj) {
            loadDataFromPyObject(obj);
        }
        ~Vector3() {};

        Vector3<T> cross(const Vector3<T>& other) {
            return Vector3((y * other.z - z * other.y), (z * other.x - x * other.z), (x * other.y - y * other.x));
        }

        T magnitude() {
            return std::sqrt((*this) * (*this));
        }

        Vector3<T> normalized() {
            return (*this) / magnitude();
        }

        void loadDataFromPyObject(PyObject* obj) {
            assert(std::is_arithmetic<T>());
            assert(PyList_Check(obj));
            assert(PyList_Size(obj) == 3);

            x = PyFloat_AsDouble(PyList_GetItem(obj, 0));
            y = PyFloat_AsDouble(PyList_GetItem(obj, 1));
            z = PyFloat_AsDouble(PyList_GetItem(obj, 2));
        }

        PyObject* convertToPyObject() {
            assert(std::is_arithmetic<T>());

            PyObject* obj = PyList_New(3);
            PyList_SetItem(obj, 0, PyFloat_FromDouble(x));
            PyList_SetItem(obj, 1, PyFloat_FromDouble(y));
            PyList_SetItem(obj, 2, PyFloat_FromDouble(z));

            return obj;
        }

        Vector3<T> operator+ (const Vector3<T>& other) {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3<T> operator+ (const T& other) {
            return Vector3(x + other, y + other, z + other);
        }

        Vector3<T> operator- (const Vector3<T>& other) {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3<T> operator- (const T& other) {
            return Vector3(x - other, y - other, z - other);
        }

        T operator* (const Vector3<T>& other) {
            return x * other.x + y * other.y +  z * other.z;
        }

        Vector3<T> operator* (const T& other) {
            return Vector3(x * other, y * other, z * other);
        }

        Vector3<T> operator/ (const T& other) {
            return Vector3(x / other, y / other, z / other);
        }

        bool operator== (const Vector3<T>& other) {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!= (const Vector3<T>& other) {
            return !(*this == other);
        }
    };
}
#endif