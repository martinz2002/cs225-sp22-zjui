# README

This is the readme file for code testing. You may see three python script files in `Ass04Ex4` folder:

- `autotest.py` -- a script that automatically run testpoints stored in `./data` folder.
- `compare.py` -- a script for comparing the answer file and the user output.
- `data_gen.py` -- a script to generate random input.

We made some modifications to `heap.cpp`, in the `main()` function, to have it capable for our automatic testing script.

By default, all three scripts will deal with a number of 10 testpoints.

After running `python3 autotest.py`, the result of each testpoint will be written in `data\<Name>.result<TestPoint#>`, e.g. `heap.result2`. There will be another overview file called `resultOverview.txt`in the code folder.

**NOTE:** If you are encountered with that the CMD interface requires your response on question like:

> `D:\cs225groupworks\assignments\Ass04\ass04ex4\user_output\*, Are you sure (Y/N)?`

Then choose `Y` forever.

## Input Format

The input contains $n+1$ lines, the first one denoting the number of input numbers $n$, and in the  next $n$ lines, each of them contains one input number.



## Output Format

The output contains $n+1$ lines, the first one of which is the result of `max()` function, and the following $n$ lines are the sorted list of input numbers. In theory, the first and second lines should be the same.

If input is an empty list, the output should be a string `EMPTY HEAP`.