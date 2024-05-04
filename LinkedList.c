#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This struct hold info of students.
struct student
{ 
    char F_name[12];
    char L_name[12];
    int Std_id;
    char Std_address[20];
    char Std_email[30];
    char Std_mobile[12];
    char department[3]; 
    float GPA;
};
//This sturct is node.
struct node
{
    struct student info;
    struct node *next;
};
typedef struct node node;

//This fuction append of normally.
void appendnormal(node **r, struct student info) {
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    temp->info = info;
    temp->next = NULL;

    if (*r == NULL) {
        *r = temp;
        return;
    }

    node *current = *r;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
}
//This fuction append of firstly.
void appendfirst(node **r, struct student info) {
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    temp->info = info;
    temp->next = *r;
    *r = temp;
}
//This fuction append of secondly.
void appendsecond(node **r, struct student info) {
    if (*r == NULL || (*r)->next == NULL) {
        printf("Error: List does not have enough elements.\n");
        return;
    }

    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    temp->info = info;
    temp->next = (*r)->next->next;
    (*r)->next->next = temp;
}
// This function delete the first node
void deleteFirst(node **r) {
    if (*r == NULL) {
        printf("List is empty.\n");
        return;
    }

    node *temp = *r;
    *r = (*r)->next;
    free(temp);
}
// This function delete nt node.
void deleteNth(node **r, int n) {
    if (*r == NULL) {
        printf("List is empty.\n");
        return;
    }

    node *current = *r;
    node *prev = NULL;
    int count = 1;

    while (current != NULL && count != n) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Invalid position.\n");
        return;
    }

    if (prev == NULL) {
        *r = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}
// This function insert before nt node.
void insertBeforeNth(node **r, struct student info, int n) {
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    temp->info = info;

    if (n == 1 || *r == NULL) {
        temp->next = *r;
        *r = temp;
        return;
    }

    node *current = *r;
    node *prev = NULL;
    int count = 1;

    while (current != NULL && count != n) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Invalid position.\n");
        free(temp);
        return;
    }

    temp->next = current;
    prev->next = temp;
}

// This function manually frees it in memory.
void freeList(node **r) {
    node *current = *r;
    node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *r = NULL;
    printf("\nAll List are free.\n");
}
// This function combines 2 lists.
void concatenateLists(node **r1, node **r2) {
    if (*r1 == NULL) {
        *r1 = *r2;
        *r2 = NULL;
        return;
    }

    if (*r2 == NULL) {
        return;
    }

    node *temp = *r1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = *r2;
    *r2 = NULL;
}
//This function reverses nodes.
void reverseList(node **r) {
    node *prev = NULL;
    node *current = *r;
    node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *r = prev;
}
//This function Conbinates lists by student number.
node* combineOrderedLists(node *r1, node *r2) {
    node *result = NULL;

    if (r1 == NULL) {
        return r2;
    }
    if (r2 == NULL) {
        return r1;
    }

    if (r1->info.Std_id <= r2->info.Std_id) {
        result = r1;
        result->next = combineOrderedLists(r1->next, r2);
    } else {
        result = r2;
        result->next = combineOrderedLists(r1, r2->next);
    }

    return result;
}
//This function intersections lists by student number.

node* intersectionOfLists(node *r1, node *r2) {
    node *result = NULL;
    node *temp = NULL;

    while (r1 != NULL && r2 != NULL) {
        if (r1->info.Std_id < r2->info.Std_id) {
            r1 = r1->next;
        } else if (r1->info.Std_id > r2->info.Std_id) {
            r2 = r2->next;
        } else {
            temp = (node*)malloc(sizeof(node));
            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                return NULL;
            }
            temp->info = r1->info;
            temp->next = NULL;

            if (result == NULL) {
                result = temp;
            } else {
                node *current = result;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }

            r1 = r1->next;
            r2 = r2->next;
        }
    }

    return result;
}
//This function unions lists by student number.
node* unionOfLists(node *r1, node *r2) {
    node *result = NULL;
    node *temp = NULL;

    while (r1 != NULL || r2 != NULL) {
        if (r1 == NULL) {
            temp = (node*)malloc(sizeof(node));
            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                return NULL;
            }
            temp->info = r2->info;
            temp->next = NULL;

            if (result == NULL) {
                result = temp;
            } else {
                node *current = result;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }

            r2 = r2->next;
        } else if (r2 == NULL) {
            temp = (node*)malloc(sizeof(node));
            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                return NULL;
            }
            temp->info = r1->info;
            temp->next = NULL;

            if (result == NULL) {
                result = temp;
            } else {
                node *current = result;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }

            r1 = r1->next;
        } else {
            if (r1->info.Std_id < r2->info.Std_id) {
                temp = (node*)malloc(sizeof(node));
                if (temp == NULL) {
                    printf("Memory allocation failed.\n");
                    return NULL;
                }
                temp->info = r1->info;
                temp->next = NULL;

                if (result == NULL) {
                    result = temp;
                } else {
                    node *current = result;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = temp;
                }

                r1 = r1->next;
            } else if (r1->info.Std_id > r2->info.Std_id) {
                temp = (node*)malloc(sizeof(node));
                if (temp == NULL) {
                    printf("Memory allocation failed.\n");
                    return NULL;
                }
                temp->info = r2->info;
                temp->next = NULL;

                if (result == NULL) {
                    result = temp;
                } else {
                    node *current = result;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = temp;
                }

                r2 = r2->next;
            } else {
                temp = (node*)malloc(sizeof(node));
                if (temp == NULL) {
                    printf("Memory allocation failed.\n");
                    return NULL;
                }
                temp->info = r1->info;
                temp->next = NULL;

                if (result == NULL) {
                    result = temp;
                } else {
                    node *current = result;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = temp;
                }

                r1 = r1->next;
                r2 = r2->next;
            }
        }
    }

    return result;
}
//This function prints all information of students. 
void StudePrint(node *root){
   while( root!= NULL){
        printf("\nName: %s %s\n", root->info.F_name, root->info.L_name);
        printf("Student ID: %d\n", root->info.Std_id);
        printf("Address: %s\n", root->info.Std_address);
        printf("Email: %s\n", root->info.Std_email);
        printf("Mobile: %s\n", root->info.Std_mobile);
        printf("Department: %s\n", root->info.department);
        printf("GPA: %.2f\n", root->info.GPA);
        printf("\n");
        root= root->next;
   }
}

int main(void) {
    node *root = NULL;
    node *root2 = NULL;
    char option = ' ';

    struct student student1 = {"John", "Doe", 1001, "123 Main St", "john.doe@example.com", "123-456-7890", "CE", 3.5};
    struct student student2 = {"Alice", "Smith", 1002, "456 Elm St", "alice.smith@example.com", "234-567-8901", "E", 3.7};
    struct student student3 = {"Michael", "Johnson", 1003, "789 Oak St", "michael.johnson@example.com", "345-678-9012", "CE", 3.9};
    struct student student4 = {"Walter", "White", 1004, "654 Miami", "walter.white@example.com", "385-968-6512", "CE", 4.0};

    appendnormal(&root,student1);


    struct student student5 = {"Walter", "White", 1004, "654 Miami", "walter.white@example.com", "385-968-6512", "CE", 4.0};
    struct student student6 = {"Emma", "Brown", 1005, "678 Cedar St", "emma.brown@example.com", "567-890-1234", "CS", 3.6};
    struct student student7 = {"Olivia", "Martinez", 1006, "789 Maple St", "olivia.martinez@example.com", "678-901-2345", "ECE", 3.9};

    appendnormal(&root2,student5);
    appendnormal(&root2,student6);
    appendnormal(&root2,student7);
    while (option != 'X' || "x")
    {   
        printf("\n");
        printf("Append an element to the beginning of a list: A\n");
        printf("Append an element as a second node in the list: B\n");
        printf("Delete the first element from a list: C\n");
        printf("Delete the nth element from a list: D\n");
        printf("Insert an element before the nth element of a list: E\n");
        printf("Free all nodes in a list: F\n");
        printf("Concatenate two lists: G\n");
        printf("Reverse a list, so that the last element becomes the first, and so on: H\n");
        printf("Combine two ordered lists into a single ordered list: I\n");
        printf("Form a list containing the intersection of the elements of two lists: J\n");
        printf("Form a list containing the union of the elements of two lists: K\n");
        printf("Exit: X\n");
        printf("Enter your option: ");
        scanf(" %c", &option);

        if (option == 'A' || option == 'a')
        {
            appendfirst(&root, student2);
            StudePrint(root);
        }
        if (option == 'B' || option == 'b')
        {
            appendsecond(&root, student3);
            StudePrint(root);
        }
        if (option == 'C' || option == 'c')
        {
            deleteFirst(&root);
            StudePrint(root);
        }
        if (option == 'D' || option == 'd')
        {
           deleteNth(&root,2);
            StudePrint(root);
        }
        if (option == 'E' || option == 'e')
        {
            insertBeforeNth(&root,student4,5);
            StudePrint(root);
        }
        if (option == 'f' || option == 'F')
        {
            freeList(&root);
            StudePrint(root);
        }
        if (option == 'g' || option == 'G')
        {
           concatenateLists(&root,&root);
            StudePrint(root);
        }
        if (option == 'H' || option == 'h')
        {
           reverseList(&root);
            StudePrint(root);
        }      
        if (option == 'i' || option == 'I')
        {
            node *combinedList = combineOrderedLists(root, root2);
            StudePrint(combinedList);
        }   
        if (option == 'j' || option == 'J')
        {
            node * intersectionList =intersectionOfLists(root,root2);
            StudePrint(intersectionList);
        } 
        if (option == 'K' || option == 'k')
        {
            node *unionList = unionOfLists(root,root2);
            StudePrint(unionList);
        } 
        if (option == 'X' || option == 'x')
        {
            break;
        } 
       
    }
    
    return 0;
}
