# from build.cpp_da import concatenate_list

# l = concatenate_list([1, 2, 3], [1, 2, 3])

# print(l)

from build.cpp_da import Matrix
try:
    m = Matrix([[1, 2, '4'], [1, 'fd', 1]])
    m.print()
except:
    print('2 [[ did not work')
try:
    m = Matrix([1, 2, '4'], [1, 'fd', 1])
    m.print()
except:
    print('1 [ did not work')

