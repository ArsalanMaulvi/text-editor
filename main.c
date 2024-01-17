#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct node
{
    char data[500];
    struct node *previous;
    struct node *next;

} * NODE;


NODE createnode(char *info)
{
    fflush(stdin);

    NODE node;
    node = (NODE)malloc(sizeof(struct node));
    node->next = NULL;
    node->previous = NULL;

    strcpy(node->data, info);

    return node;
}

void PUSH(char *info, NODE *TOP, NODE *head1)
{
    NODE newNODE;
    NODE temp;
    newNODE = createnode(info);

    if (*TOP != NULL)
    {
        newNODE->previous = *TOP;
        temp = *TOP;
        temp->next = newNODE;
        *TOP = temp;
    }
    else
        *head1 = newNODE;
    *TOP = newNODE;
}

char *POP(NODE *TOP, NODE *head1)
{
    NODE temp1 = *TOP;
    NODE temp2 = *TOP;

    if (*TOP != *head1)
    {
        temp2 = temp2->previous;
        temp2->next = NULL;
    }
    else
        temp2 = *head1 = NULL;

    *TOP = temp2;

    return temp1->data;
}

void display(NODE *head1)
{
    NODE ptr = *head1;
    printf("\t\t\t\t\t\t\t");
    while (ptr != NULL)
    {

        printf("%s ", ptr->data);
        ptr = ptr->next;
    }
}

void clearText(NODE *head) {
    NODE ptr = *head;
    while (ptr != NULL) {
        NODE temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    *head = NULL;
}

void clearFileContent(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        fclose(fp);
    } else {
        printf("\n\t\t\t\t\t\t\tError: Unable to clear file content!");
    }
}

void convertToUppercase(NODE *head) {
    NODE ptr = *head;
    while (ptr != NULL) {
        for (int i = 0; ptr->data[i] != '\0'; i++) {
            ptr->data[i] = toupper(ptr->data[i]);
        }
        ptr = ptr->next;
    }
}


void convertToLowercase(NODE *head) {
    NODE ptr = *head;
    while (ptr != NULL) {
        for (int i = 0; ptr->data[i] != '\0'; i++) {
            ptr->data[i] = tolower(ptr->data[i]);
        }
        ptr = ptr->next;
    }
}



int menu()
{
    int ch;
    printf("\n\t\t\t\t\t\t---------------------Menu---------------------\n");

     printf("\n\t\t\t\t\t\t\t1.Append Text\t\t2.Undo\n\t\t\t\t\t\t\t3.Redo\t\t\t4.Convert to Uppercase\n\t\t\t\t\t\t\t5.Convert to Lowercase\t6.Display Text\n\t\t\t\t\t\t\t7.Quit\n");
	printf("\n\t\t\t\t\t\tEnter Your Choice:");
    scanf("%d", &ch);
    return ch;
}

int main()
{
    NODE head1, head2;
    NODE TOP, UnRe_TOP;

    head1 = head2 = NULL;
    TOP = UnRe_TOP = NULL;

    //-----------------------------------------------------
    FILE *fp = fopen("TextFile.txt", "a+");

    char array[20] = {'\0'};

    char c;
    int i = 0;
    int count = 0;

    while (1)
    {
        c = fgetc(fp);

        if (c == EOF)
        {
            PUSH(array, &TOP, &head1);
            break;
        }

        if (c == ' ' || c == '\n')
        {
            i = 0;
            PUSH(array, &TOP, &head1);
            for (int j = 0; j < 20; j++)
            {
                array[j] = '\0';
            }
        }
        else
        {
            array[i++] = c;
        }
    }

    //-----------------------------------------------------

    printf("\n\n\t\t\t----------Implementation of Undo/Redo Functionality of TEXT EDITOR using Doubly Liked List as Stack----------\n");
    int ch;
    char para[500];

    while (1)
    {

        ch = menu();

        switch (ch)
        {
        case 1:
        {
            fflush(stdin);
            printf("\n\t\t\t\t\t\t\tEnter Text: ");
            gets(para);

            char *word = strtok(para, " ");

            while (word != NULL)
            {
                PUSH(word, &TOP, &head1);
                word = strtok(NULL, " ");
            }

            head2 = UnRe_TOP = NULL;
            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
            break;
        }

        case 2:
        {
            if (head1 != NULL)
            {
                strcpy(para, POP(&TOP, &head1));
                PUSH(para, &UnRe_TOP, &head2);
            }
            else
            {
                //color(1);
                printf("\n\t\t\t\t\t\t\tNothing To Undo!\n");
                //color(0);
            }
            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
            break;
        }

        case 3:
        {
            if (head2 != NULL)
            {
                strcpy(para, POP(&UnRe_TOP, &head2));
                PUSH(para, &TOP, &head1);
            }
            else
            {
                //color(1);
                printf("\n\t\t\t\t\t\t\tNothing To Redo!\n");
                //color(0);
            }
            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
            break;
        }

        case 6:
        {
            if (head1 != NULL)
            {
                printf("\n");
                display(&head1);
            }
            else
            {
                //color(1);
                printf("\t\t\t\t\t\t\tNO DATA Exists!");
                //color(0);
            }
            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
            break;
        }

        case 7:
        {
        	
    char newFilename[100];
    //printf("\n\t\t\t\t\t\t\tEnter the new filename to save: ");
    fflush(stdin);
    gets(newFilename);
    
    // Save modified content to the new file
   // saveToFile(newFilename, &head1);
    
    //printf("\n\t\t\t\t\t\t\tFile saved successfully as %s\n", newFilename);

    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
    printf("\n\t\t\t\t\t\t------------Project is prepared by------------\n");
    printf("\n\t\t\t\t\t\t\t\tARSALAN MAULVI (21BCE177)");

    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
    return 0;


        	//case 7:
//{
//    fclose(fp);
//    clearFileContent("TextFile.txt"); // Clear file content
//    FILE *fp = fopen("TextFile.txt", "a+");
//
//    NODE ptr = head1;
//
//    while (ptr != NULL)
//    {
//        fputs(ptr->data, fp);
//        fputs(" ", fp);
//        ptr = ptr->next;
//    }
//    fclose(fp);
//    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//    printf("\n\t\t\t\t\t\t------------Project is prepared by------------\n");
//    printf("\n\t\t\t\t\t\t\t\tARSALAN MAULVI (21BCE177)");
//
//    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//    printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//    return 0;
//}

//            fclose(fp);
//            FILE *fp = fopen("TextFile.txt", "w");
//
//            NODE ptr = head1;
//
//            while (ptr != NULL)
//            {
//                fputs(ptr->data, fp);
//                fputs(" ", fp);
//                ptr = ptr->next;
//            }
//            fclose(fp);
//            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//            printf("\n\t\t\t\t\t\t------------Project is prepared by------------\n");
//            printf("\n\t\t\t\t\t\t\t\tARSALAN MAULVI (21BCE177)");
//
//            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//            printf("\n\t\t\t\t\t\t----------------------------------------------\n");
//            return 0;
        }
		case 4:{


    convertToUppercase(&head1);
    printf("\n\t\t\t\t\t\tText converted to UPPERCASE.\n");
    break;
		}
case 5:
	{
	
    convertToLowercase(&head1);
    printf("\n\t\t\t\t\t\tText converted to lowercase.\n");
    break;
}
case 8:
{
    clearText(&head1);
    printf("\n\t\t\t\t\t\tText cleared.\n");
    break;
}

        default:
        {
            printf("\t\t\t\t\t\t\tInvalid Input!");
            break;
        }
        }
    }
}
