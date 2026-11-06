#include <iostream>
#include <fstream>
using namespace std;

class Date {
public:
    int year;
    int month;
    int day;
    int oil_count;
    Date() : year(0), month(0), day(0), oil_count(0) {}
    Date(int year, int month, int day, int oil_count) {
        this->day = day;
        this->month = month;
        this->year = year;
        this->oil_count = oil_count;
    }

    void print() {
        cout << year << "/" << month << "/" << day << "\n";
    }

    bool equal(Date date) {
        if (year == date.year && month == date.month && day == date.day) {
            return true;
        }
        return false;
    }
};

class Oil {
public:
    string title;
    int volume;
    int max_volume;
    Date* supply_dates;
    Date* shipment_dates;
    int supply_size;
    int shipment_size;

    Oil()
        : title(""),
        volume(0),
        max_volume(50000),
        supply_dates(nullptr),
        shipment_dates(nullptr),
        supply_size(0),
        shipment_size(0) {
    }

    Oil(string title, int volume, int max_volume)
        : title(title),
        volume(volume),
        max_volume(max_volume),
        supply_dates(nullptr),
        shipment_dates(nullptr),
        supply_size(0),
        shipment_size(0) {
    }

    void add_to_supply_dates(Date supply_date) {
        Date* p = new Date[supply_size + 1];

        for (int i = 0; i < supply_size; i++) {
            p[i] = supply_dates[i];
        }

        p[supply_size] = supply_date;
        delete[] supply_dates;
        supply_dates = p;
        supply_size++;
    }

    void add_to_shipment_dates(Date shipment_date) {
        Date* p = new Date[shipment_size + 1];

        for (int i = 0; i < shipment_size; i++) {
            p[i] = shipment_dates[i];
        }

        p[shipment_size] = shipment_date;
        delete[] shipment_dates;
        shipment_dates = p;
        shipment_size++;
    }

    void print_supply_dates() {
        for (int i = 0; i < supply_size; i++) {
            supply_dates[i].print();
        }
    }

    void print_shipment_dates() {
        for (int i = 0; i < shipment_size; i++) {
            shipment_dates[i].print();
        }
    }

    int search_by_date(Date date) {
        for (int i = 0; i < shipment_size; i++) {
            if (shipment_dates[i].equal(date)) {
                return shipment_dates[i].oil_count;
            }
        }
        return -1;
    }
};

ostream& operator <<(ostream& out, const Oil& oil) {
    out << oil.title << " " << oil.volume << " " << oil.max_volume << "\n";
    out << oil.supply_size << "\n";
    for (int i = 0; i < oil.supply_size; i++) {
        const Date& date = oil.supply_dates[i];

        out << date.day << " " << date.month << " " << date.year << " " << date.oil_count << "\n";
    }
    out << oil.shipment_size << "\n";
    for (int i = 0; i < oil.shipment_size; i++) {
        const Date& date = oil.shipment_dates[i];

        out << date.day << " " << date.month << " " << date.year << " " << date.oil_count << "\n";
    }
    return out;
}

class Gas_station {
public:
    Oil A92;
    Oil A95;
    Oil A98;

    Gas_station()
        : A92("A92", 0, 50000),
        A95("A95", 0, 50000),
        A98("A98", 0, 50000) {
    }
    Gas_station(Oil A92, Oil A95, Oil A98) {
        this->A92 = A92;
        this->A95 = A95;
        this->A98 = A98;
    }
};

class Gas_station_for_passenger_car : public Gas_station {
public:
    Gas_station_for_passenger_car() : Gas_station(){}
};

class Gas_station_for_truck_car : public Gas_station {
public:
    Gas_station_for_truck_car() : Gas_station(){}
    
};

class chain_of_gas_station: public Gas_station, Gas_station_for_passenger_car, Gas_station_for_truck_car {
public:
    Gas_station* gas_stations;

    chain_of_gas_station(Gas_station* gas_stations) : gas_stations(gas_stations) {}

    void set_type_and_gas_station_for_delivery() {
        Date date;
        Oil type;
        Gas_station gas_station;
        int choice1;
        cout << "1 - Passenger car\n";
        cout << "2 - Truck\n";
        cout << "Enter car type for delivery: ";
        cin >> choice1;
        switch (choice1) {
        case 1:
            gas_station = gas_stations[0];
            break;
        case 2:
            gas_station = gas_stations[1];
            break;
        }

        int choice2;
        cout << "1 - A92\n";
        cout << "2 - A95\n";
        cout << "3 - A98\n";
        cout << "Enter type for delivery: ";
        cin >> choice2;
        switch (choice2) {
        case 1 :
            type = gas_station.A92;
            break;
        case 2:
            type = gas_station.A95;
            break;
        case 3:
            type = gas_station.A98;
            break;
        }

        cout << "How many liters you want to supply?: \n";
        cin >> date.oil_count;
        
        if (date.oil_count + type.volume <= type.max_volume) {
            cout << "Enter year of delivery: ";
            cin >> date.year;
            cout << "Enter month of delivery: ";
            cin >> date.month;
            cout << "Enter day of delivery: ";
            cin >> date.day;
            type.add_to_supply_dates(date);
            type.volume += date.oil_count;
        }
        else {
            cout << "To much oil";
        }
    }

    void set_type_and_gas_station_for_shipment() {
        Date date;
        Oil type;
        Gas_station gas_station;
        int choice1;
        cout << "1 - Passenger car\n";
        cout << "2 - Truck\n";
        cout << "Enter car type for shipment: ";
        cin >> choice1;
        switch (choice1) {
        case 1:
            gas_station = gas_stations[0];
            break;
        case 2:
            gas_station = gas_stations[1];
            break;
        }

        int choice2;
        cout << "1 - A92\n";
        cout << "2 - A95\n";
        cout << "3 - A98\n";
        cout << "Enter type for shipment: ";
        cin >> choice2;
        switch (choice2) {
        case 1:
            type = gas_station.A92;
            break;
        case 2:
            type = gas_station.A95;
            break;
        case 3:
            type = gas_station.A98;
            break;
        }

        cout << "How many liters you want to ship?: \n";
        cin >> date.oil_count;

        if (type.volume - date.oil_count >= 0) {

            cout << "Enter year of shipment: ";
            cin >> date.year;
            cout << "Enter month of shipment: ";
            cin >> date.month;
            cout << "Enter day of shipment: ";
            cin >> date.day;
            type.add_to_shipment_dates(date);
            type.volume -= date.oil_count;
        }
        else {
            cout << "You havent got oil";
        }
    }


    void print_statics_for_gas_station() {
        Gas_station gas_station;
        int choice;
        cout << "Select gas_station: \n";
        cout << "1 - Gas station for cars\n";
        cout << "2 - Gas station for trucks\n";
        cin >> choice;
        switch (choice) {
        case 1:
            gas_station = gas_stations[0];
            break;
        case 2:
            gas_station = gas_stations[1];
            break;
        }

        cout << "count of A92: " << gas_station.A92.volume << "\n";
        gas_station.A92.print_shipment_dates();
        cout << "count of A95: " << gas_station.A95.volume << "\n";
        gas_station.A95.print_shipment_dates();
        cout << "count of A98: " << gas_station.A98.volume << "\n";
        gas_station.A98.print_shipment_dates();
    }


    void print_report() {
        Date date;
        cout << "Enter year of shipment: ";
        cin >> date.year;
        cout << "Enter month of shipment: ";
        cin >> date.month;
        cout << "Enter day of shipment: ";
        cin >> date.day;

        int* max_shipments = new int [2] {0, 0};

        for (int i = 0; i < 2; i++) {
            Gas_station gas_station = gas_stations[i];
            int shipment_oil1 = gas_station.A92.search_by_date(date);
            int shipment_oil2 = gas_station.A95.search_by_date(date);
            int shipment_oil3 = gas_station.A98.search_by_date(date);
            cout << "Shipment oil A92" << shipment_oil1 << "\n" << "Shipment oil A95" << shipment_oil2 << "\n" << "Shipment_oil A98" << shipment_oil3 << "\n";
            int max_shipment = shipment_oil1;
            if (max_shipment < shipment_oil2) {
                max_shipment = shipment_oil2;
            }

            if (max_shipment < shipment_oil3) {
                max_shipment = shipment_oil3;
            }

            max_shipments[i] = max_shipment;
        }

        if (max_shipments[0] > max_shipments[1]) {
            cout << "Max shipment: " << max_shipments[0];
        }
        else {
            cout << "Max shipment: " << max_shipments[1];
        }
    }

    void save() {
        ofstream data("Data.txt");
        if (!data.is_open()) {
            cout << "Error 404\n";
        }
        
        data << 2;

        for (int i = 0; i < 2; i++) {
            data << gas_stations[i].A92 << " " << gas_stations[i].A95 << " " << gas_stations[i].A98 << "\n";
        }

        data.close();
    }
};



int menu() {
    int choice;
    cout << "0 - Exit\n";
    cout << "1 - Supply\n";
    cout << "2 - Shipment\n";
    cout << "3 - Print Stat\n";
    cout << "4 - Print report\n";
    cout << "5 - Save\n";
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

int main()
{
    int zaglushka;
    bool is_running = true;

    Gas_station* gas_stations = new Gas_station[2]{
        Gas_station_for_passenger_car(),
        Gas_station_for_truck_car()
    };

    chain_of_gas_station chain = chain_of_gas_station(gas_stations);

    do {
        system("cls");
        int choice = menu();

        switch (choice) {
        case 0:
            is_running = false;
            break;
        case 1:
            chain.set_type_and_gas_station_for_delivery();
            break;
        case 2:
            chain.set_type_and_gas_station_for_shipment();
            break;
        case 3:
            chain.print_statics_for_gas_station();
            cin >> zaglushka;
            break;
        case 4:
            chain.print_report();
            cin >> zaglushka;
            break;
        case 5:
            chain.save();
            break;
        }
    } while (is_running);
}