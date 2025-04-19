#include <iostream>
#include <vector>
#include <string> // Include for std::string
#include <variant> // Include for std::variant

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>      // Needed for vector conversions
#include <pybind11/variant.h> 


namespace py = pybind11;

// Define types using std directly for clarity
using Value = std::variant<int, double, std::string>;
using Row = std::vector<Value>;
using MixedMatrix = std::vector<Row>; // Equivalent to std::vector<std::vector<Value>>


class Matrix {
private:
    MixedMatrix data;

public:
    // Constructor for C++ usage (optional if only constructing from Python)
    Matrix(std::initializer_list<Row> values) : data(values) {}

    // Constructor more suitable for pybind11 from Python lists
    Matrix(const MixedMatrix& values) : data(values) {}

    // operator overload to operwrite new values
    Value& operator()(size_t i, size_t j) {
        if (i >= data.size() || j >= data[i].size()) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i][j]; // Use [] for potentially better performance if bounds checked
        // return data.at(i).at(j); // .at() includes bounds checking
    }

    // operator overload to call read-only
    const Value& operator()(size_t i, size_t j) const {
         if (i >= data.size() || j >= data[i].size()) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i][j];
        // return data.at(i).at(j);
    }

    // print
    void print() const {
        for (const auto& row : data) {
            for (const auto& cell : row) {
                // Use std::visit for handling variant types
                std::visit([](const auto& val) { // Make lambda argument const&
                    std::cout << val << "\t";   // Use tab for better spacing
                }, cell);
            }
            std::cout << '\n';
        }
    }

    // Optional: Add methods to get dimensions
    size_t rows() const { return data.size(); }
    size_t cols() const { return (data.empty() ? 0 : data[0].size()); } // Assuming non-ragged
};


vector<float> concatenate_list(vector<float> list1, vector<float> list2) {
    int end_size = list1.size() + list2.size();
    vector<float> result(end_size);
    for (int i = 0; i < list1.size(); i++) {
        result[i] = list1[i];
    }
    for (int i = 0; i < list2.size(); i++) {
        result[i + list1.size()] = list2[i];
    }
    return result;
}


class Matrix{
    private:
        MixedMatrix data;

    public:
        // Matrix(initializer_list<Row> values) : data(values) {}
        Matrix(const MixedMatrix &values) : data(values) {}

        // operator overload to operwrite new values
        Value& operator()(size_t i, size_t j) {
            return data.at(i).at(j);
        }
    
        // operator overload to call read-only
        const Value& operator()(size_t i, size_t j) const {
            return data.at(i).at(j);
        }
        
        // print 
        void print() const {
            for (const auto& row : data) {
                for (const auto& cell : row) {
                    visit([](auto& val) {
                        std::cout << val << " ";
                    }, cell);
                }
                cout << '\n';
            }
        }
};


PYBIND11_MODULE(cpp_da, handle) {
    handle.doc() = "C++ Matrix module with mixed data types";
    // handle.def("concatenate_list", &concatenate_list); // Include if needed

    py::class_<Matrix>(handle, "Matrix")
        // Bind the constructor taking a vector of vectors (list of lists from Python)
        .def(py::init<const MixedMatrix&>(), "Construct matrix from a list of lists (rows)")
        // You could still bind the initializer_list constructor if needed for specific C++ interop
        // .def(py::init<std::initializer_list<Row>>(), "Construct from one or more rows (C++ style)")
        .def("print", &Matrix::print, "Print the matrix to stdout")
        .def("rows", &Matrix::rows, "Get the number of rows")
        .def("cols", &Matrix::cols, "Get the number of columns")
        // Example of binding operator() for reading (__getitem__)
        // Takes a tuple (i, j) as argument from Python: matrix[i, j]
        .def("__getitem__", [](const Matrix &m, std::pair<size_t, size_t> i) {
            // Check bounds if needed, though operator() does it now
            return m(i.first, i.second);
        }, "Access element at (row, col) - read only")
        // Example of binding operator() for writing (__setitem__)
        // Takes a tuple (i, j) and a value: matrix[i, j] = value
        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> i, const Value &v) {
            // Check bounds if needed, though operator() does it now
            m(i.first, i.second) = v;
        }, "Set element at (row, col)");

    // Allow pybind11 to implicitly convert Python types to the C++ variant
    // This is usually handled automatically when <pybind11/variant.h> is included
    // and the variant types are bindable (int, double, string are by default).
}



PYBIND11_MODULE(cpp_da, handle){
    handle.doc() = "This is module with some basic function written in C++";
    handle.def("concatenate_list", &concatenate_list);

    py::class_<Matrix>(handle, "Matrix")
    .def(py::init<std::initializer_list<Row>>(), "Construct from one or more rows")
    .def("print", &Matrix::print, "Print the matrix to stdout")
    ;
}
