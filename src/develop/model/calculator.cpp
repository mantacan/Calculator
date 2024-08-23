#include <utility>

#include "../smartcalc.h"

namespace s21 {

/**
 * @brief Default constructor initializing model with empty values.
 */
model::model()
    : expression(""),
      postfixExpression(""),
      x_values(),
      y_values(),
      x(0),
      result(0) {}

/**
 * @brief Constructor initializing model with a given expression.
 * @param str Initial mathematical expression as a string.
 * Processes the expression, calculates related graph data, validates the
 * expression, converts infix to postfix if valid, and finally calculates the
 * expression.
 */
model::model(const std::string &str)
    : expression(str),
      postfixExpression(""),
      x_values(),
      y_values(),
      x(0),
      result(0) {
  processExpression();
  calculateGraphData();
  isValid();

  if (!error) {
    infixToPostfix();
    calculate();
    everythingOkay();
  } else {
    returnResult = "NOT VALID EXPRESSION";
  }
}

/**
 * @brief Destructor.
 */
model::~model() {}

/**
 * @brief Converts a numeric value to its natural logarithm.
 * @param value A double value to compute the logarithm for.
 * @return Natural logarithm of the given value.
 */
double myLog(double value) { return std::log(value); }

/**
 * @brief Converts a numeric value to its logarithm base 10.
 * @param value A double value to compute the logarithm for.
 * @return Logarithm base 10 of the given value.
 */
double myLog10(double value) { return std::log10(value); }

/**
 * @brief Converts the calculation result from double to string with fixed
 * precision.
 */
void model::fromDoubleToString() {
  std::ostringstream oss;
  oss.precision(2);
  oss << std::fixed << result;
  returnResult = oss.str();
}

/**
 * @brief Validates the current mathematical expression.
 * Checks if the custom functions defined in the parser are valid within the
 * expression context.
 */
void model::isValid() {
  if (!checkFunctions()) {
    error = true;
  }
}

/**
 * @brief Retrieves the current mathematical expression.
 * @return The mathematical expression as a string.
 */
std::string model::getExpression() { return expression; }

/**
 * @brief Retrieves the current postfix expression.
 * @return The postfix expression as a string.
 */
std::string model::getPostfixExpression() { return postfixExpression; }

/**
 * @brief Retrieves the X values for graph plotting.
 * @return A constant reference to the vector of X values.
 */
const std::vector<double> &model::getXValues() const { return x_values; }

/**
 * @brief Retrieves the Y values for graph plotting.
 * @return A constant reference to the vector of Y values.
 */
const std::vector<double> &model::getYValues() const { return y_values; }

/**
 * @brief Retrieves the result of the mathematical expression evaluation.
 * @return The result as a string.
 */
std::string model::getResult() { return returnResult; }

/**
 * @brief Checks if a given string is an operator.
 * @param token The string to check.
 * @return True if the string is an operator, false otherwise.
 */
bool model::isOperator(const std::string &token) {
  return token == "+" || token == "-" || token == "*" || token == "/" ||
         token == "^" || token == "%";
}

/**
 * @brief Determines the precedence of an operator used in the expression.
 * @param op The operator to evaluate.
 * @return The precedence level as an integer.
 */
int model::precedence(const std::string &op) {
  if (op == "+" || op == "-") return 1;
  if (op == "*" || op == "/" || op == "%") return 2;
  if (op == "^") return 3;
  return 0;
}

/**
 * @brief Checks if the given operator is left associative.
 * @param op The operator to check.
 * @return True if the operator is left associative, false otherwise.
 */
bool model::isLeftAssociative(const std::string &op) { return op != "^"; }

/**
 * @brief Processes the mathematical expression to extract the value of 'x' and
 * update the expression accordingly.
 *
 * This method searches for a pattern to isolate the value assigned to 'x' and
 * then replaces all instances of 'x' in the expression with this numerical
 * value.
 */
void model::processExpression() {
  std::regex pattern(R"(\|\s*x\s*=\s*([-+]?\d*\.?\d+))");
  std::smatch matches;

  if (std::regex_search(expression, matches, pattern)) {
    x = std::stod(matches[1].str());
    size_t pos = expression.find('|');
    if (pos != std::string::npos) {
      expression = expression.substr(0, pos);
    }
    replaceXWithNumber();
  }
}

/**
 * @brief Verifies the mathematical functions defined in the expression are
 * valid.
 *
 * Custom functions like 'ln' and 'log' are defined and tested against the
 * current expression to ensure they do not result in errors upon evaluation.
 * @return True if the functions are valid within the expression context; False
 * otherwise.
 */
bool model::checkFunctions() {
  parser.DefineFun("ln", myLog);
  parser.DefineFun("log", myLog10);

  try {
    parser.SetExpr(expression);
    double smartCheck = parser.Eval();
    if (std::isnan(smartCheck) || std::isnan(-smartCheck)) {
      return false;
    }
    std::cout << "RES " << smartCheck << std::endl;

    parser.Eval();
    return true;
  } catch (const mu::Parser::exception_type &e) {
    std::cerr << "Parsing error: " << e.GetMsg() << std::endl;
    return false;
  }
}

/**
 * @brief Sets an error message and flags the current state as erroneous.
 * @param errorsMessage A message describing the error that occurred.
 */
void model::setErrors(std::string errorsMessage) {
  error = true;
  message = std::move(errorsMessage);
}

/**
 * @brief Final validation to ensure the computational process has completed
 * without errors.
 *
 * If no errors are found, it converts the numeric result to a string format;
 * otherwise, it sets the result to an error message.
 */
void model::everythingOkay() {
  if (error) {
    returnResult = message;
  } else {
    fromDoubleToString();
  }
}

/**
 * @brief Replaces all occurrences of 'x' in the expression with its current
 * numeric value.
 */

void model::replaceXWithNumber() {
  std::regex xPattern("x");
  expression = std::regex_replace(expression, xPattern, std::to_string(x));
}

/**
 * @brief Replaces all occurrences of 'x' in a given expression with a specified
 * numeric value.
 * @param value The numeric value to replace 'x' with.
 * @param expression The expression where 'x' will be replaced.
 */
void model::GraphReplaceXWithNumber(double value, std::string &expression) {
  std::regex xPattern("x");
  expression = std::regex_replace(expression, xPattern, std::to_string(value));
}

/**
 * @brief Converts an infix mathematical expression into postfix notation.
 *
 * This method uses a stack to reorder the operators and operands to postfix
 * format, facilitating easier computation.
 */
void model::infixToPostfix() {
  std::stack<std::string> stack;
  std::string output;
  std::unordered_set<std::string> func{"cos",  "sin",  "tan", "acos", "asin",
                                       "atan", "sqrt", "ln",  "log"};

  for (size_t i = 0; i < expression.size(); ++i) {
    char c = expression[i];

    if (isdigit(c) || c == '.') {
      std::string number;
      bool decimalFound = false;
      while (
          i < expression.size() &&
          (isdigit(expression[i]) || (expression[i] == '.' && !decimalFound))) {
        if (expression[i] == '.') {
          if (!decimalFound) {
            decimalFound = true;
          } else {
            break;
          }
        }
        number += expression[i++];
      }
      --i;
      output += number + " ";
    } else if (isalpha(c)) {
      std::string token;
      while (i < expression.size() && isalpha(expression[i]))
        token += expression[i++];
      --i;
      if (func.find(token) != func.end()) {
        stack.push(token);
      } else {
        output += token + " ";
      }
    } else if (c == '(') {
      stack.push("(");
    } else if (c == ')') {
      while (!stack.empty() && stack.top() != "(") {
        output += stack.top() + " ";
        stack.pop();
      }
      stack.pop();
      if (!stack.empty() && func.find(stack.top()) != func.end()) {
        output += stack.top() + " ";
        stack.pop();
      }
    } else if (isOperator(std::string(1, c))) {
      std::string op(1, c);
      while (!stack.empty() && isOperator(stack.top()) &&
             ((isLeftAssociative(op) &&
               precedence(op) <= precedence(stack.top())) ||
              (!isLeftAssociative(op) &&
               precedence(op) < precedence(stack.top())))) {
        output += stack.top() + " ";
        stack.pop();
      }
      stack.push(op);
    }
  }

  while (!stack.empty()) {
    output += stack.top() + " ";
    stack.pop();
  }

  postfixExpression = output;
}

/**
 * @brief Computes the result of the mathematical expression after converting it
 * to postfix notation.
 *
 * This method evaluates the postfix expression using a stack to handle operands
 * and operators, calculating the result as it proceeds.
 */
void model::calculate() {
  std::stack<double> stack;
  std::istringstream iss(postfixExpression);
  std::string token;

  while (iss >> token && !error) {
    if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
      double num = std::stod(token);
      stack.push(num);
    } else if (isOperator(token)) {
      double second = stack.top();
      stack.pop();
      double first = stack.top();
      stack.pop();
      double result = 0;
      if (token == "+")
        result = first + second;
      else if (token == "-")
        result = first - second;
      else if (token == "*")
        result = first * second;
      else if (token == "/") {
        if (second == 0) {
          setErrors("division by zero");
          continue;
        }
        result = first / second;
      } else if (token == "^") {
        result = pow(first, second);
      }
      stack.push(result);
    } else {
      double operand = stack.top();
      stack.pop();
      double result = applyFunction(token, operand);
      stack.push(result);
    }
  }
  if (!error) {
    if (stack.size() != 1) setErrors("Invalid postfix expression.");
    this->result = stack.top();
  }
}

/**
 * @brief Calculates and returns the result of a binary operation between two
 * numbers.
 * @param first The first operand.
 * @param second The second operand.
 * @param op The operator to apply.
 * @return The result of the operation.
 */
double model::applyOperation(double first, double second,
                             const std::string &op) {
  if (op == "+")
    return first + second;
  else if (op == "-")
    return first - second;
  else if (op == "*")
    return first * second;
  else if (op == "/")
    return (second != 0) ? first / second
                         : std::numeric_limits<double>::quiet_NaN();
  else if (op == "^")
    return std::pow(first, second);
  return 0;
}

/**
 * @brief Generates data for graph plotting based on the computed X and Y
 * values.
 *
 * This method recalculates the expression for a range of X values to produce
 * the corresponding Y values, which are used for graph plotting.
 */
void model::calculateGraphData() {
  x_values.clear();
  y_values.clear();

  std::cout << "X VAL: " << x << std::endl;

  x_start = x - 5;
  x_end = x + 5;
  x_step = 0.2;

  for (double x = x_start; x <= x_end; x += x_step) {
    x_values.push_back(x);
    std::string tempExpression = postfixExpression;
    GraphReplaceXWithNumber(x, tempExpression);
    std::istringstream iss(tempExpression);
    std::string token;
    std::stack<double> stack;

    while (iss >> token) {
      if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
        stack.push(std::stod(token));
      } else if (isOperator(token)) {
        double second = stack.top();
        stack.pop();
        double first = stack.top();
        stack.pop();
        double result = applyOperation(first, second, token);
        stack.push(result);
      } else {
        double operand = stack.top();
        stack.pop();
        double result = applyFunction(token, operand);
        stack.push(result);
      }
    }
    if (!stack.empty()) {
      double y = stack.top();
      y_values.push_back(y);
    }
  }
}

/**
 * Applies the specified mathematical function to the given operand.
 *
 * @param func The name of the mathematical function to apply.
 * @param operand The value to which the function is applied.
 * @return The result of applying the function to the operand.
 *         If an error occurs, returns 0 and sets the error flag.
 */
double model::applyFunction(const std::string &func, double operand) {
  while (!error) {
    if (func == "sin") {
      return sin(operand);
    } else if (func == "cos") {
      return cos(operand);
    } else if (func == "tan") {
      return tan(operand);
    } else if (func == "asin") {
      if (operand < -1.0 || operand > 1.0) {
        error = true;
        return 0;
      }
      return asin(operand);
    } else if (func == "acos") {
      if (operand < -1.0 || operand > 1.0) {
        error = true;
        return 0;
      }
      return acos(operand);
    } else if (func == "atan") {
      return atan(operand);
    } else if (func == "sqrt") {
      if (operand < 0) {
        error = true;
        return 0;
      }
      return sqrt(operand);
    } else if (func == "ln") {
      if (operand <= 0) {
        error = true;
        return 0;
      }
      return log(operand);
    } else if (func == "log") {
      if (operand <= 0) {
        error = true;
        return 0;
      }
      return log10(operand);
    } else {
      error = true;
      return 0;
    }
  }
  return 0;
}

};  // namespace s21
