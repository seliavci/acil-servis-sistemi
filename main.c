//
//  main.c
//  hastane acil servis uygulaması
//
//  Created by Selin Avcı on 10.03.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Hasta bilgilerini tutan yapı
typedef struct Patient {
    char patientID[10];     // Hasta ID
    char nationalID[15];    // TC Kimlik No
    char name[50];          // Ad ve Soyad
    char birthDate[15];     // Doğum Tarihi
    char gender;            // Cinsiyet (M/F)
    char phone[15];         // Telefon
    char prescriptionID[10];// Reçete Numarası
    int priority;           // Öncelik seviyesi (1 = en yüksek, 3 = en düşük)
    struct Patient* next;   // Sonraki hastaya işaret eden pointer
} Patient;

// Rastgele reçete numarası üretme fonksiyonu
void generatePrescriptionID(char* prescriptionID) {
    int num = rand() % 900000 + 100000; // 100000 ile 999999 arasında bir numara üret
    sprintf(prescriptionID, "RX-%d", num);
}

// Yeni hasta ekleme fonksiyonu (öncelik sırasına göre)
void addPatient(Patient** head, char* patientID, char* nationalID, char* name, char* birthDate, char gender, char* phone, int priority) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));

    strcpy(newPatient->patientID, patientID);
    strcpy(newPatient->nationalID, nationalID);
    strcpy(newPatient->name, name);
    strcpy(newPatient->birthDate, birthDate);
    newPatient->gender = gender;
    strcpy(newPatient->phone, phone);
    newPatient->priority = priority;

    generatePrescriptionID(newPatient->prescriptionID); // Reçete numarası oluştur

    // Hastayı önceliğe göre uygun yere ekleme
    if (*head == NULL || (*head)->priority > priority) {
        newPatient->next = *head;
        *head = newPatient;
    } else {
        Patient* current = *head;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newPatient->next = current->next;
        current->next = newPatient;
    }
}

// Hastaneye en öncelikli hastayı alma fonksiyonu
void admitPatient(Patient** head) {
    if (*head == NULL) {
        printf("\nHastane listesi boş!\n");
        return;
    }

    Patient* admitted = *head;
    printf("\nHastaneye alınan hasta: %s\n", admitted->name);
    *head = admitted->next;
    free(admitted);
}

// Hasta listesini yazdıran fonksiyon
void printPatients(Patient* head) {
    if (head == NULL) {
        printf("\nHasta listesi boş!\n");
        return;
    }

    Patient* current = head;
    printf("\n--- Öncelik Sırasına Göre Hasta Listesi ---\n");
    while (current != NULL) {
        printf("Öncelik: %d, Hasta ID: %s, TC: %s, Ad: %s, Doğum Tarihi: %s, Cinsiyet: %c, Telefon: %s, Reçete No: %s\n",
               current->priority, current->patientID, current->nationalID, current->name, current->birthDate,
               current->gender, current->phone, current->prescriptionID);
        current = current->next;
    }
}

// HL7 formatında hasta bilgilerini yazdıran fonksiyon
void printHL7Format(Patient* patient) {
    printf("\n--- HL7 Formatında Hasta Bilgileri ---\n");
    printf("MSH|^~\\&|HastaneSistemi|AcilServis|HastaTakip|20250310||ADT^A01|123456|P|2.3\n");
    printf("PID|||%s||%s||%s|%c|||%s||\n",
           patient->nationalID, patient->name, patient->birthDate, patient->gender, patient->phone);
    printf("PV1||Acil||||||||||||||HastaID%s||\n", patient->patientID);
    printf("RXE|||%s||\n", patient->prescriptionID);
}

// Tüm hastaları HL7 formatında yazdıran fonksiyon
void printAllHL7(Patient* head) {
    Patient* current = head;
    while (current != NULL) {
        printHL7Format(current);
        current = current->next;
    }
}

// Hastanın önceliğini değiştiren fonksiyon
void updatePatientPriority(Patient* head, char* patientID, int newPriority) {
    Patient* current = head;
    while (current != NULL) {
        if (strcmp(current->patientID, patientID) == 0) {
            current->priority = newPriority;
            printf("\nHasta ID %s'nin önceliği güncellendi. Yeni Öncelik: %d\n", patientID, newPriority);
            return;
        }
        current = current->next;
    }
    printf("\nHasta ID %s bulunamadı.\n", patientID);
}

// Hastayı silme fonksiyonu
void removePatient(Patient** head, char* patientID) {
    if (*head == NULL) {
        printf("\nHasta listesi boş!\n");
        return;
    }

    // Eğer ilk hasta silinecekse
    if (strcmp((*head)->patientID, patientID) == 0) {
        Patient* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("\nHasta ID %s listeden silindi.\n", patientID);
        return;
    }

    Patient* current = *head;
    while (current->next != NULL) {
        if (strcmp(current->next->patientID, patientID) == 0) {
            Patient* temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("\nHasta ID %s listeden silindi.\n", patientID);
            return;
        }
        current = current->next;
    }

    printf("\nHasta ID %s bulunamadı.\n", patientID);
}

int main() {
    srand(time(NULL)); // Rastgele reçete numarası üretimi için seed ayarla

    Patient* head = NULL;

    // Örnek hastalar ekleyelim (öncelikleri de ekleniyor)
    addPatient(&head, "1", "12345678901", "Beyza Bilgit", "2004-08-16", 'F', "05551234567", 2);
    addPatient(&head, "2", "98765432109", "Ali Alper", "1995-01-01", 'M', "05431234567", 1);
    addPatient(&head, "3", "11223344556", "Damla Ağır", "1978-04-16", 'F', "05331234567", 3);

    // Hastaları yazdıralım
    printPatients(head);

    // Hastaneye bir hasta alalım (öncelikli olan alınır)
    admitPatient(&head);

    // Güncellenmiş hasta listesini yazdıralım
    printPatients(head);

    // HL7 formatında yazdır
    printAllHL7(head);

    // Hasta ID 2'nin önceliğini güncelleyelim
    updatePatientPriority(head, "2", 1);  // 2. hastayı acil olarak önceliğini 1 yapalım

    // Güncellenmiş hasta listesini yazdıralım
    printPatients(head);

    // Hasta ID 3'ü silelim
    removePatient(&head, "3");

    // Güncellenmiş hasta listesini yazdıralım
    printPatients(head);

    return 0;
}

