# Project Three: NIC Sensor
Project 3-NIC management for sensor networks

Group members:

Name: Anthony Maida

Email: amaida@csu.fullerton.edu

Project Three required us to implement functions to solve our goal of finding the best hash table. The first task was to implement a function that takes in a character which will be a hex, and then it returns the decimal value. This will be used to call for each of the 6 characters inside the NICs. Our next three functions are addItem, removeItem, and bestHashing. The addItem just involved us adding each item to the hashtable using the nic as the key and making and item structure and having that as the value. We add it to all six tables. The removeItem required a nic as an arguement and would look in the table for the key that matched the nic and we would remove the element from the tables. It would return true if an item was found and removed, or false if it couldn't find the key. The final task to do was the bestHashing, which involved finding the balance of each table and the returning the table that had the lowest balance. The balance was found by getting the minimum and max bucket size of each table and then getting the difference.
