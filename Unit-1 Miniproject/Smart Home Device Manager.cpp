#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Base class for all smart devices
class SmartDevice
{
protected:
    string deviceID;
    string location;
    string status;
    string lastUpdated;

public:
    // Constructor
    SmartDevice(string id, string loc)
    {
        deviceID = id;
        location = loc;
        status = "OFF";
        updateTime();
    }

    // Function to get current time
    void updateTime()
    {
        time_t now = time(0);
        lastUpdated = ctime(&now);

        // Remove newline character
        if (!lastUpdated.empty() && lastUpdated.back() == '\n')
            lastUpdated.pop_back();
    }

    // Switch device ON
    virtual void turnOn()
    {
        status = "ON";
        updateTime();
        cout << deviceID << " is now ON.\n";
    }

    // Switch device OFF
    virtual void turnOff()
    {
        status = "OFF";
        updateTime();
        cout << deviceID << " is now OFF.\n";
    }

    // Change device status
    void changeStatus(string newStatus)
    {
        status = newStatus;
        updateTime();
        cout << "Status changed successfully.\n";
    }

    // Display device information
    virtual void display()
    {
        cout << "\nDevice ID    : " << deviceID;
        cout << "\nLocation     : " << location;
        cout << "\nStatus       : " << status;
        cout << "\nLast Updated : " << lastUpdated << endl;
    }

    string getStatus()
    {
        return status;
    }

    string getID()
    {
        return deviceID;
    }
};


// Light class
class Light : public SmartDevice
{
private:
    int brightness;

public:
    Light(string id, string loc) : SmartDevice(id, loc)
    {
        brightness = 50;
    }

    void setBrightness(int value)
    {
        if (value >= 0 && value <= 100)
        {
            brightness = value;
            updateTime();
            cout << "Brightness changed to " << brightness << "%.\n";
        }
        else
        {
            cout << "Invalid brightness value!\n";
        }
    }

    void display() override
    {
        cout << "\n--- LIGHT ---";
        SmartDevice::display();
        cout << "Brightness   : " << brightness << "%" << endl;
    }
};


// Thermostat class
class Thermostat : public SmartDevice
{
private:
    float temperature;

public:
    Thermostat(string id, string loc) : SmartDevice(id, loc)
    {
        temperature = 24.0;
    }

    void setTemperature(float temp)
    {
        temperature = temp;
        updateTime();
        cout << "Temperature set to " << temperature << " C.\n";
    }

    void display() override
    {
        cout << "\n--- THERMOSTAT ---";
        SmartDevice::display();
        cout << "Temperature  : " << temperature << " C" << endl;
    }
};


// Camera class
class Camera : public SmartDevice
{
public:
    Camera(string id, string loc) : SmartDevice(id, loc)
    {
    }

    void display() override
    {
        cout << "\n--- CAMERA ---";
        SmartDevice::display();
    }
};


// Door Lock class
class DoorLock : public SmartDevice
{
public:
    DoorLock(string id, string loc) : SmartDevice(id, loc)
    {
    }

    void lockDoor()
    {
        status = "LOCKED";
        updateTime();
        cout << "Door is LOCKED.\n";
    }

    void unlockDoor()
    {
        status = "UNLOCKED";
        updateTime();
        cout << "Door is UNLOCKED.\n";
    }

    void display() override
    {
        cout << "\n--- DOOR LOCK ---";
        SmartDevice::display();
    }
};


// Main function
int main()
{
    vector<SmartDevice*> devices;

    // Creating devices
    Light light1("L001", "Living Room");
    Light light2("L002", "Bedroom");

    Thermostat thermostat1("T001", "Hall");

    Camera camera1("C001", "Main Door");

    DoorLock door1("D001", "Main Door");

    // Adding devices to vector
    devices.push_back(&light1);
    devices.push_back(&light2);
    devices.push_back(&thermostat1);
    devices.push_back(&camera1);
    devices.push_back(&door1);

    int choice;

    do
    {
        cout << "\n\n================================";
        cout << "\n     SMART HOME DEVICE MANAGER";
        cout << "\n================================";
        cout << "\n1. Display Home Dashboard";
        cout << "\n2. Turn Device ON";
        cout << "\n3. Turn Device OFF";
        cout << "\n4. Change Device Status";
        cout << "\n5. Set Light Brightness";
        cout << "\n6. Set Thermostat Temperature";
        cout << "\n7. Lock Door";
        cout << "\n8. Unlock Door";
        cout << "\n9. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        string id;

        switch (choice)
        {
        case 1:
            cout << "\n\n========== HOME DASHBOARD ==========";

            for (SmartDevice* device : devices)
            {
                device->display();
            }

            cout << "\n====================================";
            break;

        case 2:
            cout << "Enter Device ID: ";
            cin >> id;

            if (id == "L001")
                light1.turnOn();
            else if (id == "L002")
                light2.turnOn();
            else if (id == "T001")
                thermostat1.turnOn();
            else if (id == "C001")
                camera1.turnOn();
            else
                cout << "Device not found!";
            break;

        case 3:
            cout << "Enter Device ID: ";
            cin >> id;

            if (id == "L001")
                light1.turnOff();
            else if (id == "L002")
                light2.turnOff();
            else if (id == "T001")
                thermostat1.turnOff();
            else if (id == "C001")
                camera1.turnOff();
            else
                cout << "Device not found!";
            break;

        case 4:
            cout << "Enter Device ID: ";
            cin >> id;

            if (id == "L001")
            {
                string newStatus;
                cout << "Enter new status: ";
                cin >> newStatus;
                light1.changeStatus(newStatus);
            }
            else if (id == "L002")
            {
                string newStatus;
                cout << "Enter new status: ";
                cin >> newStatus;
                light2.changeStatus(newStatus);
            }
            else if (id == "T001")
            {
                string newStatus;
                cout << "Enter new status: ";
                cin >> newStatus;
                thermostat1.changeStatus(newStatus);
            }
            else
            {
                cout << "Device not found!";
            }
            break;

        case 5:
        {
            int brightness;

            cout << "Enter brightness (0-100): ";
            cin >> brightness;

            light1.setBrightness(brightness);
            break;
        }

        case 6:
        {
            float temperature;

            cout << "Enter temperature: ";
            cin >> temperature;

            thermostat1.setTemperature(temperature);
            break;
        }

        case 7:
            door1.lockDoor();
            break;

        case 8:
            door1.unlockDoor();
            break;

        case 9:
            cout << "\nExiting Smart Home Device Manager...\n";
            break;

        default:
            cout << "\nInvalid choice!";
        }

    } while (choice != 9);

    return 0;
}