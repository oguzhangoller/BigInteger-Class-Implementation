/*
Student Name: 
Student Number: 
Project Number: 
Operating System: 
Compile Status: 
Program Status: 
Notes: Anything you want to say about your code that will be helpful in the grading process.

*/

#include "BigInteger.h"
#include <algorithm>
#include <stack>



    BigInteger :: BigInteger(int number){
        this->num = new LinkedList;
        num->head = new Node(0) ;
    }

    /*
     * Here i kept the numbers from string in reverse order
     * for instance : "498" is held as "894"
     */

    BigInteger :: BigInteger(const string& bigInteger)
    {
        this->num = new LinkedList;



        stack<int> st ;         //i used a stack to keep numbers in reverse order
        int length = bigInteger.length();
        int count = 0 ;
            while (length / 1 > 0) {        //for keeping only one digit in a node

                int data = std::stoi(bigInteger.substr(count, 1));
                st.push(data);
                count += 1;
                length -= 1;
            }

        while(!st.empty()){
            this->num->pushTail(st.top());      //for keeping digits in reverse order
            st.pop();
        }

    }

    BigInteger BigInteger :: operator+(const BigInteger &list) {

        BigInteger sum ;
        sum.num = new LinkedList;
        int length1, length2 ;
        Node *n1 = this->num->head;
        Node *n2 = list.num->head;
        length1 = this->num->length ;
        length2 = list.num->length ;
        int leftover = 0 ;          //keeps the left digit of addition if greater than 9
        if(length1<length2) {       //if *this is less than &list
            for (int i = 0; i < length1; i++) {         //add numbers according to *this' number of digits
                int sumData = n1->data + n2->data + leftover ;
                leftover = 0 ;
                if(sumData>9){
                    int firstDigit = sumData / 10 ;
                    int secondDigit = sumData % 10 ;
                    sum.num->pushTail(secondDigit);     //push the right digit and store left digit if greater than 10
                    leftover = firstDigit ;
                }
                else {
                    sum.num->pushTail(sumData);
                }
                n1 = n1->next;
                n2 = n2->next;
            }
            for(int k = length1 ; k< length2 ; k++){        // store &list's not added digits

                int sumData = n2->data + leftover ;
                leftover = 0 ;
                if(sumData>9){
                    int firstDigit = sumData / 10 ;
                    int secondDigit = sumData % 10 ;
                    sum.num->pushTail(secondDigit);
                    leftover = firstDigit ;
                }
                else {
                    sum.num->pushTail(sumData);
                }
                n2 = n2->next ;
            }
            if(leftover != 0){
                sum.num->pushTail(leftover);        // if leftover isn't 0 yet, place it to leftmost digit
            }

        }


        else{
            for (int i = 0; i < length2; i++) {
                int sumData = n2->data  + leftover;
                sumData = sumData + n1->data ;
                leftover = 0 ;
                if(sumData>9){
                    int firstDigit = sumData / 10 ;
                    int secondDigit = sumData % 10 ;
                    sum.num->pushTail(secondDigit);
                    leftover = firstDigit ;
                }
                else {
                    sum.num->pushTail(sumData);
                }
                n1 = n1->next ;
                n2 = n2->next ;
            }
            for(int k = length2 ; k< length1 ; k++){
                int sumData = n1->data + leftover ;
                leftover = 0 ;
                if(sumData>9){
                    int firstDigit = sumData / 10 ;
                    int secondDigit = sumData % 10 ;
                    sum.num->pushTail(secondDigit);
                    leftover = firstDigit ;
                }
                else {
                    sum.num->pushTail(sumData);
                }
                n1 = n1->next ;
            }
        }
        if(leftover != 0){
            sum.num->pushTail(leftover);
        }

        return sum;

    }
    /*
     * I multiply digit by digit from *this and list
     */

    BigInteger BigInteger :: operator*(const BigInteger &list) {
        Node *temp1 = this->num->head ;
        Node *temp2 = list.num->head ;
        BigInteger result("0") ;
        int counter1 = 0 ;
        int counter2 = 0 ;

        while(temp2!=  nullptr){       //this one is the outer loop for checking digits of &list
            int digit = temp2->data ;
            counter1 = 0;
            BigInteger sum("0");
            BigInteger temp("0");
            while(temp1 != nullptr){        //this one is the outer loop for checking digits of &list
                string str = to_string(temp1->data * digit);        //multiply digit by digit *this with list
                BigInteger x(str);
                temp = x ;
                temp1 = temp1->next ;
                for(int k=0 ; k<counter1 ; k++){    //according to decimal position of digit in *this
                    temp = temp * 10 ;              //increase temp value by 10
                }
                counter1++ ;
                sum = sum + temp ;                  //this sum equals the multiplication result of *this with one digit of &list
            }
            temp1 = this->num->head ;
            temp2 = temp2->next ;
            for(int i=0 ; i< counter2 ; i++){       //according to decimal position of digit in &list
                sum = sum * 10 ;                     //increase sum value by 10
            }

            counter2++;                         //position of digit in &list
            result = result + sum;              //it updates the result after every multiplication

        }
        return result ;
    }

    BigInteger BigInteger :: operator*(int i) {
        Node *temp = this->num->head;
        vector<long> vec;
        while(temp != nullptr) {

            long result = temp->data * i ;      //multiply this BigInteger digit by digit with i
            vec.push_back(result) ;             //and store it in a vector of type long
            temp = temp->next;
        }
        BigInteger big("0");

        int size = vec.size();

        for(int i=0 ; i<size ; i++){
            string number = to_string(vec[i]);
            for(int k=0 ; k<i ; k++) {
                number.append("0");     //add 0's to number according to its decimal value
            }
            BigInteger temp(number);
            big = big + temp;           //add result with this temporary value to get the sum
        }
        return big;
    }

    BigInteger::BigInteger(const BigInteger &other) {
        this->num = new LinkedList;
        *num = *(other.num) ;
    }

    BigInteger& BigInteger :: operator=(const BigInteger &list){
        Node *temp = list.num->head ;
        delete this->num ;
        this->num = new LinkedList ;
        while(temp != nullptr){
            this->num->pushTail(temp->data);
            temp = temp->next;
        }
    }

    BigInteger :: ~BigInteger(){
        delete this->num ;
    }

/*
ostream &operator<<(ostream &out, const BigInteger &bigInteger)  {
    string str = "";
    Node *head = bigInteger.num->head;
    while (head) {
        str += to_string(head->data);
        head = head->next;
    }
    reverse(str.begin(), str.end());
    if (str == "")
        str = "0";
    out << str;
    return out;
}
*/