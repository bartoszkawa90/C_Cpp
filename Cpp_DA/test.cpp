#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <string>
#include <variant>


using namespace std;
namespace py = pybind11;


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

py:array_t<string> sort_dataframe(py:array_t<string> frame) {

    return 
}

int main(){

    vector<vector<float>> arr1 = {
        {1.0, 2.0, 3.0}, 
        {4.0, 5.0, 6.0}, 
        {1.0, 3.0, 6.0}
    };

    vector<vector<float>> arr2 = {
        {1.0, 2.0, 0.0}, 
        {9.0, 1.0, 6.0}, 
        {1.0, 3.0, 8.0}
    };

    vector<vector<float>> arr3 = {
        {1.9, 2.0, 0.0}, 
        {9.0, 1.2, 6.0}, 
        {1.1, 3.0, 8.1}
    };

    process(arr1);

    return 0;
}





// PASSING ANY DATA TYPE
// #include <iostream>
// #include <variant>
// #include <vector>
// #include <string>
// #include <functional>

// using ValueType = std::variant<int, double, std::string>;

// void process(const std::vector<ValueType>& arr) {
//     for (const auto& value : arr) {
//         std::visit([](const auto& elem) {
//             std::cout << elem << std::endl;
//         }, value);
//     }
// }

// int main() {
//     std::vector<ValueType> arr = {42, 3.14, "Hello"};
//     process(arr);
//     return 0;
// }
