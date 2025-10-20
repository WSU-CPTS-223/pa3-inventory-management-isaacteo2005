[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA4 Skeleton Code
We expect a fully functioninig command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.

These are the categories I decided to emit: Brand Name, Asin, Upcan Ean Code, List Price, Quantity, Sku, Stock, Product Details, Dimensions, Color, Ingredients, Directions to Use, Size Quantity Variant, Product description.

Most if not all of the cells in these categories were empty.

I encountered a problem where the categories read had spaces and backslashes which would mess with the data so I made a cleanString function to help clean out the extra spaces and backslashes

I also encountered a problem certain fields had comas inside of them which messed with how I used to read the fields from coma to coma. This is why I had to create a getCSVField function that reads each field completely and ignores comas inside the field.
Testing:
Insert: I decided to test inserting multiple key value pairs into the map then checking to see if one of the values exist and the map is not empty, this is my normal case since it just checks if the insert happened. For my edge case, I checked if inserting multiple items of the same key worked, since my map implements seperate chaining each value should be in a linkedlist with the same key, I then checked if my get function would get all the values with the same key and asserted if it works.
Get: My normal case was just calling get on a known key with 1 item and checking if the output list is not empty, this just checks if the get works. My edge case was testing if get retreives multiple items with the same key and places them all in the output list, this helps check if my get retreives all values of a specific key.

Remove: Normal case tests removing just one key with only 1 item matching the key in the map, this is the easiest case I could test and shows the remove function works. Edge case tests deleting a key with 2 items matching the key in the map, since my remove function is supposed to delete all values with the same key, I also tested if after the delete, get would not add anything to the output list to confirm that the values are gone. i also tested if remove worked on am enpty map to see if it doesn't crash.

rehash: my normal/stress case involves creating a map with an extremely small max size and inserting many elements in order to force the map to rehash multiple times, I then assert if the rehashed work by using get to find a value I know is in the map and asserting if the get went through. For my edge case, I just tested if rehash worked on an empty map to see if it doesn't crash.