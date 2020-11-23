#include "list.h"

void displayMenu()
{
    puts("");
    puts("Here is the menu for this list.");
    puts("============================================================");
    puts("1: Load data			2: Save data");
    puts("3: Append a node		4: Insert a node after another");
    puts("5: Delete a node		6: Destroy current list");
    puts("7: Count current list		8: Display current list");
    puts("9: Exit				10: Create a list");
}
   
// main function call list operations //
int main(int argc, char *argv[])
{
    int choice, tmp, done = 0;
    person *head = NULL, *p;
    system("clear");

    // Continuously prompt user input //
    while (!done) {
        displayMenu();
        puts("Input action: ");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
            case 1:
                head = load(head, "data");
                break;

            case 2:
                save(head, "data");
                break;

            case 3:
                head = append(head, makeNode());
                break;

            case 4:
                fflush(stdin);
                printf("Input person ID to insert after: ");
                fflush(stdin);
                scanf("%d", &tmp);
                fflush(stdin);
                insertAfter(head, tmp, makeNode());
                break;

            case 5:
                fflush(stdin);
                printf("Input person ID to delete: ");
                fflush(stdin);
                scanf("%d", &tmp);
                fflush(stdin);
                deleteNode(&head, tmp);
                break;

            case 6:
                destroy(&head);
                break;

            case 7:
                printf("\nNumber of nodes on list: %d", count(head));
                break;

            case 8:
                display(head);
                break;

            case 9:
                puts("Thank you. GoodBye.");
                done = 1;
                break;

            case 10:
                if (head == NULL)
                    head = create();
                else
                    puts("A list already exists.");
                break;

            default:
                puts("Invalid input. Please try again.");
                break;
        }
    }

    return 0;
}

