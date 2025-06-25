#include <iostream>
#include <sstream>
#include<signal.h>

#include "CTrie.h"

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void* context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
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
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] +=
    2;  // skip the seg fault
}

#define ASSERT(cond) \
do { \
  if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" \
       << " passed!" << endl; \
  } \
} while (0)
#endif

struct CTrieTest {
  static void DefaultConstructorTest() {
    CTrie q = CTrie();
    ASSERT(q.numChildren() == 0);
    ASSERT(!q.hasChild());
    ASSERT(q.isEndpoint() == false);
  }

  static void AddAssignOperatorTest() {
    CTrie q = CTrie();
    ASSERT(!q.hasChild('h'));
    q += "h";
    ASSERT(q.hasChild('h'));

    const CTrie *hChild = q.getChild('h');
    ASSERT(hChild != nullptr);
    ASSERT(!hChild->hasChild('i'));
    q += "hi";
    ASSERT(hChild->hasChild('i'));
  }

  static void CopyConstructorTest() {
    CTrie q = CTrie();
    q += "hello";
    q += "hell";
    q += "help";
    q += "johns";
    q += "joanna";
    q += "johnson";

    CTrie p(q);

    ASSERT((p == q));
    p += "jelly";
    ASSERT(!(p == q));
  }

  static void AssignmentOperatorTest() {
    CTrie q = CTrie();
    q += "hello";
 
    CTrie r = CTrie();
    r += "rice";
    r += "beans";

    ASSERT(q ^ "hello");
    ASSERT(!(q ^ "rice"));
    ASSERT(!(q ^ "beans"));
    ASSERT(!(r ^ "hello"));
    ASSERT(r ^ "rice");
    ASSERT(r ^ "beans");

    q = r;

    ASSERT(!(q ^ "hello"));
    ASSERT(q ^ "rice");
    ASSERT(q ^ "beans");
    ASSERT(!(r ^ "hello"));
    ASSERT(r ^ "rice");
    ASSERT(r ^ "beans");
  }

  static void CaratOperatorTest() {
    CTrie q = CTrie();
    q += "hello";
    ASSERT(q ^ "hello");
    ASSERT(!(q ^ "h"));
    q += "h";
    ASSERT((q ^ "h"));

    ASSERT(!(q ^ "hell"));
    q += "hell";
    ASSERT((q ^ "hell"));
  }

  static void ChainingTest() {
    CTrie q = CTrie();
    (q += "hello") += "help";
    ASSERT(q ^ "hello");
    ASSERT(q ^ "help");
    ASSERT(!(q ^ "hell"));
  }

  static void EqualityOperatorTest() {
    CTrie q = CTrie();
    q += "hello";
    q += "hell";
    q += "help";
    q += "johns";
    q += "joanna";
    q += "johnson";

    CTrie p = CTrie();
    p += "joanna";
    p += "johnson";
    p += "help";
    p += "johns";
    p += "hell";
    p += "hello";

    ASSERT((p == q));
    p += "howdy";
    ASSERT(!(p == q));
  }

  static void OutputStreamOperatorTest() {
    CTrie q = CTrie();
    q += "hello";
    q += "hell";
    q += "help";
    q += "johns";
    q += "joanna";
    q += "johnson";

    std::stringstream ss;
    ss << q;
    ASSERT(ss.str() == "hell\nhello\nhelp\njoanna\njohns\njohnson\n");
  }
};

int main(int, char* argv[]) {
  cout << "Testing CTrie" << endl;
  // register a seg fault hanlder
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);

  CTrieTest::DefaultConstructorTest();
  CTrieTest::AddAssignOperatorTest();
  CTrieTest::CopyConstructorTest();
  CTrieTest::AssignmentOperatorTest();
  CTrieTest::CaratOperatorTest();
  CTrieTest::ChainingTest();
  CTrieTest::EqualityOperatorTest();
  CTrieTest::OutputStreamOperatorTest();
}
