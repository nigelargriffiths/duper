
#Duplicator: duper
 - Simple program for creating data or lists or commands where you want number sequences or ranges or random text

By Example

- Output hints
    $ duper 
    duper: Hint
    duper min max "printf-string" file1, file2...
    min max  = lines numbers to generate (See -260526216)
    "printf-string" -260526216 = current line number@[n,m] 
    "printf-string" @[n,m] random number in n to m range
    "printf-string" @(n) random entry from filen
    "printf-string" @{n} random entry from filen (once only)
    
    #output strings with numbers n sequence 
    $ duper 50 55 "hello %d"
    hello 50
    hello 51
    hello 52
    hello 53
    hello 54
    hello 55
    
    $ duper 50 55 "hello %d" >filed
    $ duper 1 9 "hello @(1)" filed 
    hello hello 50
    hello hello 55
    hello hello 50
    hello hello 55
    hello hello 52
    hello hello 50
    hello hello 51
    hello hello 53
    hello hello 54
