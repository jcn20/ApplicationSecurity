/
// Created by Julio C Nunez on 2019-09-28.
//
// Assistance and guidance from:
// - NYU Cyber Fellows Cohort of 2021
// - Professor Kevin Gallagher

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h
#include <stdlib.h>

bool check_word(const char* word, hashmap hashtable[])
{
    // We need to create a lower case word

    int str_length = strlen(word);
    char lowered[LENGTH+1];

    // Take the characters for each word  and change it to lower case

    for(int i = 0; i < str_length; i++){
        if(isupper(word[i])){ // if any character is uppercase, change to lowercase
            lowered[i] = tolower(word[i]);
        }
        else{
            lowered[i] = word[i]; // Already lower case, so just copy it over.
        }
    }

    // Protect against overflow
    // Add null character to the end of the array to stop that from happening.

    lowered[str_length] = '\0';

    // Next part

    int bucket = hash_funtion(word);
    node* cursor = hashtable[bucket];
    while (cursor != NULL)
    {
        if (strcmp(lowered, cursor->word) == 0)
        {
            return True;
        }
        cursor = cursor->next;
    }

    // All words are now lower case so no need to re-do our work.

    return False; // Assumes no match, so we return False to account for that.
}


bool load_dictionary(const char* dictionary, hashmap hashtable[]){
    for(int i = 0; i < HASH_SIZE; i++){ // Loop through the hash table and set all values to NULL.
        hashtable[i] = NULL;
    }

    // Opening files now.
    // Create a FILE* and call it dictionary_file
    FILE* dict_file;
    dictionary_file = fopen(dictionary, "r"); // Open the dictionary file to read it.

    if(dictionary_file == NULL)
    {
        return False; // Well, nothing inside of it. Might as well.
    }

    char word_buffer[LENGTH+1]; // Gonna need a buffer when we loop the file. Not in the pseudocode.
    // Might not need it but will use it for now and see how it works.

    while (fscanf(dictionary_file, "%s", word_buffer) > 0) // While we're not at the EOF.
    {
        // Create new_node, allocate the memory to keep the code safe and not to break it.
        node* new_node = malloc(sizeof(node)); // Needs the same amount of memory - can't create a new node otherwise. Might break.

        // Set new_node's next to NULL
        new_node->next = NULL;

        // Use strcopy to make new_node->word equal to the buffer.
        strcpy(new_node->word, word_buffer);

        int bucket = hash_function[word];
    }

    if (hashtable[bucket] == NULL)
    {
        hashtable[bucket] = new_node;
    }

    else{
        new_node->next = hashtable[bucket];
        hashtable[bucket] = new_node;
    }

    fclose(dictionary_file);
    return True; // To return a value to the function.
}

int check_words(file fp, hashmap hashtable[], string misspelled[]){
    int num_misspelled = 0;


    return num_misspelled;


}
