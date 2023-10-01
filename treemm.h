#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED


#include <cstddef>
#include <vector>
#include <iostream>


template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            temp_vector = nullptr;
        }

        Iterator(std::vector<ValueType>* p)
        {
            temp_vector = p;
            m_it = temp_vector->begin();
        }


        ValueType& get_value() const
        {
            return *m_it;
        }

        bool is_valid() const
        {
            if(temp_vector != nullptr && m_it != temp_vector->end())
            {
                return true;
            }
            
            return false;

        }

        void advance()
        {
            m_it++;
        }

      private:

        std::vector<ValueType>* temp_vector;
        typename std::vector<ValueType>::iterator m_it;

    };

    TreeMultimap()
    {
       m_root = nullptr;
    }

    ~TreeMultimap()
    {
        eraseAll(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
       if (m_root == nullptr){   
            m_root = new Node(key, value);   
            return; 
        }

        Node *ptr = m_root;
        for (;;) {
            if (key == ptr -> key){
                ptr -> values.push_back(value);
                return;
            }   

            if (key < ptr -> key) {
                if (ptr->left != nullptr)      
                    ptr = ptr -> left;
                else {
                    ptr -> left = new Node(key, value);
                    return;
                }
            }
            else if (key > ptr -> key)
            {
                if (ptr -> right != nullptr)     
                    ptr  = ptr -> right;
                else {
                    ptr -> right = new Node(key, value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* temp = findHelp(key, m_root);
        if(temp == nullptr)
        {
            return Iterator();
        }
        
        return Iterator(&(temp->values));
    }

  private:

    struct Node
    {
        
        Node(KeyType t_key, ValueType t_val):key(t_key), left(nullptr), right(nullptr)
        {
            values.push_back(t_val);
        }
        std::vector<ValueType> values;
        KeyType key;
        Node* left;
        Node* right;
    };

    Node* m_root;

    void eraseAll(Node* &p){
        if(p == nullptr) 
        {
          return;
        }
        eraseAll(p->left);
        eraseAll(p->right);
        delete p;
    }

    Node* findHelp(const KeyType& key, Node* p) const
    {
        if(p == nullptr)
        {
            return nullptr;
        }
        else if(key == p->key)
        {
            return p;
        }
        else if(key < p->key) 
        {
           return findHelp(key, p->left);  
        }
        else return findHelp(key, p->right);
    
    }



};

#endif // TREEMULTIMAP_INCLUDED
