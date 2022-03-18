# README

This is the readme file for code testing. You may see three python script files in `Ass04Ex4` folder:

- `autotest.py` -- a script that automatically run testpoints stored in `./data` folder.
- `compare.py` -- a script for comparing the answer file and the user output.
- `data_gen.py` -- a script to generate random input.

We made some modifications in `main` function of `heap.cpp` to enable file I/O thus have it capable for our automatic testing script. 

```cpp
int main()
{
    // We use file I/O to allow automatic testing.
    freopen("heap.in", "r", stdin);
    freopen("heap.out", "w", stdout);

    AList<int> input_array;
    int elm;
    while (scanf("%d", &elm) != EOF)    // input the data
    {
        input_array.append(elm);
    }

    MaxHeap<int> max_heap;
    max_heap.build_heap(input_array);
    cout << max_heap.max() << "\n";  // test build_heap() and max()
    max_heap.heap_sort(input_array); // test heap_sort()
    max_heap.print_elements();
    return 0;
}
```

## Usage

By design, two of the three files -- `autotest.py` and `compare.py` can be reused for all assignments, once the judging process is based on comparison between standard answers and user outputs.

### Generating Data

Data generating is done by `data_gen.py`. There's no much to say -- each assignment have different data generation script.

