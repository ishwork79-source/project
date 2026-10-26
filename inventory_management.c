#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
    char category[50];
};

struct Product inventory[MAX];
int totalProducts = 0;
int nextProductId = 106;

/* Remove the trailing newline from a string */
void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* 1. Add product */
void addProduct(void) {
    if (totalProducts >= MAX) {
        printf("\n[ERROR] Inventory is full! Cannot add more.\n");
        return;
    }// checking if there is space in the inventory to add a new product`

    struct Product p;

    p.id = nextProductId++;
    printf("\n--- ADD NEW PRODUCT ---\n");
    
    getchar();
    printf("Enter Product Name: ");
    if (fgets(p.name, sizeof(p.name), stdin) == NULL) return;
    removeNewline(p.name);

    printf("Enter Price (Rs.): ");
    if (scanf("%f", &p.price) != 1 || p.price < 0) {
        printf("[ERROR] Enter a valid non-negative price.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    printf("Enter Quantity: ");
    if (scanf("%d", &p.quantity) != 1 || p.quantity < 0) {
        printf("[ERROR] Enter a valid non-negative quantity.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    getchar();
    printf("Enter Category: ");
    if (fgets(p.category, sizeof(p.category), stdin) == NULL) return;
    removeNewline(p.category);

    inventory[totalProducts++] = p;
    printf("\n[SUCCESS] Product added successfully!\n");
}

/* 2. Display all products */
void displayProducts(void) {
    if (totalProducts == 0) {
        printf("\n[INFO] Inventory is empty!\n");
        return;
    }

    printf("\n+------+----------------------+------------+----------+----------------------+\n");
    printf("| %-4s | %-20s | %-10s | %-8s | %-20s |\n",
           "ID", "Name", "Price (Rs)", "Quantity", "Category");
    printf("+------+----------------------+------------+----------+----------------------+\n");

    for (int i = 0; i < totalProducts; i++) {
        printf("| %-4d | %-20.20s | %-10.2f | %-8d | %-20.20s |\n",
               inventory[i].id, inventory[i].name, inventory[i].price,
               inventory[i].quantity, inventory[i].category);
    }

    printf("+------+----------------------+------------+----------+----------------------+\n");
    printf("Total Products: %d\n", totalProducts);
}

/* 3. Search product using linear search */
void searchProduct(void) {
    if (totalProducts == 0) {
        printf("\n[INFO] Nothing to search!\n");
        return;
    }

    int searchId;
    printf("\nEnter Product ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("[ERROR] Invalid product ID.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].id == searchId) {
            printf("\n[FOUND] Product Details:\n");
            printf("--------------------------------\n");
            printf("ID       : %d\n", inventory[i].id);
            printf("Name     : %s\n", inventory[i].name);
            printf("Price    : Rs. %.2f\n", inventory[i].price);
            printf("Quantity : %d\n", inventory[i].quantity);
            printf("Category : %s\n", inventory[i].category);
            printf("--------------------------------\n");
            return;
        }
    }

    printf("\n[ERROR] Product with ID %d not found!\n", searchId);
}

/* 4. Update product */
void updateProduct(void) {
    if (totalProducts == 0) {
        printf("\n[INFO] Nothing to update!\n");
        return;
    }

    int updateId;
    printf("\nEnter Product ID to update: ");
    if (scanf("%d", &updateId) != 1) {
        printf("[ERROR] Invalid product ID.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].id == updateId) {
            getchar();
            printf("Enter New Name: ");
            if (fgets(inventory[i].name, sizeof(inventory[i].name), stdin) == NULL) return;
            removeNewline(inventory[i].name);

            printf("Enter New Price: ");
            if (scanf("%f", &inventory[i].price) != 1 || inventory[i].price < 0) {
                printf("[ERROR] Enter a valid non-negative price.\n");
                while (getchar() != '\n' && !feof(stdin)) {}
                return;
            }

            printf("Enter New Quantity: ");
            if (scanf("%d", &inventory[i].quantity) != 1 || inventory[i].quantity < 0) {
                printf("[ERROR] Enter a valid non-negative quantity.\n");
                while (getchar() != '\n' && !feof(stdin)) {}
                return;
            }

            getchar();
            printf("Enter New Category: ");
            if (fgets(inventory[i].category, sizeof(inventory[i].category), stdin) == NULL) return;
            removeNewline(inventory[i].category);

            printf("\n[SUCCESS] Product updated successfully!\n");
            return;
        }
    }

    printf("\n[ERROR] Product with ID %d not found!\n", updateId);
}

/* 5. Delete product */
void deleteProduct(void) {
    if (totalProducts == 0) {
        printf("\n[INFO] Nothing to delete!\n");
        return;
    }

    int deleteId;
    printf("\nEnter Product ID to delete: ");
    if (scanf("%d", &deleteId) != 1) {
        printf("[ERROR] Invalid product ID.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].id == deleteId) {
            for (int j = i; j < totalProducts - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            totalProducts--;
            printf("\n[SUCCESS] Product deleted successfully!\n");
            return;
        }
    }

    printf("\n[ERROR] Product with ID %d not found!\n", deleteId);
}

/* 6. Update stock */
void updateStock(void) {
    if (totalProducts == 0) {
        printf("\n[INFO] No products in inventory!\n");
        return;
    }

    int stockId, newQty;
    printf("\nEnter Product ID: ");
    if (scanf("%d", &stockId) != 1) {
        printf("[ERROR] Invalid product ID.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].id == stockId) {
            printf("Current Stock of %s: %d\n",
                   inventory[i].name, inventory[i].quantity);
            printf("Enter new quantity: ");

            if (scanf("%d", &newQty) != 1 || newQty < 0) {
                printf("[ERROR] Quantity must be a non-negative integer.\n");
                while (getchar() != '\n' && !feof(stdin)) {}
                return;
            }

            inventory[i].quantity = newQty;
            printf("[SUCCESS] Stock updated!\n");
            return;
        }
    }

    printf("\n[ERROR] Product not found!\n");
}

/* 7. Sort products using bubble sort */
void sortProducts(void) {
    if (totalProducts <= 1) {
        printf("\n[INFO] Not enough products to sort!\n");
        return;
    }

    int choice;
    printf("\nSort by:\n");
    printf("1. Price (Low to High)\n");
    printf("2. Price (High to Low)\n");
    printf("3. Quantity (Low to High)\n");
    printf("4. Name (A to Z)\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("[ERROR] Invalid sort choice!\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    for (int i = 0; i < totalProducts - 1; i++) {
        for (int j = 0; j < totalProducts - i - 1; j++) {
            int shouldSwap = 0;

            if (choice == 1)
                shouldSwap = inventory[j].price > inventory[j + 1].price;
            else if (choice == 2)
                shouldSwap = inventory[j].price < inventory[j + 1].price;
            else if (choice == 3)
                shouldSwap = inventory[j].quantity > inventory[j + 1].quantity;
            else if (choice == 4)
                shouldSwap = strcmp(inventory[j].name, inventory[j + 1].name) > 0;

            if (shouldSwap) {
                struct Product temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;
            }
        }
    }

    printf("\n[SUCCESS] Products sorted successfully!\n");
    displayProducts();
}

/* 8. Check low stock */
void checkLowStock(void) {
    if (totalProducts == 0) {
        printf("\n[INFO] Inventory is empty!\n");
        return;
    }

    int threshold;
    printf("\nEnter low stock threshold (e.g., 10): ");
    if (scanf("%d", &threshold) != 1 || threshold < 0) {
        printf("[ERROR] Enter a valid non-negative threshold.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }

    printf("\n--- Products with Stock <= %d ---\n", threshold);
    int found = 0;

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].quantity <= threshold) {
            printf("-> %s (ID: %d) - Qty: %d\n",
                   inventory[i].name, inventory[i].id, inventory[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("[ALL GOOD] All products have stock above %d!\n", threshold);
    }
}

int main(void) {
    inventory[0] = (struct Product){101, "Keyboard", 800.0f, 25, "Computer Accessories"};
    inventory[1] = (struct Product){102, "Mouse", 450.0f, 50, "Computer Accessories"};
    inventory[2] = (struct Product){103, "Monitor", 12000.0f, 5, "Electronics"};
    inventory[3] = (struct Product){104, "USB Cable", 150.0f, 200, "Accessories"};
    inventory[4] = (struct Product){105, "Headphones", 2500.0f, 8, "Audio"};
    totalProducts = 5;

    int choice;

    do {
        printf("\n========================================\n");
        printf("     INVENTORY MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf(" 1. Add Product\n");
        printf(" 2. Display All Products\n");
        printf(" 3. Search Product\n");
        printf(" 4. Update Product\n");
        printf(" 5. Delete Product\n");
        printf(" 6. Update Stock\n");
        printf(" 7. Sort Products\n");
        printf(" 8. Check Low Stock\n");
        printf(" 9. Exit\n");
        printf("========================================\n");
        printf("Enter your choice (1-9): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Please enter a number from 1 to 9.\n");
            while (getchar() != '\n' && !feof(stdin)) {}
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: updateStock(); break;
            case 7: sortProducts(); break;
            case 8: checkLowStock(); break;
            case 9: printf("\nThank you! Exiting system.\n"); break;
            default: printf("\n[ERROR] Invalid choice! Please enter 1-9.\n");
        }
    } while (choice != 9);

    return 0;
}
