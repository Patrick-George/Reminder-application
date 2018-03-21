#include<bits/stdc++.h>
#include<cstring>
using namespace std;


// structure for a particular reminder
typedef struct reminder_node{
	pair <int,pair<int,int> > date;
	string subject;
    string description;
    int tag;                 // identifier
}reminder_node;

/* 
  let us design a data structure supporting 
   
   1. Insert in constant time
   2. Delete in constant time
   3. Search in constant time( Using this, we will track a reminder to update )
   
   These time complexities would be most suitable for app-operation and quick functioning.

   We are storing this data structure in main memory but disk-write feature can be added to make it secondary memory-type
   for bigger size;

*/

typedef struct reminder{

    // hash table that will contain the indices of a particular reminder
	unordered_map<int,int> table;

	//allocating an array of reminders non - dynamically to prevent fragmentation
	reminder_node reminder_array[50]; 
	int size;

}reminder;

// inserts and returns a tag for a new reminder if succesful; otherwise returns -1
int insert_new_reminder(reminder* rem){
	string input;
	int inp;
	cout<<"Enter date as :: dd/mm/yyyy\ndd : ";
    cin>>inp;
    reminder_node newrem;
    if(rem->size==50){
       return -1;
    }
    newrem.date.first=inp;
    cout<<"\nmm : ";
    cin>>inp;
    newrem.date.second.first=inp;
    cout<<"\nyyyy : ";
    cin>>inp;
    newrem.date.second.second=inp;

    cout<<"Enter subject\n";
    cin>>input;
    newrem.subject=input;
    cout<<"Enter description\n";
    cin>>input;
    newrem.description=input;


    // We insert at the end of the array and store the size as index(tag).
    // If max size reached then we returned error flag
    
         
    rem->size=rem->size+1;
    newrem.tag=rem->size;
    if(rem->size==1){
		(rem->reminder_array)[0]=newrem;
	}
    (rem->reminder_array)[rem->size]=newrem;
    // store the tag (index of reminder the array) as the index in the hash table with "tag" as key
    (rem->table)[newrem.tag]=newrem.tag;
    return rem->size;
}

void delete_reminder(reminder* rem, int tag){
    //the index of the reminder is in table 
    if((rem->table).find(tag)==(rem->table).end()){
		cout<<"The reminder doesn't exist\n";
		return;
	
	}
    int index=rem->table[tag];
    (rem->table).erase(tag);
    //replace this element with last element
    rem->reminder_array[index]=rem->reminder_array[rem->size];

    //update the index of the previously last element
    (rem->table)[(rem->reminder_array)[index].tag]=index;

    //reduce the size to delete the last element
    rem->size= rem->size-1;

    return;
} 

void update_reminder(reminder *rem,int tag){
    //to update, create a new reminder and swap it with current; delete the old one

	insert_new_reminder(rem);
	delete_reminder(rem,tag);
	return;

}
void print_reminder(reminder* rem,int tag){
	
	int index=rem->table[tag];
	reminder_node curr=rem->reminder_array[index];
	cout<<"Date :: ";
	cout<<curr.date.first<<"/"<< curr.date.second.first<<"/"<<curr.date.second.second;
	cout<<"\n\nSubject ::  "<<curr.subject<<" \n";
	cout<<"Description :: "<<curr.description<<" \n\n";
	
	
	
}
int main(){
	int choice,res,tag;
	ios_base::sync_with_stdio(false);
	reminder reminder_init;
    reminder* rem=&reminder_init;

    rem->size=0;
    (rem->table)[-1]=-1;
    assert(rem);
    while(1){
    	cout<<"\nEnter a choice ::\n1 for new reminder\n2 for updating an existing reminder\n3 for deleting a remider\n0 to exit\n";
        cin>>choice;
        switch(choice){
        	

        	case 1:
        	
              	res=insert_new_reminder(rem);
                if(res==-1) cout<<"Insert unsuccessful"; 
                else cout<<"The tag of the inserted reminder is "<<res<<"\n";// this tag can be used by Operatin System in application-environment
                break;
            

            case 2:
            
                cout<<"Enter the tag of the reminder to update"; //cannot find reminder
                cin>>tag;
                while((rem->table).find(tag)==(rem->table).end()){
                	cout<<"The reminder does not exist; please enter again";
                    cin>>tag;
                }
                //to update, create a new reminder and swap it with current; delete the old one
                update_reminder(rem,tag);
                cout<<"\n####################################\nNew reminder with tag "<<tag<<" is \n\n";
                print_reminder(rem,tag);
                break;
            

            case 3:
                cout<<"Enter the tag of the reminder to delete : ";
                cin>>tag;
                while((rem->table).find(tag)==(rem->table).end()){
                	cout<<"\n###################################\nThe reminder does not exist; please enter again";
                    cin>>tag;
                }
                delete_reminder(rem,tag);
                if(rem->size > 0) {
                   cout<<"\n####################################\nNew reminder with tag "<<tag<<" is \n\n";
                   print_reminder(rem,tag);
                }
                break;
            

             case 0:
                cout<<"The total number of reminders are "<<rem->size<<"\n..Exiting\n";
                exit(0);
        }

    }


}
