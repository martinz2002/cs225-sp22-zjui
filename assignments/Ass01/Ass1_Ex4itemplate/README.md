# README

This test aims to prove the correctness of member function `AList<class T>::delete_last()`.

This set of test code contains the following parts:

1. Different types of data
2. Different length of list
3. Different $k$-s for `delete_last` function

The test depends on a series of input files in `data\list1.in.txt`, `data\list2.in.txt`, ... The test script written in python is supposed to rename `list?.in.txt` into `list.in` to let testing code run.

## Data Type
We use a single-digit number to denote the type we want to test with.

| Numebr | Datatype
| --- | --- |
| 0 | `int` |
| 1 | `double` |
| 2 | `char` |


## Input Structure
`list.in.txt`
```
<DataType#>
<ListLength>
<Element 1> <Element 2> <Element 3> ... // Seperated by space
<k>
```

## Input Example
```
0       // Denoting <int>
3       // Denoting length
3 2 5   // Denoting initial elements in the list
4       // Denoting $k$
```

## Output `list.out.txt`
```
<ValueOf-k>
<OutputSequence>
<TestStatusPassedFailed>
```

## Output Example
```
4
Index error: list index out of range
Passed
```