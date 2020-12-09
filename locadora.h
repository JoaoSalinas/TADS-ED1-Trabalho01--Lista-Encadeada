typedef struct Vehicle{
    int code;
    char model[30];
    char board[10];
    float dailyValue;
    struct Vehicle *next;
}Vehicle;

typedef struct List{
    Vehicle *first;
    Vehicle *last;
    int length;
}List;

 List* newList();
 Vehicle* newVehicle();

 Vehicle* getVehicle(List* list, int position);

 int push(List *list, Vehicle *vehicle);
 int unshift(List *list , Vehicle *vehicle);
 int splice(List *list, Vehicle *vehicle, int position);

 Vehicle* shift(List *list);
 Vehicle* pop(List *list);
 Vehicle* deleteVehicle(List *list, int position);

 int findIndex(List *list, char model[]);
 int length(List *list);
 void toString(List *list);
 void printVehicle(Vehicle *v);

 void rentVehicle(List *listRented, List *listAvaliable);
 void giveBackVehicle(List *list, List *listAvaliable);

 void pause();
 void menu(List* listRented, List* listAvaliable);

