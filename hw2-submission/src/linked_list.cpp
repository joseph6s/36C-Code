#include "datastructure.hpp"
#include <sstream>
using namespace std;

bool LinkedList::is_circular()
{
    Node *temp = new Node;
    temp = this->head;
    Node *temp2 = new Node;
    temp2 = this->head->next;
    while(temp2!= NULL)
    {
        if (temp == temp2)
        {
            return 1;
        }
        temp2 = temp2->next;
    }
    return 0;
}

string LinkedList::print()
{
    Node *temp = new Node;
    temp = this->head;
    string str;
    while (temp != NULL)
    {
        //cout<<"str is "<<str<<endl;
        string num_str = to_string(temp->val);
        str.append(num_str);
        str.append(" ");
        temp = temp->next;
        if(temp == this->head)
        {
            break;
        }
    }
    //cout<<"str is "<<str<<endl;
    return str;
}

string LinkedList::print(int i, int j)
{
    int len;
    len = j-i;
    string str;
    Node *temp = new Node;
    temp = this->head;
    while(i!=0)
    {
        temp =temp->next;
        i -= 1;
    }
    while(len>0)
    {
        string num_str = to_string(temp->val);
        str.append(num_str);
        str.append(" ");
        temp = temp->next;
        len -= 1;
    }
    return str;
}

void LinkedList::insert(int v)
{
    Node *temp = new Node;
    temp = this->head;
    this->head = new Node;
    this->head->val = v;
    this->head->next = temp;
    //cout<<"this head"<<this->head->val<<endl;
    //cout<<"this head next"<<this->head->next->val<<endl;
}

void LinkedList::del(int v)
{
    Node *temp = new Node;
    temp = this->head;
    if(temp->val == v)
    {
        this->head = this->head->next;
    }
    while(temp->next->val != v)
    {
        temp = temp->next;
        if(temp == NULL)
        {
            exit(1);
        }
    }
    Node *temp2 = new Node;
    temp2 = temp->next->next;
    temp->next = temp2;
    //cout<<"this headdd"<<this->head->val<<endl;
    //cout<<"this headddd next"<<this->head->next->val<<endl;
}

void LinkedList::reverse()
{
    if((this->head == NULL) || (this->head->next == NULL))
    {
        exit(1);
    }
    Node *prev = new Node;
    Node *next = new Node;
    Node *temp = new Node;
    temp = this->head;
    while(temp != NULL)
    {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    temp = prev;
    this->head = temp;
}

void LinkedList::link(int a, int b)
{    
    if((this->head == NULL) || (this->head->next == NULL))
    {
        exit(1);
    }
    Node *node_a = new Node;
    Node *node_b = new Node;
    Node *temp = new Node;
    temp = this->head;
    while(temp != NULL)
    {
        if(temp->val == a)
        {
            node_a = temp;
        }
        else if(temp->val == b)
        {
            node_b = temp;
        }
        temp = temp->next;
    }
    node_a->next = node_b;
/*     cout<<"le head xxxx"<<this->head->val<<endl;
    cout<<"le head next xxxx"<<this->head->next->val<<endl;
    cout<<"le head next next "<<this->head->next->next->val<<endl; */

}

void LinkedList::create_new(int a, int b)
{
    Node *node_b = new Node;
    node_b->val = b;
    Node *temp = new Node;
    temp = this->head;
    if(temp->val == a)
    {
        node_b->next = this->head->next;
        this->head->next = node_b;
/*         cout<<"this hea11 "<<this->head->val<<endl;
        cout<<"this hea1 next"<<this->head->next->val<<endl;
        cout<<"this hea1 next"<<this->head->next->next->val<<endl;  */
    }
    else
    {
        while(temp->next->val != a)
        {
            temp = temp->next;
            if(temp == NULL)
            {
                exit(1);
            }        
        }
        Node *temp2 = new Node;
        temp2 = temp->next->next;
        temp->next->next = node_b;
        node_b->next = temp2;
/*          cout<<"this hea1"<<this->head->val<<endl;
        cout<<"this hea1k next"<<this->head->next->val<<endl;
        cout<<"this heak1next"<<this->head->next->next->val<<endl; */
    }

}

LinkedList::LinkedList(int v)
{
    this->head = new Node;
    this->head->val = v;
    this->head->next = NULL; 
}

void LinkedList::solution(const char *input_path, const char *output_path)
{
    string line;
    ifstream input_file(input_path);
    ofstream output_file(output_path);
    getline(input_file,line);
    int v;
    if (line[0] =='h')
        {
            string num_str;
            int num;
            int i = 0;
            for (std::istringstream is(line);is>>num_str;)
            {
                if (i>=1)
                {
                    num = std::stoi(num_str,nullptr);
                    v = num;
                    break;
                }
                i++;
            }
        }
    LinkedList ll = LinkedList(v);
    while(getline(input_file,line))
    {
        int v;
        if(line[0]=='c')
        {
            continue;
        }
        else if (line[0] =='i')
        {
            string num_str;
            int num;
            int i = 0;
            for (std::istringstream is(line);is>>num_str;)
            {
                if (i>=1)
                {
                    num = std::stoi(num_str,nullptr);
                    ll.insert(num); 
                }
                i++;
            }
        }
        else if (line[0] =='d')
        {
            string num_str;
            int num;
            int i = 0;
            for (std::istringstream is(line);is>>num_str;)
            {
                if (i>=1)
                {
                    num = std::stoi(num_str,nullptr);
                    ll.del(num); 
                }
                i++;
            }
        } 
        else if (line[0] =='n')
        {
            string num_str;
            int a;
            int b;
            int i = 0;

            for (std::istringstream is(line);is>>num_str;)
            {
                if (i==1)
                {
                    a = std::stoi(num_str,nullptr);
                }
                else if(i==2)
                {
                    b = std::stoi(num_str,nullptr);
                    ll.create_new(a,b);
                }
                i++;
            }
            
        }
        else if (line[0] =='r')
        {
            ll.reverse();
        }
        else if (line[0] =='l')
        {
            string num_str;
            int a;
            int b;
            int i = 0;

            for (std::istringstream is(line);is>>num_str;)
            {
                if (i==1)
                {
                    a = std::stoi(num_str,nullptr);
                }
                else if(i==2)
                {
                    b = std::stoi(num_str,nullptr);
                    ll.link(a,b);
                }
                i++;
            }
        }
        else if (line[0] =='o')
        {
            int rc = ll.is_circular();
            if (rc == 1)
            {
                output_file<<"1"<<endl;
            }
            else{
                output_file<<"0"<<endl;
            }

        }
        else if (line[0] =='p')
        {
            string num_str;
            int k = 0;
            int a;
            int b;
            int i = 0;
            for (std::istringstream is(line);is>>num_str;)
            {
                if (i==1)
                {
                    a = std::stoi(num_str,nullptr);
                    k = 1;
                }
                else if(i==2)
                {
                    b = std::stoi(num_str,nullptr);

                    k = 1;
                    string result = ll.print(a,b);
                    output_file<<result<<endl;
                    break;
                }
                i++;
            }
            if(k == 0 )
            {
                string result = ll.print();
                output_file<<result<<endl;
            }
        } 
    }
}
