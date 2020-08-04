#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <iostream>

using namespace std;


template<typename T>
class List1
{
public:
    struct Node
    {
        T value;
        Node* next = nullptr;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    List1() = default;
    List1(List1&& other)
    {
        head = std::exchange(other.head, nullptr);
        tail = std::exchange(other.tail, nullptr);
    }

    Node* insert(Node* predNode, T value)
    {
        auto newNode = new List1::Node{
            move(value),
            
            predNode ? predNode->next : nullptr
        };

        if (predNode) 
        {

            if (predNode->next)
            {
                
            }
            
            else
            {
                tail = newNode;
            }

            predNode->next = newNode;
        }

       
        else 
        {
            if(head)
            {
            newNode->next = head;
            head = newNode;
            }
            if (!head)
            {
                head = newNode;
                tail = newNode;
            }

        }
        return newNode;

    }
    
    Node* erase(Node* Nodepred)
    {
        Node* erasingNode = nullptr;

        if (!head)
            return nullptr;

        if (Nodepred != nullptr)
        {
            erasingNode = Nodepred->next;
            Nodepred->next = erasingNode->next;

            if (!erasingNode->next)
            {
                tail = Nodepred;
            }
        }
        else 
        {
            erasingNode = head;
            head = head->next;

            if (!head->next)
            {
                head = tail = nullptr;
            }

        }

        auto nextNode = erasingNode->next;
        delete erasingNode;
        return nextNode;
    }
    
   

    void clean()
    {
        while (erase(nullptr));
    }

    ~List1()
    {
        clean();
    }
};


List1<string> fillList()
{
    cout << "enter the file name: ";
    List1<string> list;
    string filename;
    cin >> filename;
    ifstream input(filename);
    if (input.is_open())
    {        
        while (!input.eof())
        {
            string words;
            input >> words;
            if(words == "")
            {
                break;
            }
            list.insert(list.tail, move(words));
        }
        
        if (!list.head || list.head->value == "")
        {
            cout << "no words in the input file " << endl;
            exit(0);
        }
        return list;
    }

    else
    {
        cout << "the file was not detected, restart ";
        exit(0);
    }
    return List1<string>{};
}


void print(ostream& out, const List1<string>& list_to_print)
{
    
    for (auto node = list_to_print.head; node->next != nullptr; node = node->next) 
    {
        out << node->value << " ";
    }
    out << endl << endl;
}

void outputResult(List1<string>& list, string& filename)
{
        
        ofstream output(filename, ios::app);

        if (output.is_open())
        {
            output << endl << endl;
            print(output, list);
            return;
        }
    
}

int main()
{
    cout << "this is a file to process, ";
    List1<string> list_original = fillList();

    cout << "check output of list for transform : " << endl;
    print(cout, list_original);

    cout << "Type the name of the file where the results will be saved: " << endl;
    string filename;
    cin >> filename;
    outputResult(list_original, filename);


    cout << endl << "this is a file for adding elements, ";
    List1 <string> list_add = fillList();

    cout << endl << "check output of list to add: " << endl;
    print(cout, list_add);
    outputResult(list_add, filename);


    cout << "print number of elements to "  << endl;
    
    int nomber_to_add;
    cin >> nomber_to_add;
    if (nomber_to_add <= 0)
    {
        cout << "you are trying to add 0 or fewer elements, the text will not be changed, restart programm " << endl;
        exit(0);
    }
    cout << "print element value, before which new elements will be inserted " << endl;;
    string keyEl;
    cin >> keyEl;

    auto pred_node = list_original.head;
    
    int count_add_limit = 0;
    int count_add = 0;
    int count_keyEl = 0;

    for (auto node_original = list_original.head; node_original != nullptr; node_original = node_original->next) //вывод неисправленных слов (убрать)
    {
        
        if (node_original->value == keyEl)
        {
            count_keyEl++;
            
            for (auto node_add = list_add.head; node_add != nullptr && count_add_limit < nomber_to_add; node_add = node_add->next)
            {
                if (keyEl == list_original.head->value)
                {
                    list_original.insert(nullptr, node_add->value);
                    pred_node = list_original.head;

                }
                else
                {
                    list_original.insert(pred_node, node_add->value);
                    pred_node = pred_node->next;
                }
                
                count_add_limit++;
                count_add++;

            }
            count_add_limit = 0;
        }
        pred_node = node_original;
    }

    if ((count_add/ count_keyEl) < nomber_to_add && count_add!=0)
    {
        cout << "there are fewer items in the list than you want to add, all possible " << (count_add / count_keyEl) << " items have been added " << endl << endl;
    }
    if (count_keyEl ==0)
    {
        cout << "no element matching the query was found, restart programm " << endl;
    }
    
    cout << "check output of list with result: ";
    print(cout, list_original);
    outputResult(list_original, filename);
    list_add.clean();
    list_original.clean();

}



