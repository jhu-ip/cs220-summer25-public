#include "TTrie.h"

#include <iostream>
#include <sstream>
#include<signal.h>

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler 
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void *context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName, (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;  
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] +=2 ; // skip the seg fault
}

#define ASSERT(cond) \
do { \
  if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" << " passed!" << endl; \
  } \
} while (0)
#endif

struct TTrieTest {

  // alias
  using CTrie = TTrie<char>;
  using STrie = TTrie<std::string>;
  using ITrie = TTrie<int>;

  static void DefaultConstructorTest() {
    CTrie q = CTrie();
    ASSERT(q.numChildren() == 0);
    ASSERT(!q.hasChild());
    ASSERT(!q.isEndpoint());

    ITrie r = ITrie();
    ASSERT(r.numChildren() == 0);
    ASSERT(!r.hasChild());
    ASSERT(!r.isEndpoint());

    STrie s = STrie();
    ASSERT(s.numChildren() == 0);
    ASSERT(!s.hasChild());
    ASSERT(!s.isEndpoint());
  }

  static void AddAssignOperatorTest() {
    CTrie q = CTrie();
    ASSERT(!q.hasChild('h'));
    std::vector<char> h({'h'});

    q += h;
    ASSERT(q.hasChild('h'));

    const CTrie *hChild = q.getChild('h');
    ASSERT(hChild != nullptr);
    ASSERT(!hChild->hasChild('i'));
    std::vector<char> hi({'h', 'i'});
    q += hi;
    ASSERT(hChild->hasChild('i'));

    STrie r = STrie();
    std::string test1("test1");
    std::string test2("test2");
    ASSERT(!r.hasChild(test1));
    std::vector<std::string> vec1, vec2;
    vec1.push_back(test1);
    vec2.push_back(test1);
    vec2.push_back(test2);
    r += vec1;
    ASSERT(r.hasChild(test1));

    const STrie *test1Child = r.getChild(test1);
    ASSERT(test1Child != nullptr);
    ASSERT(!test1Child->hasChild(test2));
    r += vec2;
    ASSERT(test1Child->hasChild(test2));
  }

  static void CopyConstructorTest() {
    CTrie q = CTrie();
    std::vector<char> hello({'h', 'e', 'l', 'l', 'o'});
    std::vector<char> hell({'h', 'e', 'l', 'l'});
    std::vector<char> help({'h', 'e', 'l', 'p'});
    std::vector<char> johns({'j', 'o', 'h', 'n', 's'});
    std::vector<char> johnson({'j', 'o', 'h', 'n', 's', 'o', 'n'});
    std::vector<char> joanna({'j', 'o', 'a', 'n', 'n', 'a'});

    q += hello;
    q += hell;
    q += help;
    q += johns;
    q += joanna;
    q += johnson;

    CTrie p(q);
    
    ASSERT(p == q);
    ASSERT(q == p);
    std::vector<char> jelly({'j', 'e', 'l', 'l', 'y'});
    p += jelly;
    ASSERT(!(p == q));

    ITrie it1;
    std::vector<int> iseq1({8, 6, 7, 5, 3, 0, 9});
    std::vector<int> iseq2({8, 6, 7, 101});
    std::vector<int> iseq3({8, 6, 7, 101, 3, 4, 5});
    std::vector<int> iseq4({90125});

    it1 += iseq1;
    it1 += iseq2;
    it1 += iseq3;
    it1 += iseq4;

    ITrie it2(it1);
    ASSERT(it1 == it2);
    ASSERT(it2 == it1);

    std::vector<int> iseq5({8, 6, 7, 101, 2});
    it1 += iseq5;
    ASSERT(!(it1 == it2));
    ASSERT(!(it2 == it1));

    STrie st1;
    std::vector<std::string> sseq1({"spam", "spam", "spam", "baked beans", "spam"});
    std::vector<std::string> sseq2({"spam", "spam", "spam"});
    std::vector<std::string> sseq3({"avocado", "egg"});
    std::vector<std::string> sseq4({"avocado", "marmalade"});
    std::vector<std::string> sseq5({"potato"});
    std::vector<std::string> sseq6({"avocado", "toast"});

    st1 += sseq1;
    st1 += sseq2;
    st1 += sseq3;
    st1 += sseq4;
    st1 += sseq5;
    st1 += sseq6;

    STrie st2(st1);
    ASSERT(st1 == st2);
    ASSERT(st2 == st1);
    std::vector<std::string> sseq7({"avocado", "souffle"});
    st2 += sseq7;
    ASSERT(!(st1 == st2));
    ASSERT(!(st2 == st1));
  }

  static void AssignmentOperatorTest() {
    CTrie ct1, ct2;

    std::vector<char> cseq1({'a', 'b', 'c'});
    std::vector<char> cseq2({'a', 'b', 'd'});
    std::vector<char> cseq3({'a', 'c', 'b'});

    ct1 += cseq1;
    ct1 += cseq2;

    ct2 += cseq3;

    ASSERT(ct1 ^ cseq1);
    ASSERT(ct1 ^ cseq2);
    ASSERT(!(ct1 ^ cseq3));

    ASSERT(!(ct2 ^ cseq1));
    ASSERT(!(ct2 ^ cseq2));
    ASSERT(ct2 ^ cseq3);

    ct1 = ct2; // assign contents of ct2 to ct1

    ASSERT(!(ct1 ^ cseq1));
    ASSERT(!(ct1 ^ cseq2));
    ASSERT(ct1 ^ cseq3);

    ASSERT(!(ct2 ^ cseq1));
    ASSERT(!(ct2 ^ cseq2));
    ASSERT(ct2 ^ cseq3);

    ITrie it1, it2;

    std::vector<int> iseq1({1, 2, 3});
    std::vector<int> iseq2({1, 2, 4});
    std::vector<int> iseq3({1, 3, 4, 5});

    it1 += iseq1;
    it1 += iseq2;

    it2 += iseq3;

    ASSERT(it1 ^ iseq1);
    ASSERT(it1 ^ iseq2);
    ASSERT(!(it1 ^ iseq3));

    ASSERT(!(it2 ^ iseq1));
    ASSERT(!(it2 ^ iseq2));
    ASSERT(it2 ^ iseq3);

    it1 = it2; // assign contents of it2 to it1

    ASSERT(!(it1 ^ iseq1));
    ASSERT(!(it1 ^ iseq2));
    ASSERT(it1 ^ iseq3);

    ASSERT(!(it2 ^ iseq1));
    ASSERT(!(it2 ^ iseq2));
    ASSERT(it2 ^ iseq3);

    STrie st1, st2;

    std::vector<std::string> sseq1({"rice", "beans"});
    std::vector<std::string> sseq2({"rice", "beans", "avocado"});
    std::vector<std::string> sseq3({"quinoa", "mushrooms"});

    st1 += sseq1;
    st1 += sseq2;

    st2 += sseq3;

    ASSERT(st1 ^ sseq1);
    ASSERT(st1 ^ sseq2);
    ASSERT(!(st1 ^ sseq3));

    ASSERT(!(st2 ^ sseq1));
    ASSERT(!(st2 ^ sseq2));
    ASSERT(st2 ^ sseq3);

    st1 = st2; // assign contents of st2 to st1

    ASSERT(!(st1 ^ sseq1));
    ASSERT(!(st1 ^ sseq2));
    ASSERT(st1 ^ sseq3);

    ASSERT(!(st2 ^ sseq1));
    ASSERT(!(st2 ^ sseq2));
    ASSERT(st2 ^ sseq3);
  }

  static void CaratOperatorTest() {
    CTrie q = CTrie();
    std::vector<char> hello({'h', 'e', 'l', 'l', 'o'});
    std::vector<char> h({'h'});
    std::vector<char> hell({'h', 'e', 'l', 'l'});

    q += hello;

    ASSERT(q ^ hello);
    ASSERT(!(q ^ h));
    q += h;
    ASSERT((q ^ h));

    ASSERT(!(q ^ hell));
    q += hell;
    ASSERT((q ^ hell));

    ITrie it1;
    std::vector<int> iseq1({8, 6, 7, 5, 3, 0, 9});
    std::vector<int> iseq2({8, 6, 7, 101});
    std::vector<int> iseq3({8, 6, 7, 101, 3, 4, 5});
    std::vector<int> iseq4({90125});
    std::vector<int> iseq5({8, 6, 7, 101, 2});

    it1 += iseq1;
    it1 += iseq5;

    ASSERT(it1 ^ iseq1);
    ASSERT(it1 ^ iseq5);
    ASSERT(!(it1 ^ iseq2));
    ASSERT(!(it1 ^ iseq3));
    ASSERT(!(it1 ^ iseq4));

    it1 += iseq2;
    it1 += iseq3;
    it1 += iseq4;

    ASSERT(it1 ^ iseq2);
    ASSERT(it1 ^ iseq3);
    ASSERT(it1 ^ iseq4);

    std::vector<int> iseq6({8, 6, 7});
    ASSERT(!(it1 ^ iseq6));

    STrie st1;
    std::vector<std::string> sseq1({"spam", "spam", "spam", "baked beans", "spam"});
    std::vector<std::string> sseq2({"spam", "spam", "spam"});
    std::vector<std::string> sseq3({"avocado", "egg"});
    std::vector<std::string> sseq4({"avocado", "marmalade"});
    std::vector<std::string> sseq5({"potato"});
    std::vector<std::string> sseq6({"avocado", "toast"});
    std::vector<std::string> sseq7({"avocado", "souffle"});

    st1 += sseq1;

    ASSERT(st1 ^ sseq1);
    ASSERT(!(st1 ^ sseq2));
    ASSERT(!(st1 ^ sseq3));
    ASSERT(!(st1 ^ sseq4));
    ASSERT(!(st1 ^ sseq5));
    ASSERT(!(st1 ^ sseq6));
    ASSERT(!(st1 ^ sseq7));

    st1 += sseq2;
    st1 += sseq3;
    st1 += sseq4;
    st1 += sseq5;
    st1 += sseq6;

    ASSERT(st1 ^ sseq1);
    ASSERT(st1 ^ sseq2);
    ASSERT(st1 ^ sseq3);
    ASSERT(st1 ^ sseq4);
    ASSERT(st1 ^ sseq5);
    ASSERT(st1 ^ sseq6);
    ASSERT(!(st1 ^ sseq7));

    st1 += sseq7;
    ASSERT(st1 ^ sseq7);
  }

  static void ChainingTest() {
    CTrie p;
    std::vector<char> hello({'h', 'e', 'l', 'l', 'o'});
    std::vector<char> hell({'h', 'e', 'l', 'l'});
    std::vector<char> help({'h', 'e', 'l', 'p'});

    (p += hello) += help;
    ASSERT(p ^ hello);
    ASSERT(p ^ help);
    ASSERT(!(p ^ hell));

    ITrie q;
    std::vector<int> iseq1({8, 6, 7, 5, 3, 0, 9});
    std::vector<int> iseq2({8, 6, 7, 101});
    std::vector<int> iseq3({8, 6, 7, 101, 3, 4, 5});
    (q += iseq1) += iseq3;
    ASSERT(q ^ iseq1);
    ASSERT(q ^ iseq3);
    ASSERT(!(q ^ iseq2));

    STrie r;
    std::vector<std::string> sseq1({"spam", "spam", "spam", "baked beans", "spam"});
    std::vector<std::string> sseq2({"spam", "spam", "spam"});
    std::vector<std::string> sseq3({"avocado", "egg"});

    (r += sseq1) += sseq3;
    ASSERT(r ^ sseq1);
    ASSERT(r ^ sseq3);
    ASSERT(!(r ^ sseq2));
  }

  static void EqualityOperatorTest() {
    CTrie q = CTrie();
    std::vector<char> hello({'h', 'e', 'l', 'l', 'o'});
    std::vector<char> hell({'h', 'e', 'l', 'l'});
    std::vector<char> help({'h', 'e', 'l', 'p'});
    std::vector<char> johns({'j', 'o', 'h', 'n', 's'});
    std::vector<char> johnson({'j', 'o', 'h', 'n', 's', 'o', 'n'});
    std::vector<char> joanna({'j', 'o', 'a', 'n', 'n', 'a'});

    q += hello;
    q += hell;
    q += help;
    q += johns;
    q += joanna;
    q += johnson;

    CTrie p = CTrie();
    p += hello;
    p += hell;
    p += help;
    p += johns;
    p += joanna;
    p += johnson;

    ASSERT(p == q);
    ASSERT(q == p);
    std::vector<char> howdy({'h', 'o', 'w', 'd', 'y'});
    p += howdy;
    ASSERT(!(p == q));

    ITrie it1;
    std::vector<int> iseq1({8, 6, 7, 5, 3, 0, 9});
    std::vector<int> iseq2({8, 6, 7, 101});
    std::vector<int> iseq3({8, 6, 7, 101, 3, 4, 5});
    std::vector<int> iseq4({90125});
    std::vector<int> iseq5({8, 6, 7, 101, 2});
    it1 += iseq1;
    it1 += iseq2;
    it1 += iseq3;
    it1 += iseq4;
    it1 += iseq5;

    ITrie it2;
    it2 += iseq1;
    it2 += iseq2;
    it2 += iseq3;
    it2 += iseq4;
    it2 += iseq5;

    ASSERT(it1 == it2);
    ASSERT(it2 == it1);

    std::vector<int> iseq6({8, 6, 7});
    it1 += iseq6;
    ASSERT(!(it1 == it2));
    ASSERT(!(it2 == it1));

    STrie st1;
    std::vector<std::string> sseq1({"spam", "spam", "spam", "baked beans", "spam"});
    std::vector<std::string> sseq2({"spam", "spam", "spam"});
    std::vector<std::string> sseq3({"avocado", "egg"});
    std::vector<std::string> sseq4({"avocado", "marmalade"});
    std::vector<std::string> sseq5({"potato"});
    std::vector<std::string> sseq6({"avocado", "toast"});

    st1 += sseq1;
    st1 += sseq2;
    st1 += sseq3;
    st1 += sseq4;
    st1 += sseq5;
    st1 += sseq6;

    STrie st2;
    st2 += sseq1;
    st2 += sseq2;
    st2 += sseq3;
    st2 += sseq4;
    st2 += sseq5;
    st2 += sseq6;

    ASSERT(st1 == st2);
    ASSERT(st2 == st1);

    std::vector<std::string> sseq7({"avocado", "souffle"});
    st1 += sseq7;

    ASSERT(!(st1 == st2));
    ASSERT(!(st2 == st1));
  }

  static void OutputStreamOperatorTest() {
    CTrie q = CTrie();
    std::vector<char> hello({'h', 'e', 'l', 'l', 'o'});
    std::vector<char> hell({'h', 'e', 'l', 'l'});
    std::vector<char> help({'h', 'e', 'l', 'p'});
    std::vector<char> johns({'j', 'o', 'h', 'n', 's'});
    std::vector<char> johnson({'j', 'o', 'h', 'n', 's', 'o', 'n'});
    std::vector<char> joanna({'j', 'o', 'a', 'n', 'n', 'a'});

    q += hello;
    q += hell;
    q += help;
    q += johns;
    q += joanna;
    q += johnson;

    std::stringstream ss;
    ss << q;
    ASSERT(ss.str() == "h-e-l-l\nh-e-l-l-o\nh-e-l-p\nj-o-a-n-n-a\nj-o-h-n-s\nj-o-h-n-s-o-n\n");

    ITrie it1;
    std::vector<int> iseq1({8, 6, 7, 5, 3, 0, 9});
    std::vector<int> iseq2({8, 6, 7, 101});
    std::vector<int> iseq3({8, 6, 7, 101, 3, 4, 5});
    std::vector<int> iseq4({90125});
    std::vector<int> iseq5({8, 6, 7, 101, 2});

    it1 += iseq1;
    it1 += iseq2;
    it1 += iseq3;
    it1 += iseq4;
    it1 += iseq5;

    std::stringstream ss2;
    ss2 << it1;
    ASSERT(ss2.str() == "8-6-7-5-3-0-9\n"
                        "8-6-7-101\n"
                        "8-6-7-101-2\n"
                        "8-6-7-101-3-4-5\n"
                        "90125\n");

    STrie st1;
    std::vector<std::string> sseq1({"spam", "spam", "spam", "baked beans", "spam"});
    std::vector<std::string> sseq2({"spam", "spam", "spam"});
    std::vector<std::string> sseq3({"avocado", "egg"});
    std::vector<std::string> sseq4({"avocado", "marmalade"});
    std::vector<std::string> sseq5({"potato"});
    std::vector<std::string> sseq6({"avocado", "toast"});
    std::vector<std::string> sseq7({"avocado", "souffle"});

    st1 += sseq1;
    st1 += sseq2;
    st1 += sseq3;
    st1 += sseq4;
    st1 += sseq5;
    st1 += sseq6;
    st1 += sseq7;

    std::stringstream ss3;
    ss3 << st1;
    ASSERT(ss3.str() == "avocado-egg\n"
                        "avocado-marmalade\n"
                        "avocado-souffle\n"
                        "avocado-toast\n"
                        "potato\n"
                        "spam-spam-spam\n"
                        "spam-spam-spam-baked beans-spam\n");
  }

};

int main(int, char* argv[]) {
  cout << "Testing TTrie" << endl;
  // register a seg fault hanlder
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);

  TTrieTest::DefaultConstructorTest();
  TTrieTest::AddAssignOperatorTest();
  TTrieTest::CopyConstructorTest();
  TTrieTest::AssignmentOperatorTest();
  TTrieTest::CaratOperatorTest();
  TTrieTest::ChainingTest();
  TTrieTest::EqualityOperatorTest();
  TTrieTest::OutputStreamOperatorTest();
}
