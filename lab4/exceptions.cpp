struct ItemNotInList : public std::exception {
   const char * what () const throw () {
      return "Item is not in list";
   }
};

struct ListIsFull : public std::exception {
   const char * what () const throw () {
      return "List is full";
   }
};

struct ListIsEmpty : public std::exception {
   const char * what () const throw () {
      return "List is empty";
   }
};
