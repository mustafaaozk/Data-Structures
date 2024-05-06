#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTUDENTS 10

struct tenPerson {
    char F_name[12];
    char L_name[12];
    int Std_id;
    char Std_address[12];
    char Std_email[12];
    char Std_mobile[12];
    char gender; /* M=male, F=Female */
    float GPA;
};

struct queue {
    struct tenPerson std_info[MAXSTUDENTS];
    int front, rear;
};

void cqinsert(struct queue *, struct tenPerson);
struct tenPerson cqdelete(struct queue *);
void separateByGender(struct queue *, struct queue *, struct queue *);
void displayQueue(struct queue);


struct tenPerson COME205_Students[MAXSTUDENTS] = {
    {"Ahmet", "Osman", 123, "21", "M", "1234567890", 'M', 3.5},
    {"Sevgi", "Mert", 26, "", "", "", 'F', 3.8},
    {"Osman", "Kemal", 18, "", "", "", 'M', 3.2},
    {"Mert", "Osman", 27, "", "", "", 'M', 3.7},
    {"Ayse", "Omer", 34, "", "", "", 'F', 3.9},
    {"Kemal", "Ali", 21, "", "", "", 'M', 3.6},
    {"Lale", "Can", 16, "", "", "", 'F', 3.3},
    {"Sefer", "Mert", 15, "", "", "", 'M', 3.1},
    {"Meral", "Jemal", 27, "", "", "", 'F', 3.4},
    {"Demet", "Kemal", 34, "", "", "", 'F', 3.9}
};

int main() {
    struct queue Q1,MaleQ, FemaleQ;
    Q1.front = -1;
    Q1.rear = -1;
    MaleQ.front = -1;
    MaleQ.rear = -1;
    FemaleQ.front = -1;
    FemaleQ.rear = -1;
    int choice;
    struct tenPerson s;
    while (1) {
        printf("\n1. Insert Students\n2. Delete Students\n3. DeleteForFE/MALE\n4.List the content of Male queue and Female\n5.Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                for (int i = 0; i < MAXSTUDENTS; i++) {
                    cqinsert(&Q1, COME205_Students[i]);
                }
                break;
            case 2:
                while (Q1.front != -1) {
                    s = cqdelete(&Q1);
                    printf("Deleted student: %s %s\n", s.F_name, s.L_name);
                }
                break;
            case 3:
            while (Q1.front != -1) {
                    s = cqdelete(&Q1);
                    printf("Deleted student: %s %s\n", s.F_name, s.L_name);
                    if (s.gender == 'M') {
                        cqinsert(&MaleQ, s);
                    } else if (s.gender == 'F') {
                        cqinsert(&FemaleQ, s);
                    }
                }
                printf("\nStudents separated by gender:\n");
                printf("Deleted Male Students:\n");
                while (MaleQ.front != -1) {
                    s = cqdelete(&MaleQ);
                    printf("%s %s\n", s.F_name, s.L_name);
                }
                printf("\nDeletedFemale Students:\n");
                while (FemaleQ.front != -1) {
                    s = cqdelete(&FemaleQ);
                    printf("%s %s\n", s.F_name, s.L_name);
                }
                break;
                case 4:
                separateByGender(&Q1, &MaleQ, &FemaleQ);
                printf("\nMale Students:\n");
                displayQueue(MaleQ);
                printf("\nFemale Students:\n");
                displayQueue(FemaleQ);
                break;
                case 5:
                exit(0);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    return 0;
}

void cqinsert(struct queue *pq, struct tenPerson x) {
    if ((pq->front == 0 && pq->rear == MAXSTUDENTS - 1) || (pq->front == pq->rear + 1)) {
        printf("\nQueue Overflow \n");
        exit(0);
    }
    if (pq->front == -1) { 
        pq->front = 0;
        pq->rear = 0;
    } else if (pq->rear == MAXSTUDENTS - 1) {
        pq->rear = 0;
    } else {
        pq->rear = pq->rear + 1;
    }
    pq->std_info[pq->rear] = x;
    printf("\nStudent %s %s is inserted \n", x.F_name, x.L_name);
}

struct tenPerson cqdelete(struct queue *pq) {
    if (pq->front == -1) {
        printf("\nQueue Underflow\n");
        exit(1);
    }
    struct tenPerson item = pq->std_info[pq->front];
    if (pq->front == pq->rear) {
        pq->front = -1;
        pq->rear = -1;
    } else if (pq->front == MAXSTUDENTS - 1) {
        pq->front = 0;
    } else {
        pq->front = pq->front + 1;
    }
    return item;
}
void separateByGender(struct queue *mainQ, struct queue *maleQ, struct queue *femaleQ) {
    while (mainQ->front != -1) {
        struct tenPerson student = cqdelete(mainQ);
        if (student.gender == 'M') {
            cqinsert(maleQ, student);
        } else if (student.gender == 'F') {
            cqinsert(femaleQ, student);
        }
    }
}
void displayQueue(struct queue Q) {
    if (Q.front == -1) {
        printf("Queue is empty\n");
        return;
    }
    int i;
    for (i = Q.front; i != Q.rear; i = (i + 1) % MAXSTUDENTS) {
        printf("%s %s\n", Q.std_info[i].F_name, Q.std_info[i].L_name);
    }
    printf("%s %s\n", Q.std_info[i].F_name, Q.std_info[i].L_name);
}