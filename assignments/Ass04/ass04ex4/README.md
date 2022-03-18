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

Start the script by running `python data_gen.py`. The script will check whether the configuration file `data/config` exists. If not, it will requires you to enter:

- Base name of input/output file.
- Name of the executable to test.
- Number of test points.

Those infomation is stored in `data/config`, and if the file is missing `autotest.py` will automatically call `data_gen.py` on running; other wise `autotest.py` will assume all testpoints data are stored in `data/` and run the test.

### Testing
The script `autotest.py` is used for automatic test. Run it by `python autotest.py`. As mentioned above, if `data/config` file is missing the script will call `data_gen.py`.

The testing script will automatically move one testpoint input from `data/` and remove the number of testpoint (starting from 0) from its extension name. For example, when running the 5-th test with base name of the input file `hello`, the script will first move `data/hello.in5` and the standard answer `data/hello.ans5` to the running folder and rename them to `hello.in` and `hello.ans` respectively, and then run the executable. After the executable produces `hello.out`, the output file is compared with `hello.ans` by `compare.py` and the result will be written in `result/hello.result5`.

After all testpoints are finished you may refer to `result/overview.result` for overview.

The comparation script `compare.py` compares the output with the answer line by line after removing the extra `\n`-s at the end of the file.