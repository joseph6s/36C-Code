#include "datastructure.hpp"
#include <sstream>
using namespace std;

void Queue::enqueue(int e)
{
    if (this->s_size == 0)
    {
        //cout<<"a"<<endl;
        this->head->val = e;
        //cout<<"ac"<<endl;
        this->s_size += 1;
    }
    else
    {
        //cout<<"ab"<<endl;
        Node *temp = new Node;
        temp = this->head;
        this->head =  new Node;
        this->head->val = e;
        this->head->next = temp;
        this->s_size += 1;
    }
}

int Queue::dequeue()
{
    if(this->s_size == 0)
    {
        //cout<<"exit"<<endl;
        exit(1);
    }
    Node *temp = new Node;
    temp = this->head;
    //cout<<"111"<<endl;
    Node *temp2 = new Node;
    while (temp!=NULL)
    {
        //cout<<"temp is"<<temp->val<<endl;
        temp2 = temp;
        temp = temp2->next;
        
    }
    //cout<<"122"<<endl;
    this->s_size -= 1;
    int x = temp2->val;
    if(this->head->next == temp2)
    {
        this->head->next = NULL;
    }
    else if(this->head == temp2){
        this->head = new Node;
        this->head->next = NULL;
    }
    else{
        Node *temp3 = new Node;
        temp3 = this->head;
        while(temp3->next->next != NULL)
        {
            temp3 = temp3->next;
        }
        temp3->next = NULL;
        //cout<<"after while loop head.val is"<<this->head->val<<endl;
    }
    //cout<<"133"<<endl;
    //cout<<"144"<<endl;

    return x;
}
Queue::Queue()
{
    this->head = new Node;
    this->head->next = NULL;
    this->s_size = 0;
}

void Queue::solution(const char *input_path, const char *output_path)
{
    Queue QueueIn;
    string line;
    ifstream input_file(input_path);
    ofstream output_file(output_path);
    while(getline(input_file,line))
    {
        if(line[0]=='q')
        {
            Queue(); 
        }
        else if (line[0]=='d')
        {
            //cout<<"de"<<endl;
            int x = QueueIn.dequeue();
            //cout<<"de result is "<<x<<endl;
            output_file<<x<<endl;

        }
        else if (line[0]=='c')
        {
            //cout<<"c"<<endl;
            continue;
        }
        else
        {
            string num_str;
            int num;
            int i = 0;
            for (std::istringstream is(line);is>>num_str;)
            {
                if (i>=1)
                {
                    num = std::stoi(num_str,nullptr);
                    //cout<<"enQ"<<endl;
                    QueueIn.enqueue(num); 
                }
                i++;
            }
        }            
    }
    input_file.close();
    output_file.close();
}