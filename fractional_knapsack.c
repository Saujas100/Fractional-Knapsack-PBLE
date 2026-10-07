#include <stdio.h>

#define MAX 100

struct Package
{
    int id;
    float value;
    float weight;
    float ratio;
    float selected;
};

struct Package packages[MAX];
int n = 0;
float capacity = 0;
int detailsEntered = 0;
int ratioCalculated = 0;
int sorted = 0;
int resultCalculated = 0;

void enterPackageDetails()
{
    int i;

    printf("\nEnter number of packages: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of packages.\n");
        n = 0;
        return;
    }

    for (i = 0; i < n; i++)
    {
        packages[i].id = i + 1;

        printf("\nPackage %d\n", i + 1);

        printf("Enter value: ");
        scanf("%f", &packages[i].value);

        printf("Enter weight: ");
        scanf("%f", &packages[i].weight);

        if (packages[i].weight <= 0)
        {
            printf("Weight must be greater than 0.\n");
            i--;
            continue;
        }

        packages[i].ratio = 0;
        packages[i].selected = 0;
    }

    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);

    detailsEntered = 1;
    ratioCalculated = 0;
    sorted = 0;
    resultCalculated = 0;

    printf("\nPackage details entered successfully.\n");
}

void displayPackageDetails()
{
    int i;

    if (!detailsEntered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\n-------------------------------------------------\n");
    printf("ID\tValue\tWeight\tRatio\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               packages[i].id,
               packages[i].value,
               packages[i].weight,
               packages[i].ratio);
    }

    printf("-------------------------------------------------\n");
    printf("Vehicle Capacity: %.2f\n", capacity);
}

void calculateRatio()
{
    int i;

    if (!detailsEntered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        packages[i].ratio = packages[i].value / packages[i].weight;
    }

    ratioCalculated = 1;

    printf("\nValue/Weight ratios calculated successfully.\n");

    printf("\nPackage\tValue\tWeight\tRatio\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               packages[i].id,
               packages[i].value,
               packages[i].weight,
               packages[i].ratio);
    }
}

void sortPackages()
{
    int i, j;
    struct Package temp;

    if (!detailsEntered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    if (!ratioCalculated)
    {
        calculateRatio();
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (packages[j].ratio < packages[j + 1].ratio)
            {
                temp = packages[j];
                packages[j] = packages[j + 1];
                packages[j + 1] = temp;
            }
        }
    }

    sorted = 1;

    printf("\nPackages sorted by decreasing Value/Weight ratio.\n");

    printf("\nPackage\tValue\tWeight\tRatio\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               packages[i].id,
               packages[i].value,
               packages[i].weight,
               packages[i].ratio);
    }
}

void findMaximumValue()
{
    int i;
    float remainingCapacity;
    float totalValue = 0;
    float fraction;

    if (!detailsEntered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    if (!sorted)
    {
        sortPackages();
    }

    remainingCapacity = capacity;

    for (i = 0; i < n; i++)
    {
        packages[i].selected = 0;
    }

    for (i = 0; i < n; i++)
    {
        if (remainingCapacity <= 0)
        {
            break;
        }

        if (packages[i].weight <= remainingCapacity)
        {
            packages[i].selected = 1;
            remainingCapacity -= packages[i].weight;
            totalValue += packages[i].value;
        }
        else
        {
            fraction = remainingCapacity / packages[i].weight;
            packages[i].selected = fraction;
            totalValue += packages[i].value * fraction;
            remainingCapacity = 0;
        }
    }

    resultCalculated = 1;

    printf("\nMaximum value calculated successfully.\n");
    printf("Total weight used: %.2f\n", capacity - remainingCapacity);
    printf("Maximum value obtained: %.2f\n", totalValue);
}

void displaySelectedPackages()
{
    int i;
    float totalWeight = 0;
    float totalValue = 0;

    if (!resultCalculated)
    {
        printf("\nPlease calculate maximum value first.\n");
        return;
    }

    printf("\n---------------------------------------------------------\n");
    printf("Package\tFraction\tWeight Used\tValue Obtained\n");
    printf("---------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (packages[i].selected > 0)
        {
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   packages[i].id,
                   packages[i].selected,
                   packages[i].weight * packages[i].selected,
                   packages[i].value * packages[i].selected);

            totalWeight += packages[i].weight * packages[i].selected;
            totalValue += packages[i].value * packages[i].selected;
        }
    }

    printf("---------------------------------------------------------\n");
    printf("Total Weight Used: %.2f\n", totalWeight);
    printf("Maximum Value: %.2f\n", totalValue);
}

int main()
{
    int choice;

    do
    {
        printf("\n========== FRACTIONAL KNAPSACK ==========\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("=========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterPackageDetails();
                break;

            case 2:
                displayPackageDetails();
                break;

            case 3:
                calculateRatio();
                break;

            case 4:
                sortPackages();
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelectedPackages();
                break;

            case 7:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid menu choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}