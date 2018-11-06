#pragma once

#include "signal.hpp"

namespace ctree {

  //! signal_vector extends std::vector with two public Signal attributes;
  //! `newItemSignal` and `itemRemovedSignal`, which are emited when mutations
  //! on the vector happen.
  template<typename T>
  class signal_vector : public std::vector<T> {

    public:
      // modifier methods
      bool push_back(T item);
      void clear();

      // TODO overload the remaining modifier methods to make sure they all trigger the necessary event(s)
      // void insert(T item){ std::cerr << "ctree::signal_vector::insert not yet implemented"; }
      // emplace
      // emplace_back
      // pop_back
      // resize
      // swap

  	  typename std::vector<T>::iterator erase(typename std::vector<T>::iterator pos) {
  		  T removed = (pos != this->end()) ? *pos : nullptr;

  		  auto result = std::vector<T>::erase(pos);

  		  if (removed) {
  			  itemRemovedSignal.emit(removed);
  		  }

  		  return result;
  	  }

  	  typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator pos) {
  		  T removed = (pos != this->end()) ? *pos : nullptr;

  		  auto result = std::vector<T>::erase(pos);

  		  if (removed) {
  			  itemRemovedSignal.emit(*pos);
  		  }

  		  return result;
  	  }

      typename std::vector<T>::iterator erase(typename std::vector<T>::iterator first, typename  std::vector<T>::iterator last ) {
  		  typename std::vector<T> removes(first, last);

  		  auto result = std::vector<T>::erase(first, last);

  		  for (auto item : removes) {
  			  itemRemovedSignal.emit(item);
  		  }

  		  return result;
  	  }

  	  typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last) {
  		  typename std::vector<T> removes(first, last);

  		  auto result = std::vector<T>::erase(first, last);

  		  for (auto item : removes) {
  			  itemRemovedSignal.emit(item);
  		  }

  		  return result;
  	  }

      typename std::vector<T>::iterator erase(T item) {
        return this->erase(std::find(this->begin(), this->end(), item));
      }

    public: // signals
      Signal<void(T)> newItemSignal;
      Signal<void(T)> itemRemovedSignal;
  };

  template<typename T>
  bool ctree::signal_vector<T>::push_back(T item){
    bool containsAlready = std::find(this->begin(), this->end(), item) != this->end();

    if(containsAlready)
      return false;

    std::vector<T>::push_back(item);
    this->newItemSignal.emit(item);
    return true;
  }

  template<typename T>
  void ctree::signal_vector<T>::clear(){
    for(int i=this->size()-1; i>=0; i--)
      this->erase((*this)[i]);
  }
}
