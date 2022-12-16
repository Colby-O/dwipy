#ifndef MATRIX_H_
#define MATRIX_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cassert>
#include <iostream>
//#include <dwipy/math/include/linalg/Vector3.h>
/*
namespace linalg {
    template<class T> 
    class Matrix {
    private:
        T* mData;
        int mWidth, mHeight;

        void loadDataFromPyObject(PyObject* obj);
        void loadDataFromArray(const T* data);
    public:
        Matrix(int n, int m);
        Matrix(const T* data, int n, int m);
        Matrix(PyObject* obj) { loadDataFromPyObject(obj); }
        Matrix(const Matrix<T>& matrix);
        ~Matrix();

        static Matrix<T> getIdentity(int n);

        Matrix<T> getInverse();

        T* getData() { return mData; }
        const T* getData() const { return mData; }
        int getWidth() const { return mWidth; }
        int getHeight() const { return mHeight; }
        int getSize() const { return mWidth * mHeight; }

        Matrix<T> operator+ (const Matrix<T>& other) const;
        Matrix<T> operator- (const Matrix<T>& other) const;
        Matrix<T> operator* (const Matrix<T>& other) const;
        Matrix<T> operator* (const Vector<T>& other) const;
        T* operator[] (int i);
        const T* operator[] (int i) const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
            for (int i = 0; i < mat.getHeight(); ++i) {
                for (int j = 0; j < mat.getWidth(); ++j) {
                    os << mat[i][j] << " ";
                }
                os << std::endl;
            }

            return os;
        }
    };

    template<class T> 
    Matrix<T>::Matrix(int n, int m) {
        mWidth  = n;
        mHeight = m;
        mData = new T[mWidth * mHeight];

        std::fill_n(mData, mWidth * mHeight, 0); 
    }

    template<class T> 
    Matrix<T>::Matrix(const T* data, int n, int m) 
    : Matrix<T>(n, m) {
        loadDataFromArray(data);
    }

    template<class T> 
    Matrix<T>::Matrix(const Matrix<T>& other)
    : Matrix<T>(other.getData(), other.getWidth(), other.getHeight()) {
    }

    template<class T> 
    Matrix<T>::~Matrix() {
        delete mData;
    }

    template<class T> 
    void Matrix<T>::loadDataFromArray(const T* data) {
        for (int i = 0; i < this->getSize(); ++i) {
            mData[i] = data[i];
        }
    }

    template<class T> 
    Matrix<T> Matrix<T>::getIdentity(int n) {
        Matrix<T> identity(n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                identity[i][j] = (i == j) ? 1 : 0;
            }
        }

        return identity;
    }

    template<class T> 
    void Matrix<T>::loadDataFromPyObject(PyObject* obj) {

    }

    template<class T> 
    Matrix<T> Matrix<T>::getInverse() {

    }

    template<class T> 
    Matrix<T> Matrix<T>::operator+ (const Matrix<T>& other) const {
        assert(other.getWidth() == mWidth);
        assert(other.getHeight() == mHeight);

        Matrix<T> mat(mWidth, mHeight);

        for (int i = 0; i < mHeight; ++i) {
            for (int j = 0; j < mWidth; ++j) {
                mat[i][j] = (*this)[i][j] + other[i][j];
            }
        }

        return mat;
    }

    template<class T> 
    Matrix<T> Matrix<T>::operator- (const Matrix<T>& other) const {
        assert(other.getWidth() == mWidth);
        assert(other.getHeight() == mHeight);

        Matrix<T> mat = Matrix(mWidth, mHeight);

        for (int i = 0; i < mHeight; ++i) {
            for (int j = 0; j < mWidth; ++j) {
                mat[i][j] = (*this)[i][j] - other[i][j];
            }
        }

        return mat;
    }

    template<class T> 
    Matrix<T> Matrix<T>::operator* (const Matrix<T>& other) const {
        assert(mWidth == other.getHeight());

        Matrix<T> res(other.getWidth(), mHeight);

        for (int i = 0; i < res.getHeight(); ++i) {
            for (int j = 0; j < res.getWidth(); ++j) {
                res[i][j] = 0;
                for (int k = 0; k < mWidth; ++k) {
                    res[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }

        return res;
    }

    template<class T> 
    Matrix<T> Matrix<T>::operator* (const Vector<T>& other) const {

    }

    template<class T> 
    T* Matrix<T>::operator[] (int i) { 
        return &mData[mWidth * i];
    }

    template<class T> 
    const T* Matrix<T>::operator[] (int i) const { 
        return &mData[mWidth * i];
    }
}
*/
#endif