#include "headerr.h"
int main() {
	struct ryad infa;
    int choice;
    menu();
    do {
        if (scanf_s("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("chislo pls\n");
            continue;
        }
        if ((choice >= 1) && (choice <= 4)) {
            switch (choice) {
            case 1:
                fill(&infa, nextsin, 10);
                vivodzn(&infa, sin, 10);
                free(infa.x);
                free(infa.err);
                free(infa.sum);
                break;
            case 2:
                fill(&infa, nextcos, 10);
                vivodzn(&infa, cos, 10);
                free(infa.x);
                free(infa.err);
                free(infa.sum);
                break;
            case 3:
                fill(&infa, nextln, 0.9);
                vivodzn(&infa, log, 1.9);
                free(infa.x);
                free(infa.err);
                free(infa.sum);
                break;
            case 4:
                fill(&infa, nextexp, 10);
                vivodzn(&infa, exp, 10);
                free(infa.x);
                free(infa.err);
                free(infa.sum);
                break;
            }
        }
    } while (choice != 5);
}