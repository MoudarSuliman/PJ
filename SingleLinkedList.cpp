#include <iostream>
#include "Lab1.h"
using namespace std;

int adittion_of_info(const int& first, const int& second){
    return second+first;
}

int main(){
    Sequence<int, int> var , t1,t2;
    cout <<"Checking if the list is empty" <<endl;
    if(var.isEmpty() == 1){
        cout<<"The list is empty" <<endl;
    }else
    {
        cout<<"The list is not empty" <<endl;
    }
    cout << "Adding elements to the linked list from the front:" <<endl;
    var.push_front(0, 6);
    var.push_front(1,2);
    var.push_front(3,5);
    var.push_front(23,42);
    var.print();
    cout<<endl;
    cout << "Adding elements to the linked list from the back " <<endl;
    var.append(10,10);
    var.append(2,3);
    var.append(1,2);
    var.append(123,123);
    var.print();
    cout <<endl;
    cout <<"Deleting element of occurance 2nd (1,2) " << endl;
    if(var.removeAt(1,2,2)==1){
        var.print();
        cout<<endl;
    }else
    {
        cout<<"Couldn't be deleted " << endl;
    }

    cout<<"Deleting element of occurance 2nd (0,6)" <<endl;
    if(var.removeAt(0,6,2)==1){
        var.print();
        cout<<endl;
    }else
    {
        cout<<"Couldn't be deleted " << endl;
    }
    
    cout << "Removing the first element" << endl;
    var.pop_front();
    var.print();
    cout<<endl;
    cout<<"Checking if the element (123,123) exist" <<endl;
    if(var.searchFor(123,123)==1){
        cout<<"Element was found" <<endl;
    }else
    {
        cout<<"Element was not found " << endl;
    }
    cout <<"Removing last element " <<endl;
    var.pop_back();
    var.print();
    cout<<endl;
    cout<<"Checking if the list is empty" <<endl;
    if(var.isEmpty() == 1){
        cout<<"The list is empty" <<endl;
    }else
    {
        cout<<"The list is not empty" <<endl;
    }
    cout<<"Insert an element in the list in 3rd position " <<endl;
    var.insert(4,23,3);
    var.print();
    cout<<endl;
    cout<<"Addition" << endl;
    cout<<"List one" << endl;
    t1.push_front(3232,4324);
    t1.append(4021,234);
    t1.print();
    cout<<endl;
    cout<<"List two" <<endl;
    var.print();
    cout<<endl;
    cout<<"Added list" <<endl;
    t1.addition(var);
    t1.print();
    cout<<endl;
    cout<<"Copy constructor" <<endl;
    Sequence<int,int> t3(var);
    t3.print();
    cout<<endl;
    cout<<"Assignement operator" <<endl;
    t2.operator=(var);
    t2.print();
    cout<<endl;
    cout<<"Using the join function" <<endl;
    int (*aggregate)(const int&, const int&) = &adittion_of_info;
    Sequence<int,int> t4 = join(var,t1,aggregate);
    cout<<"List one" << endl;
    t1.print();
    cout<<endl;
    cout<<"List two" <<endl;
    var.print();
    cout<<endl;
    cout<<"Joined list" << endl;
    t4.print();
    cout<<endl;
    // var.removeAll(); removes all elements in the list unused
    cout << "Displaying the list" << endl;
    var.print();
    cout<<endl;
    cout <<"IT WORKS!!" << endl;
}
