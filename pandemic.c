#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SYMPTOM "symptom"
#define STUDENT "student"
#define QUERY 'q'
#define UPDATE 'u'
#define DEFAULT_LENGTH 101

typedef struct symptoms
{
    char* str;
    int size, cap;
} symptoms;

typedef struct names
{
    char* str;
    symptoms* symp;
    int size, cap;
} names;

names* update(names*);
void query(names*);

int main()
{
    int i, j, n;
    char choice;

    names* student = malloc(1 * sizeof(names));
    student->size = 0;
    student->cap = 1;

    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        scanf(" %c", &choice);

        if (choice == UPDATE)
        {
            student = update(student);
        }

        else if (choice  == QUERY)
        {
            query(student);
        }
    }
    
    for (i = 0; i < student->size; i++)
    {
        for (j = 0; j < student[i].symp->size; j++)
        {
            free(student[i].symp[j].str);
        }
        free(student[i].symp);
        free(student[i].str);
    }

    free(student);

    return 0;
}

names* update(names* student)
{
    int i, j, lastIndex, foundName = 0, foundSymp = 0, indexFlag = -1;
    char nameStr[DEFAULT_LENGTH], sympStr[DEFAULT_LENGTH];
    scanf("%s", nameStr);
    scanf("%s", sympStr);

    for (i = 0; i < student->size; i++)
    {
        if (strcmp(student[i].str, nameStr) == 0)
        {
            foundName = 1;
            indexFlag = i;

            break;
        }
    }

    if (foundName == 1)
    {
        for (i = 0; i < student[indexFlag].symp->size; i++)
        {
            if (strcmp(student[indexFlag].symp[i].str, sympStr) == 0) // Checks if symptom is already on list after student is found.
            {
                foundSymp = 1;

                break;
            }
        }

        if  (foundSymp != 1)
        {
            lastIndex = student[indexFlag].symp->size;

            student[indexFlag].symp = realloc(student[indexFlag].symp, student[indexFlag].symp->cap * sizeof(symptoms));
            student[indexFlag].symp->size++;
            student[indexFlag].symp->cap++;

            student[indexFlag].symp[lastIndex].str = malloc(strlen(sympStr) * sizeof(char) + 1);

            strcpy(student[indexFlag].symp[lastIndex].str, sympStr);
        }

        return student;
    }

    else
    {
        lastIndex = student->size;

        student = realloc(student, student->cap * sizeof(names));
        student->size++;
        student->cap++;

        student[lastIndex].str = malloc(strlen(nameStr) * sizeof(char) + 1);
        strcpy(student[lastIndex].str, nameStr);

        student[lastIndex].symp = malloc(1 * sizeof(symptoms));
        student[lastIndex].symp[0].str = malloc(strlen(sympStr) * sizeof(char) + 1);

        student[lastIndex].symp->size = 1;
        student[lastIndex].symp->cap = 2;
        strcpy(student[lastIndex].symp[0].str, sympStr);
        
        return student;
    }
}

void query(names* student)
{
    int i, j, count = 0, foundStudent = 0;
    char query1[DEFAULT_LENGTH], query2[DEFAULT_LENGTH];

    scanf("%s", query1);
    scanf("%s", query2);

    if (strcmp(STUDENT, query1) == 0)
    {
        for (i = 0; i < student->size; i++)
        {
            if (strcmp(student[i].str, query2) == 0)
            {
                foundStudent = 1;
                printf("%d\n", student[i].symp->size);

                for (j = 0; j < student[i].symp->size; j++)
                {
                    printf("%s\n", student[i].symp[j].str);
                }
            }
        }

        if (foundStudent != 1)
        {
            printf("%d\n", foundStudent);
        }
    }

    else if (strcmp(query1, SYMPTOM) == 0)
    {
        for (i = 0; i < student->size; i++)
        {
            for (j = 0; j < student[i].symp->size; j++)
            {
                if (strcmp(student[i].symp[j].str, query2) == 0)
                    count++;
            }
        }

        printf("%d\n", count);

        for (i = 0; i < student->size; i++)
        {
            for (j = 0; j < student[i].symp->size; j++)
            {
                if (strcmp(student[i].symp[j].str, query2) == 0)
                    printf("%s\n", student[i].str);
            }
        }
    }
}