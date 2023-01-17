#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
 
 // Zdefiniowanie struktury
typedef struct ListElement {
    int data;   //pole przechowujące daną
    struct ListElement * previous;  //pole wskazujące na poprzedni element listy 
    struct ListElement * next;  //pole wskazujące na następny element listy
} ListElement_type;
 
 
void show(ListElement_type *head);
void show_reverse(ListElement_type *head);
int list_size(ListElement_type *head);
void add_front(ListElement_type **head, int number);
void add_back(ListElement_type **head, int number);
void add_by_index(ListElement_type **head, int number, int position);
void delete_front(ListElement_type **head);
void delete_back(ListElement_type **head);
void delete_by_index(ListElement_type **head, int position);
 
int main()
{
    // Stworzenie głowy
    ListElement_type *head;
    // Uzycie wskaznika do alokowania pamieci
    head = (ListElement_type *)malloc(sizeof(ListElement_type));    
    // malloc() - parametr to rozmiar jaki w pamięci komputera zajmuje jeden węzeł
    // sizeof() - zwraca rozmiar typu struktury podanej w argumencie
    head=NULL; // Ustawienie na NULL bo lista powinna byc pusta na poczatku
 
    int option=-1;
    int number=-1;
    int index=-1;
 
    while(option!=0)
    {
 
    system("cls");
    printf("-------------------\n");
    printf("Lista dwukierunkowa\n");
    printf("-------------------\n");
    printf("\nPoglad listy: ");
    show(head);
    

    printf("1. Dodaj element na poczatek listy.\n");
    printf("2. Dodaj element na koniec listy.\n");
    printf("3. Dodaj element zgodnie z wybranym indeksem.\n");
    printf("4. Usun element z poczatku listy.\n");
    printf("5. Usun element z konca listy.\n");
    printf("6. Usun element o wybranym indeksie.\n");
    printf("7. Wyswietl liste w odwrotnej kolejnosci.\n");
    printf("0. Zakoncz program.\n");
    
    scanf("%i", &option);
 
    switch (option) //mozliwosc wyboru
    {
    case 0:
        return 0;
        break;
    
    case 1:
        printf("Wpisz liczbe jaka chcesz dodac: ");
        scanf("%i", &number);
        add_front(&head, number);
        break;

     case 2:
        printf("Wpisz liczbe jaka chcesz dodac: ");
        scanf("%i", &number);
        add_back(&head, number);
        break;

    case 3:
        printf("Wpisz liczbe jaka chcesz dodac: ");
        scanf("%i", &number);
        printf("Wpisz indeks: ");
        scanf("%i", &index);
        add_by_index(&head, number, index);
        break;

    case 4:
        delete_front(&head);
        break;

    case 5:
        delete_back(&head);
        break;
 
    case 6:
        printf("Wpisz indeks(0 to poczatek) elementu, ktorego chcesz usunac z listy: ");
        scanf("%i", &index);
        delete_by_index(&head, index);
        break;
    
    case 7:
        show_reverse(head); 
        Sleep(4000);
        break;

    default:
        printf("Podaj wlasciwa opcje.");
        Sleep(2000);
        break;
    }
    }
    return 0;
}


// Dodawanie elementu na początek listy
void add_front(ListElement_type **head, int number) {
    if(*head==NULL) {   // jesli lista jest pusta
        // alokujemy pamiec dla nowego elementu
        *head = (ListElement_type *)malloc(sizeof(ListElement_type));   
        (*head)->data = number; // przypisanie wartosci
        (*head)->previous=NULL; // poprzedni element ustawiamy na NULL
        (*head)->next = NULL;   // nastepny element ustawiamy na NULL
    } else {    // jesli cos jest na liscie
        ListElement_type *current;  // tworzymy wskaznik dla nowego elementu
        // alokujemy pamiec dla nowego elementu
        current=(ListElement_type *)malloc(sizeof(ListElement_type));
        current->data=number;   // przypisanie wartosci
        current->previous=NULL; // poprzedni element ustawiamy na NULL
        // zamiana nowego elementu na head
        current->next=(*head);  
        (*head)->previous=current;
        *head=current;
    }
}

// Dodawanie elementy na końcu listy
void add_back(ListElement_type **head, int number) { 
    if(*head==NULL) // gdy lista jest pusta
    {
        // alokujemy pamiec dla nowego elementu
        *head = (ListElement_type *)malloc(sizeof(ListElement_type));
        (*head)->data = number; // przypisanie wartosci
        (*head)->previous = NULL;   // poprzedni element ustawiamy na NULL
        (*head)->next = NULL;   // nastepny element ustawiamy na NULL
    } else {    // jesli cos jest na liscie
        ListElement_type *current=*head;
        ListElement_type *new_element;
        while (current->next != NULL) {
            current = current->next;
        }   // przechodzimy przez liste az nastepny element nie bedzie pusty
        // lokujemy pamiec dla nowego elementu
        current->next = (ListElement_type *)malloc(sizeof(ListElement_type));
        current->next->data = number;   // przypisanie wartosci
        current->next->previous=current;
        current->next->next = NULL; // nastepny element ustawiamy na NULL
    }
}

// Dodawanie elementu o wybranym indeksie
void add_by_index(ListElement_type **head, int number, int position) {
    // jesli indeks to 0, wykorzystujemy funkcje dodajaca elementu na poczatek listy
    if(position==0) add_front(head, number);
    else {
        if(position==list_size(*head)) add_back(head, number);
        else {
        ListElement_type *current=*head;
            ListElement_type *tmp;
        
            int i=0;
            while (current->next != NULL && i<position-1) {
                current = current->next;
                i++;
            }   // przechodzimy przez liste do elementu poprzedniego od indeksu
            tmp=current->next;  // tmp jako nastepny
            // alokujemy pamiec
            current->next=(ListElement_type *)malloc(sizeof(ListElement_type));
            current->next->data=number; // przypisujemy wartosc
            current->next->previous=current;    // 
            tmp->previous=current->next;
            current->next->next=tmp; 
        }
    }
}

// Usuwanie pierwszego elementu listy
void delete_front(ListElement_type **head) {
    if (*head!=NULL) {  // jesli lista nie jest pusta
        if((*head)->next==NULL) {   //jesli na liscie znajduje sie tylko jeden element
        *head=NULL; // usuwamy element
        } else {
            ListElement_type *tmp;
            tmp=(*head)->next;  // nastepny element po pierwszym przypisujemy do tmp
            free(*head);    // zwalniamy pamiec
            *head=tmp;      // tmp staje sie nowa glowa
            (*head)->previous=NULL; //usuwamy pierwszy element
        }
    }   
}

// Usuwanie elementu z konca listy
void delete_back(ListElement_type **head) {
    if((*head)->next==NULL) { //jezeli na liscie jest tylko jeden element
    *head=NULL; // lista staje sie pusta 
    } else {    //jezeli jest wiecej elementow na liscie
        ListElement_type *current=*head;
        while (current->next->next!= NULL) {
                current = current->next;
        }   // przechodzimy do przedostatniego elementu
        free(current->next);// zwolnienie pamieci 
        current->next=NULL; // usuniecie ostatniego elementu
    }  
}

// Usuwanie elementu o wybranym indeksie
void delete_by_index(ListElement_type **head, int position) {
    // jesli indeks=0, wykonaj funkcję usuwajacą element z początku listy
    if(position==0) pop_front(head);
    else {  // jesli indeks jest inny niż 0
        ListElement_type *current=*head;
        ListElement_type *tmp;
        int i=0;
        while (current->next != NULL && i<position-1) {
            current=current->next;
            i++;
        }   // przechodzimy po liście do elementu poprzedzającego węzeł
        tmp = current->next;    // tymczasowy element przechowuje element ktory chcemy usunac
        //Ustaw nastepnik elementu poprzedzającego węzeł, który chcesz usunąć, 
        //następnikiem tego elementu (z wykorzystaniem tymczasowego elementu),
        current->next = tmp->next;  
        current->next->previous=current;
        free(tmp);  //zwolnij pamiec z tymczasowego elementu
    }
}

// Pokazywanie listy od początku
void show(ListElement_type *head) {
    printf("\n");
    if(head==NULL) printf("Lista jest pusta");
    else {
        ListElement_type *current=head;
        do {    //wypisywanie elementów po kolei
            printf("%i", current->data);
            printf("\n");
            current = current->next;
        } while (current != NULL);
    }
}
 
// Pokazanie listy od końca
void show_reverse(ListElement_type *head) {
    printf("\n");
    if(head==NULL) printf("Lista jest pusta");
    else {
        ListElement_type *current=head;
        while (current->next != NULL) {
            current = current->next; 
        }   // przechodzimy na koniec listy
        do {    // wypisujemy elementy od końca listy
            printf("%i", current->data);
            printf("\n");
            current = current->previous;
        } while(current!=NULL);
    }
}

// Sprawdzanie ile elementów jest na liście
int list_size(ListElement_type *head) {
    int counter=0;
    if(head==NULL) return counter;  // jeśli lista jest pusta zwraca 0
    else {  // w przeciwnym razie
        ListElement_type *current=head;
        do {// przechodząc przez listę liczy elementy
            counter++;
            current = current->next;
        } while (current != NULL);
    }
    return counter; // zwraca liczbe elementów
}