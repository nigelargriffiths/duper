
#Duplicator: duper
 - Simple program for creating data or lists or commands where you want number sequences or ranges or random text

Learn By Example


Help information - run with no arguements
```
    $ duper
    duper: Hint
    duper min max "printf-string" file1, file2...
    min max  = lines numbers to generate (See -260526216)
    "printf-string" -260526216 = current line number@[n,m]
    "printf-string" @[n,m] random number in n to m range
    "printf-string" @(n) random entry from filen
    "printf-string" @{n} random entry from filen (once only)
```
 
Output strings with numbers in sequence
 - Arguements  1 and 2 are the start and stop numbers inclusive
 - Arguement 3 is the C language printf strings %d is print the current number
 - Note: you can use %d up to 10 times.

```
    $ duper 50 55 "hello %d"
    hello 50
    hello 51
    hello 52
    hello 53
    hello 54
    hello 55
```

List of random numbers
 - Arguements 1 and 4 means generate four likes
 - Arguement @[100,200] select a random number between 100 and 200

```
    $ duper 1 4 "@[100,200]"
    177
    130
    110
    100
```


Take random lines from a file
 - Create a 10 line file as below called filed

````
    $ cat filed
    one
    two
    three
    four
    five
    six
    seven
    eight
    nine
    ten
```
 - then read the file and randomly select lines
 - Note the "Reading file files ..." is on the stderr output so you can remove it with a a 2>/dev/null
```
    $ duper 1 20 "Random numner %d is @(1)" filed
    Reading file "filed" as set 0, 10 items found
    Random number 1 is three
    Random number 2 is one
    Random number 3 is one
    Random number 4 is six
    Random number 5 is eight
    Random number 6 is one
    Random number 7 is one
    Random number 8 is eight
    Random number 9 is one
    Random number 10 is two
    Random number 11 is six
    Random number 12 is seven
    Random number 13 is one
    Random number 14 is five
    Random number 15 is six
    Random number 16 is six
    Random number 17 is ten
    Random number 18 is eight
    Random number 19 is one
    Random number 20 is ten
```
 - Perhaps you want the lines of the faile to be randomised but only appear once
```
$ duper 1 10 "Random number %d is @{1}" filed 2>x
Random number 1 is six
Random number 2 is eight
Random number 3 is two
Random number 4 is four
Random number 5 is one
Random number 6 is ten
Random number 7 is five
Random number 8 is three
Random number 9 is nine
Random number 10 is seven
```
There are problems if you request more thn the number of lines in the file
```
$ duper 1 12 "Random number %d is @{1}" filed    
Reading file "filed" as set 0, 10 items found
Random number 1 is two
Random number 2 is ten
Random number 3 is seven
Random number 4 is one
Random number 5 is three
Random number 6 is five
Random number 7 is eight
Random number 8 is six
Random number 9 is four
Random number 10 is nine
ERROR: no items left in set 0
```

Assuming a files full of firstnames, lastnames, streets, towns
```
$ duper 1 10 "@(1) @{2}, at @[1,500] @(3), @(4)." firstnames lastnames streets towns   
Reading file "firstnames" as set 0, 10 items found
Reading file "lastnames" as set 1, 10 items found
Reading file "streets" as set 2, 10 items found
Reading file "towns" as set 3, 10 items found
Janet Smith, at 431 Green Tree Lane, Dartford.
Sarah Griffiths, at 313 Green Tree Lane, London.
Elisa Boyd, at 232 Long Road, Sidcup.
James  Giles, at 304 High Street, Gravesend.
Jane Bonner, at 4 Worm Road, London.
Elisa Barker, at 409 Village Bypass, London.
Luke Wordsworth, at 64 Garden Close, Gravesend.
Jane Carpenter, at 160 Elmers End, Sidcup.
John Smith, at 381 Wide Cresent, Dartford.
Sarah Jones, at 193 Wide Cresent, Dartford.
```

Removing the "reading ..." lines
 - Note these foru input files only have 10 lines each  = making repetition common.

```
James  Giles, at 295 Elmers End, London.
Sarah Smith, at 125 Green Tree Lane, Hartley.
James  Wordsworth, at 144 Garden Close, London.
Nigel Griffiths, at 280 Main Street, Dover.
Sally Carpenter, at 288 Wide Cresent, Sevenoaks.
James  Barker, at 309 Elmers End, Birmingham.
John Smith, at 124 Broad Avenue, Sevenoaks.
William Boyd, at 500 Broad Avenue, Hartley.
Elisa Jones, at 457 Garden Close, Dartford.
Sally Bonner, at 269 Elmers End, London.
```
