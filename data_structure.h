#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

struct stall
{
    struct stall *prev;
    int stall_id;
    char stall_name[100];
    char contact_number[12];
    struct stall *next;
};

struct stall *create_stall(int stall_id, char *stall_name, char *contact_number);
void add_stall(struct stall **head, int stall_id, char *stall_name, char *contact_number);
void delete_stall(struct stall **head, int stall_id);
struct stall *search_stall(struct stall *head, int stall_id);
struct stall *search_stall_by_name(struct stall *head, char *stall_name);
void display_all_stalls(struct stall *head);
void free_all_stalls(struct stall *head);

struct item
{
    struct item *prev;
    int item_id;
    char item_name[100];
    float price;
    int quantity_available;
    int stall_id;
    struct item *next;
};

struct item *create_item(int item_id, char *item_name, float price, int quantity_available, int stall_id);
void add_item(struct item **head, int item_id, char *item_name, float price, int quantity_available, int stall_id);
void delete_item(struct item **head, int item_id);
struct item *search_item(struct item *head, int item_id);
struct item *search_item_by_name(struct item *head, char *item_name);
struct item *search_items_by_stall(struct item *head, int stall_id);
void display_all_items(struct item *head);
void display_items_by_stall(struct item *head, int stall_id);
void update_item_quantity(struct item *head, int item_id, int new_quantity);
void free_all_items(struct item *head);

struct customer
{
    struct customer *prev;
    char customer_id[14];
    char customer_name[50];
    char contact_number[12];
    struct customer *next;
};

struct customer *create_customer(char *customer_id, char *customer_name, char *contact_number);
void add_customer(struct customer **head, char *customer_id, char *customer_name, char *contact_number);
void delete_customer(struct customer **head, char *customer_id);
struct customer *search_customer(struct customer *head, char *customer_id);
void display_all_customers(struct customer *head);
void free_all_customers(struct customer *head);

struct cart
{
    struct cart *prev;
    int cart_id;
    char customer_id[14];
    int item_id;
    int quantity;
    float item_price;
    struct cart *next;
};

struct cart *create_cart(int cart_id, char *customer_id, int item_id, int quantity, float item_price);
void add_to_cart(struct cart **head, int cart_id, char *customer_id, int item_id, int quantity, float item_price);
void remove_from_cart(struct cart **head, int cart_id);
struct cart *search_cart(struct cart *head, int cart_id);
struct cart *search_cart_by_customer(struct cart *head, char *customer_id);
void display_cart(struct cart *head, char *customer_id);
void display_all_cart(struct cart *head);
float calculate_cart_total(struct cart *head, char *customer_id);
void free_all_cart(struct cart *head);


#endif