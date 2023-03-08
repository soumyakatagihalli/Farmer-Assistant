#include <iostream>
#include <string>
using namespace std;
#define MAXSIZE 100

class farm_items
{
protected:
    bool availability = true;
    int id;

public:
    float price = 0;
    virtual float getprice(int discount) = 0;
    virtual void display() = 0;
    virtual string getType() = 0;
    bool getAvailability()
    {
        return availability;
    }
    void markAsSoldout()
    {
        availability = false;
    }
    bool matchItemId(int id)
    {
        return this->id == id ? true : false;
    }
    float getprice()
    {
        return price;
    }
};
class tractor_attachments : public farm_items
{
private:
    string tname;
    static int counter;
    string brand;

public:
    tractor_attachments(string tname, string brand) : tname(tname), brand(brand)
    {
        id = ++counter;
    }
    float getprice(int discount)
    {
        if (tname == "Plow")
        {
            price = 2000.0;
        }
        else if (tname == "Seeder")
        {
            price = 3000.0;
        }
        else if (tname == "Fertilizer_spreader")
        {
            price = 1100.0;
        }
        this->price = price;
        return price;
    }

    void display()
    {
        cout << "Tractor Attachment Name= " << tname << "\t"<< "id=" << id << "\t"<< "Price= Rs" << getprice(10) << endl;
    }
    string getType()
    {
        return "tractorattachments";
    }
};
int tractor_attachments::counter = 0;

class seeds : public farm_items
{
private:
    string seed_name;
    static int counter;
    string seasoned_seed;

public:
    seeds(string s, string seasoned_seed) : seed_name(s)
    {
        id = ++counter;
    }
    float getprice(int discount)
    {
        // no discount for stationary
        if (seed_name == "Wheat")
            price = 500;
        else if (seed_name == "Rice")
            price = 700;
        else if (seed_name == "Cotton")
            price = 800;
        this->price = price;
        return price;
    }
    void display()
    {
        cout << "Seed Name= " << seed_name <<"\t"<< " id=" << id <<"\t"<< "Price= Rs" << getprice(15) << endl;
    }
    string getType()
    {
        return "seeds";
    }
};
int seeds::counter = 0;

class fertilizers : public farm_items
{
private:
    string fertilizer_name;
    static int counter;
    float quantity;
    static float per_kg_value;

public:
    fertilizers(string fn, float n) : fertilizer_name(fn), quantity(n)
    {
        id = ++counter;
    }
    float getprice(int discount)
    {
        float price = quantity * per_kg_value;
        price = price * (100.0 - discount) / 100.0;
        this->price = price;
        return price;
    }
    void display()
    {
        cout << "Fertilizer Name= " << fertilizer_name <<"\t"<< " id=" << id << "\t"<<"Price= Rs" << getprice(10) << endl;
    }
    float get_quantity()
    {
        return quantity;
    }
    string getType()
    {
        return "fertilizers";
    }
};
float fertilizers::per_kg_value = 250;
int fertilizers::counter = 0;

class farmer
{
private:
    string name;
    long mobNum;
    farm_items *purchasedItems[MAXSIZE];
    int purchaseCount = 0;

public:
    farmer(string name, long mobNum) : name(name), mobNum(mobNum)
    {
    }
    void display()
    {
        cout << "Farmer name= " << name <<"\t"<< " Mobile number=" << mobNum << endl;
        for (int i = 0; i < purchaseCount; i++)
        {
            cout << "Purchased ";
            purchasedItems[i]->display();
        }
    }
    bool matchMobileNumber(long num)
    {
        return num == mobNum ? true : false;
    }
    void addPurchasedItem(farm_items *t)
    {
        if (purchaseCount < MAXSIZE)
        {
            purchasedItems[purchaseCount] = t;
            purchaseCount++;
        }
    }
    int getPurchaseCount()
    {
        return purchaseCount;
    }
};

class farm_equipments : public farm_items
{
private:
    string ename;
    static int counter;
    float no_of_equipments;

public:
    farm_equipments(string e, float n) : ename(e), no_of_equipments(n)
    {
        id = ++counter;
    //}

   // void execption()
    //{
        try
        {
            if(no_of_equipments<3)
            {
            throw(3);
            }

        }

    catch(int x)
        {
           cout<<"ALERT "<<endl;
           cout<<"Farmer has to buy at least 3 equipments"<<endl;
           cout<<endl;
           cout<<endl;
           cout<<endl;
           cout<<endl;
           cout<<endl;
           cout<<endl;

        }

    }

    float getprice(int discount)
    {
        float price = no_of_equipments * 1000;
        price = price * (100.0 - discount) / 100.0;
        this->price=price;
        return price;

    }
    void display()
    {
        cout << "Equipment name is " << ename << "\t"<<" Id=" << id << "\t"<<"Price= Rs" << getprice(10) << endl;
    }
    float getequipments()
    {
        return no_of_equipments;
    }
    string getType()
    {
        return "farm_equip";
    }
};
int farm_equipments::counter = 0;

class farm_store
{
private:
    string owner;
    farm_items *items[MAXSIZE];
    int itemCount = 0;
    farmer *f[MAXSIZE];
    int fcount = 0;

public:
    farm_store(string owner) : owner(owner)
    {
    }
    void addItem(farm_items *t)
    {
        if (itemCount < MAXSIZE)
        {
            items[itemCount] = t;
            itemCount++;
        }
    }
    void addfarmer(farmer *f1)
    {
        if (fcount < MAXSIZE)
        {
            f[fcount] = f1;
            fcount++;
        }
    }
    void displayAllItems()
    {
        cout << " DISPLAYING ITEM " << endl;
        for (int i = 0; i < itemCount; i++)
        {
            cout << i + 1 << ") ";
            items[i]->display();
        }
    }
    void display_all_farmers()
    {
        cout<<"\n";
        cout << "DISPLAYING all FARMERS" << endl;
        for (int i = 0; i < fcount; i++)
        {
            cout << i + 1 << ") ";
            f[i]->display();
            cout<<"\n";
        }
    }

    void sellAnItem(int itemId, string itemChoice, long customerMobile)
    {
        int itemFlag = -1, Flag = -1, discount = 0;
        // search farmer is premimum customer on mobile number
        for (int i = 0; i < fcount; i++)
        {
            if (f[i]->matchMobileNumber(customerMobile))
            {
                Flag = i;
                discount = 50;
                break;
            }
        }
        // search if item with given id is available
        for (int i = 0; i < itemCount; i++)
        {
            if (items[i]->matchItemId(itemId) && items[i]->getAvailability()  && items[i]->getType() == itemChoice)
            {
                itemFlag = i;
                break;
            }
        }
        // flag indicates if item found and not yet sold
        if (itemFlag != -1)
        {
            // check if it premimum customer to whom item is sold
            if (Flag != -1)
            {
                if (f[Flag]->getPurchaseCount() < 2)
                    discount = 100;
                else
                    discount = 150;
                items[itemFlag]->markAsSoldout();
                f[Flag]->addPurchasedItem(items[itemFlag]);
            }
            items[itemFlag]->getprice(discount); // this will calculate price
            items[itemFlag]->markAsSoldout();
            cout << "Selling item with id= " << itemId<< " to Farmer with Mobile number =" << customerMobile << " Discount= " << discount << endl;
            cout <<"Selling item detail:";

            items[itemFlag]->display();
             cout<<"\n";
        }
        else
        {
            cout << "Item with id=" << itemId << " is unavailable" << endl;
        }
    }

    void displaySaleDetails(int itemChoice)
    {
        float saleAmount = 0;
        cout << "Displaying Details of Sold out ";
        if (itemChoice == 1)
            cout << "tractor_attachments" << endl;
        else if (itemChoice == 2)
            cout << "Seeds" << endl;
        else if (itemChoice == 3)
            cout << "Fertilizers" << endl;
        else
            cout << "All items" << endl;
        for (int i = 0; i < itemCount; i++)
        {
            if (!items[i]->getAvailability()) // getAvailability() returns false,then item is soldout
            {
                if (itemChoice == 1)
                {
                    if (items[i]->getType() == "tractorattachments")
                    {
                        items[i]->display();
                        saleAmount += items[i]->getprice();
                    }
                }
                else if (itemChoice == 2)
                {
                    if (items[i]->getType() == "seeds")
                    {
                        items[i]->display();
                        saleAmount += items[i]->getprice(0);
                    }
                }
                else if (itemChoice == 3)
                {
                    if (items[i]->getType() == "fertilizers")
                    {
                        items[i]->display();
                        saleAmount += items[i]->getprice(5);
                    }
                }
                else if(itemChoice==4)
                {
                    if (items[i]->getType() == "farm_equip")
                    {
                        items[i]->display();
                        saleAmount += items[i]->getprice(5);
                    }
                }
                else
                {
                    items[i]->display();
                    saleAmount += items[i]->getprice(15);
                }
            }
        }
        cout << "Sale amount=" << saleAmount << endl;
    }
};
int main()
{
    farm_store *farmer1 = new farm_store("soumya");
    farmer1->addItem(new tractor_attachments("Plow", "Bajaj"));
    farmer1->addItem(new tractor_attachments("Seeder", "Swastik"));
    farmer1->addItem(new seeds("Wheat", "Rabi"));
    farmer1->addItem(new seeds("Rice", "Kharif"));
    farmer1->addItem(new fertilizers("Urea", 10));
    farmer1->addItem(new fertilizers("Iorganic", 3));
    farmer1->addItem(new farm_equipments("Axe",2));

    farmer1->addfarmer(new farmer("Jaganna", 98632));
    farmer1->addfarmer(new farmer("Raddi", 98765));
    farmer1->addfarmer(new farmer("Nehav", 43228));

    cout <<"\n"<< "Display all ITEM before selling" <<"\n"<< endl;
    farmer1->displayAllItems();
    farmer1->display_all_farmers();

    cout << endl;
        cout << "Selling some farm items" <<"\n"<< endl;
    farmer1->sellAnItem(2, "seeds", 98632);
    cout<<endl;
     farmer1->sellAnItem(2, "fertilizers", 43228);
    cout<<endl;
    farmer1->sellAnItem(1, "tractorattachments", 98765);
    cout<<endl;
    farmer1->sellAnItem(1,"farm_equip",98760);
    cout << endl<< " ITEM SELLING DETAILS" << "\n"<<endl;
    farmer1->sellAnItem(4, "seeds", 93632);
    cout<<endl;
    farmer1->displaySaleDetails(1);
    cout<<endl;
    farmer1->displaySaleDetails(2);
    cout<<endl;
    farmer1->displaySaleDetails(3);
    cout<<endl;
    farmer1->displaySaleDetails(4);

    cout << endl
         << "AFTER SALE DISPLAYING PREMIUM FARMER DETAILS"<< endl;
    farmer1->display_all_farmers();
}
