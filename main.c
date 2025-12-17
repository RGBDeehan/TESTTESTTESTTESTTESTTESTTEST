#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"

struct stall *stalls = NULL;
struct item *items = NULL;
struct customer *customers = NULL;
struct cart *carts = NULL;

int stall_id_counter = 1;
int item_id_counter = 1;
int cart_id_counter = 1;

void flush_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void admin_menu()
{
    int choice;

    while (1)
    {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Stall\n");
        printf("2. View All Stalls\n");
        printf("3. View All Items\n");
        printf("4. View All Customers\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            char stall_name[100], contact[12];
            printf("Enter stall name: ");
            fgets(stall_name, sizeof(stall_name), stdin);
            stall_name[strcspn(stall_name, "\n")] = 0;

            printf("Enter contact: ");
            fgets(contact, sizeof(contact), stdin);
            contact[strcspn(contact, "\n")] = 0;

            add_stall(&stalls, stall_id_counter++, stall_name, contact);
            printf("Stall added successfully!\n");
        }
        else if (choice == 2)
        {
            display_all_stalls(stalls);
        }
        else if (choice == 3)
        {
            display_all_items(items);
        }
        else if (choice == 4)
        {
            display_all_customers(customers);
        }
        else if (choice == 5)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

void stall_menu()
{
    int choice;
    char stall_name[100];
    
    printf("Enter stall name: ");
    fgets(stall_name, sizeof(stall_name), stdin);
    stall_name[strcspn(stall_name, "\n")] = 0;

    struct stall *v = search_stall_by_name(stalls, stall_name);
    if (v == NULL)
    {
        printf("Stall not found!\n");
        return;
    }

    while (1)
    {
        printf("\n===== STALL: %s =====\n", stall_name);
        printf("1. View My Items\n");
        printf("2. Add New Item\n");
        printf("3. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            display_items_by_stall(items, v->stall_id);
        }
        else if (choice == 2)
        {
            char item_name[100];
            float price;
            int quantity;

            printf("Enter item name: ");
            fgets(item_name, sizeof(item_name), stdin);
            item_name[strcspn(item_name, "\n")] = 0;

            printf("Enter price: ");
            scanf("%f", &price);
            flush_input_buffer();

            printf("Enter quantity: ");
            scanf("%d", &quantity);
            flush_input_buffer();

            add_item(&items, item_id_counter++, item_name, price, quantity, v->stall_id);
            printf("Item added successfully!\n");
        }
        else if (choice == 3)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

void customer_menu()
{
    int choice, item_id, quantity;
    char customer_id[14];

    printf("Enter your customer ID: ");
    fgets(customer_id, sizeof(customer_id), stdin);
    customer_id[strcspn(customer_id, "\n")] = 0;

    struct customer *c = search_customer(customers, customer_id);
    if (c == NULL)
    {
        char name[100], contact[12];
        printf("New customer! Enter your name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter contact: ");
        fgets(contact, sizeof(contact), stdin);
        contact[strcspn(contact, "\n")] = 0;

        add_customer(&customers, customer_id, name, contact);
        c = search_customer(customers, customer_id);
    }

    while (1)
    {
        printf("\n===== CUSTOMER: %s =====\n", c->customer_name);
        printf("1. Browse Items by Stall\n");
        printf("2. View My Cart\n");
        printf("3. Checkout\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            char stall_name[100];
            printf("Enter stall name to browse: ");
            fgets(stall_name, sizeof(stall_name), stdin);
            stall_name[strcspn(stall_name, "\n")] = 0;

            struct stall *v = search_stall_by_name(stalls, stall_name);
            if (v == NULL)
            {
                printf("Stall not found!\n");
                continue;
            }

            printf("\n--- Items from %s ---\n", stall_name);
            struct item *runner = items;
            int found = 0;

            while (runner != NULL)
            {
                if (runner->stall_id == v->stall_id)
                {
                    printf("ID: %d | %s | Price: %.2f TK | Available: %d\n", 
                           runner->item_id, runner->item_name, runner->price, runner->quantity_available);
                    found = 1;
                }
                runner = runner->next;
            }

            if (!found)
            {
                printf("No items available from this stall!\n");
                continue;
            }

            printf("\nEnter item ID to add (0 to skip): ");
            scanf("%d", &item_id);
            flush_input_buffer();

            if (item_id == 0)
                continue;

            struct item *item = search_item(items, item_id);
            if (item == NULL || item->stall_id != v->stall_id)
            {
                printf("Invalid item!\n");
                continue;
            }

            printf("How many? (Available: %d): ", item->quantity_available);
            scanf("%d", &quantity);
            flush_input_buffer();

            if (quantity > 0 && quantity <= item->quantity_available)
            {
                add_to_cart(&carts, cart_id_counter++, customer_id, item_id, quantity, item->price);
                item->quantity_available -= quantity;
                printf("Added to cart!\n");
            }
            else
            {
                printf("Invalid quantity!\n");
            }
        }
        else if (choice == 2)
        {
            printf("\n--- YOUR CART ---\n");
            display_cart(carts, customer_id);
        }
        else if (choice == 3)
        {
            float total = calculate_cart_total(carts, customer_id);
            if (total > 0)
            {
                printf("\n--- CHECKOUT ---\n");
                printf("Total Amount: %.2f TK\n", total);
                printf("Thank you for shopping!\n");
            }
            else
            {
                printf("Cart is empty!\n");
            }
        }
        else if (choice == 4)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n========================================\n");
        printf("  EWU E-CANTEEN MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Admin\n");
        printf("2. Stall Owner\n");
        printf("3. Customer\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            admin_menu();
        }
        else if (choice == 2)
        {
            stall_menu();
        }
        else if (choice == 3)
        {
            customer_menu();
        }
        else if (choice == 4)
        {
            printf("Thank you! Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    free_all_stalls(stalls);
    free_all_items(items);
    free_all_customers(customers);
    free_all_cart(carts);

    return 0;
}
