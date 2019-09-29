
// Created by Julio C Nunez on 2019-09-28.
//
// Assistance and guidance from:
// - NYU Cyber Fellows Cohort of 2021
// - Professor Kevin Gallagher
// - Ben Halperin Github


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[])
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

    int bucket = hash_function(lowered);
    node* cursor = hashtable[bucket];
    while (cursor != NULL)
    {
        if (strcmp(lowered, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    // All words are now lower case so no need to re-do our work.

    return false; // Assumes no match, so we return False to account for that.
}


bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){
    for(int i = 0; i < HASH_SIZE; i++){ // Loop through the hash table and set all values to NULL.
        hashtable[i] = NULL;
    }

    // Opening files now.
    // Create a FILE* and call it dict_file
    FILE* dict_file;
    dict_file = fopen(dictionary_file, "r"); // Open the dictionary file to read it.

    if(dict_file == NULL)
    {
        return false; // Well, nothing inside of it. Might as well.
    }

    char word_buffer[LENGTH+1]; // Gonna need a buffer when we loop the file. Not in the pseudocode.
    // Might not need it but will use it for now and see how it works.

    while (fscanf(dict_file, "%s", word_buffer) > 0) // While we're not at the EOF.
    {
        // Create new_node, allocate the memory to keep the code safe and not to break it.
        node* new_node = malloc(sizeof(node)); // Needs the same amount of memory - can't create a new node otherwise. Might break.

        // Set new_node's next to NULL
        new_node->next = NULL;

        // Use strcopy to make new_node->word equal to the buffer.
        strcpy(new_node->word, word_buffer);

        int bucket = hash_function(new_node->word);

        if (hashtable[bucket] == NULL)
        {
            hashtable[bucket] = new_node;
        }

        else{
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
    }


    fclose(dict_file);
    return true; // To return a value to the function.
}


int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]){
    int num_misspelled = 0;

    // To make a buffer to stop any issues from arising with a buffer overflow while
    // reading the file.
    char word_buffer_2[LENGTH+1];

    if(fp == NULL){
        // Exit the program if a file isn't read in or it has nothing.
        exit(1);
    }

    // Read the file line by line until the end of the file.
    // Use the buffer to stop any buffer overflows from happening.
    // Split on a space using '%s'
    while (fscanf(fp, "%s", word_buffer_2) > 0)
    {
        node* new_node = malloc(sizeof(node));
        new_node->next = NULL;

        strcpy(new_node->word, word_buffer_2);

        if(check_word(word_buffer_2, hashtable)== false){
            for(int i=0; i < MAX_MISSPELLED; i++){
                misspelled[i] = malloc(strlen(word_buffer_2) + 1);
                misspelled[i] = strcpy(misspelled[i], word_buffer_2);
                num_misspelled++;
            }
        }
    }

    return num_misspelled;
}
