#ifndef TTRIE_H
#define TTRIE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

template< typename DataType>
class TTrie {
public:
  /**
   * Default Constructor.
   */
  TTrie();

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
  TTrie(const TTrie& rhs);

  /**
   * Destructor.
   */
  ~TTrie();

  /**
   * Assignment operator.
   */
  TTrie& operator=(const TTrie<DataType> &rhs);

  /**
   * Overloaded addition/assignment operator to input a new vector into the TTrie.
   * \param sequence is the vector to insert into the trie
   * \return a reference to the TTrie object
   */
  TTrie& operator+=(const std::vector<DataType>& sequence);

  /**
   * Overloaded carat operator to check whether a given sequence exists in the object.
   * \param sequence is the sequence to find
   * \return true if the sequence is a member of the trie, false otherwise
   */
  bool operator^(const std::vector<DataType> &sequence) const;

  /**
   * Overloaded equality operator to check whether two TTrie objects are equal.
   * \param rhs A const reference to the TTrie object to compare.
   * \return true if the other object represents exactly the same set of sequences,
   *         false otherwise
   */
  bool operator==(const TTrie<DataType>& rhs) const;

  /**
   * \brief Overloaded output stream operator<< to print the sequences
   *        in the TTrie one per line, with values separated by '-'
   *        (hyphen) characters, in lexicographical order (note that if
   *        you use a map to represent links to children, a recursive
   *        traversal should allow you to generate the sequences in
   *        sorted order very easily)
   * \param os A reference to the output stream object
   * \param tt A constant reference to the input TTrie object
   * \return A reference to the output stream object
  */
  template< typename U>
  friend std::ostream& operator<<(std::ostream& os, const TTrie<U>& tt);

  /**
   * \return the number of children
   */
  unsigned numChildren() const;

  /**
   * \return true if there are any children, false otherwise
   */
  bool hasChild() const;

  /**
   * Check whether a child linked by a specific value exists.
   * \param value a value
   * \return true if there is a link to a child labeled with the value,
   *         false otherwise
   */
  bool hasChild(const DataType &value) const;

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified value.
   * \param value a value
   * \return pointer to child node, or nullptr if there is no such child
   */
  const TTrie<DataType>* getChild(const DataType &value) const;

  /**
   * \return true if this node is an endpoint, false otherwise
   */
  bool isEndpoint() const; 

private:
  // TODO: fields

  // TODO: helper functions
};

#include "TTrie.inc"

#endif // TTRIE_H
