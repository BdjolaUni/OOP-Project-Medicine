//Still i haven't get along with git, but one way or another i saved all versions of my Project. ver1 - ver3 are test versions.
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <windows.h>

#ifdef max
#undef max
#endif

#define ver_fin

#ifdef ver1 
const std::vector<std::string> names = { "John", "Jane", "Alice", "Bob", "Charlie" };
const std::vector<std::string> surnames = { "Doe", "Smith", "Johnson", "Williams", "Brown" };

enum DiseaseType { FLU, COLD, COVID, ALLERGY };

enum MedicineType { STRONG_FLU_MEDICINE, WEAK_FLU_MEDICINE, STRONG_COLD_MEDICINE, WEAK_COLD_MEDICINE, STRONG_COVID_MEDICINE, WEAK_COVID_MEDICINE, STRONG_ALLERGY_MEDICINE, WEAK_ALLERGY_MEDICINE };

struct Patient {
    std::string name;
    int age;
    DiseaseType disease;
    int region;
    int health;
};

struct Medicine {
    MedicineType type;
    int price;
    int effect;
};

class Pharmacy {
public:
    virtual ~Pharmacy() {}
    virtual bool hasMedicine(MedicineType type) const = 0;
    virtual int getPrice(MedicineType type) const = 0;
    virtual Medicine getMedicine(MedicineType type) = 0;
};

class ConcretePharmacy : public Pharmacy {
    std::vector<Medicine> medicines;

public:
    ConcretePharmacy(std::vector<Medicine> meds) : medicines(meds) {}

    bool hasMedicine(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return true;
            }
        }
        return false;
    }

    int getPrice(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return med.price;
            }
        }
        return -1; 
    }

    Medicine getMedicine(MedicineType type) override {
        for (auto it = medicines.begin(); it != medicines.end(); ++it) {
            if (it->type == type) {
                Medicine med = *it;
                medicines.erase(it);
                return med;
            }
        }
        return { type, -1, 0 }; 
    }
};

Patient generateRandomPatient(int maxRegion) {
    Patient patient;
    patient.name = names[rand() % names.size()] + " " + surnames[rand() % surnames.size()];
    patient.age = rand() % 50 + 10; 
    patient.disease = static_cast<DiseaseType>(rand() % 4);
    patient.region = rand() % maxRegion;
    patient.health = rand() % 21 + 80; 
    return patient;
}

Pharmacy* generateRandomPharmacy() {
    std::vector<Medicine> meds;
    for (int i = 0; i < 2; ++i) {
        MedicineType type = static_cast<MedicineType>(rand() % 8);
        int price = rand() % 50 + 10; 
        int effect = (type % 2 == 0) ? 30 : 15; 
        meds.push_back({ type, price, effect });
    }
    return new ConcretePharmacy(meds);
}

void updatePatient(Patient& patient) {
    int damage = 0;
    switch (patient.disease) {
    case FLU:
        damage = (patient.age > 40) ? 15 : 10;
        break;
    case COLD:
        damage = (patient.age > 40) ? 10 : 5;
        break;
    case COVID:
        damage = (patient.age > 40) ? 20 : 15;
        break;
    case ALLERGY:
        damage = (patient.age > 40) ? 5 : 3;
        break;
    }
    patient.health -= damage;
}

void asking() {
    std::string ask;
    while (ask != ".start") {
        std::cin >> ask;
        if (ask == ".info") {
            std::cout << "Hello doctor.\n"; Sleep(1200);
            std::cout << "Congratulations on joining the position of remote consultant.\n"; Sleep(1800);
            std::cout << "I am your supervisor, "; Sleep(1200);
            std::cout << "from this day, until the end of the month, I will instruct you and also make sure that you do your work efficiently.\n"; Sleep(2400);
            std::cout << "As you should already know, your job is to use this terminal to monitor the condition of the patients who will be provided to you.\n"; Sleep(2400);
            std::cout << "Depending on the situation and their condition, you will need to provide them with medicine, "; Sleep(1800);
            std::cout << "I hope I don't need to clarify that you need to keep them alive, "; Sleep(1800); 
            std::cout << "under any circumstances.\n"; Sleep(1800);
            std::cout << "I cannot know which patients will be given to you, but I know for sure that our services are available only in the Region.\n"; Sleep(2400);
            std::cout << "While working, do not forget that the Region is divided into 5 districts, and the price of delivering medicines from district to district can vary, both for the better and for the worse.\n"; Sleep(3000);
            std::cout << "Well, then I think you’ll figure it out on your own, "; Sleep(1800);
            std::cout << "we’ll see your results in a month...\n"; Sleep(1800);
            std::cout << "Good luck,"; Sleep(1800); std::cout << " Doctor.\n"; Sleep(2400);
        }
        else if (ask == ".start") {
            Sleep(3000);
            std::cout << "\n";
            break;
        }
        else {
            std::cout << "Invalid input.\n";
        }
    }
}

int main() {
    std::cout << "Welcome to Project Medicine. \n" << "- For context, type \".info\"\n" << "- To start your shift, type \".start\"\n";

    asking();

    srand(static_cast<unsigned int>(time(0)));

    const int numRegions = 5;
    const int numPatients = 3;
    const int numTurns = 4;

    std::vector<Patient> patients;
    for (int i = 0; i < numPatients; ++i) {
        patients.push_back(generateRandomPatient(numRegions));
    }

    std::vector<Pharmacy*> pharmacies(numRegions);
    int noPharmacyRegion = rand() % numRegions;
    for (int i = 0; i < numRegions; ++i) {
        if (i != noPharmacyRegion) {
            pharmacies[i] = generateRandomPharmacy();
        }
        else {
            pharmacies[i] = nullptr; 
        }
    }

    int money = 100; 

    for (int turn = 0; turn < numTurns; ++turn) {
        std::cout << "Turn " << turn + 1 << ":\n";

        for (auto& patient : patients) {
            std::cout << "Patient " << patient.name << " (Age: " << patient.age << ", Health: " << patient.health << ")\n";
            std::cout << "Disease: " << patient.disease << ", Region: " << patient.region << "\n";

            if (pharmacies[patient.region] != nullptr) {
                std::cout << "Available medicines:\n";
                for (int i = 0; i < 8; ++i) {
                    if (pharmacies[patient.region]->hasMedicine(static_cast<MedicineType>(i))) {
                        int price = pharmacies[patient.region]->getPrice(static_cast<MedicineType>(i));
                        std::cout << i << ": Medicine " << i << " (Price: " << price << ")\n";
                    }
                }

                int choice;
                std::cout << "Choose a medicine for the patient (enter the number): ";
                std::cin >> choice;

                if (pharmacies[patient.region]->hasMedicine(static_cast<MedicineType>(choice))) {
                    Medicine med = pharmacies[patient.region]->getMedicine(static_cast<MedicineType>(choice));
                    if (money >= med.price) {
                        money -= med.price;
                        patient.health += med.effect;
                        std::cout << "Patient treated. Health is now " << patient.health << "\n";
                    }
                    else {
                        std::cout << "Not enough money for this medicine.\n";
                    }
                }
                else {
                    std::cout << "Invalid choice.\n";
                }
            }
            else {
                std::cout << "No pharmacy in this region.\n";
            }
        }

        for (auto& patient : patients) {
            updatePatient(patient);
            if (patient.health <= 0) {
                std::cout << "Patient " << patient.name << " has died.\n";
                return 0;
            }
        }
    }

    std::cout << "End of the game. All patients survived!\n";
    return 0;
}
#endif

#ifdef ver2
const std::vector<std::string> names = { "John", "Jane", "Alice", "Bob", "Charlie" };
const std::vector<std::string> surnames = { "Doe", "Smith", "Johnson", "Williams", "Brown" };

enum DiseaseType { FLU, COLD, COVID, ALLERGY };

enum MedicineType { STRONG_FLU_MEDICINE, WEAK_FLU_MEDICINE, STRONG_COLD_MEDICINE, WEAK_COLD_MEDICINE, STRONG_COVID_MEDICINE, WEAK_COVID_MEDICINE, STRONG_ALLERGY_MEDICINE, WEAK_ALLERGY_MEDICINE };

struct Patient {
    std::string name;
    int age;
    DiseaseType disease;
    int region;
    int health;
};

struct Medicine {
    MedicineType type;
    int price;
    int effect;
};

class Pharmacy {
public:
    virtual ~Pharmacy() {}
    virtual bool hasMedicine(MedicineType type) const = 0;
    virtual int getPrice(MedicineType type) const = 0;
    virtual Medicine getMedicine(MedicineType type) = 0;
};

class ConcretePharmacy : public Pharmacy {
    std::vector<Medicine> medicines;

public:
    ConcretePharmacy(std::vector<Medicine> meds) : medicines(meds) {}

    bool hasMedicine(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return true;
            }
        }
        return false;
    }

    int getPrice(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return med.price;
            }
        }
        return -1; 
    }

    Medicine getMedicine(MedicineType type) override {
        for (auto it = medicines.begin(); it != medicines.end(); ++it) {
            if (it->type == type) {
                Medicine med = *it;
                medicines.erase(it);
                return med;
            }
        }
        return { type, -1, 0 }; 
    }
};

Patient generateRandomPatient(int maxRegion) {
    Patient patient;
    patient.name = names[rand() % names.size()] + " " + surnames[rand() % surnames.size()];
    patient.age = rand() % 50 + 10; 
    patient.disease = static_cast<DiseaseType>(rand() % 4);
    patient.region = rand() % maxRegion;
    patient.health = rand() % 21 + 80; 
    return patient;
}

Pharmacy* generateRandomPharmacy() {
    std::vector<Medicine> meds;
    for (int i = 0; i < 2; ++i) {
        MedicineType type = static_cast<MedicineType>(rand() % 8);
        int price = rand() % 50 + 10; 
        int effect = (type % 2 == 0) ? 30 : 15; 
        meds.push_back({ type, price, effect });
    }
    return new ConcretePharmacy(meds);
}

void updatePatient(Patient& patient) {
    int damage = 0;
    switch (patient.disease) {
    case FLU:
        damage = (patient.age > 40) ? 15 : 10;
        break;
    case COLD:
        damage = (patient.age > 40) ? 10 : 5;
        break;
    case COVID:
        damage = (patient.age > 40) ? 20 : 15;
        break;
    case ALLERGY:
        damage = (patient.age > 40) ? 5 : 3;
        break;
    }
    patient.health -= damage;
}

int calculatePrice(int basePrice, int distance) {
    return basePrice + distance * 10; 
}

void showAvailableMedicines(const std::vector<Pharmacy*>& pharmacies, const Patient& patient) {
    const int numRegions = pharmacies.size();
    std::cout << "Available medicines:\n";
    for (int region = 1; region < numRegions; ++region) {
        if (pharmacies[region] != nullptr) {
            for (int i = 0; i < 8; ++i) {
                if (pharmacies[region]->hasMedicine(static_cast<MedicineType>(i))) {
                    int basePrice = pharmacies[region]->getPrice(static_cast<MedicineType>(i));
                    int distance = std::abs(patient.region - region);
                    int finalPrice = calculatePrice(basePrice, distance);
                    std::cout << "Region " << region << " - Medicine " << i << " (Price: " << finalPrice << "$)\n";
                }
            }
        }
    }
}

void asking() {
    std::string ask;
    while (ask != ".start") {
        std::cin >> ask;
        if (ask == ".info") {
            std::cout << "Hello doctor.\n"; Sleep(1200);
            std::cout << "Congratulations on joining the position of remote consultant.\n"; Sleep(1800);
            std::cout << "I am your supervisor, "; Sleep(1200);
            std::cout << "from this day, until the end of the month, I will instruct you and also make sure that you do your work efficiently.\n"; Sleep(2400);
            std::cout << "As you should already know, your job is to use this terminal to monitor the condition of the patients who will be provided to you.\n"; Sleep(2400);
            std::cout << "Depending on the situation and their condition, you will need to provide them with medicine, "; Sleep(1800);
            std::cout << "I hope I don't need to clarify that you need to keep them alive, "; Sleep(1800);
            std::cout << "under any circumstances.\n"; Sleep(1800);
            std::cout << "I cannot know which patients will be given to you, but I know for sure that our services are available only in the Region.\n"; Sleep(2400);
            std::cout << "While working, do not forget that the Region is divided into 5 districts, and the price of delivering medicines from district to district can vary, both for the better and for the worse.\n"; Sleep(3000);
            std::cout << "Well, then I think you'll figure it out on your own, "; Sleep(1800);
            std::cout << "we'll see your results in a month...\n"; Sleep(1800);
            std::cout << "Good luck,"; Sleep(1800); std::cout << " Doctor.\n"; Sleep(2400);
        }
        else if (ask == ".start") {
            Sleep(3000);
            std::cout << "\n";
            break;
        }
        else {
            std::cout << "Invalid input.\n";
        }
    }
}

int main() {

    std::cout << "Welcome to Project Medicine. \n" << "- For context, type \".info\"\n" << "- To start your shift, type \".start\"\n";

    asking();

    srand(static_cast<unsigned int>(time(0)));

    const int numRegions = 5;
    const int numPatients = 3;
    const int numTurns = 5;

    std::vector<Patient> patients;
    for (int i = 0; i < numPatients; ++i) {
        patients.push_back(generateRandomPatient(numRegions));
    }

    std::vector<Pharmacy*> pharmacies(numRegions);
    int noPharmacyRegion = rand() % numRegions;
    for (int i = 0; i < numRegions; ++i) {
        if (i != noPharmacyRegion) {
            pharmacies[i] = generateRandomPharmacy();
        }
        else {
            pharmacies[i] = nullptr;
        }
    }

    int money = 100;

    for (int turn = 0; turn < numTurns; ++turn) {
        std::cout << "Week " << turn + 1 << ":\n" << "You have: " << money << "$\n\n";

        for (auto& patient : patients) {
            std::cout << "Patient " << patient.name << " (Age: " << patient.age << ", Health: " << patient.health << ")\n";
            std::cout << "Disease: " << DiseaseType{ patient.disease } << ", Region: " << patient.region << "\n";

            showAvailableMedicines(pharmacies, patient);

            int choice, chosenRegion;
            std::cout << "Choose a region and a medicine for the patient (enter region number and medicine number): ";
            std::cin >> chosenRegion >> choice;

            if (chosenRegion >= 0 && chosenRegion < numRegions && pharmacies[chosenRegion] != nullptr && pharmacies[chosenRegion]->hasMedicine(static_cast<MedicineType>(choice))) {
                int distance = std::abs(patient.region - chosenRegion);
                int basePrice = pharmacies[chosenRegion]->getPrice(static_cast<MedicineType>(choice));
                int finalPrice = calculatePrice(basePrice, distance);
                if (money >= finalPrice) {
                    Medicine med = pharmacies[chosenRegion]->getMedicine(static_cast<MedicineType>(choice));
                    money -= finalPrice;
                    patient.health += med.effect;
                    std::cout << "Medicine is delivered. Pacient's health is now " << patient.health << "\n\n";
                    money += med.effect / 2 + 10;
                }
                else {
                    std::cout << "Not enough money for this medicine.\n\n";
                }
            }
            else {
                std::cout << "Invalid choice.\n\n";
            }
        }

        for (auto& patient : patients) {
            updatePatient(patient);
            if (patient.health <= 0) {
                std::cout << "Patient " << patient.name << " has died.\n";
                return 0;
            }
        }
    }

    std::cout << "End of the game. All patients survived!\n";
    return 0;
}

#endif

#ifdef ver3
const std::vector<std::string> names = { "John", "Jane", "Alice", "Bob", "Charlie" };
const std::vector<std::string> surnames = { "Cklab", "Gery", "Bule", "Whiet", "Brownie" };

enum DiseaseType { FLU, COLD, COVID, ALLERGY };

enum MedicineType { STRONG_FLU_MEDICINE, WEAK_FLU_MEDICINE, STRONG_COLD_MEDICINE, WEAK_COLD_MEDICINE, STRONG_COVID_MEDICINE, WEAK_COVID_MEDICINE, STRONG_ALLERGY_MEDICINE, WEAK_ALLERGY_MEDICINE };

struct Patient {
    std::string name;
    int age;
    DiseaseType disease;
    int region;
    int health;
};

struct Medicine {
    MedicineType type;
    int price;
    int effect;
};

class Pharmacy {
public:
    virtual ~Pharmacy() {}
    virtual bool hasMedicine(MedicineType type) const = 0;
    virtual int getPrice(MedicineType type) const = 0;
    virtual Medicine getMedicine(MedicineType type) = 0;
};

class ConcretePharmacy : public Pharmacy {
    std::vector<Medicine> medicines;

public:
    ConcretePharmacy(std::vector<Medicine> meds) : medicines(meds) {}

    bool hasMedicine(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return true;
            }
        }
        return false;
    }

    int getPrice(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return med.price;
            }
        }
        return -1; 
    }

    Medicine getMedicine(MedicineType type) override {
        for (auto it = medicines.begin(); it != medicines.end(); ++it) {
            if (it->type == type) {
                Medicine med = *it;
                medicines.erase(it);
                return med;
            }
        }
        return { type, -1, 0 }; 
    }
};

Patient generateRandomPatient(int maxRegion) {
    Patient patient;
    patient.name = names[rand() % names.size()] + " " + surnames[rand() % surnames.size()];
    patient.age = rand() % 50 + 10; 
    patient.disease = static_cast<DiseaseType>(rand() % 4);
    patient.region = rand() % maxRegion;
    patient.health = rand() % 21 + 80; 
    return patient;
}

Pharmacy* generateRandomPharmacy() {
    std::vector<Medicine> meds;
    for (int i = 0; i < 2; ++i) {
        MedicineType type = static_cast<MedicineType>(rand() % 8);
        int price = rand() % 50 + 10; 
        int effect = (type % 2 == 0) ? 15 : 10; 
        meds.push_back({ type, price, effect });
    }
    return new ConcretePharmacy(meds);
}

void updatePatient(Patient& patient) {
    int damage = 0;
    switch (patient.disease) {
    case FLU:
        damage = (patient.age > 50) ? 27 : 11;
        break;
    case COLD:
        damage = (patient.age > 40) ? 19 : 5;
        break;
    case COVID:
        damage = (patient.age > 30) ? 29 : 12;
        break;
    case ALLERGY:
        damage = (patient.age > 20) ? 18 : 3;
        break;
    }
    patient.health -= damage;
}

int calculatePrice(int basePrice, int distance) {
    return basePrice + distance * 10; 
}

std::string getDiseaseName(DiseaseType disease) {
    switch (disease) {
    case FLU: return "Flu";
    case COLD: return "Cold";
    case COVID: return "COVID-19";
    case ALLERGY: return "Allergy";
    default: return "Unknown";
    }
}

std::string getMedicineName(MedicineType type) {
    switch (type) {
    case STRONG_FLU_MEDICINE: return "Strong Flu Medicine";
    case WEAK_FLU_MEDICINE: return "Weak Flu Medicine";
    case STRONG_COLD_MEDICINE: return "Strong Cold Medicine";
    case WEAK_COLD_MEDICINE: return "Weak Cold Medicine";
    case STRONG_COVID_MEDICINE: return "Strong COVID Medicine";
    case WEAK_COVID_MEDICINE: return "Weak COVID Medicine";
    case STRONG_ALLERGY_MEDICINE: return "Strong Allergy Medicine";
    case WEAK_ALLERGY_MEDICINE: return "Weak Allergy Medicine";
    default: return "Unknown";
    }
}

void showAvailableMedicines(const std::vector<Pharmacy*>& pharmacies, const Patient& patient) {
    const int numRegions = pharmacies.size();
    std::cout << "Available medicines:\n";
    for (int region = 0; region < numRegions; ++region) {
        if (pharmacies[region] != nullptr) {
            for (int i = 0; i < 8; ++i) {
                if (pharmacies[region]->hasMedicine(static_cast<MedicineType>(i))) {
                    int basePrice = pharmacies[region]->getPrice(static_cast<MedicineType>(i));
                    int distance = std::abs(patient.region - region);
                    int finalPrice = calculatePrice(basePrice, distance);
                    std::cout << "District " << region << " - #" << i << " " << getMedicineName(static_cast<MedicineType>(i)) << " (Price: " << finalPrice << "$)\n";
                }
            }
        }
    }
}

void asking() {
    std::string ask;
    while (ask != ".start") {
        std::cin >> ask;
        if (ask == ".info") {
            std::cout << "Hello doctor.\n"; Sleep(1200);
            std::cout << "Congratulations on joining the position of remote consultant.\n"; Sleep(1800);
            std::cout << "I am your supervisor, "; Sleep(1200);
            std::cout << "from this day, until the end of the month, I will instruct you and also make sure that you do your work efficiently.\n"; Sleep(2400);
            std::cout << "As you should already know, your job is to use this terminal to monitor the condition of the patients who will be provided to you.\n"; Sleep(2400);
            std::cout << "Depending on the situation and their condition, you will need to provide them with medicine, "; Sleep(1800);
            std::cout << "I hope I don't need to clarify that you need to keep them alive, "; Sleep(1800);
            std::cout << "under any circumstances.\n"; Sleep(1800);
            std::cout << "I cannot know which patients will be given to you, but I know for sure that our services are available only in the Region.\n"; Sleep(2400);
            std::cout << "While working, do not forget that the Region is divided into 5 districts, and the price of delivering medicines from district to district can vary, both for the better and for the worse.\n"; Sleep(3000);
            std::cout << "Well, then I think you'll figure it out on your own, "; Sleep(1800);
            std::cout << "we'll see your results in a month...\n"; Sleep(1800);
            std::cout << "Good luck,"; Sleep(1800); std::cout << " Doctor.\n"; Sleep(2400);
        }
        else if (ask == ".start") {
            Sleep(3000);
            std::cout << "\n";
            break;
        }
        else {
            std::cout << "Invalid input.\n";
        }
    }
}

int main() {

    std::cout << "Welcome to Project Medicine. \n" << "- For context, type \".info\"\n" << "- To start your shift, type \".start\"\n";

    asking();

    srand(static_cast<unsigned int>(time(0)));

    const int numRegions = 5;
    const int numPatients = 3;
    const int numTurns = 5;

    std::vector<Patient> patients;
    for (int i = 0; i < numPatients; ++i) {
        patients.push_back(generateRandomPatient(numRegions));
    }

    std::vector<Pharmacy*> pharmacies(numRegions);
    int noPharmacyRegion = rand() % numRegions;
    for (int i = 0; i < numRegions; ++i) {
        if (i != noPharmacyRegion) {
            pharmacies[i] = generateRandomPharmacy();
        }
        else {
            pharmacies[i] = nullptr; 
        }
    }

    int money = 100; 

    for (int turn = 0; turn < numTurns; ++turn) {
        std::cout << "Week " << turn + 1 << ":\n" << "You have: " << money << "$\n\n";

        for (auto& patient : patients) {
            std::cout << "Patient " << patient.name << " (Age: " << patient.age << ", Health: " << patient.health << ")\n";
            std::cout << "Disease: " << getDiseaseName(patient.disease) << ", District: " << patient.region << "\n";

            showAvailableMedicines(pharmacies, patient);

            int choice, chosenRegion;
            std::cout << "Choose a region and a medicine for the patient (enter region number and medicine number): ";
            std::cin >> chosenRegion >> choice;

            if (chosenRegion >= 0 && chosenRegion < numRegions && pharmacies[chosenRegion] != nullptr && pharmacies[chosenRegion]->hasMedicine(static_cast<MedicineType>(choice))) {
                int distance = std::abs(patient.region - chosenRegion);
                int basePrice = pharmacies[chosenRegion]->getPrice(static_cast<MedicineType>(choice));
                int finalPrice = calculatePrice(basePrice, distance);
                if (money >= finalPrice) {
                    Medicine med = pharmacies[chosenRegion]->getMedicine(static_cast<MedicineType>(choice));
                    money -= finalPrice;
                    patient.health += med.effect;
                    std::cout << getMedicineName(med.type) << " was delivered to pacient. Health is now " << patient.health << "\n\n";
                    money += med.effect / 2 & + 10;
                }
                else {
                    std::cout << "Not enough money for this medicine.\n\n";
                }
            }
            else {
                std::cout << "Invalid choice.\n\n";
            }
        }

        for (auto& patient : patients) {
            updatePatient(patient);
            if (patient.health <= 0) {
                std::cout << "Patient " << patient.name << " has died.\n\n";
                return 0;
            }
        }
    }
    std::cout << "End of the game. All patients survived!\n";
    return 0;
}

#endif

#ifdef ver_fin
const std::vector<std::string> names = { "John", "Jane", "Alice", "Bob", "Charlie" };
const std::vector<std::string> surnames = { "Cklab", "Gery", "Bule", "Whiet", "Brownie" };

enum DiseaseType { FLU, COLD, COVID, ALLERGY };

enum MedicineType { STRONG_FLU_MEDICINE, WEAK_FLU_MEDICINE, STRONG_COLD_MEDICINE, WEAK_COLD_MEDICINE, STRONG_COVID_MEDICINE, WEAK_COVID_MEDICINE, STRONG_ALLERGY_MEDICINE, WEAK_ALLERGY_MEDICINE };

struct Patient {
    std::string name;
    int age;
    DiseaseType disease;
    int region;
    int health;
};

struct Medicine {
    MedicineType type;
    int price;
    int effect;
    DiseaseType effectiveAgainst;
};

class Pharmacy {
public:
    virtual ~Pharmacy() {}
    virtual bool hasMedicine(MedicineType type) const = 0;
    virtual int getPrice(MedicineType type) const = 0;
    virtual Medicine getMedicine(MedicineType type) = 0;
};

class ConcretePharmacy : public Pharmacy {
    std::vector<Medicine> medicines;

public:
    ConcretePharmacy(std::vector<Medicine> meds) : medicines(meds) {}

    bool hasMedicine(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return true;
            }
        }
        return false;
    }

    int getPrice(MedicineType type) const override {
        for (const auto& med : medicines) {
            if (med.type == type) {
                return med.price;
            }
        }
        return -1; 
    }

    Medicine getMedicine(MedicineType type) override {
        for (auto it = medicines.begin(); it != medicines.end(); ++it) {
            if (it->type == type) {
                Medicine med = *it;
                medicines.erase(it);
                return med;
            }
        }
        return { type, -1, 0, FLU }; 
    }
};

Patient generateRandomPatient(int maxRegion) {
    Patient patient;
    patient.name = names[rand() % names.size()] + " " + surnames[rand() % surnames.size()];
    patient.age = rand() % 50 + 10; 
    patient.disease = static_cast<DiseaseType>(rand() % 4);
    patient.region = rand() % maxRegion;
    patient.health = rand() % 21 + 80; 
    return patient;
}

Pharmacy* generateRandomPharmacy() {
    std::vector<Medicine> meds;
    for (int i = 0; i < 2; ++i) {
        MedicineType type = static_cast<MedicineType>(rand() % 8);
        int price = rand() % 50 + 10; 
        int effect = (type % 2 == 0) ? 30 : 15; 
        DiseaseType effectiveAgainst;
        switch (type) {
        case STRONG_FLU_MEDICINE:
        case WEAK_FLU_MEDICINE:
            effectiveAgainst = FLU;
            break;
        case STRONG_COLD_MEDICINE:
        case WEAK_COLD_MEDICINE:
            effectiveAgainst = COLD;
            break;
        case STRONG_COVID_MEDICINE:
        case WEAK_COVID_MEDICINE:
            effectiveAgainst = COVID;
            break;
        case STRONG_ALLERGY_MEDICINE:
        case WEAK_ALLERGY_MEDICINE:
            effectiveAgainst = ALLERGY;
            break;
        }
        meds.push_back({ type, price, effect, effectiveAgainst });
    }
    return new ConcretePharmacy(meds);
}

void updatePatient(Patient& patient) {
    int damage = 0;
    switch (patient.disease) {
    case FLU:
        damage = (patient.age > 50) ? 27 : 11;
        break;
    case COLD:
        damage = (patient.age > 40) ? 19 : 5;
        break;
    case COVID:
        damage = (patient.age > 30) ? 29 : 12;
        break;
    case ALLERGY:
        damage = (patient.age > 20) ? 18 : 3;
        break;
    }
    patient.health -= damage;
}

int calculatePrice(int basePrice, int distance) {
    return basePrice + distance * 10; 
}

std::string getDiseaseName(DiseaseType disease) {
    switch (disease) {
    case FLU: return "Flu";
    case COLD: return "Cold";
    case COVID: return "COVID-19";
    case ALLERGY: return "Allergy";
    default: return "Unknown";
    }
}

std::string getMedicineName(MedicineType type) {
    switch (type) {
    case STRONG_FLU_MEDICINE: return "Strong Flu Medicine";
    case WEAK_FLU_MEDICINE: return "Weak Flu Medicine";
    case STRONG_COLD_MEDICINE: return "Strong Cold Medicine";
    case WEAK_COLD_MEDICINE: return "Weak Cold Medicine";
    case STRONG_COVID_MEDICINE: return "Strong COVID Medicine";
    case WEAK_COVID_MEDICINE: return "Weak COVID Medicine";
    case STRONG_ALLERGY_MEDICINE: return "Strong Allergy Medicine";
    case WEAK_ALLERGY_MEDICINE: return "Weak Allergy Medicine";
    default: return "Unknown";
    }
}

void showAvailableMedicines(const std::vector<Pharmacy*>& pharmacies, const Patient& patient) {
    const int numRegions = pharmacies.size();
    std::cout << "Available medicines:\n";
    for (int region = 0; region < numRegions; ++region) {
        if (pharmacies[region] != nullptr) {
            for (int i = 0; i < 8; ++i) {
                if (pharmacies[region]->hasMedicine(static_cast<MedicineType>(i))) {
                    int basePrice = pharmacies[region]->getPrice(static_cast<MedicineType>(i));
                    int distance = std::abs(patient.region - region);
                    int finalPrice = calculatePrice(basePrice, distance);
                    std::cout << "District " << region << " - #" << i << " " << getMedicineName(static_cast<MedicineType>(i)) << " (Price: " << finalPrice << "$)\n";
                }
            }
        }
    }
}

void handleInvalidInput() {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

void asking() {
    std::string ask;
    while (ask != ".start") {
        std::cin >> ask;
        if (ask == ".info") {
            std::cout << "Hello doctor.\n"; Sleep(1200);
            std::cout << "Congratulations on joining the position of remote consultant.\n"; Sleep(1800);
            std::cout << "I am your supervisor, "; Sleep(1200);
            std::cout << "from this day, until the end of the month, I will instruct you and also make sure that you do your work efficiently.\n"; Sleep(2400);
            std::cout << "As you should already know, your job is to use this terminal to monitor the condition of the patients who will be provided to you.\n"; Sleep(2400);
            std::cout << "Depending on the situation and their condition, you will need to provide them with medicine, "; Sleep(1800);
            std::cout << "I hope I don't need to clarify that you need to keep them alive, "; Sleep(1800);
            std::cout << "under any circumstances.\n"; Sleep(1800);
            std::cout << "I cannot know which patients will be given to you, but I know for sure that our services are available only in the Region.\n"; Sleep(2400);
            std::cout << "While working, do not forget that the Region is divided into 5 districts, and the price of delivering medicines from district to district can vary, both for the better and for the worse.\n"; Sleep(3000);
            std::cout << "Well, then I think you'll figure it out on your own, "; Sleep(1800);
            std::cout << "we'll see your results in a month...\n"; Sleep(1800);
            std::cout << "Good luck,"; Sleep(1800); std::cout << " Doctor.\n"; Sleep(2400);
        }
        else if (ask == ".start") {
            Sleep(3000);
            std::cout << "\n";
            break;
        }
        else {
            std::cout << "Invalid input.\n";
        }
    }
}

int main() {

    std::cout << "Welcome to Project Medicine. \n" << "- For context, type \".info\"\n" << "- To start your shift, type \".start\"\n";

    asking();

    srand(static_cast<unsigned int>(time(0)));

    const int numRegions = 5;
    const int numPatients = 3;
    const int numTurns = 5;

    std::vector<Patient> patients;
    for (int i = 0; i < numPatients; ++i) {
        patients.push_back(generateRandomPatient(numRegions));
    }

    std::vector<Pharmacy*> pharmacies(numRegions);
    int noPharmacyRegion = rand() % numRegions;
    for (int i = 0; i < numRegions; ++i) {
        if (i != noPharmacyRegion) {
            pharmacies[i] = generateRandomPharmacy();
        }
        else {
            pharmacies[i] = nullptr; 
        }
    }

    int money = 125; 

    for (int turn = 0; turn < numTurns; ++turn) {
        std::cout << "Week " << turn + 1 << ":\n" << "You have: " << money << "$\n\n";

        for (auto& patient : patients) {
            std::cout << "Patient " << patient.name << " (Age: " << patient.age << ", Health: " << patient.health << ")\n";
            std::cout << "Disease: " << getDiseaseName(patient.disease) << ", District: " << patient.region << "\n";

            showAvailableMedicines(pharmacies, patient);

            int choice, chosenRegion;
            std::cout << "Choose a district and a medicine for the patient (enter district number and medicine number): ";
            if (!(std::cin >> chosenRegion >> choice)) {
                handleInvalidInput();
                std::cout << "Invalid input, please enter numeric values.\n\n";
                continue;
            }

            if (chosenRegion >= 0 && chosenRegion < numRegions && pharmacies[chosenRegion] != nullptr && pharmacies[chosenRegion]->hasMedicine(static_cast<MedicineType>(choice))) {
                int distance = std::abs(patient.region - chosenRegion);
                int basePrice = pharmacies[chosenRegion]->getPrice(static_cast<MedicineType>(choice));
                int finalPrice = calculatePrice(basePrice, distance);
                if (money >= finalPrice) {
                    Medicine med = pharmacies[chosenRegion]->getMedicine(static_cast<MedicineType>(choice));
                    money -= finalPrice;
                    if (med.effectiveAgainst == patient.disease) {
                        patient.health += med.effect;
                    }
                    else {
                        patient.health += med.effect / 2; 
                    }
                    std::cout << getMedicineName(med.type) << " was delivered to pacient. Health is now " << patient.health << "\n\n";
                    money += med.effect / 2;
                }
                else {
                    std::cout << "Not enough money for this medicine.\n\n";
                }
            }
            else {
                std::cout << "Invalid region or medicine choice.\n\n";
            }
            std::cout << "Remaining money: " << money << "$\n\n";
        }

        money += 15;

        for (auto& patient : patients) {
            updatePatient(patient);
            if (patient.health <= 0) {
                std::cout << "Patient " << patient.name << " has died.\nYour shift was failed.\n"; Sleep(1200);
                std::cout << "Pleas wait for the corporation to take action on your fail. Have a good day.\n";
                return 0;
            }
        }
    }

    std::cout << "Your shift is over! After your shift patient states are:\n";
    for (const auto& patient : patients) {
        std::cout << "Patient " << patient.name << " (Age: " << patient.age << ", Disease: " << getDiseaseName(patient.disease) << ", District: " << patient.region << ")" << " - ALIVE.\n";
    }

    for (auto pharmacy : pharmacies) {
        delete pharmacy;
    }

    return 0;
}

#endif