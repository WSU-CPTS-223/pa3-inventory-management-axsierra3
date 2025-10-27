#pragma once
#include "Product.hpp"

//this funct modifies the buffer between calls, gets called once for each field that we want to save
std::string parseField(string& buffer)
{
    string field;
    size_t delim = 0;

    if(buffer.empty()) //empty to begin with
    {
        return "N/A";
    }
    //some fields with quotes have commas inside them, so lets use quotes as delim
   if(buffer[0] == '\"')
   {
    while(true) //infinite loop we break out of
    {
    delim = buffer.find('\"', delim + 1); //find next quote (start search at index 1 first time), and start after next inner quote other runs
    if (buffer[delim + 1] == ',')
    {
        break; //this is the very last end quote before the comma
    } //else keep looking

    }
    field = buffer.substr(0, delim + 1); //inclduing quotes
    buffer = buffer.substr(delim + 1, buffer.length()); //crop it to after comma
   }

    //normal case: no quotes just comma
   else
   {
    delim = buffer.find(','); //index of first comma
    field = buffer.substr(0, delim); //field is everything from 0 to delim
    if(delim == 0 && buffer[delim + 1] == ',') //if empty field w/ double comma
    {
        buffer = buffer.substr(delim + 2, buffer.length()); //skip the comma after it too if there is one
    }
    else {
    buffer = buffer.substr(delim + 1, buffer.length()); //crop it to after comma to start again
    }
   }
       if(field.empty()) //check again bc we modified it so it could be empty now (back to back commas or empty quotes)
    {
        return "N/A";
    }
    return field;

}