#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>


using namespace std;
namespace py = pybind11;

/*
Build with  " cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..  "  to make it work on Macos
*/



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


PYBIND11_MODULE(cpp_da, handle){
    handle.doc() = "This is module with some basic function written in C++";
    handle.def("concatenate_list", &concatenate_list);
}
