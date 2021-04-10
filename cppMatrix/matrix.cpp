#ifndef __QS_MATRIX_CPP
#define __QS_MATRIX_CPP

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "matrix.h"
#include <string>


using namespace std;

// Parameter Constructor                                                                                                                                                      
template<typename T>
QSMatrix<T>::QSMatrix(unsigned _rows, unsigned _cols, const T& _initial) {

  vector<vector<T> > placeHolder(_rows, vector<T>(_cols, _initial));
  mat = placeHolder;
  

  rows = _rows;
  cols = _cols;
}

// need to figure out how to wrap constructor
static PyObject* py_QsMatrix(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",QsMatrix(n));
}

// Copy Constructor                                                                                                                                                           
template<typename T>
QSMatrix<T>::QSMatrix(const QSMatrix<T>& rhs) {
  mat = rhs.mat;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// how to wrap copy constructor?

// (Virtual) Destructor                                                                                                                                                       
template<typename T>
QSMatrix<T>::~QSMatrix() {}

// how to wrap destructor?

// how to wrap operators?

// Assignment Operator                                                                                                                                                        
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator=(const QSMatrix<T>& rhs) {
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  mat.resize(new_rows);
  for (unsigned i=0; i<mat.size(); i++) {
    mat[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) {
    for (unsigned j=0; j<new_cols; j++) {
      mat[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
QSMatrix<T> QSMatrix<T>::operator+(const QSMatrix<T>& rhs) {
  QSMatrix result(rows, cols, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(i,j) = this->mat[i][j] + rhs(i,j);
    }
  }

  return result;
}

// Cumulative addition of this matrix and another                                                                                                                             
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator+=(const QSMatrix<T>& rhs) {
  unsigned rows = rhs.get_rows();
  unsigned cols = rhs.get_cols();

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      this->mat[i][j] += rhs(i,j);
    }
  }

  return *this;
}

// Subtraction of this matrix and another                                                                                                                                     
template<typename T>
QSMatrix<T> QSMatrix<T>::operator-(const QSMatrix<T>& rhs) {
  unsigned rows = rhs.get_rows();
  unsigned cols = rhs.get_cols();
  QSMatrix result(rows, cols, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(i,j) = this->mat[i][j] - rhs(i,j);
    }
  }

  return result;
}

// Cumulative subtraction of this matrix and another                                                                                                                          
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator-=(const QSMatrix<T>& rhs) {
  unsigned rows = rhs.get_rows();
  unsigned cols = rhs.get_cols();

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      this->mat[i][j] -= rhs(i,j);
    }
  }

  return *this;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
QSMatrix<T> QSMatrix<T>::operator*(const QSMatrix<T>& rhs) {
  unsigned rows = rhs.get_rows();
  unsigned cols = rhs.get_cols();
  

  unsigned n = this->get_rows();
  unsigned m = this->get_cols();
  
  //We need to throw some sort of exception for when mat multiplication is invalid, don't know how though
  // if(int(m) != int(cols) && false){
  //   throw invalid_argument;
  // }
  

  QSMatrix result(n, cols, 0.0);

  for (unsigned i=0; i<n; i++) {
    for (unsigned j=0; j<cols; j++) {
      for (unsigned k=0; k<rows; k++) {
        result(i,j) += this->mat[i][k] * rhs(k,j);
      }
    }
  }

  return result;
}

// Cumulative left multiplication of this matrix and another                                                                                                                  
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator*=(const QSMatrix<T>& rhs) {
  QSMatrix result = (*this) * rhs;
  (*this) = result;
  return *this;
}



// Calculate a transpose of this matrix                                                                                                                                       
template<typename T>
QSMatrix<T> QSMatrix<T>::transpose() {
  QSMatrix result(cols, rows, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(j,i) = this->mat[i][j];
    }
  }

  return result;
}

static PyObject* py_transpose(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",transpose(n));
}

template<typename T>
void  QSMatrix<T>::setIdentity() {


  for (unsigned i=0; i<mat.size(); i++) {
    mat[i].resize(rows, 0.0);
  }


  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < rows; ++c) {
      this->mat[r][c] = (r == c) ? 1.0 : 0.0;
    }
  }

  cols = rows; 

}

static PyObject* py_setIdentity(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",setIdentity(n));
}

template<typename T>
string QSMatrix<T>::printMatrix() {
  string ret;
  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      ret += to_string(this->mat[i][j]) + ", ";
    }
    ret+='\n';
  }
  ret+='\n';  
  return ret;

}

static PyObject* py_printMatrix(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",printMatrix(n));
}

// Matrix/scalar addition                                                                                                                                                     
template<typename T>
QSMatrix<T> QSMatrix<T>::operator+(const T& rhs) {
  QSMatrix result(rows, cols, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(i,j) = this->mat[i][j] + rhs;
    }
  }

  return result;
}

// Matrix/scalar subtraction                                                                                                                                                  
template<typename T>
QSMatrix<T> QSMatrix<T>::operator-(const T& rhs) {
  QSMatrix result(rows, cols, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(i,j) = this->mat[i][j] - rhs;
    }
  }

  return result;
}

// Matrix/scalar multiplication                                                                                                                                               
template<typename T>
QSMatrix<T> QSMatrix<T>::operator*(const T& rhs) {
  QSMatrix result(rows, cols, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(i,j) = this->mat[i][j] * rhs;
    }
  }

  return result;
}

// Matrix/scalar division                                                                                                                                                     
template<typename T>
QSMatrix<T> QSMatrix<T>::operator/(const T& rhs) {
  QSMatrix result(rows, cols, 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result(i,j) = this->mat[i][j] / rhs;
    }
  }

  return result;
}

// Multiply a matrix with a vector                                                                                                                                            
template<typename T>
std::vector<T> QSMatrix<T>::operator*(const std::vector<T>& rhs) {
  std::vector<T> result(rhs.size(), 0.0);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      result[i] = this->mat[i][j] * rhs[j];
    }
  }

  return result;
}

// Obtain a vector of the diagonal elements                                                                                                                                   
template<typename T>
std::vector<T> QSMatrix<T>::diag_vec() {
  std::vector<T> result(rows, 0.0);

  for (unsigned i=0; i<rows; i++) {
    result[i] = this->mat[i][i];
  }

  return result;
}

static PyObject* py_diag_vec(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",diag_vec(n));
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& QSMatrix<T>::operator()(const unsigned& row, const unsigned& col) {
  return this->mat[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& QSMatrix<T>::operator()(const unsigned& row, const unsigned& col) const {
  return this->mat[row][col];
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned QSMatrix<T>::get_rows() const {
  return this->rows;
}

static PyObject* py_get_rows(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",get_rows(n));
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned QSMatrix<T>::get_cols() const {
  return this->cols;
}

static PyObject* py_get_cols(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",get_cols(n));
}

// Wrapper overhead
static PyMethodDef myMethods[] = {
    {"QsMatrix",py_QsMatrix,METH_VARARGS,"Constructor"},
    {"transpose",py_transpose,METH_VARARGS,"Constructor"},
    {"setIdentity",py_setIdentity,METH_VARARGS,"Turn matrix into identity matrix"},
    {"printMatrix",py_printMatrix,METH_VARARGS,"Print matrix"},
    {"diag_vec",py_diag_vec,METH_VARARGS,"Vector of diagonal elements of matrix"},
    {"get_rows",py_get_rows,METH_VARARGS,"Rows of matrix"},
    {"get_cols",py_get_cols,METH_VARARGS,"Cols of matrix"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef matrixModule = {
    PyModuleDef_HEAD_INIT,
    "matrixModule",
    "Documentation",
    -1,
    myMethods
};

PyMODINIT_FUNC 
PyInit_matrixModule(void)
{
    return PyModule_Create(&matrixModule);
}

#endif