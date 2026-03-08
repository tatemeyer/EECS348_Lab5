// Sales Report
// Given 12 monthly sales figures in an input file, generate: 
// - Monthly sales report (month and sales in two columns)
// - Sales Summary Report (min, max, and average monthly sales)
// - Six-Month Moving Average Report
// - Sales Report (highest to lowest)

#include <stdio.h>
#include <string.h>

void monthly_sales_report(double sales[12], const char *months[12]) {
    FILE *fptr;
    fptr = fopen("sales.txt", "r");
  

    for (int i = 0; i < 12; i++) {
        fscanf(fptr, "%lf", &sales[i]);
    }
    fclose(fptr);
    printf("Monthly Sales Report:\n");
    printf("%-15s%10s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {
        printf("%-15s%10.2f\n", months[i], sales[i]);
    }
}

void sales_summary_report(double sales[12], const char *months[12]) {
    double min_sales = sales[0];
    double max_sales = sales[0];
    double total_sales = 0;
    double average_sales;
    int min_idx = 0, max_idx = 0;

    for (int i = 0; i < 12; i++) {
        if (sales[i] < min_sales) {
            min_sales = sales[i];
            min_idx = i;
        }
        if (sales[i] > max_sales) {
            max_sales = sales[i];
            max_idx = i;
        }
        total_sales += sales[i];
    }
    average_sales = total_sales / 12;

    printf("\nSales Summary Report:\n");
    printf("Minimum sales: %.2f (%s)\n", min_sales, months[min_idx]);
    printf("Maximum sales: %.2f (%s)\n", max_sales, months[max_idx]);
    printf("Average sales: %.2f\n", average_sales);
}

void moving_average_report(double sales[12], const char *months[12]) {
    double avg[7];
    double sum = 0.0;

    for (int i = 0; i < 6; ++i) sum += sales[i];   // initial window Jan-Jun
    avg[0] = (double)(long long)(sum / 6.0 * 100 + 0.5) / 100.0;

    for (int w = 1; w <= 6; ++w) {                  // windows 1..6 (Feb-Jul .. Jul-Dec)
        sum += sales[w + 5] - sales[w - 1];         // add new month, subtract leaving month
        avg[w] = (double)(long long)(sum / 6.0 * 100 + 0.5) / 100.0;
    }

    printf("\nSix-Month moving average report:\n");
    printf("%-25s%s\n", "Months", "Average Sales");
    for (int w = 0; w <= 6; ++w) {
        char label[32];
        snprintf(label, sizeof(label), "%s-%s", months[w], months[w + 5]);
        printf("%-25s%.2f\n", label, avg[w]);
    }
}

void sorted_sales_report(double sales[12], const char *months[12]) {
    double sorted_sales[12];
    const char *sorted_months[12];
    for (int i = 0; i < 12; i++) {
        sorted_sales[i] = sales[i];
        sorted_months[i] = months[i];
    }
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11 - i; j++) {
            if (sorted_sales[j] < sorted_sales[j + 1]) {
                double temp_sales = sorted_sales[j];
                sorted_sales[j] = sorted_sales[j + 1];
                sorted_sales[j + 1] = temp_sales;
                const char *temp_month = sorted_months[j];
                sorted_months[j] = sorted_months[j + 1];
                sorted_months[j + 1] = temp_month;
            }
        }
    }
    printf("\nSales report (highest to lowest):\n");
    printf("%-15s%10s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {
        printf("%-15s$%9.2f\n", sorted_months[i], sorted_sales[i]);
    }
}


int main() {
    double sales[12];
    const char *months[12] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
    monthly_sales_report(sales, months);
    sales_summary_report(sales, months);
    moving_average_report(sales, months);
    sorted_sales_report(sales, months);
    return 0;
}