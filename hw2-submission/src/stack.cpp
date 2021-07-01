#include "datastructure.hpp"
#include <sstream>
void Stack::push(int e)
{
    if (this->s_size == 0)
    {
        this->head->val = e;
        this->s_size += 1;
    }
    else
    {
        Node *temp = new Node;
        temp = this->head;
        this->head =  new Node;
        this->head->val = e;
        this->head->next = temp;
        this->s_size += 1;
    }
}

int Stack::pop()
{   
    if(this->s_size == 0)
    {
        exit(1);
    }
    Node *temp = new Node;
    temp = this->head;
    this->head = new Node;
    if(this->s_size == 1)
    {
        this->head->next = NULL;
    }
    else
    {
        this->head= temp->next;
    }
    this->s_size -= 1;
    return temp->val; 
}

Stack::Stack()
{
    this->head = new Node;
    this->head->next = NULL;
    this->s_size = 0;
}

void Stack::solution(const char *input_path, const char *output_path)
{
    Stack StackInstance;
    string line;
    ifstream input_file(input_path);
    ofstream output_file(output_path);
    while(getline(input_file,line))
    {
        if(line[0]=='s')
        {
            //cout<<"stack"<<endl;
            Stack();
            
        }
        else if (line[0]=='o')
        {
            //cout<<"pop"<<endl;
            int x = StackInstance.pop();
            //cout<<"pop result is "<<x<<endl;
            output_file<<x<<endl;

        }
        else if (line[0]=='c')
        {
            //cout<<"c"<<endl;
            continue;
        }
        else
        {
            //cout<<"push"<<endl;
            string num_str;
            int num;
            int i = 0;
            for (std::istringstream is(line);is>>num_str;)
            {
                if (i>=1)
                {
                    num = std::stoi(num_str,nullptr);
                    StackInstance.push(num); 
                }
                i++;
            }
        }
    }
    input_file.close();
    output_file.close();

}
