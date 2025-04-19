#include <iostream>
#include <vector>
// #include <pybind11/pybind11.h>
// #include <pybind11/numpy.h>
// #include <pybind11/complex.h>
// #include <pybind11/stl.h>
#include <string>
#include <variant>


using namespace std;
using Value = variant<int, double, string>;  // Allowed types
using Row = vector<Value>;
using MixedMatrix = vector<vector<Value>>;

class Matrix{
    private:
        MixedMatrix data;

    public:
        Matrix(initializer_list<Row> values) : data(values) {}

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


// MixedMatrix sort_by_types(MixedMatrix matrix) {
    
//     Value row;
//     Value elem;
//     for (auto row: )


//     return 
// }


int main(){

    //     {1.9, 2.0, 0.0}, 
    //     {9.0, 1.2, 6.0}, 
    //     {1.1, 3.0, 8.1}
    // };
    Matrix matrix = {
        {42, 3.14, "hello"},
        {"world", 7, 2.718}
    };

    matrix.print();

    cout << "Value at (1, 0): ";
    visit([](auto&& v) {
        std::cout << v << '\n';
    }, matrix(1, 0));

    matrix(0, 2) = string("updated");
    cout << "\nAfter update:\n";
    matrix.print();

    return 0;
}
