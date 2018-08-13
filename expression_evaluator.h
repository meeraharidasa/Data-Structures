#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cmath>
#include "./stack.h"
using namespace std;
using std::string;

Stack<double>valStck;
Stack<char> opStck;
class ExpressionEvaluator{
  //Stack<double> valStck;
  //Stack<char> opStck; 
 public:
  static double evaluate(string exp, double x, double y, double z){
    int i = 0; 
    while(exp[i] != '\0'){
      string number = "";
      while(isdigit(exp[i]) || exp[i] == '.'){
	number += exp[i];
	i++;
      }
      // if(exp[i] != 's' && exp[i] != 'c' && exp[i] != 't' && exp[i] != 'l' && exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/' && exp[i] != '^' && exp[i] != ')' && exp[i] != '(' && exp[i] != ' '){
      if(number != ""){
	double numCheck = stod(number);
	valStck.push(numCheck);
      }
	// }
      if(exp[i] == 'x'){
	valStck.push(x);
      }
      else if(exp[i] == 'y'){
	valStck.push(y);
      }
      else if(exp[i] == 'z'){
	valStck.push(z);
      }
      if(exp[i] == '('){
	opStck.push(exp[i]);
      }
      if(exp[i] == ')'){
	while(opStck.peep() != '('){
	  if(prec(exp[i]) <= prec(opStck.peep())){
	    char  op = opStck.pop();
	    double first = valStck.pop();
	    double second = valStck.pop();
	    double result = doOp(op,first,second);
	    valStck.push(result);
	  }
	  
	}
	opStck.pop();
	
	if(opStck.peep() == 's' || opStck.peep() == 'c' || opStck.peep() == 't' || opStck.peep() == 'l'){
	  char op1 = opStck.pop();
	  double first1 = valStck.pop();
	  double result1 = doOp(op1,first1,10);
	  valStck.push(result1);
	  
	}
      }
      else if(exp[i] == 's' || exp[i] == 'c' || exp[i] == 't' || exp[i] == 'l'){
	opStck.push(exp[i]);
	i += 2;
      }
      if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^'){
	while(!(opStck.isEmpty()) && (prec(opStck.peep()) >= prec(exp[i]))){
	  char op2 = opStck.pop();
	  double first2 = valStck.pop();
	  double second2 = valStck.pop();
	  double result2 = doOp(op2,first2,second2);
	  valStck.push(result2);
	}
	opStck.push(exp[i]);
      }
      i++;
    }

    while(!(opStck.isEmpty())){
      char op3 = opStck.pop();
      double first3 = valStck.pop();
      double second3 = valStck.pop();
      double result3 = doOp(op3, first3, second3);
      valStck.push(result3);
	  
	
	
      
	 
	 
	  
    }
	
  }

static  double doOp(char x, double y, double z){
    if(x == '*'){
      return z*y;
    }
    else if(x == '/'){
      return z/y;
    }
    else if(x == '+'){
      return z+y;
    }
    else if(x == '-'){
      return z-y;
    }
    else if(x == 's'){
      return sin(y * (M_PI/180));
    }
    else if(x == 'c'){
      return cos(y * (M_PI/180));
    }
    else if(x == 't'){
      return tan(y * (M_PI/180));
    }
    else if(x == 'l'){
      return log10(y);
    }
    return -1;
  }
static  double prec(char op){
    if(op == 's' || op == 'c' || op == 't' || op == '^' || op == 'l'){
      return 5;
    }
    else if( op == '*' || op == '/'){
      return 4;
    }
    else if(op == '+' || op == '-' || op == ')'){
      return 3;
    }
    return 0;
  }
};


