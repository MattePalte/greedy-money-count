#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char * order_string(char * string);
size_t index_of_n_most_grater_value(size_t n, char ** array, size_t max_len);
char ** split(char * input_str, size_t max_len_array);
int get_value(char * record);
char get_letter(char * record);
char * greedy_algorithm_variant(int number, char ** array, size_t n_elem, size_t start_n);
char * spiccioli(int number, char * string);
size_t count_occurrence(char * string, char c);
void printArr(char * array[], int dim);

//SORT CHAR OF A STRING IN ALPHABETICAL ORDER (BUBBLESORT)
char * order_string(char * string){
    char * new_str = strdup(string);
    size_t counter = 0;
    size_t i = 0;
    char temp = '0';
    //DEFINE MAX NUMBER OF ITERATIONS
    for(counter=0; counter<strlen(new_str); counter++){
        //CONTROLL EACH CHAR WITH THE NEXT ONE
        for(i=0; i<(strlen(new_str)-1); i++){
            if (new_str[i]>new_str[i+1]){
                temp = new_str[i+1];
                new_str[i+1] = new_str[i];
                new_str[i] = temp;
            }
        }
    }
    return new_str;
}

//GET THE INDEX OF THE N-th VALUE IN DESCENDING ORDER
// if n = 0 it returns the gratest value
// if n = max_len-1 it returns the smallest value
// IMPORTANT: max_len IS THE NUMBER OF ELEMS OF THE ARRAY
size_t index_of_n_most_grater_value(size_t n, char ** array, size_t max_len){
    size_t i = 0;
    size_t j = 0;
    size_t counter_grater = 0;
    int value_i = 0;
    int value_j = 0;
    size_t index_found = 0;
    for (i=0; i<max_len; i++){

        value_i = get_value(array[i]);
        for (j=0; j<max_len; j++){
            value_j = get_value(array[j]);
            if (value_i<value_j){
                counter_grater++;
            }
        }
        if (n == counter_grater){
            return i;
        }
        counter_grater = 0;
    }
    return 0;

}

// GIVEN A STRING "a:4" IT RETURNS 'a' (the first char)
int get_value(char * record){
    char * delimit_pos = strpbrk(record, ":");
    return atoi(delimit_pos+1);
}

// GIVEN A STRING "a:4" IT RETURNS 4 (integer)
char get_letter(char * record){
    return record[0];
}

// COUNTS HOW MANY TIMES A CHAR c APPEARS IN A STRING
size_t count_occurrence(char * string, char c){
    size_t max_len = strlen(string);
    size_t i = 0;
    size_t counter = 0;
    for (i=0; i<max_len; i++){
        if (string[i] == c){
            counter++;
        }
    }
    return counter;
}

// PRINTS AN ARRAY OF STRINGS
void printArr(char * array[], int dim){
    size_t i = 0;
    for (i=0; i<dim; i++){
        printf("%s\n", array[i]);
        //printf("letter %c\n", get_letter(array[i]));
        //printf("value %i\n", get_value(array[i]));
    }
}

// RETURN AN ARRAY BY DIVIDING A STRING (DELIMITER IS ',')
char ** split(char * input_str, size_t max_len_array){
    //DICHIARA VARIABILI
    char * strPtr = input_str;
    char ** array = (char**) calloc(max_len_array, sizeof(char*));
    char field[32];
    int n = 0;
    size_t i = 0;
    //ELABORA VARIABILI
    while(sscanf(strPtr, "%31[^,]%n", field, &n) == 1){
        array[i] = strdup(field);
        i++;
        strPtr += n;
        if (*strPtr != ','){
            break;
        }
        strPtr++;
    }
    return array;
}


char * spiccioli(int number, char * string){
    // DECLARE AND INITIALIZE VARIABLE
    size_t start_n = 0;
    size_t max_len_array = count_occurrence(string, ',') + 1;
    char ** array = split(string, max_len_array);
    char * best_res_so_far = NULL;
    size_t low_lenght = 0;
    char * current_res = NULL;
    // ALGORITHM
    // REPEAT greedy_algorithm_variant FOR EACH NUMBERS OF ELEMS IN THE ARRAY
    for(start_n=0 ; start_n<(max_len_array) ; start_n++){
        // SEARCH FOR BEAST SEQUENCE WITH THIS MAX NUM
        current_res = greedy_algorithm_variant(number, array, max_len_array, start_n);
        //DEGUG --> printf("current_res %s\n", current_res);
        if (low_lenght==0){
            // FIRST FOUND ALWAYS ADDED
            best_res_so_far = current_res;
            low_lenght = strlen(best_res_so_far);
        }
        // UPDATE ONLY IT SEQUENCE IS SHORTER
        if (strlen(current_res)<low_lenght){
            free(best_res_so_far);
            best_res_so_far = current_res;
            low_lenght = strlen(best_res_so_far);
        }
    }
    free(array);
    //DEGUG --> printf("FINAL RESULT >%s<\n", best_res_so_far);
    return best_res_so_far;
}

char * greedy_algorithm_variant(int number, char ** array, size_t max_len_array, size_t start_n ){
    // DECLARE AND INITIALIZE VARIABLE
    size_t n = 0;
    size_t current_record_index = 0;
    int current_value = 0;
    char current_char = '0';
    size_t last_record_index = 0;
    int last_value = 0;
    char last_char = '0';
    size_t last_n_added = 0;
    size_t current_len = 0;
    // CHECK IF THE ARRAY WAS PROPERLY FULLFILLED
    //DEGUG --> printArr(array,max_len_array);
    size_t smallest_index = index_of_n_most_grater_value(max_len_array-1, array, max_len_array);
    int smallest_value = get_value(array[smallest_index]);
    size_t max_len_res = number/smallest_value + 2;
    char * risultato = (char*) calloc(max_len_res, sizeof(char));
    risultato[0] = '\0';
    // ELABORATION - GREEDY ALGORITHM
    for(n=0+start_n ; n<max_len_array ; n++){
        current_record_index = index_of_n_most_grater_value(n, array, max_len_array);
        current_value = get_value(array[current_record_index]);
        current_char = get_letter(array[current_record_index]);
        // SUBTRACT THAT COIN (ADD THE CORRESPONDING CHAR TO THE SEQUENCE)
        // UNTIL IT IS POSSIBLE (NUMBER >= 0)
        while((number-current_value) >=0){
            number = number-current_value;
            last_n_added = n;
            current_len = strlen(risultato);
            risultato[current_len] = current_char;
            risultato[current_len+1] = '\0';
            //DEGUG --> printf("current_char added %c \n", current_char);
        }
        // WHEN A THE END OF FOR CICLE,
        // IF THERE IS ANY REST: JUMP BACK
        // - REMOVE LAST CHAR ADDED
        // - RESUME FROM SMALLER COIN AFTER IT
        if (n == (max_len_array-1) && number > 0){
            //DEGUG --> printf("\nATTENTION --> current risultato = >%s<\n", risultato);
            //DEGUG --> printf("max_len_array = %i number = %i\n", max_len_array, number);
            n = last_n_added;
            last_record_index = index_of_n_most_grater_value(last_n_added, array, max_len_array);
            last_value = get_value(array[last_record_index]);
            last_char = get_letter(array[last_record_index]);
            //DEGUG --> printf("last_value %i last_char >%c<\n", last_value, last_char);
            number = number + last_value;
            current_len = strlen(risultato);
            //DEGUG --> printf("current_char removed %c \n", risultato[current_len-1]);
            risultato[current_len-1] = '\0';
        }
    }
    char * o_res = order_string(risultato);
    free(risultato);
    return o_res;
}

void main(){
    // TEST:
    // index_of_n_most_grater_value
    int i = 0;
    for(i=0; i<3; i++){
        printf("index of %i-th geater value is %i\n", i, index_of_n_most_grater_value(i,split("a:9,b:2,c:1", 3),3) );
    }
    // printArr & split
    printf("printArr & split\n");
    printArr(split("a:9,b:2,c:1", 3),3);
    // count_occurrence
    printf("count_occurrence of ',' : %i\n", count_occurrence("a:9,b:2,c:1", ','));
    // order_string
    printf("Ordered string %s \n", order_string("ciaocomeva"));
    // assert for spiccioli
    assert(strcmp(spiccioli(20, "b:2,a:9,c:1"), "aab")==0);
    assert(strcmp(spiccioli(4, "a:5,b:2,c:1"),"bb")==0);
    assert(strcmp(spiccioli(12,"a:3,b:2"),"aaaa")==0);
    assert(strcmp(spiccioli(20, "a:6,b:5,c:1"), "bbbb")==0);
    assert(strcmp(spiccioli(21, "a:2,b:2,c:3"), "ccccccc")==0);
    assert(strcmp(spiccioli(151, "a:150,b:15,c:14,d:10,e:5,f:3,g:2,h:1"), "ah")==0);
    assert(strcmp(spiccioli(8, "a:6,b:4,c:2,d:1"), "ac")==0);
    // EXPLICIT TEST WITH OUTPUT
    //printf("spiccioli res %s\n", spiccioli(20, "a:6,b:5,c:1"));
    //printf("spiccioli res %s\n", spiccioli(10, "a:6,b:5,c:2"));
    //printf("spiccioli res %s\n", spiccioli(20, "a:12,b:3,c:2,d:15"));
    //printf("spiccioli res %s\n", spiccioli(10, "a:4,b:5,c:1,d:a+b")); //overpowered (NOT WORKING)
    //CONGRATULATION!
    printf("\n -- ALL TEST PASSED -- CONGRATULATION! \n");
}
