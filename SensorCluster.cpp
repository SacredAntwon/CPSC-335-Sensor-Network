#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

/* function to convert a character into its digit; 'A' converts into 10; 'B' into 11, etc.
*/
unsigned int hexa_to_number(char ch) {
    // Will check if the characteris between 0-9 or A-F.
    // If it is 0-9 we will only subtract 48 from it and return the decimal value.
    // If it is A-F we wil subtract 55 from the integer value and return that decimal value.
    unsigned int temp = 0;
    if (ch>='0' && ch<='9')
    {
      temp = (ch - 48);
    }

    else if (ch>='A' && ch<='F')
    {
      temp = (ch - 55);
    }

    // TODO: implement this function
    return temp;
}

// Each of the hashfct will return a the decimal value it gets from the call
// it gets from the hexa to number value. There are 6 characters in a string,
// so each function does one of the six characters in the string.
// function to return the hash value based on the first digit
unsigned int hashfct1(string nic) {
    return hexa_to_number(nic[0]);
}

// function to return the hash value based on the second digit
unsigned int hashfct2(string nic) {
    return hexa_to_number(nic[1]);
}

// function to return the hash value based on the third digit
unsigned int hashfct3(string nic) {
	return hexa_to_number(nic[2]);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(string nic) {
	return hexa_to_number(nic[3]);
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(string nic) {
	return hexa_to_number(nic[4]);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(string nic) {
	return hexa_to_number(nic[5]);
}

// Constructor for struct Item
Item::Item(string itemName, string nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    string nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

// function that adds the specified NIC to the sensor network (i.e., to all hash tables)
void SensorNIC::addItem(string itemName, string nic) {
  // We will insert the nic as the key and the structure Item as the value.
  // We do this for all six tables.
  struct Item pairNameNic = {itemName, nic};
  hT1.insert({nic, pairNameNic});
  hT2.insert({nic, pairNameNic});
  hT3.insert({nic, pairNameNic});
  hT4.insert({nic, pairNameNic});
  hT5.insert({nic, pairNameNic});
  hT6.insert({nic, pairNameNic});
  return;
}

// function that removes the sensor specified by the nic value from the network
// if sensor is found, then it is removed and the function returns true
// else returns false
bool SensorNIC::removeItem(string nic) {
   // Find the element in the tables using the nic as the key.
   // If it is found, remove the element from all tables and return true.
   // If nothing is found, it will return false.
   if(hT1.count(nic))
   {
     hT1.erase(nic);
     hT2.erase(nic);
     hT3.erase(nic);
     hT4.erase(nic);
     hT5.erase(nic);
     hT6.erase(nic);
     return true;
   }

  return false;
}

// function that decides the best hash function, i.e. the ones among
// fct1-fct6 that creates the most balanced sensor network for the current
// set of NIC addresses, i.e. data member allItems

// Hints:
// Calculate the balance of each hashtable, one by one.
unsigned int SensorNIC::bestHashing() {
  // Set two arrays with six elements each, because we have six tables we want
  // to find the minimum and maximum bucket size.
  long unsigned int min[6] = {hT1.bucket_size(0), hT2.bucket_size(0), hT3.bucket_size(0), hT4.bucket_size(0), hT5.bucket_size(0), hT6.bucket_size(0)};
  long unsigned int max[6] = {hT1.bucket_size(0), hT2.bucket_size(0), hT3.bucket_size(0), hT4.bucket_size(0), hT5.bucket_size(0), hT6.bucket_size(0)};

  // This loop will find the min and max for each table.
  for (unsigned i = 1; i < 16; ++i)
  {
    min[0] = std::min(min[0], hT1.bucket_size(i));
    max[0] = std::max(max[0], hT1.bucket_size(i));

    min[1] = std::min(min[1], hT2.bucket_size(i));
    max[1] = std::max(max[1], hT2.bucket_size(i));

    min[2] = std::min(min[2], hT3.bucket_size(i));
    max[2] = std::max(max[2], hT3.bucket_size(i));

    min[3] = std::min(min[3], hT4.bucket_size(i));
    max[3] = std::max(max[3], hT4.bucket_size(i));

    min[4] = std::min(min[4], hT5.bucket_size(i));
    max[4] = std::max(max[4], hT5.bucket_size(i));

    min[5] = std::min(min[5], hT6.bucket_size(i));
    max[5] = std::max(max[5], hT6.bucket_size(i));
  }

  // Once we find the minimum and maximum bucket size, we will have
  // another array that finds the balance by getting the difference of the max and min.
  long unsigned int balance[6] = {max[0]-min[0], max[1]-min[1], max[2]-min[2], max[3]-min[3], max[4]-min[4], max[5]-min[5]};
  long unsigned int minNumber = balance[0];
  int best = 0;

  // We then create a for loop to go through the balance and find the first
  // index with the lowest balance.
  for(int i = 1; i < 6; i++)
  {
    if (minNumber > balance[i])
    {
      minNumber = balance[i];
      best = i;
    }
  }

  // We will then return the index/hash table with the lowest balance (had to add one to
  // the index because it starts from 0).
  return (best + 1);
}

// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	throw std::length_error("Hash table sizes are not the same");

	return hT1.size();
}
