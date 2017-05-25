#include <iostream>
#include <vector>
using namespace std;

/*
*     Trie Node
*/
class Node{
public:
  Node(){ mContent=' '; marker=false; mPrefix = 1;}
  ~Node(){}
  Node*      findChild(char c) const ;
  void      addChild(Node * child) {children.push_back(child);}
  void      setMarker(bool t){marker=t;}
  bool      getMarker() const {return marker;}
  char      content() const {return mContent;}
  void      setContent(char c) { mContent = c;}
  void      setPrefix(int p){mPrefix = p;}
  int      getPrefix() {return mPrefix;}
  int      countChild() const {return children.size();}
  bool      deleteChild(char c);
  Node *      getChild(int index)
  {
             if(index >=0 && index < countChild())
             return children[index];

else

    return NULL;
                 }
  void      setChild(Node *t, int index){
                                                  if(index>=0 && index< countChild())
                                                         children[index]=t;
                                               }
private:
  char mContent;
  bool marker;
  vector<Node*> children;
  int mPrefix;          //how many words this node prefixes
};

ostream& operator << (ostream& output, Node & node)
{
  output << node.content();
  return output;
}

/*
*          Trie class
*/
class Trie
{
public:
  Trie(){root = new Node();}
  ~Trie();
  void     addWord(const string & word);
  bool     findWord(const string  & word) const;
  bool      deleteWord(const string &  word);
  void     print() const;
  void      sort() const;
private:
  Node      *root;
  void      printWords(Node*, char *, int length) const;
  void      sortTrie(Node *) const;
  void      deleteSubTrie(Node *);
};

/*
     Sort the trie words in alaphabetic order
*/

void Trie::sort() const
{
  sortTrie(root);
}


void Trie::sortTrie(Node *current) const
{
  int i;
  int j;
  Node *t;

  //sort the children of current node level
  for(i = 0; i < current->countChild()-1; i++)
       for(j=i+1; j < current->countChild(); j++)
            if(current->getChild(i)->content() > current->getChild(j)->content())
            {
                 t = current->getChild(i);
                 current->setChild(current->getChild(j), i);
                 current->setChild(t, j);
            }

  //recursively sort children
  for(i = 0; i < current->countChild(); i++)
  {
       sortTrie(current->getChild(i));
  }
}
/*
*     Enumerate all words in the trie
*/
void Trie::print() const
{
  char word[256]={""};

  printWords(root,word, 0);

}

void Trie::printWords(Node *current, char *word, int index) const
{
  int i;
  if(current == root)
       index = 0;
  for(i = 0; i < current->countChild(); i++)
  {
       Node *child = current->getChild(i);
       word[index] = child->content();

       if(child->getMarker())
       {
            word[index+1]='\0';
            cout << word << endl;
       }

       printWords(child, word, index+1);
  }
}

/*
*     Trie deconstructor
*/
Trie::~Trie()
{
  deleteSubTrie(root);
}

/*
*     delete a child of a node
*/
bool Node::deleteChild(char c)
{
  int i;
  for(i = 0; i < children.size(); i++){
       if(children[i]->content() == c)
            children.erase(children.begin() + i);
  }
}

/*
*     Find a child of a node
*     input: single char
*     return: child if exists, NULL if does not exist
*/

Node* Node::findChild(char c) const
{
  int i;
  for(i=0; i < children.size(); i++)
       if(children[i]->content() == c)
            return children[i];
  return NULL;

}

/*
*
*     Add a word to the trie
*/
void Trie::addWord(const string  & word)
{
  int i;
  char c;
  Node *current= root;
  if(word.length() == 0)
  {
       current->setMarker(true);
       return;
  }

  for(i=0; i < word.length(); i++)
  {

       Node* child = current->findChild(word[i]);

       if(child != NULL)
       {
            child->setPrefix(child->getPrefix() + 1);
            current = child;
       }
       else
       {
            Node * tmp = new Node();
            tmp->setContent(word[i]);
            current->addChild(tmp);
            current = tmp;
       }

       if(i == word.length() - 1 )
       {
            current->setMarker(true);
       }
  }
}

/*
*     delete a sub trie
*/
void Trie::deleteSubTrie(Node *current)
{
  for(int i = 0; i < current->countChild(); i++)
  {
       deleteSubTrie(current->getChild(i));
  }

       delete current;

}

/*
*     Find a word from the trie
*/
bool     Trie::findWord(const string & word) const
{

  Node *current = root;

  int i;
  for(i = 0; i < word.length(); i++)
  {
       current = current->findChild(word[i]);
       if(current == NULL)
            return false;
  }

  if(current->getMarker())
       return true;
  else
       return false;
}

/*
*          delete a word from the trie
*/
bool Trie::deleteWord(const string & word)
{
  //if the word exists
  if(!findWord(word))
       return false;

  Node *current = root;
  int i;
  for(i = 0; i < word.length(); i++)
  {
       Node* child = current->findChild(word[i]);
       //cout << *child << " \t" <<child->getPrefix() << endl;
       if (child == NULL)
            return false;
       else if(child->getPrefix() == 1)
       {
            current->deleteChild(child->content());
            deleteSubTrie(child);
            return true;
       }
       else
       {
            child->setPrefix(child->getPrefix() - 1);
            current = child;
       }
  }
  //remove the word marker
  current->setMarker(false);

}

int main()
{

  Trie *t = new Trie();

  t->addWord("BOB");
  t->addWord("ABCDEF");
  t->addWord("ABCD");

  //t->print();

  t->sort();
  //cout << "After sort" << endl;
  t->print();


  /*t->deleteWord("ABCD");
  cout << "ABCD is deleted" << endl;

  t->print();*/


  //cout << "delete tree" << endl;
  delete(t);
  t = NULL;

}
