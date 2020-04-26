#include <iostream>
#include <string.h>
#include "FamilyTree.hpp"
#include <string>
#include <stdio.h>
#include <exception>
#include <bits/stdc++.h>
bool static check1 = false ;



using namespace std;
using namespace family;
node static *ans=NULL;



 Tree& Tree::addFather( string child, string father) 
 {
    if(this->root==NULL)
    {
       throw out_of_range{"The Family tree is Empty!"};
        return  *this;
    }
    node *temp=nullptr;
    /*size_t found=father.find(" "),found1=child.find(" ");

    if(found != string::npos || found1 != string::npos)
            throw out_of_range{"You entered incorrect names!"};*/

    find_node(this->root,&temp ,child);
    if(temp==NULL)
    {
       throw out_of_range{"cannot find this child!"};
        return *this;
    }
    if(temp->father!=NULL)
    {
        throw  out_of_range{"this child has a father "};
        return *this;
    }
    else
    {
        temp->father=new node(father);
        this->size++;
        temp->father->hight=temp->hight+1;
        temp->father->tag=0;
        temp->father->son=temp;

    }
    return *this;
    

 }
 
Tree& Tree::addMother( string child, string mother)
 {
     
    if(this->root==NULL)
    {
       throw out_of_range{"The Family tree is Empty!"};
        return *this;
    }
      /* size_t found=mother.find(" "),found1=child.find(" ");

  if(found != string::npos || found1 != string::npos)
            throw out_of_range{"You entered incorrect names!"};*/

    node *temp=nullptr;
    find_node(this->root,&temp ,child);
    if(temp==NULL)
    {
       throw out_of_range{"cannot find this child!"};
            return *this;
    }
    if(temp->mother!=NULL && temp->mother->tag !=-1)
    {
       throw out_of_range{"this child has a mother "};
        return *this;

    }
    else
    {
        temp->mother=new node(mother);
        this->size++;
        temp->mother->hight=temp->hight+1;
        temp->mother->tag=1;
        temp->mother->son=temp;
    }
       return *this;

 }
void Tree::find_node(node *root, node** temp ,const string child) {

    if(root == NULL) return  ;
    if(root->data == child )
    {
      *temp = root  ;
    }
    else
    {
        Tree::find_node(root->father, temp ,child );
        Tree::find_node(root->mother, temp ,child );
    }
}

 //tells us whats the name of the persons who has this relation with the root

 string Tree::find(string name)
 {
          cout<< name<<endl;

    size_t found=name.find(" ");
    if(found != string::npos)
            throw out_of_range{"You entered incorrect names!"};

    int l =name.length(),i=0;
    if(this->root==NULL)
        throw out_of_range{" the tree is empty"};

    if(name.compare("me")==0)
        return this->root->data;
    
    if((name.compare("mother")==0||name.compare("Mother")==0)&&this->root->mother!=NULL)
    {
        return this->root->mother->data;
    }

    if(name.compare("mother")==0&&this->root->mother==NULL)
            throw runtime_error("cannot find the reletion");

    if((name.compare("father")==0||name.compare("Father")==0 )&&this->root->father!=NULL)
    {
        return this->root->father->data;
    }

    if(name.compare("father")==0&&this->root->father==NULL)
            throw runtime_error("cannot find the reletion");

    if((name.compare("grandmother")==0||name.compare("Grandmother")==0 )&& this->root->mother->mother!=nullptr)
    {
        cout<< this->root->mother->mother->data<<endl;
        return this->root->mother->mother->data;
    }
    if((name.compare("grandmother")==0||name.compare("Grandmother")==0 )&& this->root->father->mother!=nullptr)
            return this->root->father->mother->data;

    if(name.compare("grandmother")==0&&this->root->mother->mother==NULL&&this->root->father->mother==nullptr)
            throw runtime_error("cannot find the reletion");

    if((name.compare("grandfather")==0||name.compare("Grandfather")==0)&&this->root->father->father!=NULL)
    {
        return this->root->father->father->data;
    }
    if((name.compare("grandfather")==0||name.compare("Grandfather")==0)&&this->root->mother->father!=NULL)
        return this->root->mother->father->data;

    if(name.compare("grandfather")==0&&this->root->mother->father==NULL && this->root->father->father==NULL)
            throw runtime_error("cannot find the reletion");

    int level=0;
    string s = name;
    while ((s != "grandmother" ) && (s != "grandfather"))
    {
        if(s.substr(0,6)!=("great-"))
        {
            throw runtime_error("cannot find the reletion");
        }
        s = s.substr(6,(s.length()-6));
        level++;
    }

    level=level+2;
    int tag=0;

    if(s.compare("grandfather")==0)
            tag=0;
    else 
            tag=1;         
    
    node *temp;
    findName(level,this->root,&temp,tag);
    if(check1==false)
    {
              temp=NULL;
    } 
        
    check1=false;
    if(temp==NULL)
        throw runtime_error("cannot find the reletion!");
     cout<< temp->data;
     cout<< name;
    return temp->data;
        
 }

void  Tree :: findName(int level,node *root,node **temp ,int tag)
{   
    
    if(root == NULL) 
    {
        return ;
    }
    else if(root->hight == level && root->tag==tag)
    {
        *temp=root;
        check1=true;
    }
    
    if(!check1){
        Tree::findName(level , root->father ,temp ,tag);
        Tree::findName(level , root->mother ,temp ,tag );
    }
    
}
string Tree::relation(string name)
 {
    
    node *temp=nullptr;
    find_node(this->root, &temp , name);
    if(temp==NULL)
    {
        return "unrelated" ;
    }
    
    string tempname=temp->data;

    if(tempname.compare(this->root->data)==0 && temp->hight==0)
    {
        return "me";
    }
    if(temp->hight==1 && tempname.compare(this->root->mother->data)==0)
    {
        return "mother";
    }
    if(temp->hight==1 && tempname.compare(this->root->father->data)==0)
    {
        return "father";
    }
     if(temp->hight==2 && (tempname.compare(this->root->father->father->data)==0 ||tempname.compare(this->root->mother->father->data)==0))
    {
        return "grandfather";
    }
     if(temp->hight==2 && (tempname.compare(this->root->father->mother->data)==0 ||tempname.compare(this->root->mother->mother->data)==0))
    {
        return "grandmother";
    }
    string ans="";
    if(temp->hight>2)
    {
        
        int h=temp->hight;
        while(h!=2)
        {
            ans=ans+"great-";
            h--;
        }
        if(temp->tag==1)
            ans+="grandmother";
        if(temp->tag==0)
            ans+="grandfather";
        
    }
    return ans;
 }
 
 void Tree::display()
 {
    node *ptr = root;

    if(ptr==NULL)
        return;

    display(ptr);
 }

void Tree :: display(node *n)
{
     if(n == NULL) return ;
    
    else
    {
        display(n->father);
        cout << n->data << endl;
        display(n->mother);
    }
}
 

void Tree::remove(string name)
{
    size_t found=name.find(" ");
    if(found != string::npos)
            throw out_of_range{"You entered incorrect names!"};
    if(this->root->data==name)
                throw runtime_error("cannot remove the root !");

    node *temp=NULL;
    find_node(this->root,&temp,name);
    if(temp==NULL) 
        throw runtime_error("this name is not in the tree");

    node *child=temp->son;
   if(child->mother!=nullptr && child->mother->data==name)
            {
                deleteSubTree(child->mother);
                child->mother=NULL;
            }
    else if(child->father!=nullptr && child->father->data==name)
            {
                deleteSubTree(child->father);
                child->father=NULL;
            }
}
void Tree::deleteSubTree(node *node){
    if(node==NULL) return;

    deleteSubTree(node->mother);
    deleteSubTree(node->father);
     
    delete node ;
    
    
}