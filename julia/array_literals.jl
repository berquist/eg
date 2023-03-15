# Examples of specifying array literals.

ex_mat = [[9 8 2] [4 5 3] [10 10 10]]
@assert size(ex_mat) == (1, 9)

ex_mat = [[9 8 2]; [4 5 3]; [10 10 10]]
@assert size(ex_mat) == (3, 3)

ex_mat = [9 8 2; 4 5 3; 10 10 10]
@assert size(ex_mat) == (3, 3)

# this works but 9,8,2 is down a column rather than the first row
ex_mat = [
    9
    8
    2
    ;;
    4
    5
    3
    ;;
    10
    10
    10
]
@assert size(ex_mat) == (3, 3)

ex_mat = [
    9
    8
    2
    ;
    4
    5
    3
    ;
    10
    10
    10
]
@assert size(ex_mat) == (9,)

ex_mat = transpose(reshape([9 8 2 4 5 3 10 10 10], (3, 3)))
@assert size(ex_mat) == (3, 3)

[9 8 2
 4 5 3
 10 10 10]
