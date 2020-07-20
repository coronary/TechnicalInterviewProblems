const readline = require("readline");

//------------------------------Node Class------------------------------
class Node {
  value;
  left = null;
  right = null;
  parent = null;

  constructor(val = "!") {
    this.value = val;
  }
  setValue(val) {
    this.value = val;
  }
  setParent(node) {
    this.parent = node;
  }
  createParent(val) {
    this.parent = new Node(val);
    this.parent.setLeft(this);
  }
  setLeft(node) {
    this.left = node;
    this.left.setParent(this);
  }
  setRight(node) {
    this.right = node;
    this.right.setParent(this);
  }
  getValue() {
    return this.value;
  }
  getParent() {
    return this.parent;
  }
  getLeft() {
    return this.left;
  }
  getRight() {
    return this.right;
  }
}

//------------------------------Utils------------------------------

const symbols = "^/+-*";

function isParen(item) {
  //function to check if symbol is a paren
  return "()".includes(item);
}

function isNum(item) {
  //returns valid number with string and int representations, and NaN otherwise
  return parseInt(item);
}

function findRoot(node) {
  //traverses tree from given node until the root is found
  while (node.parent) {
    node = node.parent;
  }
  return node;
}

//------------------------------Setup------------------------------
//
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

//------------------------------Main------------------------------

rl.question("Input equation: ", async (answer) => {
  //anonymous callback function that parses an inputted equation into a binary tree. Cannot parse double digits.
  rl.close();
  let pieces = answer.split("");
  var current;
  pieces.forEach((item) => {
    let num = isNum(item);
    if (num) {
      //in Javascript NaN evaluates falsy. So only enter if the item is a valid number
      if (!current) {
        //no current node defined. Define one with current value
        current = new Node(num);
      } else if (!current.getLeft()) {
        //current node exists with no left child (which means no right child). Populate left child with new node
        current.setLeft(new Node(num));
      } else if (!current.getRight()) {
        //current node exists with no right child (which means left child exists). Populate right child with new node
        current.setRight(new Node(num));
      }
    } else if (symbols.includes(item) || isParen(item)) {
      //symbols include accepted operators. Also checks for parentheses
      if (item == "(") {
        if (current) {
          //lparen indicates that the innards will need to be evaluated first so create an empty node that will hold the operator when it gets there. If current exists then that means There is a left child and this has to be set to the right child and then set as the new current node
          current.setRight(new Node());
          current = current.getRight();
        } else {
          //indicates equation starts with parenthesis. Create empty node to be filled later with operator
          current = new Node();
        }
      } else if (!isParen(item)) {
        //Indicates operator
        if (current.getValue() == "!") {
          //indicates empty operator node to be filled with
          current.setValue(item);
        } else {
          //indicates that the current node is the operator of an expression in parentheses and creates a parent node connected to the current node before switching the current node to the parent
          current.createParent(item);
          current = current.getParent();
        }
      }
    }
  });
  console.log(await solve(findRoot(current)));
});

async function solve(node) {
  //recursive function that returns the output of an arithmetic equation formatted as a binary tree. Takes in the root of the tree.
  if (isNum(node.value)) {
    return node.value;
  } else if (node.value == "+") {
    return (await solve(node.left)) + (await solve(node.right));
  } else if (node.value == "*") {
    return (await solve(node.left)) * (await solve(node.right));
  } else if (node.value == "-") {
    return (await solve(node.left)) - (await solve(node.right));
  } else if (node.value == "/") {
    return (await solve(node.left)) / (await solve(node.right));
  } else if (node.value == "^") {
    return (await solve(node.left)) ** (await solve(node.right));
  }
}
