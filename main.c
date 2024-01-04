#include <stdio.h>
#include <string.h>

// Define the Participant structure
struct Participant {
    char name[50];
    int id;
    char organization[50];
    float registrationFee;
    int paymentStatus;
};

// Function to load participants from a file
void loadParticipants(struct Participant participants[], int size) {
    FILE* file = fopen("participants.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    for (int i = 0; i < size; ++i) {
        fscanf(file, "%49[^\n]\n%d\n%49[^\n]\n%f\n%d\n",
               participants[i].name, &participants[i].id,
               participants[i].organization, &participants[i].registrationFee,
               &participants[i].paymentStatus);
    }

    fclose(file);
}

// Function to input participant data
void inputParticipantData(struct Participant *participant) {
    printf("Enter participant name: ");
    scanf(" %49[^\n]", participant->name);
    printf("Enter participant ID: ");
    scanf("%d", &participant->id);
    printf("Enter participant organization: ");
    scanf(" %49[^\n]", participant->organization);
    printf("Enter registration fee: ");
    scanf("%f", &participant->registrationFee);
    participant->paymentStatus = 0;

    FILE* file = fopen("participants.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s\n%d\n%s\n%.2f\n%d\n",
            participant->name, participant->id,
            participant->organization, participant->registrationFee,
            participant->paymentStatus);

    fclose(file);
}

// Function to update payment status
const char* updatePaymentStatus(struct Participant *participant) {
    participant->paymentStatus = 1;

    FILE* file = fopen("participants.txt", "r+");
    if (file == NULL) {
        printf("Error opening file for updating payment status.\n");
        return "Payment status updated, but error updating file.";
    }

    // Find and update the corresponding participant's payment status in the file
    while (fscanf(file, "%49[^\n]\n%d\n%49[^\n]\n%f\n%d\n",
                  participant->name, &participant->id,
                  participant->organization, &participant->registrationFee,
                  &participant->paymentStatus) == 5) {
        if (participant->id == participant->id) {
            fseek(file, -sizeof(int), SEEK_CUR);
            fprintf(file, "%d\n", participant->paymentStatus);
            fclose(file);
            return "Payment status successfully updated.";
        }
    }

    fclose(file);
    return "Participant not found in the file.";
}

// Function to display participants
void displayParticipants(struct Participant participants[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("Name: %s\nID: %d\nOrganization: %s\nRegistration Fee: %.2f\nPayment Status: %s\n\n",
               participants[i].name, participants[i].id, participants[i].organization,
               participants[i].registrationFee, participants[i].paymentStatus ? "Paid" : "Not Paid");
    }
}

// Recursive function to adjust registration fee based on certain conditions
void adjustFee(struct Participant *participant) {
    // Example: Adjust fee based on ID
    if (participant->id % 2 == 0) {
        participant->registrationFee *= 0.9; // 10% discount for even IDs
    }

    // You can add more conditions as needed

    // Recursive call with a base case to avoid infinite recursion
    if (participant->registrationFee > 100.0) {
        adjustFee(participant);
    }
}

int main() {
    struct Participant participants[50];

    loadParticipants(participants, 50);

    for (int i = 0; i < 3; ++i) {
        inputParticipantData(&participants[i]);
    }

    updatePaymentStatus(&participants[0]);

    displayParticipants(participants, 3);

    adjustFee(&participants[1]);

    displayParticipants(participants, 3);

    return 0;
}
