#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAP 30
#define CENTERX (MAP/2)
#define CENTERY (MAP/2)

char map[30][30];

struct workers{
    char workerID[10];
    char workerName[30];
    char workerPos[30];
    int workerSalary;
    struct workers* prev;
    struct workers* next;
};

struct division{
    char divisionID[20];
    char divisionName[20];
    struct workers* table[5];
    struct division* next;
    struct division* prev;
};

struct land{
    char landID[10];
    char officeID[10];
    char officeName[30];
    char officeAddress[30];
    int x;
    int y;
    struct division *div;

    struct land* north;
    struct land* west;
    struct land* east;
    struct land* south;
}*maps[30][30];

int isLand(struct land* l) {
    return strlen(l->landID) > 0 && strlen(l->officeID) == 0 && strlen(l->officeName) == 0 && strlen(l->officeAddress) == 0;
}

int isOffice(struct land* l) {
    return strlen(l->landID) > 0 && strlen(l->officeID) > 0 && strlen(l->officeName) > 0 && strlen(l->officeAddress) > 0;
}

void pushHeadAll(char officeName[], struct land* curr){
    int randID = rand() % 1000;
    char Random[10];
    int randID1 = rand() % 1000;
    char Random1[10];

    sprintf(Random, "OF%03d", randID);
    sprintf(Random1, "LA%03d", randID1);

    strcpy(curr->landID, Random1);
    strcpy(curr->officeName, officeName);
    strcpy(curr->officeID, Random);
    strcpy(curr->officeAddress, "");
    curr->div = NULL;

    /*
    newLand->north = NULL;
    newLand->south = NULL;
    newLand->west = NULL;
    newLand->east = NULL;

    centerNode = newLand;
    */
}

void printCurr(struct land* curr){
    puts("");
    printf("Current Land Information\n");
    printf("========================\n");
    printf("%-15s : %s\n", "Land ID", curr->landID);
    printf("%-15s : %s\n", "Office ID", curr->officeID);
    printf("%-15s : %s\n", "Office Name", curr->officeName);
    printf("%-15s : %s\n", "Office Address", curr->officeAddress);
}

void printMap(struct land* curr){
    int x = curr->x;
    int y = curr->y;

    for (int i = 0; i < MAP; ++i) {
        for (int j = 0; j < MAP; ++j) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void printMenu(){
    puts("");
    puts("========================");
    puts("1. Add Division");
    puts("2. Add Worker");
    puts("3. View Office");
    puts("4. View All Office");
    puts("5. Delete Office");
    puts("6. Move");
    puts("7. Exit");
    printf(">> ");
}

void delOffice(struct land* curr, int input){

    puts("");

    if(strcmp(curr->officeName, "\0")!=0){
        printf("Deleted %s Office\n", curr->officeName);

        strcpy(curr->landID, "\0");
        curr->div = NULL;
        strcpy(curr->officeID, "\0");
        strcpy(curr->officeName, "\0");

        if(input==1){
            traverse(map, &curr, 3);
        }else if(input==2){
            traverse(map, &curr, 4);
        }else if(input==3){
            traverse(map, &curr, 1);
        }else if(input==4){
            traverse(map, &curr, 2);
        }

    }else{
        printf("There is no Fuckin Office here\n");
    }

    puts("Press Enter to Continue");
    getchar();
    system("cls");
    printMap(curr);
    printCurr(curr);
    printMenu2(curr, input);
}

void printMenu2(struct land* curr, int input){
    puts("");
    puts("========================");
    puts("1. Add Division");
    puts("2. Add Worker");
    puts("3. View Office");
    puts("4. Move");
    puts("5. Delete Office");
    puts("6. Exit");
    printf(">> ");

    int res;
    do{
        scanf("%d", &res);
        getchar();
        switch(res){
            case 1:{
                system("cls");
                printMap(curr);
                printCurr(curr);
                printDivs(curr);
                break;
            }
            case 2:{
                system("cls");
                printMap(curr);
                printCurr(curr);
                printWorkers(curr);
                break;
            }
            case 3:{
                system("cls");
                printMap(curr);
                printCurr(curr);
                printOffice(curr);
                break;
            }
            case 4:{
                transportation(curr);
            }
            case 5:{
                delOffice(curr, input);
                break;
            }
            case 6:{
                puts("Thank You");
                exit(0);
                return;
            }
        }
        system("cls");
        printMap(curr);
        printCurr(curr);
        printMenu2(curr, input);
    }while(res!=5);
}

void initDivisionTable(struct division* div, struct land* curr) {
    for (int i = 0; i < 5; i++) {
        div->table[i] = NULL;
    }
}

void printDivs(struct land* curr){
    puts("");

    printf("================================================================================================\n");
    printf("|%-13s|%-15s|%43s%-21s|\n","","", "Worker Statistics", "");
    printf("|%-13s|%-15s|================================================================|\n", "Division ID", "Division Name");
    printf("|%-13s|%-15s| CEO        | Director   | Supervisor | Manager    | Staff      |\n", "", "");

    if(curr->div==NULL){
        puts("================================================================================================");
        printf("|%52s%-42s|\n", "The division is empty!", " ");
        puts("================================================================================================");
    }else{
        struct division* temp = curr->div;
        puts("================================================================================================");

        while(temp!=NULL){
            printf("|%-13s|%-15s|",temp->divisionID, temp->divisionName);

            for(int i = 0; i < 5; i++){
                int count = 0;

                struct workers* currentWork = temp->table[i];

                while(currentWork != NULL){
                    count++;
                    currentWork = currentWork->next;
                }
                printf("%-12d|", count);
            }
            puts("");
            puts("================================================================================================");
            temp = temp->next;
        }
    }

    char diviName[100];

    puts("");

    do{
        printf("Insert division name [Must be unique and have length between 5-15 character (inclusive)], 0 to cancel: ");
        scanf("%[^\n]", diviName);
        getchar();

        if(strcmp(diviName, "0")==0){
            return;
        }

        char *space = strchr(diviName, ' ');
        if(space==NULL){
            printf("Division name must contain two words separated by a space.\n");
            continue;
        }

        if(!isupper(diviName[0])|| !isupper(space[1])){
            printf("Each word in the division name must start with a capital letter.\n");
            continue;
        }

        if (strlen(diviName) < 5 || strlen(diviName) > 15) {
            printf("Division name must have a total length between 5 and 15 characters.\n");
            continue;
        }

        if( strstr(diviName, "Fuck") || strstr(diviName, "Damn") || strstr(diviName, "WSSK") || strstr(diviName, "Wong Saya Suka") || strstr(diviName, "YNTKTS") ){
            printf("Watch Your Language\n");
            continue;
        }

        if(strstr(diviName, "Jomok") || strstr(diviName, "GAY")|| strstr(diviName, "JOMOK") || strstr(diviName, "Gay") || strstr(diviName, "jomok") || strstr(diviName, "gay")){
            puts("");
            printf("LU JOMOK\n");
            puts("#pukuljomok");
            puts("");
            getchar();
            exit(0);
        }

        break;

    }while(1);

    int randID = rand() % 1000;
    char Random[10];

    sprintf(Random, "DI%03d", randID);

    struct division* newDiv = (struct division*)malloc(sizeof(struct division));
    strcpy(newDiv->divisionName, diviName);
    strcpy(newDiv->divisionID, Random);
    newDiv->next = NULL;
    newDiv->prev = NULL;

    if(curr->div==NULL){
        curr->div = newDiv;
    }else{
        struct division* temp = curr->div;
        while (temp->next != NULL && strcmp(newDiv->divisionID, temp->divisionID) >= 0) {
            temp = temp->next;
        }

        if (strcmpi(newDiv->divisionID, temp->divisionID) < 0) {
            newDiv->next = temp;
            temp->prev = newDiv;
            curr->div = newDiv;
        } else {
            newDiv->next = temp->next;
            newDiv->prev = temp;
            if (temp->next != NULL) {
                temp->next->prev = newDiv;
            }
            temp->next = newDiv;
        }
    }

    initDivisionTable(newDiv, curr);

    puts("");
    printf("Division \"%s\" [%s] Successfully Added!!", newDiv->divisionName, newDiv->divisionID);
    if(strstr(diviName, "Don") || strstr(diviName, "Tasman") || strcmpi(diviName, "don tasman")==0 ){
        printf(" [NOICE NOICE]");
    }
    puts("");
    puts("Press Enter to Continue");
    getchar();
    return;
}

int checker(char diviID[], struct land* curr){
    struct division* temp = curr->div;
    while(temp!=NULL){
        if(strcmpi(diviID, temp->divisionID)==0){
            return 1;
        }
        temp = temp->next;
    }
    puts("Input the existing ID! ");
    return 0;
}

unsigned long hashing(char *str) {

    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % 5;
}

const char* position(int index){
    if(index==0){
        return "CEO";
    }else if(index==1){
        return "Director";
    }else if(index==2){
        return "Supervisor";
    }else if(index==3){
        return "Manager";
    }else if(index==4){
        return "Staff";
    }
}

int salary(int index){
    if(index==0){
        return 20000000;
    }else if(index==1){
        return 16000000;
    }else if(index==2){
        return 12000000;
    }else if(index==3){
        return 8000000;
    }else if(index==4){
        return 5000000;
    }
}

void pushWorker(char ID[], int index, char name[], struct land* curr, char diviID[]){
    struct division* curr_div = curr->div;

    while(curr_div!=NULL){
        if(strcmpi(diviID, curr_div->divisionID)==0){
            break;
        }
        curr_div = curr_div->next;
    }

    struct workers* node = (struct workers*)malloc(sizeof(struct workers));
    strcpy(node->workerID, ID);
    strcpy(node->workerName, name);
    strcpy(node->workerPos, position(index));
    node->workerSalary = salary(index);
    node->prev = NULL;
    node->next = NULL;

    if(curr_div->table[index]==NULL){
        curr_div->table[index]=node;
    }else{
        struct workers* temp = curr_div->table[index];
        if(strcmpi(node->workerID, temp->workerID)<0){
            node->next = temp;
            temp->prev = node;
            curr_div->table[index] = node;
        }else{
            while(temp->next!=NULL && strcmpi(node->workerID, temp->next->workerID)>=0){
                temp=temp->next;
            }
            node->next = temp->next;
            node->prev = temp;
            if(temp->next!=NULL){
                temp->next->prev = node;
            }
            temp->next= node;
        }
    }
    printf("Worker Added Successfully!");
    if(strstr(name, "Don") || strstr(name, "Tasman") || strcmpi(name, "don tasman")==0 ){
        printf(" [NOICE NOICE]");
    }
    puts("");
    puts("Press enter to continue...");

    return;
}

void printWorkers(struct land* curr){
    puts("");

    printf("================================================================================================\n");
    printf("|%-13s|%-15s|%43s%-21s|\n","","", "Worker Statistics", "");
    printf("|%-13s|%-15s|================================================================|\n", "Division ID", "Division Name");
    printf("|%-13s|%-15s| CEO        | Director   | Supervisor | Manager    | Staff      |\n", "", "");

    if(curr->div==NULL){
        puts("================================================================================================");
        printf("|%52s%-42s|\n", "The division is empty!", " ");
        puts("================================================================================================");
        puts("Press Enter to Continue");
        getchar();
        return;
    }else{
        struct division* temp = curr->div;
        puts("================================================================================================");

        while(temp!=NULL){
            printf("|%-13s|%-15s|",temp->divisionID, temp->divisionName);

            for(int i = 0; i < 5; i++){
                int count = 0;

                struct workers* currentWork = temp->table[i];

                while(currentWork != NULL){
                    count++;
                    currentWork = currentWork->next;
                }
                printf("%-12d|", count);
            }
            puts("");
            puts("================================================================================================");
            temp = temp->next;
        }
    }
    char workerName[100];
    char diviID[50];

    puts("");

    do{
        printf("Insert worker division ID [Must be available and worker capacity not full], 0 to cancel: ");
        scanf("%[^\n]", diviID);
        getchar();

        if(strcmp(diviID,"0")==0){
            return;
        }
    }while(!checker(diviID, curr));

    do{
        printf("Insert worker name [Must have length between 4-12 character (inclusive)], 0 to cancel: ");
        scanf("%[^\n]", workerName);
        getchar();

        if(strcmp(workerName,"0")==0){
            return;
        }

        char *space = strchr(workerName, ' ');
        if(space==NULL){
            printf("Name must contain two words separated by a space.\n");
            continue;
        }

        if(!isupper(workerName[0])|| !isupper(space[1])){
            printf("Each word in the name must start with a capital letter.\n");
            continue;
        }

        if (strlen(workerName) < 4 || strlen(workerName) > 12) {
            printf("Division name must have a total length between 4 and 12 characters.\n");
            continue;
        }

        if( strstr(workerName, "Fuck") || strstr(workerName, "Damn") || strstr(workerName, "WSSK") || strstr(workerName, "Wong Saya Suka") || strstr(workerName, "YNTKTS") ){
            printf("Watch Your Language\n");
            continue;
        }
        break;
    }while(1);

    int randID = rand() % 1000;
    char rand1 = curr->officeName[0];
    char *space = strchr(curr->officeName, ' ');
    char rand2 = space[1];

    char Random[10] = {};

    sprintf(Random, "%c%c%03d", rand1, rand2,randID);

    int index = hashing(Random);

    pushWorker(Random, index, workerName, curr, diviID);

    getchar();
}

void printOffice(struct land* curr){
    puts("");

    struct division* temp = curr->div;

    while(temp!=NULL){
        puts("===================================================================");
        printf("|%-13s|%-51s|\n", temp->divisionID, temp->divisionName);
        puts("===================================================================");
        puts("| Worker ID | Worker Name       | Worker Position | Worker Salary |");
        puts("===================================================================");

        for(int i=0;i<5;i++){
            struct workers* worker = temp->table[i];
            while(worker!=NULL){
                printf("|%-13s|%-17s|%-17s|%15d|\n", worker->workerID, worker->workerName, worker->workerPos, worker->workerSalary);
                puts("===================================================================");
                worker = worker->next;
            }
        }
        puts("");
        temp = temp->next;
    }

    puts("");
    puts("Press enter to continue...");
    getchar();
    return;
}

void populate() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            maps[i][j] = (struct land*)malloc(sizeof(struct land));
            strcpy(maps[i][j]->landID, "\0");
            strcpy(maps[i][j]->officeID, "\0");
            strcpy(maps[i][j]->officeName, "\0");
            strcpy(maps[i][j]->officeAddress, "\0");
            maps[i][j]->x = i;
            maps[i][j]->y = j;
            maps[i][j]->north = (i > 0) ? maps[i - 1][j] : NULL;
            maps[i][j]->south = (i < 30 - 1) ? maps[i + 1][j] : NULL;
            maps[i][j]->west = (j > 0) ? maps[i][j - 1] : NULL;
            maps[i][j]->east = (j < 30 - 1) ? maps[i][j + 1] : NULL;

            if (maps[i][j]->north)
                maps[i][j]->north->south = maps[i][j];
            if (maps[i][j]->south)
                maps[i][j]->south->north = maps[i][j];
            if (maps[i][j]->west)
                maps[i][j]->west->east = maps[i][j];
            if (maps[i][j]->east)
                maps[i][j]->east->west = maps[i][j];
        }
    }
}

void traverse(char map[][30], struct land** currPtr, int input) {
    struct land* curr = *currPtr;

    int x = curr->x;
    int y = curr->y;

    int randID1 = rand() % 1000;
    char Random1[10];
    sprintf(Random1, "LA%03d", randID1);

    switch(input) {
        case 1: { // Move north
            if (x > 0){
                map[x][y] = '-';
                curr = curr->north;
                if(strcmpi(curr->landID, "\0")==0){
                    strcpy(curr->landID, Random1);
                }
                curr->x = x - 1;
                curr->y = y;
                map[x - 1][y] = 'P';
                *currPtr = curr;
            }
            break;
        }
        case 2: { // Move east
            if (y < MAP - 1){
                map[x][y] = '-';
                curr = curr->east;
                if(strcmpi(curr->landID, "\0")==0){
                    strcpy(curr->landID, Random1);
                }
                curr->y = y + 1;
                curr->x = x;
                map[x][y + 1] = 'P';
                *currPtr = curr;
            }
            break;
        }
        case 3: { // Move south
            if (x < MAP - 1){
                curr = curr->south;
                map[x][y] = '-';
                if(strcmpi(curr->landID, "\0")==0){
                    strcpy(curr->landID, Random1);
                }
                curr->x = x + 1;
                curr->y = y;
                map[x + 1][y] = 'P';
                *currPtr = curr;
            }
            break;
        }
        case 4: { // Move west
            if (y > 0){
                curr = curr->west;
                map[x][y] = '-';
                if(strcmpi(curr->landID, "\0")==0){
                    strcpy(curr->landID, Random1);
                }
                curr->y = y - 1;
                curr->x = x;
                map[x][y - 1] = 'P';
                *currPtr = curr;
            }
            break;
        }
        default:
            return;
    }
}

void transportation(struct land* curr){
    int input;
    int back = 0;
    int ret = 0;
    do{
        system("cls");
        printMap(curr);
        printCurr(curr);
        puts("========================");
        puts("1. North");
        puts("2. East");
        puts("3. South");
        puts("4. West");
        printf(">> ");
        scanf("%d", &input);
        getchar();

        traverse(map,&curr,input);
        system("cls");
        printMap(curr);
        printCurr(curr);

        int choice;

        if(strcmpi(curr->officeName,"\0")==0){
            do{
                puts("========================");
                puts("1. Build Office");
                puts("2. Back to previous office");
                printf(">> ");
                scanf("%d", &choice);
                getchar();

                switch(choice){
                    case 1:{
                        char diviName[100];
                        do{
                            puts("");
                            printf("Input Office Name [Minimum 2 words and every word start with capital], 0 to cancel: ");
                            scanf("%[^\n]", diviName);
                            getchar();

                            if(strcmp(diviName, "0")==0){
                                return;
                            }

                            char *space = strchr(diviName, ' ');
                            if(space==NULL){
                                printf("Office name must contain two words separated by a space.\n");
                            continue;
                            }

                            if(!isupper(diviName[0])|| !isupper(space[1])){
                                printf("Each word in the office name must start with a capital letter.\n");
                            continue;
                            }

                            if( strstr(diviName, "Fuck") || strstr(diviName, "Damn") || strstr(diviName, "WSSK") || strstr(diviName, "Wong Saya Suka") || strstr(diviName, "YNTKTS") ){
                                printf("Watch Your Language\n");
                                continue;
                            }
                            if(strstr(diviName, "Jomok") || strstr(diviName, "GAY")|| strstr(diviName, "JOMOK") || strstr(diviName, "Gay") || strstr(diviName, "jomok") || strstr(diviName, "gay")){
                                puts("");
                                printf("LU JOMOK\n");
                                puts("#pukuljomok");
                                puts("");
                                exit(0);
                            }

                            break;
                        }while(1);

                        strcpy(curr->officeName, diviName);

                        int randID = rand() % 1000;
                        char Random[10];

                        sprintf(Random, "OF%03d", randID);
                        strcpy(curr->officeID, Random);

                        puts("Office Built Successfully!");
                        puts("Press enter to continue...");
                        getchar();
                        break;
                    }
                    case 2:{
                        if(input==1){
                            traverse(map, &curr, 3);
                        }else if(input==2){
                            traverse(map, &curr, 4);
                        }else if(input==3){
                            traverse(map, &curr, 1);
                        }else if(input==4){
                            traverse(map, &curr, 2);
                        }
                        break;
                    }
                }
                system("cls");
                printMap(curr);
                printCurr(curr);
                printMenu2(curr, input);

            }while(!back);
        }
        else{
            printMenu2(curr, input);
        }
    }while(!ret);

}

int main()
{
    srand(time(NULL));

    populate();

    struct land* curr = maps[CENTERX][CENTERY];

    system("cls");
    puts("Welcome to FFontinental");
    puts("Lets build our first office");
    puts("Input Office Name as \"FFontinental Office\"");

    char officeName[30];
    do{
        printf("Input Office Name [Must be \"FFontinental Office\"]: ");
        scanf("%[^\n]", officeName);
        getchar();
        if(strstr(officeName, "Jomok") || strstr(officeName, "GAY")|| strstr(officeName, "JOMOK") || strstr(officeName, "Gay") || strstr(officeName, "jomok") || strstr(officeName, "gay")){
            puts("");
            printf("LU JOMOK\n");
            puts("#pukuljomok");
            puts("");
            exit(0);
        }
        if(strstr(officeName, "Don") || strstr(officeName, "Tasman") || strcmpi(officeName, "don tasman")==0 ){
            puts("");
            printf("NOICE NOICE\n");
            puts("");
        }
    }while(strcmpi(officeName, "FFontinental Office")!=0);

    pushHeadAll(officeName, curr);

    puts("Office Built Successfully!");
    printf("Press enter to continue...");
    getchar();

    for (int i = 0; i < MAP; ++i) {
        for (int j = 0; j < MAP; ++j) {
            map[i][j] = ' ';
        }
    }

    for (int i = 0; i < MAP; ++i) {
        map[0][i] = '=';
        map[MAP - 1][i] = '=';
    }

    for (int i = 0; i < MAP; ++i) {
        map[i][0] = '|';
        map[i][MAP - 1] = '|';
    }
    map[CENTERX][CENTERY] = 'P';

    curr->x = CENTERX;
    curr->y = CENTERY;

    int input;

    do{
        puts("");
        system("cls");
        printMap(curr);
        printCurr(curr);
        printMenu();

        scanf("%d", &input);
        getchar();

        switch(input){
            case 1:{
                system("cls");
                printMap(curr);
                printCurr(curr);
                printDivs(curr);
                break;
            }
            case 2:{
                system("cls");
                printMap(curr);
                printCurr(curr);
                printWorkers(curr);
                break;
            }
            case 3:{
                system("cls");
                printMap(curr);
                printCurr(curr);
                printOffice(curr);
                break;
            }
            case 4:{
                system("cls");
                printMap(curr);
                printCurr(curr);

                puts("");

                for(int i=0;i<30;i++){
                    for(int j=0;j<30;j++){
                        if(strcmpi(maps[i][j]->officeName, "\0")!=0){
                            puts("===============================================");
                            puts("| Land ID | Office ID | Office Name           |");
                            puts("===============================================");
                            printf("|%-8s | %-9s | %-21s |\n", maps[i][j]->landID, maps[i][j]->officeID, maps[i][j]->officeName);
                            puts("===============================================");
                        }
                    }
                }
                puts("Press Enter to Continue...");
                getchar();
                break;
            }
            case 5:{
                puts("You only have starting point, can't do delete office");
                puts("Press enter to continue...");
                getchar();
                break;
            }
            case 6:{
                transportation(curr);
                return 0;
            }
        }

    }while(input!=7);

    return 0;
}
