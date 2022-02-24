# README

This test aims to prove the correctness of member function `AList<class T>::delete_last()`.

This set of test code contains the following parts:


1. Different length of list
2. Different $k$ -s for `delete_last` function

The test depends on a series of input files in `data\testpt1.in`, `data\testpt2.in`, ...

The main executable `listmgt` will ask you for the location of any input file.

## Data Type

This test program only supports `int` type of `list`, but since the member function is implemented with a template, it should be functioning correctly with most of the data types.


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
<OutputSequence/FailureMsg>
```

## Output Example
```
4                                       // k = 4
Index error: list index out of range    // Failure Message
```

```
3       // k = 3
6 5 4   // List after deletion is composed with this three elements
```

**[NOTE]** If the list is empty after deletion, `listmgt` will print nothing on the second line.