# README

This is the testing log for `squeue`, the queue implemented by using two stacks.

**NOTE** our algorithm does not guarentee the correctness of `display()`, but it guarentees that `pushback()` and `popfront()` satisfies First In First Out (FIFO). i.e. If you perform `display()` you won't get the queue in the correct order; however, whenever you perform `popfront()` you will get the correct answer.