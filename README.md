# Lab_1_data_base_in_files
Now this program is combined Lab.1 and Lab.3b. Three modes provided: interactive, demo and benchmark(results are accessible in separate file.
~About Lab.1: It`s simulation of market database of products. Products can be saved in memory(std::vector) and in file(txt and bin provided). You can load, delete and print all data from both type of files.
Also you can delete and update exact products and execute search in memory or file by parameters: name, quantity and date of production.
~About Lab.3b: This lab provides sorting products in memory. As in Lab.1 all 3 modes provided. You can execute sorting as well by one parameter as by combination of parameters.
If you want to sort only by unit of measure - counting sort will be executed. If you want to sort only by expiry period - radix sort will be executed. If sort will require another parameter or any combination of parameters - smart merge sort will be executed. Comparison of all types of sorting also provided in benchmark mode.
P.S. result of exact sorting linearly depends on quantity of comparisons needed for one pair of elements, so if you change default parameters for benchmark, it can far change benchmark`s data.
