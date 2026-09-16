//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;        // ListNode의 정의를 변경해서는 안 됩니다

typedef struct _linkedlist{
    int size;
    ListNode *head;
} LinkedList;          // LinkedList의 정의를 변경해서는 안 됩니다


///////////////////////// function prototypes ////////////////////////////////////

// 이 함수의 프로토타입을 변경해서는 안 됩니다
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
    LinkedList ll;
    int c, i, j;
    c = 1;

    // 연결 리스트 1을 빈 연결 리스트로 초기화합니다
    ll.head = NULL;
    ll.size = 0;

    printf("1: Insert an integer to the sorted linked list:\n");
    printf("2: Print the index of the most recent input value:\n");
    printf("3: Print sorted linked list:\n");
    printf("0: Quit:");

    while (c != 0)
    {
        printf("\nPlease input your choice(1/2/3/0): ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("Input an integer that you want to add to the linked list: ");
            scanf("%d", &i);
            j = insertSortedLL(&ll, i);
            printf("The resulting linked list is: ");
            printList(&ll);
            break;
        case 2:
            printf("The value %d was added at index %d\n", i, j);
            break;
        case 3:
            printf("The resulting sorted linked list is: ");
            printList(&ll);
            removeAllItems(&ll);
            break;
        case 0:
            removeAllItems(&ll);
            break;
        default:
            printf("Choice unknown;\n");
            break;
        }


    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	int index = 0;

    ListNode *l = ll->head;
 
    while (l != NULL)
    {
        if (l->item == item)
		{
            return 1;
		}

        if (l->item > item)
		{
            break;
		}

        l = l->next;
        index++;
    }

    if (insertNode(ll, index, item) == 0)
	{
        return index;
	}

	/*
	int len = sizeof(ll->size);

    if (len == 0)
	{
		insertNode(ll, 0, item);
	}

	for (int i = 0; i < sizeof(len); i++)
	{
		if (ll[i] == item)
		{
			return 1;
		}

		if (ll[i] > item)
		{
			int cur = findNode(ll, i);

			insertNode(ll, cur, item);
		}
	}
	*/
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

    ListNode *cur;
    if (ll == NULL)
        return;
    cur = ll->head;

    if (cur == NULL)
        printf("Empty");
    while (cur != NULL)
    {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

void removeAllItems(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL){
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ll->head = NULL;
    ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

    ListNode *temp;

    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;

    temp = ll->head;

    if (temp == NULL || index < 0)
        return NULL;

    while (index > 0){
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // 빈 리스트이거나 첫 번째 노드를 삽입하는 경우, 헤드 포인터를 업데이트해야 합니다
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
        ll->head->next = cur;
        ll->size++;
        return 0;
    }


    // 목표 위치의 이전 노드와 해당 위치의 노드를 찾습니다
    // 새 노드를 생성하고 링크를 다시 연결합니다
    if ((pre = findNode(ll, index - 1)) != NULL){
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }

    return -1;
}

int removeNode(LinkedList *ll, int index)
{

    ListNode *pre, *cur;

    // 제거할 수 있는 가장 높은 인덱스는 size-1 입니다
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;

    // 첫 번째 노드를 제거하는 경우, 헤드 포인터를 업데이트해야 합니다
    if (index == 0){
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--; 

        return 0;
    }

    // 목표 위치의 이전 노드와 이후 노드를 찾습니다
    // 대상 노드를 해제하고 링크를 다시 연결합니다
    if ((pre = findNode(ll, index - 1)) != NULL){

        if (pre->next == NULL)
            return -1;

        cur = pre->next;
        pre->next = cur->next;
        free(cur);
        ll->size--;
        return 0;
    }

    return -1;
}